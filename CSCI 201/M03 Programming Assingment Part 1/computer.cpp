#include <iostream>
#include <iomanip>
#include <string>
#include <cctype>
#include <stdexcept>

using namespace std;

template <typename T>
T getInput(string prompt){
    bool valid = false;
    T input;
    cout << endl << prompt;
    try{
        while(!valid){
            cin >> input;
            if(cin.fail()){
                cin.clear();
                cin.ignore(10000, '\n');
                throw(runtime_error("Please enter a valid input."));
            }
            valid = true;
        }
    }catch(const exception& e){
        cerr << endl << e.what() << endl;
    }

    return input;
}


enum storageTypes{SSD, HDD, UFS};

class computer{
    private:
        string manufacturer;
        string formFactor;
        int serialNum;
        string processor;
        int ram;
        storageTypes storageType;
        string storageSize;
    public:
        // Constructor Method
        computer(
            string inputManufacturer,
            string inputFormFactor, 
            int inputSerialNum, 
            string inputProcessor, 
            int inputRam, 
            storageTypes inputStorageType, 
            string inputStorageSize
            ){


        }
        computer(){}

        // Mutator Methods
        void setManufacturer(string inputManufacturer){manufacturer = inputManufacturer;}
        void setFormFactor(string inputFormFactor){formFactor = inputFormFactor;}
        void setSerialNum(int inputSerialNum){
            try{
                if(inputSerialNum < 0) throw(invalid_argument("Please enter a valid serial number greater than 0."));
                serialNum = inputSerialNum;
            }catch(const exception& e){
                throw e;
            }
        }
        void setProcessor(string inputProcessor){processor = inputProcessor;}
        void setRam(int inputRam){
            int validRam[6] = {4, 6, 8, 16, 32, 64};
            bool valid = false;

            try{
                for(int i = 0; i < 6; i++){
                    if(inputRam == validRam[i]){
                        valid = true;
                    }
                }
                if(!valid) throw(invalid_argument("Please enter 4, 6, 8, 16, 32, or 64 as your ram."));
            }
            catch(const exception& e){
                throw e;
            }
        }
        void setStorageType(storageTypes inputStorageType){
            storageType = inputStorageType;
        }

        // Accessor Methods
        string getManufacturer(){return manufacturer;}
        string getFormFactor(){return formFactor;}
        int getSerialNum(){return serialNum;}
        string getProcessor(){return processor;}
        int getRam(){return ram;}
        storageTypes getStorageType(){return storageType;}
        string getStorageSize(){return storageSize;}
};

int main(){

    return 0;
}

computer getComputer(){
    computer newComputer;

    string manufacturer;
    bool valid = false;
    while(!valid){
        try{
            manufacturer = getInput<string>("Please enter the manufacturer of your computer: ");
            newComputer.setManufacturer(manufacturer);
            valid = true;
        }catch(const exception& e){
            cerr << endl << e.what() << endl;
        }
    }

    string formFactor;
    valid = false;
    while(!valid){
        try{
            formFactor = getInput<string>("Please enter the form factor of your computer (desktop/laptop): ");
            newComputer.setFormFactor(formFactor);
            valid = true;
        }catch(const exception& e){
            cerr << endl << e.what() << endl;
        }
    }

}

