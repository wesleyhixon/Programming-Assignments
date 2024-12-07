#pragma once

#include <string>

using namespace std;

enum Role{
    WAITER, COOK
};

class Employee{
    private:
    string name;
    int workingSpeed;    // Speed is int between 1 and 10
    double wage = 10;
    bool isWorking = false;
    Role role;

    public:
    Employee(string inputName, int inputSpeed, Role inputRole): name(inputName), workingSpeed(inputSpeed), role(inputRole) {};
    void setName(string inputName);
    string getName();
    bool isFree();
    double getWage();
    double getWorkingSpeed();
};

struct menuItem{
    double itemPrice;
    string itemName;
    int timeToMake;
};


class Customer{
    private:
    string name;
    menuItem order;
    bool placedOrder;
    bool receivedOrder;
    double waitTime;

    public:
    Customer(string inputName, menuItem inputOrder);
    void placeOrder();
    bool orderReceived();
    bool orderPlaced();
    double getWaitTime();
    void incrementWaitTime();
    void setName(string inputName);
};

