#include <iostream>
#include <iomanip>
#include <fstream>
#include <istream>
#include <string>
#include <sstream>

using namespace std;

int main(){
    
    cout << "IvyGames Tournament Results:" << endl;
    cout << setw(35) << setfill('-') << "-" << endl;
    cout << setfill(' ');
    cout << "| " << setw(15) << left << "Username" << "| " << setw(15) << "Score" << "|"<< endl; 
    cout << setw(35) << setfill('-') << "-" << endl;
    cout << setfill(' ');

    string fileName = "scores.txt";
    string line;
    int bestScore = 0, secondBestScore = 0, thirdBestScore = 0;
    string goldMedalWinner, silverMedalWinner, bronzeMedalWinner;

    ifstream scoreFile;
    scoreFile.open(fileName);

    while(getline(scoreFile, line)){
        string userName;
        int userScore;
        
        stringstream ss(line);

        ss >> userName >> userScore;

        cout << setfill(' ');
        cout << "| " << setw(15) << left << userName << "| " << setw(15) << userScore << "|"<< endl;
        cout << setw(35) << setfill('-') << "-" << endl;

        if(userScore >= bestScore){
            thirdBestScore = secondBestScore;
            secondBestScore = bestScore;
            bestScore = userScore;
            // remember to add the winners

        }
        else if(userScore < bestScore && userScore >= secondBestScore){
            thirdBestScore = secondBestScore;
            secondBestScore = userScore;
        }
        else if(userScore < secondBestScore && userScore >= thirdBestScore){
            thirdBestScore = userScore;
        }
    }

    cout << "The gold medal winner is";
    return 0;
}