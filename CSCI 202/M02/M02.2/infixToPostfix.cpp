#include <iostream>
#include <string>
#include <stack>
#include <map>

/*
    Name: Infix To Postfix
    Author: Wesley Hixon
    Date Last Updated: 11/11/2025
    Purpose: Convert infix expressions to postfix expressions using a stack
*/


class expressionConvertor{
    private:
        std::string infix;
        std::string postfix = "";
        std::map<char, int> operatorPrecedence = {
            {'*', 2},
            {'/', 2},
            {'+', 1},
            {'-', 1}
        };
    public:
        std::string showInfix() const {
            return infix;
        }
        std::string showPostfix() const {
            return postfix;
        }
        void storeInfix(std::string& inputInfix){
            infix = inputInfix;
            postfix = infixToPostfix(infix);
        }

        std::string infixToPostfix(std::string& inputInfix){
            std::string outputPostfix;
            std::stack<char> expStack;

            for(char sym : inputInfix){
                if(sym == '('){
                    expStack.push(sym);
                }
                else if(sym == ')'){

                    while(expStack.top() != '('){
                        outputPostfix += expStack.top();
                        outputPostfix += ' ';
                        
                        expStack.pop();
                    }
                    // pop that last '('
                    expStack.pop();
                }
                else if(operatorPrecedence.find(sym) != operatorPrecedence.end()){
                    
                    while(!expStack.empty() && expStack.top() != '(' && operatorPrecedence[expStack.top()] >= operatorPrecedence[sym]){
                        outputPostfix += expStack.top();
                        outputPostfix += ' ';

                        expStack.pop();
                    }

                    expStack.push(sym);
                }

                else if(sym == ' ') continue;
                else{
                    outputPostfix += sym;
                    outputPostfix += ' ';
                }
            }

            while(!expStack.empty()){
                outputPostfix += expStack.top();
                outputPostfix += ' ';

                expStack.pop();
            }

            return outputPostfix;
        }
};


int main(){
    expressionConvertor obj;
    std::string infx = "A + B - C";

    obj.storeInfix(infx);
    std::cout << "Infix: " << infx << std::endl;
    std::cout << "Postfix: " << obj.showPostfix() << std::endl;

    infx = "(A + B ) * C";
    obj.storeInfix(infx);
    std::cout << "Infix: " << infx << std::endl;
    std::cout << "Postfix: " << obj.showPostfix() << std::endl;

    infx = "(A + B) * (C - D)";
    obj.storeInfix(infx);
    std::cout << "Infix: " << infx << std::endl;
    std::cout << "Postfix: " << obj.showPostfix() << std::endl;

    infx = "A + ((B + C) * (E - F) - G) / (H - I)";
    obj.storeInfix(infx);
    std::cout << "Infix: " << infx << std::endl;
    std::cout << "Postfix: " << obj.showPostfix() << std::endl;

    infx = "A + B * (C + D) - E / F * G + H";
    obj.storeInfix(infx);
    std::cout << "Infix: " << infx << std::endl;
    std::cout << "Postfix: " << obj.showPostfix() << std::endl;

    return 0;
}