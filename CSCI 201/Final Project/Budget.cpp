#include <iostream>
#include <iomanip>
#include <sstream>
#include "Budget.h"

using namespace std;

Budget::Budget(double inputCapital): capital(inputCapital) {}
Budget::Budget() {}

string Budget::toString(){
    stringstream budgetSS;

    budgetSS << fixed << showpoint << setprecision(2);
    budgetSS << "Starting Capital: " <<  capital;
    budgetSS << "\nRevenue: " << revenue;
    budgetSS << "\nCosts: " << costs;
    budgetSS << "\nProfits: " << profit;
    budgetSS << "\nEnding Capital: " << capital + profit;

    string budgetString = budgetSS.str();
    return budgetString;
}

// Set wages and update costs
void Budget::setEmployeeWages(double inputWages){
    employeeWages = inputWages;
    costs = employeeWages + foodCost;
    profit = revenue - costs;
}

// Set food cost and update costs
void Budget::addFoodCost(double inputCost){
    foodCost += inputCost;
    costs = employeeWages + foodCost;
    profit = revenue - costs;
}

void Budget::addRevenue(double inputRevenue){
    revenue += inputRevenue;
    profit = revenue - costs;
}

ostream& operator<<(ostream& os, Budget budget){
    os << setprecision(2) << budget.toString();
    return os;
}