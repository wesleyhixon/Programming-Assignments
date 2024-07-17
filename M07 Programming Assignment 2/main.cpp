#include <iostream>

using namespace std;

/*
Program Name: Resin Molds
Author: Wesley Hixon
Date Last Updated: xx/xx/xx
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
    string fname;
    string lname;
    string address;
};

struct orderType{
    customerType customer;
    moldType products;
    int numProdOrdered;
    double subTotal;
    double totalWeight;
    double shippingCost;
};

void readCatalog(moldType productCatalog[], int numProducts);                     // Reads catalog.txt for the current catalog (it changes from time to time)
void enterOrder(orderType& order, moldType catalog[], int numItemsInCatalog);     // Prompts the user for their order. Can enter up to 10 products
void printProduct(ostream&, moldType mold);                                     // Takes info about a mold and outputs it to ostream provided
void printOrder(ostream&, orderType&);                                          // Takes info about an order and outputs it to ostream provided


int main(){

    return 0;
}