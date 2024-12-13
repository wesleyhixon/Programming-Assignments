#include <iostream>
#include <iomanip>
#include "Budget.h"

using namespace std;

Budget::Budget(double inputCapital): capital(inputCapital) {}
Budget::Budget() {}

string Budget::toString(){
    string budgetString;

    budgetString += "Starting Capital: " + to_string(capital);
    budgetString += "\nRevenue: " + to_string(revenue);
    budgetString += "\nCosts: " + to_string(costs);
    budgetString += "\nProfits: " + to_string(profit);

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