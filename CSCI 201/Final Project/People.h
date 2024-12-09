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
    Employee(string inputName, double inputSpeed, Role inputRole): name(inputName), workingSpeed(inputSpeed), role(inputRole) {};
    void setName(string inputName);
    string getName();
    bool getBusyStatus();
    void toggleBusyStatus();
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
    bool getOrderPlacedStatus();
    void receiveOrder();
    bool getOrderReceivedStatus();
    double getWaitTime();
    void incrementWaitTime();
    void setName(string inputName);
};

