#include "People.h"
#include <iostream>
#include <string>

using namespace std;

// Customer Constructor
Customer::Customer(string inputName, menuItem inputOrder): name(inputName), order(inputOrder) {};

// Name Operations
void Customer::setName(string inputName){name = inputName;}
string Customer::getName(){return name;}

// Being served operations
void Customer::setBeingServed(){isBeingServed = true;}
bool Customer::getBeingServedStatus(){return isBeingServed;}

// Increments time waiting by 5 minutes
int Customer::getWaitTime(){return waitTime;}
void Customer::incrementWaitTime(){waitTime += 5;}

// Placing orders
bool Customer::getOrderPlacedStatus(){return placedOrder;}
void Customer::placeOrder(){placedOrder = true;}

// Receiving order
bool Customer::getOrderReceivedStatus(){return receivedOrder;}
void Customer::receiveOrder(){receivedOrder = true;}

// Getting menu order
menuItem Customer::getOrder(){return order;}


// Employee Constructor
Employee::Employee(string inputName, double inputSpeed, Role inputRole): name(inputName), workingSpeed(inputSpeed), role(inputRole) {};

// Name operations
void Employee::setName(string inputName){name = inputName;}
string Employee::getName(){return name;}

// Busy status operations
bool Employee::getBusyStatus(){return (isWorking);}
void Employee::toggleBusyStatus(){isWorking = !isWorking;}

// Gets wage
double Employee::getWage(){return wage;}

// Gets speed
double Employee::getWorkingSpeed(){return workingSpeed;}
