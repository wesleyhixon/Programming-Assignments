#include <iostream>
#include <iomanip>
#include <string>
#include <cctype>

using namespace std;

enum radioBand{
    AM,
    FM
};

class StereoReciever{
    private:
        string manufacturer;
        string model;
        int serialNumber;
        int wattage;
        int numChannels;
        radioBand band;
        double frequency;
        int volume;
        bool power;
        int bass;
        int treble;
    
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
        void setBand(radioBand bandInput){
            band = bandInput;
        }
        void setFrequency(double frequencyInput){
            frequency = frequencyInput;
        }
        void setVolume(int volumeInput){
            if(volumeInput <= 10 && volumeInput >= 0){
                volume = volumeInput;
            }
            else{
                cout << "Invalid Volume!" << endl;
            }
        }
        void setPower(bool powerInput){
            power = powerInput;
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
        radioBand getBand(){
            return band;
        }
        double getFrequency(){
            return frequency;
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

            // Set default values for everything else
            setBand(FM);
            setFrequency(100.1);
            setVolume(5);
            setPower(false);
            setTreble(0);
            setBass(0);
        }
};

int main(){
    StereoReciever userStereo;

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
    userStereo.setPower(true);

    bool menu = true;
    
    while(menu){

        int userChoice;

        cout << "Input a number between 1 and 4 to select any of the following options:" << endl
        << "1. View Stereo Attrubutes" << endl
        << "2. Change Band (AM / FM)" << endl
        << "3. Change Radio Frequency" << endl
        << "4. Change Volume" << endl
        << "5. Power Off" << endl;

        valid = false;

        while(!valid){
            if(!(cin >> userChoice) || userChoice < 1 || userChoice > 5){
                cout << "Please enter a valid menu choice." << endl;
            }
            else{
                valid = true;
            }
        }

        switch(userChoice){
            case 1:
                displayStereo(userStereo);
                break;
            case 2:
        }

    }

    return 0;
}

void displayStereo(StereoReciever stereo){
    
    // Converting stereo band from enum to string for output
    string band;
    switch(stereo.getBand()){
        case 1:
            band = "AM";
            break;
        case 2:
            band = "FM";
            break;
    }

    cout << "This is your current stereo's attributes:" << endl
    << "Manufacturer: " << stereo.getManufacturer() << endl
    << "Model: " << stereo.getModel() << endl
    << "Serial Number: " << stereo.getSerialNum() << endl
    << "Wattage: " << stereo.getWattage() << endl
    << "Number of Channels: " << stereo.getNumChannels() << endl
    << "Current Band:" << band << endl
    << "Current Volume: " << stereo.getVolume() << endl
    << "Current Bass Level: " << stereo.getBass() << endl
    << "Current Treble Level: " << stereo.getTreble() << endl;

    return;
}

bool getValidInput(string& input){
    bool valid = false;
    cin >> input;
    
}