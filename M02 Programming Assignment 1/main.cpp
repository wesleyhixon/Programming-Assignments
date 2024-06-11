#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

/* Program name: Gradebook
* Author: Wesley Hixon
* Date last updated: 06/11/24
* Purpose: Read data from a file and output into a correctly formatted table
*/

int main()
{
    // declaring gradeBook file stream
    ifstream gradeBook;
    // opening gradebook.txt
    gradeBook.open("gradebook.txt");
    
    // outputting table heading
    cout << left;
    cout << setfill('-') << setw(17) << "+-" << setw(32) << "+-" << setw(12) << "+-" << setw(12) << "+-" << "+" << endl;
    cout << setfill(' ');
    cout << "| " << setw(15) << "Student Num" << "| " << setw(30) << "Student Name" << "| "<< setw(10) << "Percent" << "| " << setw(10) << "Grade" << "|" << endl; 
    cout << setfill('-') << setw(17) << "+-" << setw(32) << "+-" << setw(12) << "+-" << setw(12) << "+-" << "+" << endl;
    cout << setfill(' ');

    while(gradeBook.is_open()){
        // reading gradeBook line by line
        string line;
        while(getline(gradeBook, line)){

            // declaring variables to extract data from gradeBook
            string studentFirst, studentLast, studentGrade, studentName;
            int studentNum;
            double studentPercent;
            
            // converting line into a stringstream s
            stringstream s(line);

            // extracting data
            s >> studentNum >> studentFirst >> studentLast >> studentPercent >> studentGrade;

            // manipulating data for proper formatting
            studentName = studentFirst + " " + studentLast;
            studentPercent = studentPercent * 100;

            // outputting data
            cout << setfill(' ') << "| " << setw(15) << studentNum << "| " << setw(30) << studentName << "| " 
             << setprecision(5) << right << setw(8) << studentPercent << "%" << left << " | " << setw(10) << studentGrade << "|" << endl;
            cout << setfill('-') << setw(17) << "+-" << setw(32) << "+-" << setw(12) << "+-" << setw(12) << "+-" << "+" << endl;
        }
        
        gradeBook.close();
    }
    return 0;
}