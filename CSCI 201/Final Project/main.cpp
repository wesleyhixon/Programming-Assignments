#include <iostream>
#include <vector>
#include <string>
#include <chrono>
#include <thread>
#include <ctime>
#include "Restaurant.h"

using namespace std;


/*
For next time:
Figure out why task completion is taking so long
Make it pretty
Implement budget if you have time
*/


int main(){
    cout << "Welcome to the Restaurant Simulator!" << endl;
    cout << "This program will allow you to live out your dreams of owning a restaurant - without the hard parts!" << endl;

    cout << endl << " ---Setup--- " << endl;
    cout << endl << "1. Choose a name for your restaurant: ";

    // Get restaurant name
    string restaurantName = getStringInput();

    cout << endl << "Your restaurant is called \"" << restaurantName << "\""<< endl;

    Restaurant myRestaurant(restaurantName);

    // Create menu
    myRestaurant.setMenu();

    // Seed rand number generator
    srand(time(0));
    myRestaurant.hireEmployees();

    this_thread::sleep_for(chrono::seconds(2));

    // Create vector of customers
    myRestaurant.initializeCustomers();

    myRestaurant.printBudget();

    this_thread::sleep_for(chrono::seconds(3));
    
    // Simulate a day
    myRestaurant.simulateDay();

    myRestaurant.printBudget();
    return 0;
}




