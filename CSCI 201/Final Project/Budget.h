#pragma once

#include <iostream>

using namespace std;

class Budget{
    public:
        double profit;
        double revenue;
        double costs;
        double initialCapital = 100;

        Budget(double inputCapital);
        Budget();
        void printBudget();
};