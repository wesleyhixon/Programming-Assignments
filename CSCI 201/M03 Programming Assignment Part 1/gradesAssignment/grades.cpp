#include <iostream>
#include <iomanip>
#include <string>
#include <cctype>
#include <stdexcept>
#include <array>
#include <vector>

/*
Name: Grades Statistics
Author: Wesley Hixon
Date Last Updated: 11/08/2024
Purpose: This program will take input for 16 quiz grades.
Then it will output the highest score, the lowest score, and the average score.
*/

using namespace std;

// Function definitions
void getData(array<int, 16>& grades);
int highScore(const array<int, 16>& grades);
int lowScore(const array<int, 16>& grades);
int averageScore(const array<int, 16>& grades);

int main(){
    // Creating grades array and getting data
    array<int, 16> grades;
    getData(grades);

    // Finding max, min, and average score
    int maxIndex = highScore(grades);
    int minIndex = lowScore(grades);
    int average = averageScore(grades);

    // Outputting all grades
    cout << endl << "Quiz Grades Report:" << endl;

    for(int i = 0; i < 16; i++){
        cout << "\tModule " << i + 1 << ": " << grades[i] << endl;
    }
    
    // Outputting average, low, and high scores
    cout << "Average grade: " << average << endl;
    cout << "Your lowest score was in Module " << minIndex + 1 << " with a " << grades[minIndex] << "." << endl;
    cout << "Your highest score was in Module " << maxIndex + 1 << " with a " << grades[maxIndex] << "." << endl;
    return 0;
}

// Accept quiz scores for 16 weeks and stores in template array
void getData(array<int, 16>& grades){
    int moduleIndex = 0;
    bool valid = false;

    // Iterating through each grade in array using for loop index
    for(moduleIndex; moduleIndex < 16; moduleIndex++){
        cout << "Please enter the quiz grade for Module " << moduleIndex + 1 << ": " << endl;

        // Getting valid grade greater than 0 and storing it in array
        valid = false;
        while(!valid){
            try{
                cin >> grades[moduleIndex];

                if(cin.fail() || grades[moduleIndex] < 0){
                    cin.clear();
                    cin.ignore(10000, '\n');
                    throw(runtime_error("Please enter a valid grade of at least 0."));
                }
                valid = true;
            }catch(const exception& e){
                cerr << endl << e.what() << endl;
            }
        }
    }
    return;
}

// Returns the index of the highest score in grades array
int highScore(const array<int, 16>& grades){
    int max = 0;
    int maxIndex = 0;

    for(int i = 0; i < 16; i++){
        if(grades[i] > max){
            max = grades[i];
            maxIndex = i;
        }
    }

    return maxIndex;
}

// Returns the index of the lowest score in grades array
int lowScore(const array<int, 16>& grades){
    int min = grades[0];
    int minIndex = 0;

    for(int i = 0; i < 16; i++){
        if(grades[i] < min){
            min = grades[i];
            minIndex = i;
        }
    }

    return minIndex;
}


// Finds the average score of all grades
int averageScore(const array<int, 16>& grades){
    int average;
    int sum = 0;

    // Finding sum
    for(int i = 0; i < 16; i++){
        sum += grades[i];
    }

    // Finding average
    average = sum/16;
    return average;
}