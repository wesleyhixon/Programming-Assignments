#include <iostream>

/* 
    Name: Pointer Arithmetic Example
    Author: Wesley Hixon
    Date Last Updated: 10/30/25
    Purpose: Demonstrate pointer arithmetic
*/

int main(){
    int arrayCapacity = 10;
    int arrayOfInt[arrayCapacity] = {1, 4, 789, 1111, 312, 556, 123, 234, 222, 124};
    int largest = 0;

    std::cout << "Here is the array:" << std::endl;
    for(int i = 0; i < arrayCapacity; i++){

        // This is the pointer arithmetic
        int current = *(arrayOfInt + i);
        std::cout << current;

        if(current > largest){
            largest = current;
        }
        if(i < arrayCapacity - 1) std::cout << ", ";
    }
    std::cout << std::endl << "This is the largest element of the array: " <<  largest << std::endl;
    return 0;
}