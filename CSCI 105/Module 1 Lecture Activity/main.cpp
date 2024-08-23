#include <iostream>
#include <set>
#include <string>

using namespace std;

/*
Name: Set Operations
Author: Wesley Hixon
Date of Last Revision: 8/23/2024
Purpose: Given 2 user inputted integer sets, perform basic set operations such as:
intersection, union, difference, and symmetrical difference
*/



// Function definitions
set<int> setIntersection(const set<int>& setA, const set<int>& setB);
set<int> setUnion(const set<int>& setA, const set<int>& setB);
set<int> setDifference(const set<int>& setA, const set<int>& setB);
set<int> setSymmetricalDifference(const set<int>& setA, const set<int>& setB);
set<int> getIntSet(string setName);
bool stringIsInt(string str);
void printSet(const set<int>& inputSet);


int main(){
    // Outputting program's purpose
    cout << "This program will take input for two sets. " << endl 
    << "Then you can perform various operations on these sets, such as:" << endl 
    << "Intersection," << endl
    << "Union," << endl
    << "Difference," << endl
    << "and Symmetric Difference." << endl << endl;

    set<int> setA = getIntSet("setA");                      // Getting the two sets
    set<int> setB = getIntSet("setB");

    cout << "Here is setA: ";                               // Outputting the two sets
    printSet(setA);
    cout << endl;

    cout << "Here is setB: ";
    printSet(setB);
    cout << endl;
    
    set<int> intersection = setIntersection(setA, setB);    // Getting intersection
    
    cout << "Here is the intersection of setA and setB: ";  // Printing itersection
    printSet(intersection);
    cout << endl;


    set<int> unionSet = setUnion(setA, setB);               // Getting union
    
    cout << "Here is the union of setA and setB: ";         // Printing union
    printSet(unionSet);
    cout << endl;


    set<int> differenceAB = setDifference(setA, setB);      // Getting difference

    cout << "Here is the difference of setA and setB: ";    // Printing difference
    printSet(differenceAB);
    cout << endl;

    set<int> differenceBA = setDifference(setB, setA);      // Getting difference the other way
    
    cout << "Here is the difference of setB and setA: ";    // Printing difference
    printSet(differenceBA);
    cout << endl;

    set<int> symmetricalDifference = setSymmetricalDifference(setA, setB);  // Getting symmetrical difference
    
    cout << "Here is the symmetrical difference of setA and setB: ";        // Printing symmetrical difference
    printSet(symmetricalDifference);
    cout << endl;

    return 0;
}

set<int> setIntersection(const set<int>& setA, const set<int>& setB){
    set<int> intersection;
    set<int>::iterator itr;
    

    for(itr = setA.begin(); itr != setA.end(); itr++){      // Iterate through setA
        
        if(setB.find(*itr) != setB.end()){      // If the element is in common with setA and setB,
            intersection.insert(*itr);          // Add it to the intersection set
        }

    }
    return intersection;
}

set<int> setUnion(const set<int>& setA, const set<int>& setB){
    set<int> unionSet;
    set<int>::iterator itr;

    // Inserting everything from setA
    for(itr = setA.begin(); itr != setA.end(); itr++){
        unionSet.insert(*itr);
    }

    // Inserting everything from setB
    for(itr = setB.begin(); itr != setB.end(); itr++){
        unionSet.insert(*itr);
    }

    return unionSet;
}

set<int> setDifference(const set<int>& setA, const set<int>& setB){
    set<int> difference;
    set<int>::iterator itr;

    for(itr = setA.begin(); itr != setA.end(); itr++){  // Iterate through setA
        if(setB.find(*itr) == setB.end()){              // If the item isn't found in setB,
            difference.insert(*itr);                    // Add it to the difference set
        }
    }

    return difference;
}

set<int> setSymmetricalDifference(const set<int>& setA, const set<int>& setB){
    set<int> symmetricalDifference;
    set<int> setC, setD;    // For storing output of setDifference

    setC = setDifference(setA, setB);   // Getting difference between sets both ways
    setD = setDifference(setB, setA);

    symmetricalDifference = setUnion(setC, setD);   // Combining sets

    return symmetricalDifference;
}

set<int> getIntSet(string setName){
    bool gettingSet = true;
    string userInput;
    set<int> intSet;

    while(gettingSet){
        cout << "Please enter an integer for " << setName << ". Once you're finished, enter 'done'." << endl;
        cin >> userInput;                   // Getting input
        
        if(userInput == "done"){
            gettingSet = false;             // If user inputted "done", break loop
        }
        else if(stringIsInt(userInput)){    // Check if user inputted an int
            int userInt = stoi(userInput);  // If input was an integer, convert string to int
            intSet.insert(userInt);         // Then, insert int
        }
        else{
            cout << "Try again." << endl;   // If user inputted something other than an int or "done"
            cin.ignore(10000, '\n');
        }
    }
    
    cout << endl << "Here's the set you entered: ";

    printSet(intSet);                       // Outputting the set

    cout << endl << endl;

    return intSet;
}


// Checks if a string is an integer
bool stringIsInt(string str){
    for(int i = 0; i < str.size(); i++){    // Iterate through each string element
        if(!isdigit(str[i])){               // If the element isn't a digit
            return false;                   // Return false
        }
    }
    return true;                            // Otherwise, this string is an int
}


// Easy function to print a set with a clean look
void printSet(const set<int>& inputSet){
    cout << "{";

    // Initializing iterator and counter variables
    set<int>::iterator itr;
    int counter = 0;
    
    for(itr = inputSet.begin(); itr != inputSet.end(); itr++){
        cout << *itr;

        // This is only here to print the commas without a comma on the end
        counter += 1;
        if(counter < inputSet.size()){
            cout << ", ";
        }
    }
    cout << "}";
}