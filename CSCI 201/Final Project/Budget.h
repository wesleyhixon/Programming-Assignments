#pragma once

#include <iostream>

using namespace std;

class Budget{
    private:
        double profit = 0;
        double revenue = 0;
        double employeeWages = 0;
        double foodCost = 0;
        double costs = 0;
        double capital = 500;

    public:
        Budget(double inputCapital);
        Budget();
        void setEmployeeWages(double inputWages);
        void addFoodCost(double inputCost);
        void addRevenue(double inputRevenue);
        string toString();
        friend ostream& operator<<(ostream& os, Budget budget);
};