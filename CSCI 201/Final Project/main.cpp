#include <iostream>
#include <vector>
#include <string>
#include <chrono>
#include <ctime>
#include "Restaurant.h"

using namespace std;


int main(){

    cout << "Welcome to the Restaurant Simulator!" << endl;
    cout << "This program will allow you to live out your dreams of owning a restaurant," << endl;
    cout << "without the hard parts!" << endl;

    cout << endl << "First, choose a name for your restaurant." << endl;

    // Get restaurant name
    string restaurantName = getStringInput();
    Restaurant myRestaurant(restaurantName);

    // Create menu
    myRestaurant.setMenu();
    
    // Create vector of customers
    myRestaurant.initializeCustomers();



    return 0;
}




