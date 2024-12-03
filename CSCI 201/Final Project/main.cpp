#include <iostream>
#include <vector>
#include <string>
#include <chrono>
#include <ctime>

using namespace std;

vector<string> randomNames = {
    "Olivia", "Liam", "Emma", "Noah", "Ava", "William", "Sophia", "James", "Isabella", 
    "Benjamin", "Mia", "Lucas", "Charlotte", "Henry", "Amelia", "Alexander", "Evelyn", 
    "Michael", "Harper", "Ethan", "Luna", "Daniel", "Ella", "Matthew", "Scarlett", 
    "David", "Victoria", "Joseph", "Chloe", "Samuel", "Grace", "Jackson", "Zoey", 
    "Sebastian", "Lily", "Aiden", "Penelope", "Caleb", "Hannah", "Mason", "Aria", 
    "Luke", "Audrey", "Nathan", "Nora", "Logan", "Riley", "Dylan", "Violet", "Owen"
};


template <typename T>
T getNumInput(int lowerBound, int upperBound){
    T userInput;

    bool valid = false;
    while(!valid){
        cin >> userInput;
        if(!cin || userInput < lowerBound || userInput > upperBound){
            cerr << "Please enter a valid number input. Try again." << endl;
            cin.clear();
            cin.ignore(10000, '\n');
        }

        valid = true;
    }

    return userInput;
}



struct menuItem{
    double itemCost;
    string itemName;
    int timeToMake;
};

enum Role{
    WAITER, COOK
};

class Employee{
    private:
    string name;
    double workingSpeed;
    double wage;
    bool isWorking;
    Role role;

    public:
    string getName(){}
    bool isFree(){return (!isWorking);}
    double getWage(){return wage;}
    double getWorkingSpeed(){return workingSpeed;}
};

class Customer{
    private:
    string name;
    menuItem order;
    bool placedOrder;
    bool receivedOrder;
    double waitTime;

    public:
    Customer(string inputName, menuItem inputOrder): name(inputName), order(inputOrder) {};
    void placeOrder(){}
    bool orderReceived(){}
    bool orderPlaced(){}
    double getWaitTime(){}
    void incrementWaitTime(){}
    void setName(string inputName){name = inputName;}
};

class Restaurant{
    private:
    string name;
    vector<menuItem> menu;
    string cuisineType;
    vector<Customer> customers;
    vector<Employee> waiters;
    vector<Employee> cooks;

    public:
    Restaurant(){}
    
    void hireEmployees(){}
    // Starts simulation of a day
    void startSimulation();
    // Sets menu
    void setMenu(){}
    // Creates 5 new customers with random names and orders
    // Then, adds them to array
    void initializeCustomers(){

        for(int i=0; i < 5; i++){
            srand(time(0));
            int randomNameIndex = rand() % 50;
            string newName = randomNames[randomNameIndex];

            // create new customer with random name and order
            Customer newCustomer(newName, );
            newCustomer.setName(newName);


        }
    }
    void setName(string inputName){name = inputName;}
    string getName(){return name;}

};

void Restaurant::startSimulation(){
    cout << "Beginning simulation" << endl;

}

string getStringInput();
int getIntInput(int lowerBound, int upperBound);

int main(){

    Restaurant myRestaurant;

    cout << "Welcome to the Restaurant Simulator!" << endl;
    cout << "This program will allow you to live out your dreams of owning a restaurant," << endl;
    cout << "without the hard parts!" << endl;

    cout << endl << "First, choose a name for your restaurant." << endl;

    string restaurantName = getStringInput();

    myRestaurant.setName(restaurantName);


    vector<menuItem> menu = createMenu();
    return 0;
}

vector<menuItem> createMenu(){
    vector<menuItem> menu;
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
        newMenuItem.itemCost = itemCost;
        newMenuItem.timeToMake = timeToMake;

        menu.push_back(newMenuItem);
    }

    cout << "Here is your new menu:" << endl;
    for(auto itr = menu.begin(); itr != menu.end(); itr++){
        cout << "Item name: " << itr->itemName << endl;
        cout << "Item cost: " << itr->itemCost << endl;
        cout << "Time to make: " << itr->timeToMake << endl;
    }

    return menu;
}

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
