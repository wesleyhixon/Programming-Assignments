#include <iostream>
#include <vector>

/*
*Name: Recursive Array Reversal
*Author: Wesley Hixon
*Date Last Updated: 11/25/2025
*Purpose: Reverses the order of a range of ints in a vector using a recursive function
*/

void reverseArray(int lowIndex, int highIndex, std::vector<int> &arr);
int getIntInput(int low, int high, std::string prompt);

int main(){
    std::vector<int> arr = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    std::cout << "Original Array: ";
    for(int element : arr){
        std::cout << element << ' ';
    }
    std::cout << std::endl;


    int highIndex = getIntInput(1, arr.size() - 1, "Please enter the high index of the range you would like to reverse: ");
    int lowIndex = getIntInput(0, highIndex, "Please enter the low index of the range you would like to reverse: ");  

    reverseArray(lowIndex, highIndex, arr);

    std::cout << "Reversed Array: ";
    for(int element : arr){
        std::cout << element << ' ';
    }

    std::cout << std::endl;
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

void reverseArray(int lowIndex, int highIndex, std::vector<int> &arr){
    if(lowIndex >= highIndex || highIndex > arr.size() || lowIndex < 0){
        return;
    }

    std::swap(arr[lowIndex], arr[highIndex]);
    lowIndex++;
    highIndex--;
    reverseArray(lowIndex, highIndex, arr);
}