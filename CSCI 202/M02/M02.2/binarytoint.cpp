#include <iostream>
#include <stack>
#include <string>
#include <math.h>

/*
    Name: Convert Binary To Int
    Author: Wesley Hixon
    Date Last Updated: 11/11/2025
    Purpose: Convert a binary number to integer using a stack
*/


int main(){
    std::string binary;
    std::stack<int> binaryStack;
    int convertedInteger = 0;

    std::cout << "Please enter a binary number: ";
    
    bool valid = false;

    // Validate the binary number
    while(!valid){
        std::cin >> binary;

        valid = true;
        for(char num : binary){
            if(num != '1' && num != '0'){
                std::cout << "Try again. Please enter a binary number:";
                valid = false;
                break;
            }
        }
    }

    // Push each digit to the stack
    for(char num : binary){
        int charToInt = num - '0';
        binaryStack.push(charToInt);
    }

    int length = binaryStack.size();
    int power = 0;

    // Convert binary to decimal using powers of 2
    while(power < length){
        int digit = binaryStack.top();
        if(digit == 1){
            convertedInteger += pow(2, power);
        }
        
        binaryStack.pop();
        power++;
    }

    std::cout << "This is your binary number in decimal: " << convertedInteger << std::endl;

    return 0;
}