#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip>

using namespace std;

/*
Program Name: Resin Molds
Author: Wesley Hixon
Date Last Updated: 7/18/2024
Purpose: Generate invoices for resin mold orders
*/

enum sizeType { S, M, L };

struct moldType{
    string shape;
    sizeType size;
    double price;
    double weight;
};

struct customerType{
    string firstName;
    string lastName;
    string streetAddress;
    string cityStateZip;
};

struct orderType{
    customerType customer;
    moldType products[10];
    int numProdOrdered;
    double subTotal;
    double totalWeight;
    double shippingCost;
};

void readCatalog(moldType productCatalog[], int numProducts);                   // Reads catalog.txt for the current catalog (it changes from time to time)
void enterOrder(orderType& order, moldType catalog[], int numProducts);         // Prompts the user for their order. Can enter up to 10 products
void printProduct(ostream& output, moldType mold);                              // Takes info about a mold and outputs it to ostream provided
void printOrder(ostream& output, orderType& order);                             // Takes info about an order and outputs it to ostream provided
string getSizeString(sizeType size);                                            // Converts size enum to string
bool continuePrompt(string prompt);                                             // Asks if user would like to continue given a prompt


int main(){

    const int numProducts = 20;
    orderType orders[99];
    int numOrders = 0;

    moldType productCatalog[numProducts];
    readCatalog(productCatalog, numProducts);                                   // Getting catalog from file

    cout << "Welcome to Judy's Resin Molds!" << endl;                           // Warm greeting

    bool running = true;
    while(running){
        numOrders++;
        int orderIndex = numOrders - 1;                                         // Incrementing numOrders and getting the index of current order
        ofstream outputFile;
        
        enterOrder(orders[orderIndex], productCatalog, numProducts);            // Getting new order
        printOrder(cout, orders[orderIndex]);                                   // Printing new order to console

        string filename = orders[orderIndex].customer.firstName + ".txt";       // Getting filename from customer first name

        outputFile.open(filename);

        printOrder(outputFile, orders[orderIndex]);                             // Outputting order to file

        outputFile.close();
        running = continuePrompt("Would you like to add another order? ");      // Asking if user would like to make another order
    }

    cout << endl << "Have a nice day!";                                         // A polite farewell
    return 0;
}


// This function reads the catalog from the file and puts it in the productCatalog[] array
void readCatalog(moldType productCatalog[], int numProducts){
    string fileName = "catalog.txt";
    ifstream catalogFile;

    catalogFile.open(fileName);                 // Opening file
    for(int i = 0; i < numProducts; i++){       // Iterating through each line
        string line;
        char size;

        getline(catalogFile, line);             // getline() and create a stringstream
        stringstream ss(line);

        ss >> productCatalog[i].shape;          // Get shape
        ss >> size;                             // Get size
        productCatalog[i].size = static_cast<sizeType>(size);   // Static_cast char to sizeType
        ss >> productCatalog[i].price;          // Get price
        ss >> productCatalog[i].weight;         // Get weight
    }
    catalogFile.close();
}

void enterOrder(orderType& order, moldType catalog[], int numProducts){
    cout << "Enter the customer first name: ";                          // Get first name
    cin >> order.customer.firstName;
    
    cout << endl << "Enter the customer last name: ";                   // Get last name
    cin >> order.customer.lastName;

    cout << endl << "Enter the customer street address: ";              // Get address
    cin.ignore();
    getline(cin, order.customer.streetAddress);

    cout << endl << "Enter the customer city, state, and zip code: ";   // Get city state and zip
    getline(cin, order.customer.cityStateZip);

    bool addingProducts = true;
    while(addingProducts && order.numProdOrdered < 10){                 // While items in order < 10
        order.numProdOrdered++;                                         // Increment num of products ordered
        
        cout << "Please choose a product from the list:" << endl;
        
        for(int i = 0; i < numProducts; i++){
            cout << i + 1 << ". ";
            printProduct(cout, catalog[i]);                             // Outputting the catalog
            cout << endl;
        }

        int userChoice;
        
        bool valid = false;                                             // Get user's choice
        while(!valid){
            cin >> userChoice;
            if(!cin || userChoice < 0 || userChoice > numProducts){
                cout << "Invalid input. Please enter a number between 1 and " << numProducts << "." << endl;
                cin.clear();
                cin.ignore();
            }
            else{
                valid = true;
            }
        }

        userChoice--;                                                   // Decrementing userChoice to use for array index
        
        int currentProductIndex = order.numProdOrdered - 1;             // Getting index for current product in order
        order.products[currentProductIndex] = catalog[userChoice];      // Saving user's choice in order.products[]

        moldType& product = order.products[currentProductIndex];        // Making reference for product for readability

        cout << "Item: ";  
        printProduct(cout, product);                                    // Outputting product added
        cout << " added."<< endl;

        order.subTotal += product.price;                                // Adding to subtotal and weight
        order.totalWeight += product.weight;
        
        addingProducts = continuePrompt("Would you like to add another product to this order? ");   // Prompt to continue
    }
    if(order.numProdOrdered == 10){
        cout << "Maximum number of products ordered." << endl;          // 10 products max per order
    }

    order.shippingCost = 0.58 * (order.totalWeight/28.35);              // Calculating shipping cost
}


// This function outputs the information about 1 mold
void printProduct(ostream& output, moldType mold){
    output << fixed << setprecision(2) << mold.shape << " - " << getSizeString(mold.size)
    << " $" << mold.price << " " << mold.weight << "g";
}


// This function outputs the information about 1 order
void printOrder(ostream& output, orderType& order){
    double totalCost;
    totalCost = order.shippingCost + order.subTotal;                    // Calculating total cost

    output << "Customer: " << order.customer.firstName << " " << order.customer.lastName << endl
    << order.customer.streetAddress << endl                             // Outputting customer info
    << order.customer.cityStateZip << endl;

    output << endl << "Products Ordered:" << endl;

    for(int i = 0; i < order.numProdOrdered; i++){
        printProduct(output, order.products[i]);                        // Outputting ordered products info
        output << endl;
    }

    output << endl << fixed << setprecision(2) << "Subtotal: $" << order.subTotal << endl;  // Outputting subtotal,
    output << "Total Weight: " << order.totalWeight << "g" << endl;                         // Weight,
    output << "Shipping Cost: $" << order.shippingCost << endl;                             // Shipping cost,
    output << "Total Cost: $" << totalCost << endl;                                         // and total cost
}


// This function converts the sizeType enum to a string
string getSizeString(sizeType size){
    string sizeString;

    switch(static_cast<char>(size)){
        case 'S':
            sizeString = "Small";
            break;
        case 'M':
            sizeString = "Medium";
            break;
        case 'L':
            sizeString = "Large";
            break;
    }
    return sizeString;
}


// This function prompts for a yes or no input and returns a bool
bool continuePrompt(string prompt){
    char choice;
    bool valid = false;
    
    while(!valid){
        cout << prompt;
        cin >> choice;
        tolower(choice);

        if(!cin){                       // Case of input failure
            cout << "That is not a valid entry. Please enter y or n." << endl;
            cin.clear();
            cin.ignore();
        }
        else if(choice == 'y'){         // y = true
            return true;
        }
        else if(choice == 'n'){         // n = false
            return false;
        }
        else{                           // else, try again.
            cout << "That is not a valid entry. Please enter y or n." << endl;
            cin.ignore();
        }
    }
    return false;                       // This is here so my compiler doesn't yell at me
}