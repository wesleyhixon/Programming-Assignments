#include "People.h"
#include <iostream>
#include <string>

using namespace std;


Customer::Customer(string inputName, menuItem inputOrder): name(inputName), order(inputOrder) {};
void Customer::setName(string inputName){name = inputName;}
void Customer::incrementWaitTime(){waitTime += 1;}


void Employee::setName(string inputName){name = inputName;}
string Employee::getName(){return name;}
bool Employee::isFree(){return (!isWorking);}
double Employee::getWage(){return wage;}
double Employee::getWorkingSpeed(){return workingSpeed;}
