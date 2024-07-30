#include <iostream>
#include <math.h>
#include "PPlot.cpp"
#include "PPlot.h"
#include "SVGPainter.cpp"
#include "SVGPainter.h"

using namespace std;
using namespace SVGChart;

/*
Name: System of Linear Equations
Author: Wesley Hixon
Due Date: 07/25/2024
Purpose: Make a program which solves a system of linear equations given 2 lines of form Ax+By=C
*/



void solveSystem(double equation1[], double equation2[], double& xsolution, double& ysolution);
void copyEquation(const double equation[], double copiedEquation[]);
void multiplyEquation(double equation[], double factor);
void addEquations(double equation1[], double equation2[], double outputEquation[]);
double validateInput(string prompt);
void drawPlot(double equation1[], double equation2[], double xsolution, double ysolution);

const int xCoefficient = 0;     // Const variables to represent the coefficient array indexes
const int yCoefficient = 1;
const int zCoefficient = 2;


int main(){

    double equation1[3], equation2[3];  // Declaring equation arrays
    double xsolution, ysolution;

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
    solveSystem(equation1, equation2, xsolution, ysolution);

    // Asking if user would like to see a plot
    
    bool valid = false;
    while(!valid){
        char choice;
        cout << "Would you like to see a plot? Please enter y or n: ";
        cin >> choice;
        if(!cin){
            cout << "Please try again." << endl;
            cin.ignore(100000, '\n');
            cin.clear();
        }
        else if(choice == 'y' || choice == 'Y'){
            drawPlot(equation1, equation2, xsolution, ysolution);
            cout << "The chart has been saved to System_Graph.svg" << endl;
            valid = true;
        }
        else if(choice == 'n' || choice == 'N'){
            valid = true;
        }
        else{
            cout << "Please try again." << endl;
            cin.ignore(100000, '\n');
        }
    }
    
    return 0;
}


// This function solves a system of equations given 2 equations in form Ax + By = C
// It uses the elimination method through cancelling one variable to find the other
void solveSystem(double equation1[], double equation2[], double& xsolution, double& ysolution){
    double equation3[3];                                                // This equation is for multiplying while preserving original equations
    double slope1 = equation1[xCoefficient] / equation1[yCoefficient];  // Slopes    
    double slope2 = equation2[xCoefficient] / equation2[yCoefficient];
    double xzRatio1 = equation1[xCoefficient] / equation1[zCoefficient];
    double xzRatio2 = equation2[xCoefficient] / equation2[zCoefficient];
    bool x1Smaller;                                                     // My method requires knowing which x coefficient is smaller
    double factorToMultiply;                                            // This is the multiplication factor to cancel out the x coefficients


    if(slope1 == -(1 / slope2)){
        cout << "The lines are perpendicular" << endl;
        return;                                                         // If the slopes are opposite reciporicals, the lines are perpendicular
    }
    else if(slope1 == slope2){
        if(xzRatio1 == xzRatio2){
            cout << "The lines are the same" << endl;                           // If the ratios between the coefficients are the same, the lines are the same
            xsolution = 0;
            ysolution = 0;
            return;
        }
        else{
        cout << "The lines are parallel" << endl;                       // If the slopes are the same, the lines are parallel
        xsolution = 0;
        ysolution = 0;
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

    ysolution = equation3[zCoefficient] / equation3[yCoefficient];              // Solving for Y solution

    copyEquation(equation1, equation3);                                         // Copying equation 1 to solve for X

    equation3[yCoefficient] *= ysolution;                                       // Multiplying Y coefficient by Y solution
    equation3[zCoefficient] -= equation3[yCoefficient];                         // Subtracting Y coefficient to leave X on its own

    xsolution = equation3[zCoefficient] / equation3[xCoefficient];              // Dividing Z coefficient by X coefficient to get X solution

    cout << "The lines intersect at (" << xsolution << ", " << ysolution << ")" << endl;// Outputting solution

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


void drawPlot(double equation1[], double equation2[], double xsolution, double ysolution){
    double tempEquation[3];
    PPlot myPlot;

    // Data for equation 1
    PlotData *xdata1 = new PlotData ();
    PlotData *ydata1 = new PlotData ();

    // Data for equation 2
    PlotData *xdata2 = new PlotData ();
    PlotData *ydata2 = new PlotData ();

    // Making sure the intersection point fits in the graph view
    double leftbound, rightbound;
    leftbound = xsolution - 25;
    rightbound = xsolution + 25;

    // Creating data from leftbound to rightbound
    for(int i = leftbound; i < rightbound; i++){
        // Creating data for equation 1
        copyEquation(equation1, tempEquation);
        xdata1->push_back(i);                                       // Storing x value

        tempEquation[xCoefficient] *= i;                            // Plugging in X variable

        tempEquation[zCoefficient] -= tempEquation[xCoefficient];   // Subtracting X
        tempEquation[xCoefficient] = 0;                             
        tempEquation[zCoefficient] /= tempEquation[yCoefficient];   // Dividing Z by Y coefficient to get Y by itself
        ydata1->push_back(tempEquation[zCoefficient]);              // Storing final Y value

        // Creating data for equation 2
        copyEquation(equation2, tempEquation);
        xdata2->push_back(i);

        tempEquation[xCoefficient] *= i;

        tempEquation[zCoefficient] -= tempEquation[xCoefficient];
        tempEquation[xCoefficient] = 0;
        tempEquation[zCoefficient] /= tempEquation[yCoefficient];
        ydata2->push_back(tempEquation[zCoefficient]);
    }


    // Creating legend for equation 1
    LegendData *legend1 = new LegendData();
    legend1->mName = "Equation 1";
    legend1->mColor = PColor(3, 3, 252);

    // Creating legend for equation 2
    LegendData *legend2 = new LegendData();
    legend2->mName = "Equation 2";
    legend2->mColor = PColor(252, 3, 3);

    myPlot.mPlotDataContainer.AddXYPlot(xdata1, ydata1, legend1);
    myPlot.mPlotDataContainer.AddXYPlot(xdata2, ydata2, legend2);
    
    SVGPainter painter(800, 600);
    
    myPlot.Draw(painter);
    painter.writeFile("System_Graph.svg");
}