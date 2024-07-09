#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;
/*
Program Name: Custom Cars Continued
Author: Wesley Hixon
Date Last Updated: 07/08/2024
Purpose:
*/


// Declaring my enum with every color
enum carColorType{SUNSET, CHERRY, PHANTOM, TITANIUM, GEAUX, LIGHTNING, FOREST, MIDNIGHT, PASSION, ROOT, STORM, OCEAN, GLACIAL};
string customerNames[10]; // String array containing customer last names
carColorType partColors[10][3]; // enum array containing 3 part colors for every customer 
int customerIndex = 0; // Customer index to keep track of which customer we're on

// Declaring my function prototypes before main()
carColorType getColor(string part);
string printColor(carColorType color);
void addNewOrder();
int menu();
bool continuePrompt();
void quit(int totalCustomers);
void findOrder();

int main(){
    // Prompt for colors for body, top and trim.
    // Then output the colors the user has chosen.
    // Ask if they'd like to continue with their order
    // If yes, output the colors to a .txt file
    char userInput;
    int menuChoice;
    bool continuing = true;

    cout << "Welcome to the car customizer!" << endl; // Welcoming my wonderful user
    while(continuing){
        menuChoice = menu(); // Get menu choice

        switch(menuChoice){
            case 1:
                // Find existing order
                findOrder();
                break;
            case 2:
                // Add new order
                addNewOrder();
                break;
            case 3:
                // Quit
                quit(customerIndex);
                continuing = false;
                break;
        }

        if(continuing && customerIndex == 10){ // 10 is maximum amount of orders
            cout << "You have entered the maximum number of orders, the program will now save all orders and quit." << endl;
            quit(customerIndex);
            break;
        }
        else if(continuing){
            continuing = continuePrompt();
        }
    }
    return 0;
}

void quit(int totalCustomers){
    
    customerIndex = 0;
    cout << "Thank you for using the car customizer. The orders will be saved in files named [customerLastName].txt" << endl;
    for(int i = 0; i <= totalCustomers; i++){
        ofstream outputFile;
        outputFile.open(customerNames[customerIndex] + ".txt");
        
        carColorType topColor = partColors[customerIndex][0];
        carColorType bodyColor = partColors[customerIndex][1];
        carColorType trimColor = partColors[customerIndex][2];

        outputFile << topColor << endl;
        outputFile << bodyColor << endl;
        outputFile << trimColor << endl;

        outputFile.close();
    }
}

void findOrder(){ // This function prompts for a last name and reads the order associated with that name
    string lastName;
    cout << "Enter the customer last name for the order" << endl;
    
    bool valid = false;
    while(!valid){ // Getting valid last name input
        cin >> lastName;
        if(!cin){
            cout << "Please enter a valid input." << endl;
            cin.clear();
            cin.ignore(10000, '\n');
        }
        else{
            valid = true;
        }
    }

    bool found = false;
    int foundCustomerIndex = 0;
    for(int i = 0; i < 10; i++){ // Search the array for the customer's name
        if(customerNames[i] == lastName){
            found = true;
            foundCustomerIndex = i; // If found, store the index of the customer we just found
            break;
        }
    }
    if(found == true){
        carColorType topColor = partColors[foundCustomerIndex][0];
        carColorType bodyColor = partColors[foundCustomerIndex][1];
        carColorType trimColor = partColors[foundCustomerIndex][2];

        cout << "Here is the order for " << customerNames[foundCustomerIndex] << endl;
        cout << "Top color: " << printColor(topColor) << endl;
        cout << "Body color: " << printColor(bodyColor) << endl;
        cout << "Trim color: " << printColor(trimColor) << endl;
    }
    else{
        cout << "The order for " << lastName << " was not found." << endl;
    }
    return;
}

bool continuePrompt(){
    char userInput;
    cout << "Would you like to continue with your order? Type Y or N: " << endl; // Asking if the user would like to continue ordering
    
    bool valid = false;
    while(!valid){
        cin >> userInput;
        if(userInput == 'Y' || userInput == 'y'){
            return true; // If yes, return true
        }
        else if(!cin){ // In case of input failure
            cout << "Please enter Y or N: " << endl;
            cin.clear();
            cin.ignore(10000, '\n');
        }
        else if(userInput == 'N' || userInput == 'n'){ // Otherwise, exit and return false
            valid = true;
            quit(customerIndex);
            return false;
        }
        else{
            cout << "Please enter Y or N: " << endl;
        }
    }
}

int menu(){
    int userInput;
    cout << "Please choose an option from the menu:" << endl // Output menu
    << "1. Read Existing Order" << endl
    << "2. Add New Order" << endl
    << "3. Quit" << endl;

    bool valid = false;
    while(!valid){ // Validate input
        cin >> userInput;
        if(userInput >= 1 && userInput <= 3){ // If input valid, break loop and return input
            valid = true;
        }
        else if(!cin){
            cout << "Please enter a number between 1 and 3." << endl;
            cin.clear();
            cin.ignore(100000, '\n');
        }
        else{
            cout << "Please enter a number between 1 and 3." << endl;
        }
    }
    return userInput;
}


void addNewOrder(){
    carColorType bodyColor, topColor, trimColor;
    string lastName;
    bodyColor = partColors[customerIndex][0];
    topColor = partColors[customerIndex][1];
    trimColor = partColors[customerIndex][2];
    cout << "Enter the customer last name for the order: ";
    
    bool valid = false; // Getting valid user input
    while(!valid){
        cin >> lastName;
        if(!cin){
            cout << "Please enter a valid last name.";
            cin.clear();
            cin.ignore(10000, '\n');
        }
        else {
            customerNames[customerIndex] = lastName;
            valid = true;
        }
    }
    
    bodyColor = getColor("body"); // Getting orders for each car part
    topColor = getColor("top");
    trimColor = getColor("trim");

    partColors[customerIndex][0] = bodyColor;
    partColors[customerIndex][1] = topColor;
    partColors[customerIndex][2] = trimColor;
    
    cout << "You have chosen " << printColor(bodyColor) << " for the body, " // Outputting what the user input
    << printColor(topColor) << " for the top, and " << printColor(trimColor) << " for the trim." << endl;
    
    // Move on to the next customer
    customerIndex += 1;
}


carColorType getColor(string part){
    // This prompts user for the color of a part indicated by parameter
    // It will then use a switch statement to return a carColorType
    
    int userInput;
    cout << "Please choose a color for the " << part << endl; // Outputting Menu
    cout << "1. Sunset Orange" << endl;
    cout << "2. Cherry Bomb" << endl;
    cout << "3. Phantom Black" << endl;
    cout << "4. Titanium Silver" << endl;
    cout << "5. Geaux Gold" << endl;
    cout << "6. Lightning Yellow" << endl;
    cout << "7. Forest Green" << endl;
    cout << "8. Midnight Blue" << endl;
    cout << "9. Passion Purple" << endl;
    cout << "10. Root Beer" << endl;
    cout << "11. Storm Surge" << endl;
    cout << "12. Ocean's Rip" << endl;
    cout << "13. Glacial White" << endl;

    bool valid = false; // Verifying user input
    while(!valid){
        cin >> userInput;
        if(userInput > 0 && userInput <= 13){
            valid = true;
        }
        else if(!cin){
            cin.clear();
            cin.ignore(100000, '\n');
            cout << "Try again. Please enter a number between 1 and 13." << endl;
        }
        else{
            cout << "Try again. Please enter a number between 1 and 13." << endl;
        }
    }
    
    switch(userInput){ // Switch statement converting int to carColorType
        case 1:
            return SUNSET;
            break;
        case 2:
            return CHERRY;
            break;
        case 3:
            return PHANTOM;
            break;
        case 4:
            return TITANIUM;
            break;
        case 5:
            return GEAUX;
            break;
        case 6:
            return LIGHTNING;
            break;
        case 7:
            return FOREST;
            break;
        case 8:
            return MIDNIGHT;
            break;
        case 9:
            return PASSION;
            break;
        case 10:
            return ROOT;
            break;
        case 11:
            return STORM;
            break;
        case 12:
            return OCEAN;
            break;
        case 13:
            return GLACIAL;
            break;
    }
} 


string printColor(carColorType color){
// Switch statement converting carColorType to string
    switch(color){
        case SUNSET:
            return "Sunset Orange";
            break;
        case CHERRY:
            return "Cherry Bomb";
            break;
        case PHANTOM:
            return "Phantom Black";
            break;
        case TITANIUM:
            return "Titanium Silver";
            break;
        case GEAUX:
            return "Geaux Gold";
            break;
        case LIGHTNING:
            return "Lightning Yellow";
            break;
        case FOREST:
            return "Forest Green";
            break;
        case MIDNIGHT:
            return "Midnight Blue";
            break;
        case PASSION:
            return "Passion Purple";
            break;
        case ROOT:
            return "Root Beer";
            break;
        case STORM:
            return "Storm Surge";
            break;
        case OCEAN:
            return "Ocean's Rip";
            break;
        case GLACIAL:
            return "Glacial White";
            break;
}
}