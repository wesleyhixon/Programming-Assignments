#include <iostream>
#include <iomanip>
#include <string>
#include <cctype>
#include <stdexcept>
#include <vector>
#include <fstream>
#include <random>
#include <ctime>
#include <array>

using namespace std;


class nerfGun {
    private:
        string model;
        int range;
        int capacity;
        int dartCount;
    public:
        // Constructor
        nerfGun(string inputModel, int inputRange, int inputCapacity){
            setModel(inputModel);
            setRange(inputRange);
            setCapacity(inputCapacity);
            
            // Fills clip with darts
            dartCount = capacity;
        }

        // Default constructor
        nerfGun(){}

        // Mutator Methods

        void setModel(string inputModel){model = inputModel;}

        void setRange(int inputRange){
            if(inputRange < 1) throw(invalid_argument("Range cannot be less than 1"));

            range = inputRange;
        }

        void setCapacity(int inputCapacity){
            if(inputCapacity > 144) throw(invalid_argument("Capacity cannot be greater than 144"));
            if(inputCapacity < 1) throw(invalid_argument("Capacity cannot be less than 1"));

            capacity = inputCapacity;
        }

        void fire(){
            if(dartCount == 0) throw(underflow_error("Cannot fire with no darts in the clip"));
            
            // Shoot one dart
            dartCount -= 1;
        }

        void reload(int reloadAmount){
            int spaceLeft = capacity - dartCount;

            // Throws exception if not enough space in clip for reload amount
            if(reloadAmount > spaceLeft) throw(overflow_error("Not enough space in clip to reload " + to_string(reloadAmount)));
            if(reloadAmount < 0) throw(invalid_argument("Reload amount cannot be less than 0"));

            // Reloads clip
            dartCount += reloadAmount;
        }

        string toString() const {
            string gunString;
            string line(75, '-');
            string newline;
            int width = 74;

            gunString += '\n' + line;
            newline = "\n| Model: " + getModel();
            newline += string(width - newline.length(), ' ') + " |";
            gunString += newline;
            gunString += '\n' + line;

            newline = "\n| Range: " + to_string(range) + " Feet";
            newline += string(width - newline.length(), ' ') + " |";
            gunString += newline;
            gunString += '\n' + line;
            
            newline = "\n| Capacity: " + to_string(capacity) + " Darts";
            newline += string(width - newline.length(), ' ') + " |";
            gunString += newline;
            gunString += '\n' + line;

            newline = "\n| Dart Count: " + to_string(dartCount) + " Darts";
            newline += string(width - newline.length(), ' ') + " |";
            gunString += newline;
            gunString += '\n' + line;

            return gunString;
        }

        // Accessor Methods
        // Const because they don't need to change anything
        string getModel() const {return model;}
        int getCapacity() const {return capacity;}
        int getDartCount() const {return dartCount;}
        int getRange() const {return range;}

        // Operator Overloading

        // Returns true if both guns have same dart count
        bool operator==(const nerfGun& otherGun){
            if(dartCount == otherGun.getDartCount()){
                return true;
            }
            else{return false;}
        }

        // Returns true if first gun has less darts than second gun
        bool operator<(const nerfGun& otherGun){
            if(dartCount < otherGun.getDartCount()){
                return true;
            }
            else{return false;}
        }

        // Fires gun and throws exception if dartCount == 0
        void operator--(){
            fire();
        }

        // Reloads gun and throws exception if reload amount is too much or negative
        void operator+=(const int& reloadAmount){
            reload(reloadAmount);
        }
        
        // Declares stream extraction operator friend function
        friend ostream& operator<<(ostream& output, const nerfGun& gun);
        
};

// Declared outside nerfGun methods so that cout << gun works
ostream& operator<<(ostream& output, const nerfGun& gun){
    output << endl << gun.toString();
    return output;
}

vector<nerfGun> initializeGuns();
nerfGun generateGun();
void displayGuns(const vector<nerfGun> &guns);
nerfGun mostAmmunition(const vector<nerfGun> &guns);
int menu();

int main(){
    vector<nerfGun> guns;

    guns = initializeGuns();

    cout << "The following is the generated Nerf guns: ";

    bool running = true;
    while(running){
        // Display guns
        displayGuns(guns);

        // Finds the gun with the most ammo in its clip
        nerfGun mostAmmo = mostAmmunition(guns);

        cout << endl << "The gun with the most ammo is:" << mostAmmo;

        if(menu() == 0){
            running = false;
            break;
        }

    }
    return 0;
}

int menu(){
    cout << "Please choose from the following menu options:" << endl;
    cout << "1. Display guns" << endl;
    cout << "2. Fire a gun" << endl;
    cout << "3. Reload a gun" << endl;
    cout << "4. Exit Program" << endl;

    int userInput;
    bool valid = false;
    try{
        while(!valid){
            cin >> userInput;
            if(cin.fail() || userInput < 1 || userInput > 4) throw(runtime_error("Please enter a valid input."));
            valid = true;
        }
    }catch(const exception& e){
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cerr << endl << e.what() << endl;
    }

    if(userInput < 4){
        cout << "Which gun would you like to use?";
    }
}


// Initializes a vector of between 4 and 7 nerf guns and gets input for each
vector<nerfGun> initializeGuns(){
    vector<nerfGun> guns;

    cout << "Initializing guns..." << endl;
    int numOfGuns = 4;

    cout << "Generating " << numOfGuns << " guns." << endl;

    bool valid;

    for(int i = 0; i < numOfGuns; i++){
        valid = false;
        while(!valid){
            try{
                // Get newGun
                nerfGun newGun = generateGun();
                
                // Add newGun to guns vector
                guns.push_back(newGun);
                valid = true;
            }
            catch(const exception& e){
                // Throws exception and restarts gun creation
                cerr << endl << "Exception caught: " << e.what() << endl;
            }
        }
    }

    return guns;
}

// Gets input for 1 nerf gun
nerfGun generateGun(){
    string modelName;
    int range;
    int capacity;
    string line(75, '-');

    // Creating random number generator
    random_device rd;
    mt19937 gen(rd());

    // Array of gun names to pick from
    vector<string> gunNames{
        "Nerf N-Strike Elite HyperFire Blaster",
        "Nerf Elite Jr Explorer Blaster",
        "Nerf Elite 2.0 Ace SD-1 Blaster",
        "Nerf Elite 2.0 Eaglepoint RD-8 Blaster",
        "Nerf N Series Infinite Blaster",
        "Nerf N-Strike Elite Rhino-Fire Blaster",
        "Nerf Pro Torrent Blaster",
        "NERF LMTD Destiny 2 Ace of Spades Blaster",
        "Nerf N-Strike Elite Retaliator Blaster",
        "Nerf Zombie Corrupter Blaster",
        "Nerf N Series Pinpoint Blaster",
        "Nerf Rival Mirage XXIV-800 Blaster",
        "NERF Rival Nemesis MXVII-10K Blaster",
        "Nerf N-Strike Elite Rhino-Fire Blaster",
        "Nerf Elite 2.0 Echo CS-10 Blaster"
    };

    // Pick a random name for a gun from an array of names

    uniform_int_distribution<> nameDistribution(0, 14);
    int randomIndex = nameDistribution(gen);

    modelName = gunNames[randomIndex];


    // Generates random range between 1 and 50
    uniform_int_distribution<> rangeDistribution(1,50);
    range = rangeDistribution(gen);


    // Generates random capacity between 1 and 144
    uniform_int_distribution<> capacityDistribution(1,144);
    capacity = capacityDistribution(gen);

    // Create a new gun with random characteristics
    
    nerfGun newGun(modelName, range, capacity);

    return newGun;
}

void displayGuns(const vector<nerfGun> &guns){

    // Iterates through guns vector with pointer
    for(auto ptr = guns.begin(); ptr != guns.end(); ptr++){
        // Outputs each gun
        nerfGun gun = *ptr;
        cout << endl << gun;
    }
}

nerfGun mostAmmunition(const vector<nerfGun> &guns){
    int max = 0;
    nerfGun mostAmmo;
    mostAmmo = guns[0];

    for(auto ptr = guns.begin(); ptr != guns.end(); ptr++){
        nerfGun gun = *ptr;

        // Compares dart count of guns to find max
        if(mostAmmo < gun){
            max = gun.getDartCount();
            mostAmmo = gun;
        }
    }

    return mostAmmo;
}