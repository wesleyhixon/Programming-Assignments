#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

// Declaring global scores array

double scores[20][5] = { { 0 } };

// Function prototypes

void getHighScoreIndex(double scores[][5], int numRows, int colToAnalyze, int& highScoreIndex);
void getLowScoreIndex(double scores[][5], int numRows, int colToAnalyze, int& lowScoreIndex);
void getAverageScore(double scores[][5], int numRows, int colToAnalyze, double& average);
void getMedianScore(double scores[][5], int numRows, int colToAnalyze, double& median);
void selectionSort(double scoreColumn[], int numItems);

int main(){
    int numOfStudents;

    ifstream gradesFile;
    gradesFile.open("grades.txt");

    string line;
    for(int studentNum = 0; studentNum < 20; studentNum++ ){ // For each student,
        if(gradesFile.eof()){ // When eof is reached,
            numOfStudents = studentNum; // record the num of students
            break;
        }
        getline(gradesFile, line);
        
        stringstream s(line);
        
        for(int testNum = 0; testNum < 5; testNum++){        // Otherwise, read 5 test scores
            string score;
            s >> score;

            scores[studentNum][testNum] = stod(score);
        }
    }

    
    selectionSort(scores[0], numOfStudents);
    
    return 0;
}

void selectionSort(double scoreColumn[], int numItems){
    double largestScore = 0;
    for(int i = 0; i < numItems; i++){
        if(scoreColumn[i] > largestScore){
            largestScore = scoreColumn[i];
        }
        cout << largestScore << endl;
    }
}