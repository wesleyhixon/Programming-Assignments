#pragma once

#include <iostream>

using namespace std;

class Budget{
    private:
        double profit;
        double revenue;
        double employeeWages;
        double foodCost;
        double costs;
        double capital = 750;

    public:
        Budget(double inputCapital);
        Budget();
        void setEmployeeWages(double inputWages);
        void addFoodCost(double inputCost);
        void addRevenue(double inputRevenue);
        string toString();
        friend ostream& operator<<(ostream& os, Budget budget);
};