#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <random>
#include "People.h"
#include "Budget.h"
#include "Task.h"

using namespace std;

template <typename T>
T getNumInput(double lowerBound, double upperBound){
    string userInput;
    T num;

    bool valid = false;
    while(!valid){
        try{
            cin >> num;

            if(num < lowerBound || num > upperBound) throw(runtime_error("Out of range"));
            valid = true;
        }catch(const exception& e){
            cerr << "Please enter a valid input. Try again." << endl;
            cin.clear();
            cin.ignore(10000, '\n');
        }
    }

    return num;
}


double generateRandomDouble(double lowerBound, double upperBound);

string getStringInput();

class Restaurant{
    private:
    string name;
    vector<menuItem> menu;
    string cuisineType;
    vector<Customer> customers;
    vector<Customer*> customersWaiting;
    vector<Employee> waiters;
    vector<Employee> cooks;
    Budget budget;
    TaskManager manager;

    // Outputs events at a certain time in minutes
    void outputEvents(int time);

    void printEventCategory(vector<Task*> category, taskType type);
    

    public:
    // Constructor
    Restaurant(string name);
    
    // Hires waiters and cooks
    void hireEmployees();

    void printBudget();

    // Starts simulation of a 5 hour day
    void simulateDay();

    

    // Sets menu
    void setMenu();

    // Initializes customers and adds them to vector
    void initializeCustomers();

    // Name operations
    void setName(string inputName);
    string getName();

    // Returns a free employee from employees vector
    // If no free employees, returns nullptr
    Employee* getFreeEmployee(vector<Employee>& employees);

    // Takes a new order from customer
    void takeOrder(Customer* assignedCustomer, Employee* assignedEmployee);

};
