#pragma once

#include <iostream>
#include <string>
#include <vector>
#include "People.h"
#include "Budget.h"

using namespace std;

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

string getStringInput();

class Restaurant{
    private:
    string name;
    vector<menuItem> menu;
    string cuisineType;
    vector<Customer> customers;
    vector<Employee> waiters;
    vector<Employee> cooks;
    Budget budget;
    

    public:
    Restaurant(string name);
    
    // Hires waiters and cooks
    void hireEmployees();

    // Starts simulation of a day
    void simulateDay();

    // Sets menu
    void setMenu();

    // Creates 5 new customers with random names and orders
    // Then, adds them to array
    void initializeCustomers();
    void setName(string inputName);
    string getName();
};
