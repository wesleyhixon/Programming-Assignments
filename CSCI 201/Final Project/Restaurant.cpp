#include <iostream>
#include "Restaurant.h"

using namespace std;





string getStringInput(){
    string userInput;
    
    bool valid = false;
    while(!valid){
        cin >> userInput;
        if(!cin){
            cerr << "Please enter a valid input." << endl;
            cin.clear();
            cin.ignore(10000, '\n');
        }
        valid = true;
    }

    return userInput;
}


vector<string> randomNames = {
    "Olivia", "Liam", "Emma", "Noah", "Ava", "William", "Sophia", "James", "Isabella", 
    "Benjamin", "Mia", "Lucas", "Charlotte", "Henry", "Amelia", "Alexander", "Evelyn", 
    "Michael", "Harper", "Ethan", "Luna", "Daniel", "Ella", "Matthew", "Scarlett", 
    "David", "Victoria", "Joseph", "Chloe", "Samuel", "Grace", "Jackson", "Zoey", 
    "Sebastian", "Lily", "Aiden", "Penelope", "Caleb", "Hannah", "Mason", "Aria", 
    "Luke", "Audrey", "Nathan", "Nora", "Logan", "Riley", "Dylan", "Violet", "Owen"
};


Restaurant::Restaurant(string inputName): name(inputName){};

// Hires waiters and cooks
void Restaurant::hireEmployees(){
    
    // Calculate number of employees from initial capital and wages
    int employeeWage = 10;
    int numEmployees = budget.initialCapital / employeeWage;
    int maxCooks = numEmployees - 1;
    
    // Get number of cooks
    cout << "You have the budget to hire" << numEmployees << " employees." << endl;
    cout << "How many cooks would you like to hire? (Max " << maxCooks << ")" << endl;

    int numCooks = getNumInput<int>(1, maxCooks);
    
    int maxWaiters = numEmployees - numCooks;

    // Get number of waiters
    cout << "How many servers would you like to hire? (Maximum " + to_string(maxWaiters) + ")" << endl;
    int numServers = getNumInput<int>(1, maxWaiters);

    cout << "Generating Employees. . ." << endl;
    // Generate cooks
    for(int i = 0; i < numCooks; i++){
        srand(time(0));

        int randomNameIndex = rand() % 50;
        string newName = randomNames[randomNameIndex];

        int randomSpeed = rand() % 10;

        Employee newCook(newName, randomSpeed, COOK);

        cooks.push_back(newCook);
    }

    // Generate waiters
    for(int i = 0; i < numServers; i++){
        int randomNameIndex = rand() % 50;
        string newName = randomNames[randomNameIndex];

        int randomSpeed = rand() % 10;

        Employee newWaiter(newName, randomSpeed, WAITER);

        waiters.push_back(newWaiter);
    }

};


// Creates 5 new customers with random names and orders
// Then, adds them to array
void Restaurant::initializeCustomers(){
    for(int i = 0; i < 5; i++){
        srand(time(0));
        int randomNameIndex = rand() % 50;
        string newName = randomNames[randomNameIndex];

        int randomMenuItemIndex = rand() % menu.size();
        menuItem randomMenuItem = menu[randomMenuItemIndex];

        // create new customer with random name and order
        Customer newCustomer(newName, randomMenuItem);

        customers.push_back(newCustomer);

    }
}
void Restaurant::setName(string inputName){name = inputName;}
string Restaurant::getName(){return name;}


// Simulates day
// Day is 8 hours long
// Simulation happens in 15 minute increments
// 4 increments per day = 32 units of time

void Restaurant::simulateDay(){
    cout << "Beginning simulation" << endl;

    int timeUnit = 0;

    // Events that can happen:
    // Customer walks up to counter
    while(timeUnit < 32){

    }
}

void Restaurant::setMenu(){
    cout << endl << "Now, create 3 - 5 menu items for your menu." << endl;

    cout << "How many items would you like to create? Enter a number between 3 and 5: ";

    int numMenuItems = getNumInput<int>(3,5);


    for(int i = 0; i < numMenuItems; i++){
        cout << "Enter a name for menu item number " << i + 1 << ":";
        string itemName = getStringInput();

        cout << "Enter a price for this item between 5 and 20 dollars: ";
        double itemCost = getNumInput<double>(5, 20);

        cout << "Enter a number between 1 and 10 which represents how long it takes to make this item: ";
        int timeToMake = getNumInput<int>(1,10);

        menuItem newMenuItem;
        newMenuItem.itemName = itemName;
        newMenuItem.itemPrice = itemCost;
        newMenuItem.timeToMake = timeToMake;

        // Adds menu item to menu
        menu.push_back(newMenuItem);
    }

    cout << "Here is your new menu:" << endl;
    for(auto itr = menu.begin(); itr != menu.end(); itr++){
        cout << "Item name: " << itr->itemName << endl;
        cout << "Item cost: " << itr->itemPrice << endl;
        cout << "Time to make: " << itr->timeToMake << endl;
    }
}