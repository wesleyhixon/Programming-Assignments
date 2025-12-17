#include <iostream>
#include <string>
#include <fstream>
#include <unordered_set>
#include <vector>
#include <exception>
#include <algorithm>
#include <unordered_map>
#include <fmt/core.h>
#include <fmt/base.h>
#include <fmt/color.h>
#include <stdlib.h>


class wordleType {

    // Use a vector for efficiently choosing a random answer
    std::vector<std::string> potentialAnswers;

    // Use an unordered_set (hash table) to store word bank so we can check user guesses efficiently
    std::unordered_set<std::string> wordBank;

    std::string answer;

    public:
        void initializeSet(std::string filename, std::unordered_set<std::string> &set){
            std::ifstream file;

            file.open(filename);

            if(!file.is_open()){
                std::runtime_error e("Error opening " + filename);
                throw e;
            }

            std::string word;

            while(getline(file, word)){
                set.insert(word);
            }
        }

        void initializeVector(std::string filename, std::vector<std::string> &vec){
            std::ifstream file;

            file.open(filename);

            if(!file.is_open()){
                std::runtime_error e("Error opening " + filename);
                throw e;
            }

            std::string word;

            while(getline(file, word)){
                vec.push_back(word);
            }
        }

        void chooseAnswer(){
            srand(time(nullptr));

            int randIndex = rand() % potentialAnswers.size();
            answer = potentialAnswers[randIndex];
        }

        void initialize(){
            initializeVector("answers.csv", potentialAnswers);
            initializeSet("guesses.csv", wordBank);
            chooseAnswer();
        }

        void outputHint(std::string guess){
            std::vector<fmt::color> colors(5, fmt::color::gray);
            std::unordered_map<char, int> freq;
            
            if(guess == answer){
                fmt::print(fmt::fg(fmt::color::green), "{}\n", guess);
                return;
            }

            for(char c : answer){
                freq[c]++;
            }

            // Color the greens
            for(int i = 0; i < 5; i++){
                if(guess[i] == answer[i]){
                    char c = guess[i];
                    freq[c]--;

                    colors[i] = fmt::color::green;
                }
            }   

            // Color the yellows
            for(int i = 0; i < 5; i++){
                char c = guess[i];

                if(freq[c] > 0){
                    colors[i] = fmt::color::yellow;
                    freq[c]--;
                }
            }

            // Output the hint
            for(int i = 0; i < 5; i++){
                fmt::print(fg(colors[i]), "{}", guess[i]);
            }
            fmt::print("\n");
        }

        std::string getGuess(){
            std::string guess;
            bool valid = false;
            while(!valid){
                std::getline(std::cin, guess);

                std::transform(guess.begin(), guess.end(), guess.begin(), ::tolower);

                if(guess == "answer"){
                    fmt::print("{}\n", answer);
                    continue;
                }

                if(guess.length() != 5){
                    fmt::print("That was not a valid word. Try again.\n");
                    continue;
                }

                if(wordBank.find(guess) == wordBank.end()){
                    fmt::print("That was not a valid word. Try again.\n");
                }
                else{
                    valid = true;
                }
            }

            return guess;
        }

        void play(){
            fmt::print("Welcome to Wordle!\n");
            fmt::print("Please enter a 5 letter word\n");

            int numGuesses = 1;
            while(numGuesses <= 6){
                std::string guess = getGuess();
              
                
                numGuesses++;

                outputHint(guess);

                if(guess == answer){
                    break;
                }
            }
        }
};
