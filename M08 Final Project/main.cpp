#include <iostream>
#include <math.h>
#include "PPlot.cpp"
#include "PPlot.h"
#include "SVGPainter.cpp"
#include "SVGPainter.h"
#include <koolplot.h>

using namespace std;
using namespace SVGChart;

/*
Name: System of Linear Equations
Author: Wesley Hixon
Due Date: 07/25/2024
Purpose: Make a program which solves a system of linear equations given 2 lines of form Ax+By=C
*/



void solveSystem(double equation1[], double equation2[]);
void copyEquation(const double equation[], double copiedEquation[]);
void multiplyEquation(double equation[], double factor);
void addEquations(double equation1[], double equation2[], double outputEquation[]);
double validateInput(string prompt);

const int xCoefficient = 0;     // Const variables to represent the coefficient array indexes
const int yCoefficient = 1;
const int zCoefficient = 2;

PPlot myPlot;

int main(){

    double equation1[3], equation2[3];  // Declaring equation arrays
    
    cout << "Welcome to the system of equations solver!" << endl    // Welcoming user to my humble program
    << "This program will solve any system of 2 equations in the form: Ax + By = C" << endl;

    // Getting input for the first equation
    equation1[xCoefficient] = validateInput("Enter A for the first equation: ");
    equation1[yCoefficient] = validateInput("Enter B for the first equation: ");
    equation1[zCoefficient] = validateInput("Enter C for the first equation: ");

    // Getting input for the second equation
    equation2[xCoefficient] = validateInput("Enter A for the second equation: ");
    equation2[yCoefficient] = validateInput("Enter B for the second equation: ");
    equation2[zCoefficient] = validateInput("Enter C for the second equation: ");
    
    // Solving the system
    solveSystem(equation1, equation2);
    
    return 0;
}


// This function solves a system of equations given 2 equations in form Ax + By = C
// It uses the elimination method through cancelling one variable to find the other
void solveSystem(double equation1[], double equation2[]){
    double equation3[3];                                                // This equation is for multiplying while preserving original equations
    double ySolution, xSolution;                                        // Solutions
    double slope1 = equation1[xCoefficient] / equation1[yCoefficient];  // Slopes    
    double slope2 = equation2[xCoefficient] / equation2[yCoefficient];
    bool x1Smaller;                                                     // My method requires knowing which x coefficient is smaller
    double factorToMultiply;                                            // This is the multiplication factor to cancel out the x coefficients


    if(slope1 == -(1 / slope2)){
        cout << "The lines are perpendicular" << endl;
        return;                                                         // If the slopes are opposite reciporicals, the lines are perpendicular
    }
    else if(slope1 == slope2){
        if(equation1[zCoefficient] == equation2[zCoefficient]){
            cout << "The lines are the same";                           // If the equations are the same, the lines are the same
            return;
        }
        else{
        cout << "The lines are parallel" << endl;                       // If the slopes are the same, the lines are parallel
        return;
        }
    }
    
    
    if(equation1[xCoefficient] < equation2[xCoefficient]){                      // Determining which X-Coefficient is smaller
        factorToMultiply = equation2[xCoefficient] / equation1[xCoefficient];   // The factor to multiply is the bigger X divided by the smaller X

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

    if(x1Smaller){                                                              // Adding the new equation to the larger X equation to create a third equation with a cancelled out X
        addEquations(equation2, equation3, equation3);
    }
    else{
        addEquations(equation1, equation3, equation3);
    }

    ySolution = equation3[zCoefficient] / equation3[yCoefficient];              // Solving for Y solution

    copyEquation(equation1, equation3);                                         // Copying equation 1 to solve for X

    equation3[yCoefficient] *= ySolution;                                       // Multiplying Y coefficient by Y solution
    equation3[zCoefficient] -= equation3[yCoefficient];                         // Subtracting Y coefficient to leave X on its own

    xSolution = equation3[zCoefficient] / equation3[xCoefficient];              // Dividing Z coefficient by X coefficient to get X solution

    cout << "The lines intersect at (" << xSolution << ", " << ySolution << ")";// Outputting solution

    return;
}


// This function copies an equation into another
void copyEquation(const double equation[], double copiedEquation[]){
    for(int i=0; i<3; i++){
        copiedEquation[i] = equation[i];
    }
}


// This function multiplies an entire equation by a factor
void multiplyEquation(double equation[], double factor){
    for(int i=0; i<3; i++){
        equation[i] *= factor;
    }
}


// This function adds two equations and outputs it to outputEquation[]
void addEquations(double equation1[], double equation2[], double outputEquation[]){
    for(int i = 0; i < 3; i++){
        outputEquation[i] = equation1[i] + equation2[i];
    }
}


// Function to get valid double input
double validateInput(string prompt){
    double input;
    
    bool valid = false;
    while(!valid){
        cout << prompt;
        cin >> input;
        if(!cin){
            // If user inputs a letter or a symbol
            cout << "Please enter a valid number. Try again." << endl;
            cin.clear();
            cin.ignore(100000, '\n');
        }
        else{
            // If user inputs a valid number
            valid = true;
            return input;
        }
    }
    return input;
}


void drawPlot(){

}