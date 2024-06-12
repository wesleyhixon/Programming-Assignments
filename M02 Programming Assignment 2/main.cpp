#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;


/* Program name: Calendar Events
*  Author: Wesley Hixon
*  Date last updated: 06/12/2024
* Purpose: Prompts user for 5 calendar event names and dates. Outputs events to an output file along with a reminder date.
*/


void tableHeader(ofstream& outputFile){
    
    // Generate Table Header
    outputFile << left;
    outputFile << "|" << setw(50) << setfill('-') << "-" << "|" << endl;
    outputFile << setfill(' ');
    outputFile << "| " << setw(19) << "Event Name" << "| " << setw(11) << "Event Date" << "| " << setw(15) << "Reminder Date" << "| " << endl;
    outputFile << "|" << setw(50) << setfill('-') << "-" << "|" << endl;
}


void getEvent(string sequence, ofstream& outputFile){
    
    // Initializing Variables
    int day, month, year;
    string eventDate, reminderDate, eventName;

    // Prompting for event name
    // This uses getline() to accommodate for more than one word event names
    cin.ignore();
    cout << "\n" << "Enter the " + sequence + " event name: ";
    getline(cin, eventName);

    // Prompting for month
    cout << "\n" << "Enter the month of the event: ";
    cin >> month;

    // Prompting for day
    cout << "\n" << "Enter the day of the event: ";
    cin >> day;

    // Prompting for year
    cout << "\n" << "Enter the year of the event: ";
    cin >> year;

    // Creating date string in month/day/year format
    eventDate = to_string(month) + "/" + to_string(day) + "/" + to_string(year);

    // Creating reminder day one day before event day
    int reminderDay = day - 1;

    reminderDate = to_string(month) + "/" + to_string(reminderDay) + "/" + to_string(year);

    // Creating header for each event entry
    tableHeader(outputFile);

    // Outputting event information to file
    outputFile << setfill(' ') << "| " << setw(19) << eventName << "| " << setw(11) << eventDate << "| " << setw(15) << reminderDate << "| " << endl;
    outputFile << "|" << setw(50) << setfill('-') << "-" << "|" << endl;

    return;
}

int main()
{
    // Open Output File
    ofstream outputFile;
    outputFile.open("output.txt");


    // Prompt User for next 5 calendar events
    cout << "This program will prompt you for your next 5 calendar events \n";
    cout << "These events will be put into a table, along with a reminder eventDate \n";

    // Calling function to prompt for 5 calendar events
    getEvent("first", outputFile);
    getEvent("second", outputFile);
    getEvent("third", outputFile);
    getEvent("fourth", outputFile);
    getEvent("fifth", outputFile);

    outputFile.close();
    
    return 0;
}