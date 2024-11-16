#include <iostream>
#include <iomanip>
#include <string>
#include <cctype>
#include <stdexcept>
#include <vector>
#include <fstream>
#include <map>
#include <sstream>

using namespace std;

/*
Program Name: State Information
Author: Wesley Hixon
Date Last Updated: 11/10/2024
Purpose: 
Gets state abbreviation, name, flower, and governor from a text file
Then, prompts user for a state abbreviation and reads that state's info
*/


// Struct to store state name, governor, and flower
struct stateType{
    string longName;
    string governor;
    string stateFlower;
};

map<string, stateType> getStates(string filename);

int main(){
    map<string, stateType> states;

    states = getStates("states.txt");

    string userInput;
    cout << "This program will give you information for every US state's state flower and governor." << endl;
    
    bool running = true;
    while(running){
        cout << "Please enter the two-letter abbreviation for a US state. Enter 0 if you would like to exit: ";
        
        // Get user input for state abbreviation
        bool valid = false;
        while(!valid){
            try{
                cin >> userInput;

                // Exits if user inputs 0
                if(userInput == string("0")){
                    valid = true;
                    running = false;
                    cout << endl << "Have a nice day!";
                    break;
                }

                // Converts string to uppercase using itr pointer
                for(auto itr = userInput.begin(); itr != userInput.end(); itr++){
                    if(islower(*itr)){
                        *itr = toupper(*itr);
                    }
                }

                // Checks if user has entered an abbreviation in map
                bool keyNotInMap = states.find(userInput) == states.end();

                if(keyNotInMap) throw(runtime_error("Please enter a two-letter abbreviation for a US state. If you're finished, enter 0."));

                valid = true;

            }catch(const exception& e){
                // Prints error
                cerr << endl << e.what() << endl;
            }
        }

        // Skips printing state if user wants to exit
        if(userInput == string("0")) break;

        cout << "Here is the information for the state you entered:" << endl;
        cout << states[userInput].longName << ":" << endl;
        cout << "Abbreviation: " << userInput << endl;
        cout << "State Flower: " << states[userInput].stateFlower << endl;
        cout << "State Governor: " << states[userInput].governor << endl << endl;

    }
    
    return 0;
}


map<string, stateType> getStates(string filename){
    map<string, stateType> states;

    ifstream inputFile;

    try{
        // Automatically throws exception if there is an error reading file
        inputFile.exceptions(ifstream::badbit | ifstream::failbit);

        inputFile.open(filename);

        // Read every line and add state info to map
        string line;
        while(!inputFile.eof()){

            // Get line of file
            getline(inputFile, line);

            // Make stringstream from line
            stringstream s(line);
            
            // Get abbreviation (Everything before first comma)
            string abbreviation;
            getline(s, abbreviation, ',');


            // Get state name (Everything before second comma)
            string stateName;
            getline(s, stateName, ',');

            // Deleting whitespace
            stateName.erase(0,1);

            // Get state flower (Everything before third comma)
            string stateFlower;
            getline(s, stateFlower, ',');
            
            // Deleting whitespace
            stateFlower.erase(0,1);

            // Get state governor (Everything before newline)
            string stateGovernor;
            getline(s, stateGovernor, '\n');

            // Deleting whitespace
            stateGovernor.erase(0,1);

            // Create state struct
            stateType state;

            state.longName = stateName;
            state.stateFlower = stateFlower;
            state.governor = stateGovernor;
            
            // Create key value pair
            states[abbreviation] = state;
        }        
    }catch(const ifstream::failure& e){
        // If file failed to open, add error message and throw to main()
        if(!inputFile.is_open()){
            string errorMessage = "Error opening file '" + filename +"': " + e.what();
            throw ifstream::failure(errorMessage);
        }
        // If getline failed, skip line and keep going
        else if(inputFile.fail()){
            cerr << "Error reading file contents: " << e.what() << endl;
            cerr << "Skipping line and continuing..." << endl;
            inputFile.clear();
            inputFile.ignore(10000, '\n');
        }
    }
    
    // Close file
    if(inputFile.is_open()){
        inputFile.close();
    }

    return states;
}