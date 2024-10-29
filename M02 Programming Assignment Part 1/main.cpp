#include <iostream>
#include <iomanip>
#include <string>
#include <cctype>
#include <exception>
#include <map>

using namespace std;

enum Month{
    JANUARY, 
    FEBRUARY, 
    MARCH, 
    APRIL, 
    MAY, 
    JUNE, 
    JULY, 
    AUGUST, 
    SEPTEMBER, 
    OCTOBER, 
    NOVEMBER, 
    DECEMBER
};

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

class dateException
{
    private:
        string errorMessage;
    public:
        void yearOutOfRange(int year){
            if(year < 1900){
                errorMessage = "Year cannot be before 1900";
            }
            else if(year > 2020){
                errorMessage = "Year cannot be after 2020";
            }
        }
        void monthOutOfRange(int month){
            if(month < 1){
                errorMessage = "Month cannot be less than 1.";
            }
            else if(month > 12){
                errorMessage = "Month cannot be greater than 12.";
            }
        }
        void dayOutOfRange(int day){

        }

        string what(){
            return errorMessage;
        }
};


class Date{
    private:
        int month;
        int day;
        int year;
    public:
        void constructDate(int inputDay, int inputMonth, int inputYear){
            day = inputDay;
            month = inputMonth;
            year = inputYear;
        }

        string toString(){
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
        }

};



int main(){

    cout << "This program will allow you to store a date between January 1st, 1900 and December 31st, 2020." << endl;
    cout << "An error will be thrown if an invalid date is inputted, and you will be asked to re-enter your date." << endl;

    Date userDate;

    bool done = false;
    do{

    }
    while(!done);

    return 0;
}

Date buildDate(){
    int year, month, day;
    try{
        cout << "Please enter the year of your date: ";
        cin >> year;
        if(year < 1900 || year > 2020) throw(dateException());
    }
    catch(dateException){
        
    }
}