#include <iostream>
#include <iomanip>
#include <string>
#include <cctype>

using namespace std;


/*
Name: Cube Constructor
Author: Wesley Hixon
Date Last Updated: 10/22/2024
Purpose: Build a Cube class with the attributes length, width, height, and color,
as well as methods to set and get the attributes. Then, allow the user to build a
cube through setting the attributes of a new Cube object.
*/

// Cube class, includes length, width, height, and color
class Cube{
    private:
        int length;
        int width;
        int height;
        string color;

    public:
        // Methods to return attributes
        int getLength(){
            return length;
        }
        int getWidth(){
            return width;
        }
        int getHeight(){
            return height;
        }
        string getColor(){
            return color;
        }

        // Methods to set attributes
        void setLength(int inputLength){
            length = inputLength;
        }
        void setWidth(int inputWidth){
            width = inputWidth;
        }
        void setHeight(int inputHeight){
            height = inputHeight;
        }
        void setColor(string inputColor){
            color = inputColor;
        }

        // Method to calculate volume (l*w*h)
        double calculateVolume(){
            double volume = length*width*height;
            return volume;
        }
};

// Function to build a new cube
Cube constructCube();

// Function to output cube characteristics
void readCubeInfo(Cube cube);

void validateInt(int& input);

int main(){
    Cube userCube;

    userCube = constructCube();

    readCubeInfo(userCube);
    return 0;
}


Cube constructCube(){
    // Initializing variables
    int length, width, height;
    string color;
    Cube newCube;

    // Length input
    cout << "Please enter the length of your cube: ";
    validateInt(length);

    // Setting length
    newCube.setLength(length);

    // Width input
    cout << "Please enter the width of your cube: ";
    validateInt(width);


    // Setting width
    newCube.setWidth(width);

    // Height input
    cout << "Please enter the height of your cube: ";
    
    validateInt(height);

    // Setting height
    newCube.setHeight(height);

    // Color input
    cout << "Please enter the color of your cube: ";

    // Validating color input
    bool valid = false;
    bool containsNumber = false;

    while(!valid){
        cin >> color;

        // In case of input failure
        if(!cin){
            cout << "Please try again.";
            cin.clear();
            cin.ignore(10000, '\n');
        }

        else{
            // Checks every character for numbers
            containsNumber = false;
            for(int i = 0; i < color.length(); i++){
                if(!isalpha(color[i])){
                    cout << "Please enter a string without numbers.";
                    containsNumber = true;
                    break;
                }
            }
        }

        if(!containsNumber){
            valid = true;
        }
    }

    // Setting color
    newCube.setColor(color);


    // Returning newCube
    return newCube;
}

void readCubeInfo(Cube cube){

    cout << endl << "This is your cube info" << endl
    << "The length of your cube is " << cube.getLength() << endl
    << "The width of your cube is " << cube.getWidth() << endl
    << "The height of your cube is " << cube.getHeight() << endl
    << "The volume of your cube is " << cube.calculateVolume() << endl
    << "The color of your cube is " << cube.getColor() << endl;
    
    return;
}

void validateInt(int& input){
    while(!(cin >> input) || input < 0){
        cout << "Try again. Please enter a valid integer.";
        cin.clear();
        cin.ignore(10000, '\n');
    }
}