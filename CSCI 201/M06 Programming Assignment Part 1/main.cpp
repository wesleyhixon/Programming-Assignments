#include <iostream>
#include <iomanip>
#include <string>
#include <cctype>
#include <stdexcept>

using namespace std;

class player{
    protected:
        string name;
        int playerID;
        string position;
    public:
        string getName(){return name;}
        int getPlayerID(){return playerID;}
        string getPlayerPosition(){return position;}
        string toString(){
            string playerString;
            playerString = name + ", Number: " + to_string(playerID) + ", Position: " + position;
            return playerString;
        }

        void setName(string inputName){name = inputName;}
        void setPlayerID(int inputID){playerID = inputID;}
        virtual string play() = 0;
};


class QuarterBack: public player{
    private:
        string position = "Quarterback";
    public:
        string play(){
            return (name + " throws");
        }
};
class WideReceiver: public player{
    private:
        string position = "Wide Receiver";
    public:
        string play(){
            return (name + " catches");
        }
};
class TightEnd: public player{
    private:
        string position = "Tight End";
    public:
        string play(){
            return (name + " blocks and catches");
        }
};
class RunningBack: public player{
    private:
        string position = "Running Back";
    public:
        string play(){
            return (name + " runs the ball");
        }
};
class OffensiveLineman: public player{
    private:
        string position = "Offensive Lineman";
    public:
        string play(){
            return (name + " protects the quarterback");
        }
};
class DefensiveLineman: public player{
    private:
        string position = "Defensive Lineman";
    public:
        string play(){
            return (name + " tackles the ball carrier");
        }
};
class Linebacker: public player{
    private:
        string position = "Linebacker";
    public:
        string play(){
            return (name + " blocks a pass");
        }
};
class DefensiveBack: public player{
    private:
        string position = "Defensive Back";
    public:
        string play(){
            return (name + " blocks a pass");
        }
};
class TightEnd: public player{
    private:
        string position = "Tight End";
    public:
        string play(){
            return (name + "blocks and catches");
        }
};

int main(){

    return 0;
}