/* Program name: Dividing Winnings
* Author: Wesley Hixon
* Date last updated: 6/6/2024
* Purpose: Divides lottery winnings given the number of winners and amount of money
*/
#include <iostream>

using namespace std;

int main()
{
    // Declaring variables
    int jackpot, num_winners;

    // Getting jackpot amount and number of winners
    cout << "Enter the jackpot amount: ";
    cin >> jackpot;

    cout << "Enter the number of winners: ";
    cin >> num_winners;

    // Calculating the winning amount for first place and other winners
    int other_winners_amount = jackpot / (num_winners + 1);
    int first_winner_amount = other_winners_amount * 2;

    // Printing the winning amount
    cout << "The first winner gets: $" << first_winner_amount << "\n";
    cout << "All the other winners get: $" << other_winners_amount << "\n";
}