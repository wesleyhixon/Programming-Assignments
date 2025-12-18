#include <iostream>
#include <string>
#include <fstream>
#include <unordered_set>
#include <vector>
#include <exception>
#include <algorithm>
#include <map>
#include <unordered_map>
#include <fmt/core.h>
#include <fmt/base.h>
#include <fmt/color.h>



void clrscr();


/* 
//todo add a keyboard
    //- Finish adding displayKeyboard
    //- add keyboard command to handleCommands()
todo add stats functionality
//todo create a main menu
*/


/* 
Name: Wordle
Author: Wesley Hixon
Date Last Updated: 12/17/2025
Purpose: A fun Wordle game you can play in your command line!
*/

enum commandType{
    PLAY, MENU, HELP, EXIT, ANSWER, KEYBOARD
};

std::unordered_map<std::string, commandType> commandStrings{
    {"play", PLAY},
    {"menu", MENU},
    {"help", HELP},
    {"exit", EXIT},
    {"answer", ANSWER},
    {"keyboard", KEYBOARD}
};



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
    bool activeGame = false;
    bool programRunning = true;

    std::map<char, fmt::color> keyboard;
    bool displayKeyboard = false;


    public:

        StateManager(){
            initializeKeyboard();
        }
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
        void clearHistory(){ guessHistory.clear(); }

        void setKeyboard(std::map<char, fmt::color> k){ keyboard = k; }
        std::map<char, fmt::color> getKeyboard(){ return keyboard; }

        void initializeKeyboard(){
            for(char c = 'a'; c <= 'z'; c++){
                keyboard[c] = fmt::color::white;
            }
        }

        bool getDisplayKeyboard(){ return displayKeyboard; }
        void toggleDisplayKeyboard(){ displayKeyboard = !displayKeyboard; }

        void setStatus(std::string status){ statusMessage = status; }
        void clearStatus() { statusMessage = ""; }
        std::string getStatus(){ return statusMessage; }

        void toggleActiveGame(){ activeGame = !activeGame; }
        bool gameIsActive(){ return activeGame; }
        
        bool programIsRunning(){ return programRunning; }
        void toggleRunning(){ programRunning = false;}
};


class HintEvaluator{
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

        std::map<char, fmt::color> updateKeyboard(std::map<char, fmt::color> keyboard, guessResult result){

            // Add gray letters to keyboard
            for(int i = 0; i < 5; i++){
                char c = result.guess[i];
                if(result.colors[i] == fmt::color::gray){
                    keyboard[c] = fmt::color::gray;
                }
            }

            // Add yellow letters
            for(int i = 0; i < 5; i++){
                char c = result.guess[i];
                if(result.colors[i] == fmt::color::yellow && keyboard[c] != fmt::color::green){
                    keyboard[c] = fmt::color::yellow;
                }
            }

            // Add green letters
            for(int i = 0; i < 5; i++){
                char c = result.guess[i];
                if(result.colors[i] == fmt::color::green){
                    keyboard[c] = fmt::color::green;
                }
            }

            return keyboard;
        }
};

struct inputType{
    std::string word;
    bool command = false;
};



class InputManager{
    public:
        inputType getInput(){
            inputType input;
            std::string line;
            
            std::getline(std::cin, line);

            std::transform(line.begin(), line.end(), line.begin(), ::tolower);

            if(commandStrings.find(line) != commandStrings.end()){
                input.command = true;
            }
            
            input.word = line;
            return input;
        }
};


class Renderer{
    public:
        void displayHelp(){
            clrscr();
            fmt::print("List of commands:\n");
            fmt::print(" - play: Begin a game of Wordle\n");
            fmt::print(" - menu: Return to main menu\n");
            fmt::print(" - help: View this menu\n");
            fmt::print(" - exit: Exit the game\n");
            fmt::print("\nPress Enter when finished\n");
        }
        void displayMenu(){
            clrscr();
            fmt::print("Welcome to Wordle!\n");
            fmt::print("Please select a menu option:\n");
            
            
            fmt::print(" - play\n");
            fmt::print(" - keyboard\n");
            fmt::print(" - help\n");
            fmt::print(" - exit\n");

        }
        void displayGameBoard(const std::vector<guessResult> &guessHistory){
            clrscr();

            fmt::print("Please guess a five letter word.\n");

            for(guessResult guessRecord : guessHistory){
                for(int i = 0; i < 5; i++){
                    fmt::print(fg(guessRecord.colors[i]), "{}" ,guessRecord.guess[i]);
                }

                fmt::print("\n");
            }
        }

        void displayKeyboard(std::map<char, fmt::color> keyboard){
            for(char c = 'a'; c <= 'z'; c++){
                fmt::print(fmt::fg(keyboard[c]),"{} ", c);
            }

            fmt::print("\n");
        }
        void displayStatus(std::string statusMessage){
            fmt::print("{}\n", statusMessage);
        }


};



class Wordle{
    WordManager wordManager;
    StateManager stateManager;
    InputManager inputManager;
    HintEvaluator hintEvaluator;
    Renderer renderer;

    public:

        void handleCommand(std::string command){
            // Gets index of command
            commandType commandID = commandStrings[command];

            switch(commandID){
                // "play"
                case PLAY:
                    if(!stateManager.gameIsActive()){
                        stateManager.clearStatus();
                        play();
                    }
                    else{
                        stateManager.setStatus("Invalid input.");
                    }
                    break;
                // "menu"
                case MENU:
                    if(stateManager.gameIsActive()){
                        stateManager.toggleActiveGame();
                        stateManager.clearStatus();
                    }
                    else{
                        stateManager.setStatus("Invalid input.");
                    }
                    break;
                // "help"
                case HELP:
                    stateManager.clearStatus();
                    renderer.displayHelp();
                    inputManager.getInput();
                    break;
                // "exit"
                case EXIT:
                    if(stateManager.gameIsActive()){
                        stateManager.toggleActiveGame();
                    }
                    stateManager.toggleRunning();
                    break;
                // "answer"
                case ANSWER:
                    if(stateManager.gameIsActive()){
                        stateManager.setStatus(stateManager.getAnswer());
                    }
                    else{
                        stateManager.setStatus("Invalid input.");
                    }
                    break;
                // "keyboard"
                case KEYBOARD:
                    stateManager.toggleDisplayKeyboard();
                    break;
                default:
                    stateManager.setStatus("Invalid input.");
            }
        }

        void menu(){
            while(stateManager.programIsRunning()){
                renderer.displayMenu();
                inputType input = inputManager.getInput();

                handleCommand(input.word);
            }
        }

        void play(){
            stateManager.toggleActiveGame();
            stateManager.setAnswer(wordManager.chooseAnswer());
            stateManager.clearHistory();

            stateManager.initializeKeyboard();

            while(stateManager.gameIsActive()){

                renderer.displayGameBoard(stateManager.getHistory());
                if(stateManager.getDisplayKeyboard()){
                    renderer.displayKeyboard(stateManager.getKeyboard());
                }

                renderer.displayStatus(stateManager.getStatus());

                inputType input;

                input = inputManager.getInput();
                

                if(wordManager.isValidGuess(input.word)){
                    stateManager.clearStatus();
                    guessResult result = hintEvaluator.generateHint(input.word, stateManager.getAnswer());

                    stateManager.addGuess(result);
                    stateManager.setKeyboard(hintEvaluator.updateKeyboard(stateManager.getKeyboard(), result));
                }
                else if(input.command){
                    handleCommand(input.word);
                }
                else{
                    stateManager.setStatus("Invalid word. Enter help to see commands.");
                }


                if(input.word == stateManager.getAnswer()){
                    stateManager.toggleActiveGame();

                    stateManager.setStatus("\nYou got it!\nPress Enter to return to main menu.");
                    renderer.displayGameBoard(stateManager.getHistory());
                    renderer.displayStatus(stateManager.getStatus());

                    inputManager.getInput();

                    stateManager.clearStatus();
                }

                if(stateManager.guessesLeft() == 0){
                    stateManager.toggleActiveGame();

                    stateManager.setStatus("\nYou lost. The word was: " + stateManager.getAnswer() + "\nPress Enter to return to main menu.");
                    renderer.displayGameBoard(stateManager.getHistory());
                    renderer.displayStatus(stateManager.getStatus());

                    inputManager.getInput();

                    stateManager.clearStatus();
                }
            }
        }

    Wordle() : wordManager("answers.csv", "guesses.csv"){
        stateManager.setAnswer(wordManager.chooseAnswer());
    }

};

int main(){

    srand(time(nullptr));

    Wordle wordle;

    try{
        wordle.menu();
    }
    catch(const std::exception &e){
        fmt::print(e.what());
        return -1;
    }
    
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
