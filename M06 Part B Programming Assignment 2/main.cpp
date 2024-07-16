#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>

using namespace std;

/*
Program Name: Grade Analysis
Author: Wesley Hixon
Date Last Updated: 7/11/2024
Purpose: Given a .txt with up to 5 test scores for up to 20 students,
Calculate high, low, average, and median scores for each test.
*/

// Function prototypes

void getHighScoreIndex(double scores[][5], int numRows, int colToAnalyze, int& highScoreIndex);
void getLowScoreIndex(double scores[][5], int numRows, int colToAnalyze, int& lowScoreIndex);
void getAverageScore(double scores[][5], int numRows, int colToAnalyze, double& average);
void getMedianScore(double scores[][5], int numRows, int colToAnalyze, double& median);
void selectionSort(double scoreColumn[], int numItems);
void getColumn(double scores[][5], double column[], int columnIndex, int numRows);
void getScores(double scores[20][5], string fileName, int& numRows);

int main(){
    int numRows = 0;
    double scores[20][5] = {  0  };

    getScores(scores, "grades.txt", numRows); // Getting test scores and storing in scores[][]

    
    cout << "Grade Statistics:" << endl;        // Statistics table
    for(int column = 0; column < 5; column++){
        int highScoreIndex, lowScoreIndex;      // Defining variables for statistics
        double average, median;

        getHighScoreIndex(scores, numRows, column, highScoreIndex); // Getting statistics
        getLowScoreIndex(scores, numRows, column, lowScoreIndex);
        getAverageScore(scores, numRows, column, average);
        getMedianScore(scores, numRows, column, median);

        cout << "Test " << column + 1 << endl; // Outputting table values
        cout << fixed << setprecision(2);
        cout << '\t' << "Highest Score: " << scores[highScoreIndex][column] << endl;
        cout << '\t' << "Lowest Score: " << scores[lowScoreIndex][column] << endl;
        cout << '\t' << "Average Score: " << average << endl;
        cout << '\t' << "Median Score: " << median << endl;
        cout << endl << endl;
    }
    return 0;
}

// This function gets the scores from the .txt and stores them in 2d array scores[][]
void getScores(double scores[20][5], string fileName, int& numRows){
    ifstream gradesFile;
    gradesFile.open(fileName);

    string line;
    for(int row = 0; row < 20; row++ ){                         // For each row,
        if(gradesFile.eof()){                                   // If eof reached, break;
            break;
        }

        getline(gradesFile, line);                              // Get the next line,
        
        stringstream s(line);                                   // Create a stringstream to extract data
        
        for(int column = 0; column < 5; column++){              // For each column,
            string score;
            s >> score;                                         // Extract 5 lines

            scores[row][column] = stod(score);                  // And store them in scores[][]
        }
        numRows++;
    }
    gradesFile.close();
}


void selectionSort(double scoreColumn[], int numRows){
    
    double temp;
    bool sorted = false;
    int notSorted = numRows - 1;
    while(notSorted != 0){                      // Repeat this until every score is sorted
        double largestScore = 0;                // Set the largest score to 0
        int largestScoreIndex;                  // And define largestScoreIndex
        for(int i = notSorted; i >= 0; i--){    // Decrement through the items which are not sorted
            if(scoreColumn[i] > largestScore){  // If a new largest score is found,
                largestScore = scoreColumn[i];  // replace largestScore
                largestScoreIndex = i;          // and record the index
        }
    }
    temp = scoreColumn[notSorted];                              // Store the value of the last index which is not sorted temporarily,
    scoreColumn[notSorted] = scoreColumn[largestScoreIndex];    // Move the largest score to the end,
    scoreColumn[largestScoreIndex] = temp;                      // And put the temporary value where the largest score used to be
    notSorted--;                                                // Finally, decrement notSorted
    }
    
}

// This function grabs the column we need from the 2d function
// This is mostly for 
void getColumn(double scores[][5], double column[], int columnIndex, int numRows){
    for(int row = 0; row < numRows; row++){       // For each row,
        column[row] = scores[row][columnIndex];   // Grab the value at the column we are looking for
    }
}


// This function finds the index of the highest score in a column
void getHighScoreIndex(double scores[][5], int numRows, int colToAnalyze, int& highScoreIndex){
    double highestScore = 0;                            // Initializing highestScore for comparison
    
    for(int i = 0; i < numRows; i++){                   
        if(scores[i][colToAnalyze] > highestScore){     // If a new highest score is found,
            highScoreIndex = i;                         // Store the index and record the new highest score
            highestScore = scores[i][colToAnalyze];
        }
    }
}


// This function finds the index of the lowest score in a column
void getLowScoreIndex(double scores[][5], int numRows, int colToAnalyze, int& lowScoreIndex){
    double lowestScore = 100;                           // Highest possible score on a test is 100

    for(int i = 0; i < numRows; i++){
        if(scores[i][colToAnalyze] < lowestScore){      // If a new lowest score is found,
            lowScoreIndex = i;                          // Store the index and record the new lowest score
            lowestScore = scores[i][colToAnalyze];
        }
    }
}


// This function finds the average score in a column
void getAverageScore(double scores[][5], int numRows, int colToAnalyze, double& average){
    double sum = 0;                                     // Sum for later calculation

    for(int i = 0; i < numRows; i++){                   // Calculate the sum of the column
        sum += scores[i][colToAnalyze];
    }
    average = sum / numRows;                            // Calculate the average
}


// This function finds the median score in a column
void getMedianScore(double scores[][5], int numRows, int colToAnalyze, double& median){
    double column[20] = {0};                            // Defining a column for future use
    int middleIndex;                                    // Middle index to get the median score
    getColumn(scores, column, colToAnalyze, numRows);   // Getting a column so that it can be sorted
    selectionSort(column, numRows);                     // Sorting the column
    if(numRows % 2 != 0){
        numRows++;                                      // If there is an odd number of rows, add one
    }

    middleIndex = numRows / 2;                          // Find the middle row
    median = column[middleIndex];                       // Find the median
}