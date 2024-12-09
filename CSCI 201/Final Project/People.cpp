#include "People.h"
#include <iostream>
#include <string>

using namespace std;


Customer::Customer(string inputName, menuItem inputOrder): name(inputName), order(inputOrder) {};
void Customer::setName(string inputName){name = inputName;}
void Customer::incrementWaitTime(){waitTime += 1;}
void Customer::placeOrder(){
    placedOrder = true;
}
void Customer::receiveOrder(){
    receivedOrder = true;
}
bool Customer::getOrderPlacedStatus(){return placedOrder;}
bool Customer::getOrderReceivedStatus(){return receivedOrder;}


void Employee::setName(string inputName){name = inputName;}
string Employee::getName(){return name;}
bool Employee::getBusyStatus(){return (isWorking);}
void Employee::toggleBusyStatus(){isWorking = !isWorking;}
double Employee::getWage(){return wage;}
double Employee::getWorkingSpeed(){return workingSpeed;}
