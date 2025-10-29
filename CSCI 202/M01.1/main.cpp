#include <iostream>
#include <string>
#include <sstream>
#include <exception>
#include <bits/stdc++.h>
#include <vector>

class romanType{
    private:
        std::string numeral = "";
        int decimal = 0;
        std::unordered_map<char, int> numeralValues = {
            {'M', 1000},
            {'D', 500},
            {'C', 100},
            {'L', 50},
            {'X', 10},
            {'V', 5},
            {'I', 1}
        };
    public:
        romanType(std::string numeral){
            try{
                decimal = numeralToDecimal(numeral);
            }
            catch(std::exception &e){
                std::cout << e.what() << std::endl;
            }
        }

        int numeralToDecimal(std::string numeral){
            int decimal = 0;
            
            const std::string validRomanNumerals = "MDCLXVI";
            const std::vector<std::string> validSubtractionPairs = {"IV", "IX", "XL", "XC", "CD", "CM"};
            

            // Make sure all characters are roman numerals
            for(int i = 0; i < numeral.size(); i++){
                if(validRomanNumerals.find(numeral[i]) == std::string::npos) 
                    throw std::runtime_error("Invalid character in roman numeral");
            }

            int repetitionCounter = 1;

            // Check that the order is correct and convert to decimal
            for(int i = 0; i < numeral.size(); i++){


                char currentNumeral = numeral[i];
                int currentNumeralValue = numeralValues[currentNumeral];

                int lastNumeralIndex = numeral.size() - 1;
                if(i == lastNumeralIndex){
                    decimal += currentNumeralValue;
                    continue;
                }

                char nextNumeral = numeral[i + 1];
                int nextNumeralValue = numeralValues[nextNumeral];
                

                // In case of subtraction
                if(currentNumeralValue < nextNumeralValue){
                    if(repetitionCounter > 1) throw std::runtime_error("Cannot subtract more than one numeral");

                    // Check if the numeral pair is a valid subtractive pair
                    std::string numeralPair(1, currentNumeral);
                    numeralPair += nextNumeral;


                    bool found = false;
                    for(auto it = validSubtractionPairs.begin(); it != validSubtractionPairs.end(); it++){
                        if(numeralPair == *it) found = true;
                    }

                    if(!found) throw std::runtime_error("Invalid subtractive pair");

                    decimal += (nextNumeralValue - currentNumeralValue);
                    
                    // Adds two rather than one to i to skip the next character in the subtractive pair
                    i++;
                }
                else{
                    decimal += currentNumeralValue;
                }

                if(currentNumeral == nextNumeral){
                    repetitionCounter++;
                    if(currentNumeral == 'V') throw std::runtime_error("Cannot repeat V");
                    if(currentNumeral == 'L') throw std::runtime_error("Cannot repeat L");
                    if(currentNumeral == 'D') throw std::runtime_error("Cannot repeat D");
                    if(repetitionCounter > 3) throw std::runtime_error("Cannot repeat a numeral more than 3 times");
                }                
                else{
                    repetitionCounter = 1;
                }
            }
            return decimal;
        }
        void validateNumeral(std::string numeral){
            
        }
        void printNumeral(){
            if(numeral == ""){
                std::cout << "No numeral stored." << std::endl;
            }
            else{
                std::cout << numeral << std::endl;
            }
        }

        void printDecimal(){
            if(decimal == 0){
                std::cout << "No decimal number stored." << std::endl;
            }
            else{
                std:: cout << decimal << std::endl;
            }
        }
};

int main(){
    std::string numeral;

    std::cout << "Please enter a roman numeral: ";
    std::cin >> numeral;
    romanType number(numeral);

    std::cout << "Your numeral in decimal: ";
    number.printDecimal();
    return 0;
}