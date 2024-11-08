#include <iostream>
#include <iomanip>
#include <string>
#include <cctype>
#include <stdexcept>
#include <array>
#include <vector>

using namespace std;


int main(){
    int num1 = 100;
    int *ptr;
    ptr = &num1;

    cout << *ptr;
    return 0;
}