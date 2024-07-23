#include <iostream>
#include <math.h>
#include <PPlot.cpp>
#include <PPlot.h>
#include <SVGPainter.cpp>
#include <SVGPainter.h>

using namespace std;
using namespace SVGChart;

/*
Name: System of Linear Equations
Author: Wesley Hixon
Due Date: 07/25/2024
Purpose: Make a program which solves a system of linear equations given 2 lines of form Ax+By=C
*/

double equation1[3], equation2[3], smallerXEquation[3];

int solveSystem(double equation1[], double equation2[]);
void copyEquation(const double equation[], double copiedEquation[]);
void multiplyEquation(double equation[], double factor);
void addEquations(double equation1[], double equation2[], double outputEquation[]);
double validateInput(string prompt);

const int xCoefficient = 0;
const int yCoefficient = 1;
const int zCoefficient = 2;

PPlot myPlot;

int main(){
    
    cout << "Welcome to the system of equations solver!" << endl
    << "This program will solve any system of 2 equations in the form: Ax + By = C" << endl;


    equation1[xCoefficient] = validateInput("Enter A for the first equation: ");
    equation1[yCoefficient] = validateInput("Enter B for the first equation: ");
    equation1[zCoefficient] = validateInput("Enter C for the first equation: ");

    equation2[xCoefficient] = validateInput("Enter A for the second equation: ");
    equation2[yCoefficient] = validateInput("Enter B for the second equation: ");
    equation2[zCoefficient] = validateInput("Enter C for the second equation: ");
    solveSystem(equation1, equation2);
    return 0;
}

int solveSystem(double equation1[], double equation2[]){
    double equation3[3];
    double ySolution, xSolution;
    double slope1 = equation1[xCoefficient] / equation1[yCoefficient];
    double slope2 = equation2[xCoefficient] / equation2[yCoefficient];
    bool x1Smaller;
    double factorToMultiply;


    if(slope1 == -(1 / slope2)){
        cout << "The lines are perpendicular" << endl;
        return 1;                                       // If the slopes are opposite reciporicals, the lines are perpendicular
    }
    else if(slope1 == slope2){
        if(equation1[zCoefficient] == equation2[zCoefficient]){
            cout << "The lines are the same";
            return 2;
        }
        else{
        cout << "The lines are parallel" << endl;       // If the slopes are the same, the lines are parallel
        return 2;
        }
    }
    
    
    if(equation1[xCoefficient] < equation2[xCoefficient]){                      // Determining which X-Coefficient is smaller
        factorToMultiply = equation2[xCoefficient] / equation1[xCoefficient];   // That is the coefficient we will multiply and add

        copyEquation(equation1, equation3);
        x1Smaller = true;
    }
    else{
        factorToMultiply = equation1[xCoefficient] / equation2[xCoefficient];

        copyEquation(equation2, equation3);
        x1Smaller = false;
    }

    if(equation1[xCoefficient] > 0 && equation2[xCoefficient] > 0 
    || equation1[xCoefficient] < 0 && equation2[xCoefficient] < 0){
        factorToMultiply *= -1;                                                 // If both x coefficients are positive or negative, invert the factor so the x coefficients cancel out
    }

    multiplyEquation(equation3, factorToMultiply);                              // Multiplying the copied equation to make the xCoefficient inverse

    if(x1Smaller){                                                              // Adding the equations to create a third equation with no X variable
        addEquations(equation2, equation3, equation3);
    }
    else{
        addEquations(equation1, equation3, equation3);
    }

    ySolution = equation3[zCoefficient] / equation3[yCoefficient];              // Solving for Y solution

    copyEquation(equation1, equation3);
    equation3[yCoefficient] = equation3[yCoefficient] * ySolution;              // Solving for X solution
    equation3[zCoefficient] = equation3[zCoefficient] - equation3[yCoefficient];

    xSolution = equation3[zCoefficient] / equation3[xCoefficient];

    cout << "The lines intersect at (" << xSolution << ", " << ySolution << ")";

    return 0;
}

void copyEquation(const double equation[], double copiedEquation[]){
    for(int i=0; i<3; i++){
        copiedEquation[i] = equation[i];
    }
}

void multiplyEquation(double equation[], double factor){
    for(int i=0; i<3; i++){
        equation[i] *= factor;
    }
}

void addEquations(double equation1[], double equation2[], double outputEquation[]){
    for(int i = 0; i < 3; i++){
        outputEquation[i] = equation1[i] + equation2[i];
    }
}

double validateInput(string prompt){
    double input;
    
    bool valid = false;
    while(!valid){
        cout << prompt;
        cin >> input;
        if(!cin){
            cout << "Please enter a valid number. Try again." << endl;
            cin.clear();
            cin.ignore(100000, '\n');
        }
        else{
            return input;
        }
    }
}


void drawPlot(){

}