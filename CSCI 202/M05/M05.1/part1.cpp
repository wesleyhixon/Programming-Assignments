#include <iostream>
#include <string>

/* 
*Name: Recursive Pattern
*Author: Wesley Hixon
*Date Last Updated: 11/25/2025
*Purpose: Generates a pattern using a recursive function
*/

void recursivePattern(int stars);
int getIntInput(int low, int high, std::string prompt);

int main(){
    bool running = true;
    while(running){
        int input;

        input = getIntInput(0, 25, "How many lines would you like in your star pattern? Max 25. Enter 0 to exit: ");
        if(input == 0) break;

        std::cout << std::endl;
        recursivePattern(input);
        std::cout << std::endl;
    }
    return 0;
}


int getIntInput(int low, int high, std::string prompt){
    int input;
    std::cout << prompt << std::endl;

    bool valid = false;
    while(!valid){
        std::cin >> input;
        if(!std::cin){
            std::cin.clear();
            std::cin.ignore(100000, '\n');
            std::cout << "Please try again." << std::endl << prompt;
            continue;
        }
        else if(input > high || input < low){
            std::cout << "Please try again." << std::endl << prompt;
            continue;
        }
        valid = true;
    }

    return input;
}

void recursivePattern(int stars){
    if(stars <= 0) return;

    std::cout << std::string(stars, '*') << std::endl;
    recursivePattern(stars - 1);
    std::cout << std::string(stars, '*') << std::endl;
}