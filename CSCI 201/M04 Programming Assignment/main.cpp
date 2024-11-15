#include <iostream>
#include <iomanip>
#include <string>
#include <cctype>
#include <stdexcept>
#include <vector>
#include <fstream>
#include <random>

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

            gunString = "Model: " + getModel() + "\nRange: " + to_string(range) + "\nDart Count: " + to_string(dartCount) 
            + "\nCapacity: " + to_string(capacity);

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
nerfGun inputGun(int gunNum);
void displayGuns(const vector<nerfGun> &guns);
nerfGun mostAmmunition(const vector<nerfGun> &guns);


int main(){
    vector<nerfGun> guns;

    guns = initializeGuns();


    bool running = true;
    while(running){
        // Display guns
        displayGuns(guns);

        // Finds the gun with the most ammo in its clip
        nerfGun mostAmmo = mostAmmunition(guns);
    }
    return 0;
}


// Initializes a vector of between 4 and 7 nerf guns and gets input for each
vector<nerfGun> initializeGuns(){
    vector<nerfGun> guns;

    cout << "Initializing guns..." << endl;
    int numOfGuns;

    // Uses random number generator to generate a double between 0 and 1
    random_device rd;
    mt19937 gen(rd());
    double randomNumber = generate_canonical<double, 10>(gen);

    // Randomly chooses num of guns to be between 4 and 7
    if(randomNumber < .25){
        numOfGuns = 4;
    }
    else if(randomNumber >= .25 && randomNumber < .50){
        numOfGuns = 5;
    }
    else if(randomNumber >= .50 && randomNumber < .75){
        numOfGuns = 6;
    }
    else if(randomNumber >= .75){
        numOfGuns = 7;
    }

    cout << "Generating " << numOfGuns << " guns." << endl;

    bool valid;

    for(int i = 0; i < numOfGuns; i++){
        valid = false;
        while(!valid){
            try{
                // Get input for newGun
                nerfGun newGun = inputGun(i);
                
                // Add newGun to guns vector
                guns.push_back(newGun);
                valid = true;
            }
            catch(const exception& e){
                // Throws exception and restarts gun creation
                cerr << endl << "Exception caught: " << e.what() << endl;
                cerr << "Please re-enter the data for this gun." << endl;

                // Ignores newline for new gun input
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        }
    }

    return guns;
}

// Gets input for 1 nerf gun
nerfGun inputGun(int gunNum){
    string modelName;
    int range;
    int capacity;

    cout << endl << "Enter the model name for gun number " << gunNum+1 << ": ";
    getline(cin, modelName);

    cout << "Enter the range in feet: ";
    cin >> range;
    if(range < 1) throw(invalid_argument("Range cannot be less than 1"));

    cout << "Enter the dart capacity: ";
    cin >> capacity;
    if(capacity < 1 || capacity > 144) throw(invalid_argument("Capacity must be between 1 and 144"));

    // Clear newline from buffer
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    // Attempt to create a new gun with given inputs
    
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