#pragma once

#include <string>

using namespace std;

enum Role{
    WAITER, COOK
};

class Employee{
    private:
    string name;
    double workingSpeed;    // Speed is double between 0.5 and 1.5
    double wage = 10;
    bool isWorking = false;
    Role role;

    public:
    Employee(string inputName, double inputSpeed, Role inputRole);
    void setName(string inputName);
    string getName();
    bool getBusyStatus();
    void toggleBusyStatus();
    double getWage();
    double getWorkingSpeed();
};

struct menuItem{
    string itemName;
    double itemPrice;
    double ingredientCost;
    int timeToMake; // Minutes between 10 and 30
};


class Customer{
    private:
    string name;
    menuItem order;
    bool placedOrder = false;
    bool receivedOrder = false;
    bool isBeingServed = false;
    int waitTime = 0;

    public:
    // Constructor
    Customer(string inputName, menuItem inputOrder);

    // Name operations
    void setName(string inputName);
    string getName();

    // Get menu order
    menuItem getOrder();

    // Being served flag
    void setBeingServed();
    bool getBeingServedStatus();

    // Placing orders
    void placeOrder();
    bool getOrderPlacedStatus();

    // Receiving orders
    void receiveOrder();
    bool getOrderReceivedStatus();

    // Wait time logic
    int getWaitTime();
    void incrementWaitTime();
};

