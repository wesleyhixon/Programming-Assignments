#include <iostream>
#include <iomanip>
#include <string>
#include <cctype>

using namespace std;


class stereoReciever{
    private:
        string manufacturer;
        string model;
        int serialNumber;
        int wattage;
        int numChannels;
        string band = "AM";
        double fmFrequency = 100.1;
        int amFrequency = 1000;
        int volume = 5;
        bool power = false;
        int bass = 0;
        int treble = 0;
    
    public:
        // Setter Methods
        void setManufacturer(string manufacturerInput){
            manufacturer = manufacturerInput;
        }
        void setModel(string modelInput){
            model = modelInput;
        }
        void setSerialNum(int serialNumInput){
            serialNumber = serialNumInput;
        }
        void setWattage(int wattageInput){
            wattage = wattageInput;
        }
        void setNumChannels(int numChannelsInput){
            numChannels = numChannelsInput;
        }
        void changeBand(){
            if(band == "AM"){
                band = "FM";
            }
            else{
                band = "AM";
            }
        }
        void setFMFrequency(double frequencyInput){
            fmFrequency = frequencyInput;
        }
        void setAMFrequency(int frequencyInput){
            amFrequency = frequencyInput;
        }
        void setVolume(int volumeInput){
            if(volumeInput <= 10 && volumeInput >= 0){
                volume = volumeInput;
            }
            else{
                cout << "Invalid Volume!" << endl;
            }
        }
        void togglePower(){
            if(power){
                power = false;
            }
            else{
                power = true;
            }
        }
        void setBass(int bassInput){
            if(bassInput <= 5 && bassInput >= -5){
                bass = bassInput;
            }
            else{
                cout << "Invalid bass level!" << endl;
            }
        }
        void setTreble(int trebleInput){
            if(trebleInput <= 5 && trebleInput >= -5){
                treble = trebleInput;
            }
            else{
                cout << "Invalid treble level!" << endl;
            }
        }


        // Getter Methods
        string getManufacturer(){
            return manufacturer;
        }
        string getModel(){
            return model;
        }
        int getSerialNum(){
            return serialNumber;
        }
        int getWattage(){
            return wattage;
        }
        int getNumChannels(){
            return numChannels;
        }
        string getBand(){
            return band;
        }
        double getFMFrequency(){
            return fmFrequency;
        }
        int getAMFrequency(){
            return amFrequency;
        }
        int getVolume(){
            return volume;
        }
        bool getPower(){
            return power;
        }
        int getBass(){
            return bass;
        }
        int getTreble(){
            return treble;
        }

        void stereoConstructor(string manufacturerInput, string modelInput, int serialNumberInput, int wattageInput, int numChannelsInput){
            // Set values user provided
            setManufacturer(manufacturerInput);
            setModel(modelInput);
            setSerialNum(serialNumberInput);
            setWattage(wattageInput);
            setNumChannels(numChannelsInput);

            // Everything else has a default value
        }
};

void displayStereo(stereoReciever stereo);
void changeBand(stereoReciever& stereo);
bool getBoolInput(string prompt);
void changeFrequency(stereoReciever& stereo);

int main(){
    stereoReciever userStereo;

    cout << "Welcome to the stereo reciever simulation!" << endl
    << "Please create your new stereo reciever." << endl;

    cout << "Who is the manufacturer of your new stereo? E.g. Yamaha, JBL, Bose, etc." << endl;

    bool valid = false;
    string manufacturer;
    while(!valid){
        if(!(cin >> manufacturer)){
            cout << "Try again. Enter the name of your stereo's manufacturer" << endl;
            cin.clear();
            cin.ignore(10000, '\n');
        }
        else{
            valid = true;
        }
    }

    cout << "Enter the model of your new stereo." << endl;
    
    valid = false;
    string model;
    while(!valid){
        if(!(cin >> model)){
            cout << "Please try again. Enter the model of your new stereo." << endl;
            cin.clear();
            cin.ignore(10000, '\n');
        }
        else{
            valid = true;
        }
    }

    cout << "Enter the serial number of your new stereo." << endl;

    int serialNum;
    valid = false;
    while(!valid){
        if(!(cin >> serialNum)){
            cout << "Please try again. Enter the serial number of your new stereo." << endl;
            cin.clear();
            cin.ignore(10000, '\n');
        }

        else{
            valid = true;
        }
    }

    cout << "Enter the wattage of your new stereo." << endl;

    int wattage;
    valid = false;
    while(!valid){
        if(!(cin >> wattage) || wattage < 0){
            cout << "Please try again. Enter a valid wattage." << endl;
            cin.clear();
            cin.ignore(10000, '\n');
        }

        else{
            valid = true;
        }
    }

    cout << "Enter the number of channels for your new stereo." << endl;

    int numChannels;
    valid = false;
    while(!valid){
        if(!(cin >> numChannels) || numChannels <= 0){
            cout << "Please try again. Enter a valid number of channels." << endl;
            cin.clear();
            cin.ignore(10000, '\n');
        }

        else{
            valid = true;
        }
    }


    // Build new stereo with constructor
    userStereo.stereoConstructor(manufacturer, model, serialNum, wattage, numChannels);

    // Turn stereo on
    userStereo.togglePower();

    bool menu = true;
    
    while(menu){

        int menuChoice;

        cout << endl << "Input a number between 1 and 5 to select any of the following options:" << endl
        << "1. View Stereo Attrubutes" << endl
        << "2. Change Band (AM / FM)" << endl
        << "3. Change Radio Frequency" << endl
        << "4. Change Volume" << endl
        << "5. Power Off" << endl;

        valid = false;

        while(!valid){
            if(!(cin >> menuChoice) || menuChoice < 1 || menuChoice > 5){
                cout << "Please enter a valid menu choice." << endl;
                cin.clear();
                cin.ignore(10000, '\n');
            }
            else{
                valid = true;
            }
        }

        switch(menuChoice){
            case 1:
                displayStereo(userStereo);
                break;
            case 2:
                changeBand(userStereo);
                break;
            case 3:
                // change frequency
                changeFrequency(userStereo);
                break;
            case 4:
                // change volume
                break;
            case 5:
                bool input = getBoolInput("Are you sure you would like to exit? Type (y/n)");
                if(input == true){
                    userStereo.togglePower();
                    menu = false;
                }
                break;
        }

    }

    return 0;
}

void displayStereo(stereoReciever stereo){
    
    cout << endl << "This is your current stereo's attributes:" << endl
    << "Manufacturer: " << stereo.getManufacturer() << endl
    << "Model: " << stereo.getModel() << endl
    << "Serial Number: " << stereo.getSerialNum() << endl
    << "Wattage: " << stereo.getWattage() << endl
    << "Number of Channels: " << stereo.getNumChannels() << endl
    << "Current Band:" << stereo.getBand() << endl
    << "Current Volume: " << stereo.getVolume() << endl
    << "Current Bass Level: " << stereo.getBass() << endl
    << "Current Treble Level: " << stereo.getTreble() << endl;

    return;
}

// WIP
/*
bool getValidInput(string& input){
    bool valid = false;
    cin >> input;
    
}
*/

void changeBand(stereoReciever& stereo){
    string band = stereo.getBand();

    cout << endl << "The current band is set to " << band << endl;

    bool input = getBoolInput("Would you like to switch bands? (Type y/n)");

    if(input = true){
        stereo.changeBand();
    }
}

bool getBoolInput(string prompt){
    bool valid = false;
    char input;
    
    cout << endl << prompt;
    
    while(!valid){
        if(!(cin >> input) || (tolower(input) != 'y' && tolower(input) != 'n')){
            cout << endl << "Please try again. Enter y or n." << endl;
            cin.clear();
            cin.ignore(100000, '\n');
        }
        else{
            valid = true;
        }
    }

    if(tolower(input) == 'y'){
        return true;
    }
    else{
        return false;
    }
}

void changeFrequency(stereoReciever& stereo){
    double frequency;

    if(stereo.getBand() == "AM"){
        frequency = stereo.getAMFrequency();
    }
    else{
        frequency = stereo.getFMFrequency();
    }


    cout << endl << stereo.getBand() << " radio frequency is currently set to " << frequency << endl;
    
    bool input = getBoolInput("Would you like to change it? (Type y/n)");

    if(input == false){
        return;
    }

    bool valid = false;
    double frequencyInput;

    cout << "Enter your desired " << stereo.getBand() << " radio frequency: ";

    while(!valid){
        if(!(cin >> frequencyInput) || frequencyInput < 0){
            cout << endl << "Please try again. Enter a valid frequency." << endl;
            cin.clear();
            cin.ignore(10000, '\n');
        }
        else{
            valid = true;
        }
    }

    if(stereo.getBand() == "AM"){
        stereo.setAMFrequency(frequencyInput);
    }
    else{
        stereo.setFMFrequency(frequencyInput);
    }
}