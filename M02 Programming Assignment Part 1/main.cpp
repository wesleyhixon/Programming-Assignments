#include <iostream>
#include <iomanip>
#include <string>
#include <cctype>
#include <exception>
#include <map>

using namespace std;

string monthToString(int month);

map<int, int> daysInMonth{
    {1, 31},
    {2, 28},
    {3, 31},
    {4, 30},
    {5, 31},
    {6, 30},
    {7, 31},
    {8, 31},
    {9, 30},
    {10, 31},
    {11, 30},
    {12, 31}
};



class yearOutOfRangeException{
    private:
        string message;
    public:
        yearOutOfRangeException(int year){
            if(year < 1900){
                message = "Year cannot be before 1900";
            }
            else if(year > 2020){
                message = "Year cannot be after 2020";
            }
        }
        string what(){
            return message;
        }
};

class monthOutOfRangeException{
    private:
        string message;
    public:
        monthOutOfRangeException(int month){
            if(month > 12){
                message = "Month cannot be more than 12";
            }
            else if(month < 1){
                message = "Month cannot be less than 1";
            }
        }
        string what(){
            return message;
        }
};

class dayOutOfRangeException{
    private:
        string message;
    public:
        dayOutOfRangeException(int month, int day){
            int numDaysInMonth = daysInMonth[month];
            if(day > numDaysInMonth){
                message = "Day cannot be greater than number of days in " + monthToString(month) + " (" + to_string(numDaysInMonth) + ")";
            }
            else if(day < 1){
                message = "Day cannot be less than 1";
            }
        }
        string what(){
            return message;
        }
};

class menuOutOfRangeException{
    private:
        string message;
    public:
        menuOutOfRangeException(int menuChoice){
            if(menuChoice > 4 || menuChoice < 1){
                message = "Menu choice must be between 1 and 4";
            }
        }
        string what(){
            return message;
        }
};

class Date{
    private:
        int month;
        int day;
        int year;
    public:
        Date(){
            day = 1;
            month = 1;
            year = 1900;
        }
        Date(int inputDay, int inputMonth, int inputYear){
            // Handling out of range errors inside constructor function
            try{

                if(inputYear < 1900 || inputYear > 2020) throw(yearOutOfRangeException(inputYear));
                year = inputYear;

                if(inputMonth > 12 || inputMonth < 1) throw(monthOutOfRangeException(inputMonth));
                month = inputMonth;


                int numDaysInMonth = daysInMonth[month];

                if(inputDay < 1 || inputDay > numDaysInMonth) throw(dayOutOfRangeException(month, inputDay));
                day = inputDay;
            }
            catch(yearOutOfRangeException e){
                cerr << e.what() << endl;
            }
            catch(monthOutOfRangeException e){
                cerr << e.what() << endl;
            }
            catch(dayOutOfRangeException e){
                cerr << e.what() << endl;
            }
        }
        string dateToString(){
            string daySuffix;

            switch(day){
                case 1: case 21: case 31:
                    daySuffix = "st";
                    break;
                case 2: case 22:
                    daySuffix = "nd";
                    break;
                case 3: case 23:
                    daySuffix = "rd";
                    break;
                default:
                    daySuffix = "th";
                    break;

            }

            string monthString = monthToString(month);

            string dateString = to_string(day) + daySuffix + " of " + monthString + ", " + to_string(year);

            return dateString;
        }
        int getYear(){
            return year;
        }
        int getMonth(){
            return month;
        }
        int getDay(){
            return day;
        }
        void setDay(int inputDay){
            int numDaysInMonth = daysInMonth[month];
            try{
                if(inputDay < 1 || inputDay > numDaysInMonth) throw(dayOutOfRangeException(month, inputDay));
                day = inputDay;
            }
            catch(dayOutOfRangeException e){
                throw(e);
            }
        }
};

Date buildDate();
void menu(Date date);

int main(){

    cout << "This program will allow you to store a date between January 1st, 1900 and December 31st, 2020." << endl;
    cout << "An error will be thrown if an invalid date is inputted, and you will be asked to re-enter your date." << endl;

    Date userDate;

    userDate = buildDate();

    menu(userDate);

    return 0;
}

Date buildDate(){
    int year, month, day;
    bool valid = false;


    while(!valid){
        try{
            cout << endl << "Please enter the year of your date: ";
            cin >> year;

            if(!cin) throw("The input stream is in fail state.");
            if(year < 1900 || year > 2020) throw(yearOutOfRangeException(year));

            valid = true;
        }
        catch(string s){
            cerr << s << endl;
            cin.clear();
            cin.ignore(10000, '\n');
        }
        catch(yearOutOfRangeException e){
            cerr << e.what() << endl;
        }
    }

    valid = false;
    while(!valid){
        try{
            cout << endl << "Please enter the month of your date: ";
            cin >> month;

            if(!cin) throw("The input stream is in fail state.");
            if(month > 12 || month < 1) throw(monthOutOfRangeException(month));

            valid = true;
        }
        catch(string s){
            cerr << s << endl;
            cin.clear();
            cin.ignore(10000, '\n');
        }
        catch(monthOutOfRangeException e){
            cerr << e.what() << endl;
        }
    }

    int numDaysInMonth = daysInMonth[month];
    valid = false;
    while(!valid){
        try{
            cout << endl << "Please enter the day of your date: ";
            cin >> day;

            if(!cin) throw("The input stream is in fail state.");
            if(day < 1 || day > numDaysInMonth) throw(dayOutOfRangeException(month, day));

            valid = true;
        }
        catch(string s){
            cerr << s << endl;
            cin.clear();
            cin.ignore(10000, '\n');
        }
        catch(dayOutOfRangeException e){
            cerr << e.what() << endl;
        }
    }

    Date newDate(day, month, year);
    return newDate;
}


// Converts an int month to a string
string monthToString(int month){
    string monthString;

    switch(month){
        case 1:
            monthString = "January";
            break;
        case 2:
            monthString = "Feburary";
            break;
        case 3:
            monthString = "March";
            break;
        case 4:
            monthString = "April";
            break;
        case 5:
            monthString = "May";
            break;
        case 6:
            monthString = "June";
            break;
        case 7:
            monthString = "July";
            break;
        case 8:
            monthString = "August";
            break;
        case 9:
            monthString = "September";
            break;
        case 10:
            monthString = "October";
            break;
        case 11:
            monthString = "November";
            break;
        case 12:
            monthString = "December";
            break;
    }

    return monthString;
}


// Menu to edit date or exit program
void menu(Date date){
    bool running = true;
    int menuChoice;
    

    while(running){

        // Outputting menu
        cout << "Your date is: " << date.dateToString() << endl;
        cout << "Select from the following menu options:" << endl
        << "1. Change Year" << endl
        << "2. Change Month" << endl
        << "3. Change Day" << endl
        << "4. Exit Program" << endl;

        bool valid = false;
        do{
            try{
                // Get input
                cin >> menuChoice;

                // In case of cin error or out of range error
                if(!cin) throw("Please enter an integer");
                if(menuChoice > 4 || menuChoice < 1) throw(menuOutOfRangeException(menuChoice));

                valid = true;
            }

            // Output error messages and try again
            catch(menuOutOfRangeException e){
                cerr << e.what() << endl;
            }
            catch(string s){
                cerr << s << endl;
                cin.clear();
                cin.ignore(10000, '\n');
            }
        }
        while(!valid);

        if(menuChoice == 1){
            
        }
        else if(menuChoice == 2){

        }
        else if(menuChoice == 3){

        }
        else if (menuChoice == 4)
        


        running = false;

    }
}