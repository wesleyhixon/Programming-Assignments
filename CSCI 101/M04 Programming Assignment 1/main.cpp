#include <iostream>
#include <iomanip>
#include <fstream>
#include <istream>
#include <string>
#include <sstream>

using namespace std;

/*
Program Name: High Score
Author: Wesley Hixon
Date last updated: 6/24/2024
Purpose: To process results from an esports tournament, finding the top 3 scores.
*/



int main(){
    
    // Creating the table header
    cout << "IvyGames Tournament Results:" << endl;
    cout << setw(35) << setfill('-') << "-" << endl;
    cout << setfill(' ');
    cout << "| " << setw(15) << left << "Username" << "| " << setw(15) << "Score" << "|"<< endl; 
    cout << setw(35) << setfill('-') << "-" << endl;
    cout << setfill(' ');

    // Declaring variables
    string fileName = "scores.txt";
    string line;
    int bestScore = 0, secondBestScore = 0, thirdBestScore = 0, averageScore = 0, totalCompetitors = 0, totalScore = 0;
    string goldMedalWinner, silverMedalWinner, bronzeMedalWinner;

    // Opening the file containing the tournament scores
    ifstream scoreFile;
    scoreFile.open(fileName);

    // Looping through each line of the tournament file
    while(getline(scoreFile, line)){
        string userName;
        int userScore;
        
        // Creating a stringstream variable from the line to extract the data
        stringstream ss(line);

        // Extracting data
        ss >> userName >> userScore;

        // Outputting next line in the table
        cout << setfill(' ');
        cout << "| " << setw(15) << left << userName << "| " << setw(15) << userScore << "|"<< endl;
        cout << setw(35) << setfill('-') << "-" << endl;

        // Increment the total num of competitors
        // And add the player's score to the total score
        // This will be useful to calculate the average score at the end
        totalCompetitors++;
        totalScore += userScore;

        if(userScore >= bestScore){
            // If a new best score is found,
            // Displace the previous second best score to 3nd place
            thirdBestScore = secondBestScore;
            
            // and displace the previous best score to 2nd place.
            secondBestScore = bestScore;
            
            // Finally, replace the previous best with the new best.
            bestScore = userScore;
            
            // Do the same for the usernames
            bronzeMedalWinner = silverMedalWinner;
            silverMedalWinner = goldMedalWinner;
            goldMedalWinner = userName;
        }
        else if(userScore < bestScore && userScore >= secondBestScore){
            // If a new second best is found,
            // displace the previous second best score to third
            thirdBestScore = secondBestScore;
            
            // and replace the second best
            secondBestScore = userScore;

            // Do the same for the usernames
            bronzeMedalWinner = silverMedalWinner;
            silverMedalWinner = userName;
        }
        else if(userScore < secondBestScore && userScore >= thirdBestScore){
            // If a new third best score is found, replace it
            thirdBestScore = userScore;

            // Do the same for the username
            bronzeMedalWinner = userName;
        }
    }

    // Calculate the average score
    averageScore = totalScore/totalCompetitors;

    // Output the winners
    cout << "The gold medal winner is " << goldMedalWinner << " with " << bestScore << " points." << endl;
    cout << "The silver medal winner is " << silverMedalWinner << " with " << secondBestScore << " points." << endl;
    cout << "The bronze medal winner is " << bronzeMedalWinner << " with " << thirdBestScore << " points." << endl;
    
    // Output the average score along with the number of competitors
    cout << "The average score was " << averageScore << " over a total of " << totalCompetitors << " competitors." << endl;
    
    // Provide sincere congratulations
    cout << "Congratulations to all the winners! See you at the next tournament.";
    return 0;
}