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


void clrscr();


/* 
todo add a keyboard
todo add stats functionality
todo create a main menu
*/


/* 
Name: Wordle
Author: Wesley Hixon
Date Last Updated: 12/17/2025
Purpose: A fun Wordle game you can play in your command line!
*/

class WordManager{
    private:
        std::vector<std::string> answers;
        std::unordered_set<std::string> guesses;

        void initializeGuesses(std::string filename){
            std::ifstream file;

            file.open(filename);

            if(!file.is_open()){
                std::runtime_error e("Error opening " + filename);
                throw e;
            }

            std::string word;

            while(getline(file, word)){
                guesses.insert(word);
            }
        }
        void initializeAnswers(std::string filename){
            std::ifstream file;

            file.open(filename);

            if(!file.is_open()){
                std::runtime_error e("Error opening " + filename);
                throw e;
            }

            std::string word;

            while(getline(file, word)){
                answers.push_back(word);
            }
        }

    public:

        WordManager(std::string answersFile, std::string guessesFile){
            initializeAnswers(answersFile);
            initializeGuesses(guessesFile);
        }

        bool isValidGuess(const std::string word) const{
            if(guesses.find(word) != guesses.end()) return true;
            else return false;
        }

        std::string chooseAnswer(){
            srand(time(nullptr));

            int randIndex = rand() % answers.size();
            return answers[randIndex];
        }

};


struct guessResult{
    std::string guess;
    std::vector<fmt::color> colors;
    guessResult(std::string g, std::vector<fmt::color> c) : guess(g), colors(c) {}
};


class StateManager{
    int maxGuesses = 6;
    std::vector<guessResult> guessHistory;
    std::string answer;
    std::string statusMessage;

    public:
        void addGuess(guessResult guess){
            guessHistory.push_back(guess);
        }

        void addGuess(std::string guess, std::vector<fmt::color> &colors){
            guessResult result(guess, colors);
            guessHistory.push_back(result);
        }
        
        int numGuesses(){
            return guessHistory.size();
        }

        int guessesLeft(){
            return maxGuesses - guessHistory.size();
        }

        std::string getAnswer() { return answer; }
        void setAnswer(std::string a) { answer = a; }

        std::vector<guessResult> getHistory(){ return guessHistory; }

        void addStatus(std::string status){ statusMessage = status; }
        void clearStatus() { statusMessage = ""; }
        std::string getStatus(){ return statusMessage; }
};


class GuessEvaluator{
    public:
        guessResult generateHint(std::string guess, std::string answer){
            std::vector<fmt::color> colors(5, fmt::color::gray);
            std::unordered_map<char, int> freq;
            
            if(guess == answer){
                colors = std::vector<fmt::color>(5, fmt::color::green);
                return guessResult(guess, colors);
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

                if(freq[c] > 0 && guess[i] != answer[i]){
                    colors[i] = fmt::color::yellow;
                    freq[c]--;
                }
            }
            
            return guessResult(guess, colors);
        }
};

struct inputType{
    std::string word;
    bool command = false;
};

class InputManager{
    public:
        inputType readInput(){
            inputType input;
            std::string line;
            
            std::getline(std::cin, line);

            std::transform(line.begin(), line.end(), line.begin(), ::tolower);

            if(line == "help" || line == "exit" || line == "answer"){
                input.command = true;
                input.word = line;
                return input;
            }
            
            input.word = line;
            return input;
        }
};


class Renderer{
    public:
        void displayMenu();
        void displayGameBoard(const std::vector<guessResult> &guessHistory, std::string statusMessage){
            clrscr();
            for(guessResult guessRecord : guessHistory){
                for(int i = 0; i < 5; i++){
                    fmt::print(fg(guessRecord.colors[i]), "{}" ,guessRecord.guess[i]);
                }

                fmt::print("\n");
            }

            fmt::print("{}\n", statusMessage);
        }
};



class Wordle{
    WordManager wordManager;
    StateManager stateManager;
    InputManager inputManager;
    GuessEvaluator guessEvaluator;
    Renderer renderer;

    public:

        void play(){
            bool running = true;

            while(stateManager.guessesLeft() > 0 && running){
                inputType input;

                input = inputManager.readInput();

                if(input.command){
                    stateManager.clearStatus();
                    if(input.word == "exit"){
                        running = false;
                    }
                    if(input.word == "answer"){
                        fmt::print("{}\n", stateManager.getAnswer());
                    }
                    continue;
                }
                

                if(wordManager.isValidGuess(input.word)){
                    stateManager.clearStatus();
                    guessResult result = guessEvaluator.generateHint(input.word, stateManager.getAnswer());

                    stateManager.addGuess(result);
                    
                }
                else{
                    stateManager.addStatus("Invalid word. Enter help to see commands.");
                }


                renderer.displayGameBoard(stateManager.getHistory(), stateManager.getStatus());

                if(input.word == stateManager.getAnswer()){
                    running = false;
                    fmt::print("\nYou got it!\n");
                }
            }
        }

    Wordle() : wordManager("answers.csv", "guesses.csv"){
        stateManager.setAnswer(wordManager.chooseAnswer());
    }

};

int main(){

    Wordle wordle;

    wordle.play();

    
    return 0;
}

void clrscr(){
    #ifdef _WIN32
        system("cls");
    #endif

    #ifdef __linux__
        system("clear");
    #endif
}
