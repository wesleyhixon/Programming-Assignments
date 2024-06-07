/* Program Name: Binary to Decimal Conversion
*  Author: Wesley Hixon
*  Date last updated: 6/6/2024
*  Purpose: To convert a 5 digit binary number to a decimal number
*/


#include <iostream>
#include <string>

using namespace std;

int main()
{
    // Declaring variables
    int digit1, digit2, digit3, digit4, digit5;
    string binary_str;
    int decimal_num;

    // Prompting the user for input of binary digits
    cout << "Enter the 1st binary digit: ";
    cin >> digit1;

    cout << "Enter the 2nd binary digit: ";
    cin >> digit2;

    cout << "Enter the 3rd binary digit: ";
    cin >> digit3;

    cout << "Enter the 4th binary digit: ";
    cin >> digit4;

    cout << "Enter the 5th binary digit: ";
    cin >> digit5;

    // Converting the binary digits to a decimal number
    decimal_num = digit5 + (digit4 * 2) + (digit3 * 4) + (digit2 * 8) + (digit1 * 16);

    // Converting the binary digits to strings so that they can be concatenated
    string str5 = to_string(digit5);
    string str4 = to_string(digit4);
    string str3 = to_string(digit3);
    string str2 = to_string(digit2);
    string str1 = to_string(digit1);

    // Creating the binary string
    binary_str = str1 + str2 + str3 + str4 + str5;

    // Outputting the final binary string and decimal number
    cout << binary_str << " converted to decimal is " << decimal_num;
// Final output:
//   print all of the entered digits  " converted to decimal is " print the calculated number
}