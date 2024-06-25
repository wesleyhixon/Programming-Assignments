#include <iostream>
#include <math.h>

using namespace std;

/*
Program Name: Binary Number Converter 2.0
Author: Wesley Hixon
Date Last Updated: 06/25/2024
Purpose: Convert a binary number of any length into decimal
*/

int main(){
    int userInput, digitPosition = 0, decimalNum = 0;
    cout << "Welcome to the binary number converter 2.0." << endl; 
    cout << "You will enter a binary number 1 digit at a time starting at the right and the program will convert the number to decimal." << endl;

    
    while(userInput != -1){
        
        bool valid = false; 
        // This loop prompts for input until the input is determined to be valid.
        while(!valid){

            // There are different prompt cases because of 1st, 2nd, 3rd, etc.
            switch(digitPosition){
                case 0:
                    cout << "Enter the 1st binary digit (Enter -1 to complete the conversion): ";
                    break;
                case 1:
                    cout << "Enter the 2nd binary digit (Enter -1 to complete the conversion): ";
                    break;
                case 2:
                    cout << "Enter the 3rd binary digit (Enter -1 to complete the conversion): ";
                    break;
                default:
                    cout << "Enter the " << digitPosition + 1 << "th binary digit (Enter -1 to complete the conversion): ";
                    break;
            }
        
            cin >> userInput;
            cout << endl;
            
            // If input fails, clear input errors and ignore rest of input.
            if(cin.fail()){
                cout << "You have entered something that is not a number. Try again." << endl;
                cin.clear();
                cin.ignore(100000, '\n');
            }
            // If input is valid, break the loop.
            else if(userInput == 1 || userInput == 0 || userInput == -1){
                valid = true;
            }
            // Otherwise, try again.
            else{
                cout << "Binary digit can only be a 1 or 0. Try again." << endl;
            }
        }

        if(userInput == 1){
            // Calculate the decimal value of a binary 1 using 2 raised to the power of the digitPosition
            // And add it to the decimalNum
            decimalNum += pow(2, digitPosition);
        }

        // Then, increment digitPosition
        digitPosition++;
    }

    // Once loop breaks, output final decimal number
    cout << "Your number in decimal is " << decimalNum << endl;

    return 0;
}



    