
#include <iostream>
using namespace std;

/*
    Program Name: Computer Specifications
    Author: Wesley Hixon
    Date Last Updated: 06/18/2024
    Purpose: This program will determine if a user has enough RAM to do certain tasks.
    Prompt the user for the amount of RAM their computer has in GB. Then you will display the list of tasks below that the user might do with the computer.  
    Based on the task chosen, inform the user if the amount of RAM they have is sufficient.
*/

int main(){

    // Initializing variables
    int userSelection, userRAM;
    int androidStudioRAM = 12, vsCodeRAM = 8, gamingRAM = 16, chromeRAM = 8, multipleProgrammingRAM = 20, zoomRAM = 8,
    emailRAM = 6, documentRAM = 6, everythingRAM = 32;

    // Prompting user for amount of RAM
    cout << "Enter the amount of RAM in GB: ";
    cin >> userRAM;

    // Validating input
    if(userRAM < 0){
        cout << "Please enter a valid amount of RAM. Exiting...";
        return 0;
    }
    // This statement only triggers if cin fails
    if(!cin){
        cout << "Please enter an integer. Exiting... ";
        return 0;
    }
    
    // Prompting the user for menu selection
    cout << "Choose the task you want to do on your computer from the following list: \n"
    "1. Android Studio \n"
    "2. Visual Studio Code \n"
    "3. Gaming \n" 
    "4. Web Browsing with Chrome \n"
    "5. Multiple Programming Tasks (both Android Studio and Visual Studio Code) \n"
    "6. Zoom \n"
    "7. Email \n"
    "8. Create and edit documents \n"
    "9. Everything listed above \n";

    cin >> userSelection;

    // Validating input
    if(userSelection < 1 or userSelection > 9){
        cout << "Please select a valid option. Exiting...";
        return 0;
    }
    if(!cin){
        cout << "Please select a valid option. Exiting...";
        return 0;
    }

    // This switch statement handles every menu option
    // Each RAM use case is compared to the amount of RAM the user inputs
    // The user is then told whether they have enough RAM
    switch(userSelection){
        case 1:
        if(userRAM >= androidStudioRAM){
            cout << "Congratulations! You have sufficient RAM for your task.";
        }
        else{
            cout << "Sorry the RAM you have is not sufficient.";
        }
        break;

        case 2:
        if(userRAM >= vsCodeRAM){
            cout << "Congratulations! You have sufficient RAM for your task.";
        }
        else{
            cout << "Sorry the RAM you have is not sufficient.";
        }
        break;

        case 3:
        if(userRAM >= gamingRAM){
            cout << "Congratulations! You have sufficient RAM for your task.";
        }
        else{
            cout << "Sorry the RAM you have is not sufficient.";
        }
        break;

        case 4:
        if(userRAM >= chromeRAM){
            cout << "Congratulations! You have sufficient RAM for your task.";
        }
        else{
            cout << "Sorry the RAM you have is not sufficient.";
        }
        break;

        case 5:
        if(userRAM >= multipleProgrammingRAM){
            cout << "Congratulations! You have sufficient RAM for your task.";
        }
        else{
            cout << "Sorry the RAM you have is not sufficient.";
        }
        break;

        case 6:
        if(userRAM >= zoomRAM){
            cout << "Congratulations! You have sufficient RAM for your task.";
        }
        else{
            cout << "Sorry the RAM you have is not sufficient.";
        }
        break;

        case 7:
        if(userRAM >= emailRAM){
            cout << "Congratulations! You have sufficient RAM for your task.";
        }
        else{
            cout << "Sorry the RAM you have is not sufficient.";
        }
        break;

        case 8:
        if(userRAM >= documentRAM){
            cout << "Congratulations! You have sufficient RAM for your task.";
        }
        else{
            cout << "Sorry the RAM you have is not sufficient.";
        }
        break;

        case 9:
        if(userRAM >= everythingRAM){
            cout << "Congratulations! You have sufficient RAM for your task.";
        }
        else{
            cout << "Sorry the RAM you have is not sufficient.";
        }
        break;
    }
    return 0;
}