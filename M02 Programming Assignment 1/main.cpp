#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;


int main()
{
    ifstream gradeBook;
    gradeBook.open("gradebook.txt");
    int i = 0;
    // table heading output
    cout << left;
    cout << setfill('-') << setw(17) << "+-" << setw(32) << "+-" << setw(12) << "+-" << setw(12) << "+-" << "+" << endl;
    cout << setfill(' ');
    cout << "| " << setw(15) << "Student Num" << "| " << setw(30) << "Student Name" << "| "<< setw(10) << "Percent" << "| " << setw(10) << "Grade" << "|" << endl; 
    cout << setfill('-') << setw(17) << "+-" << setw(32) << "+-" << setw(12) << "+-" << setw(12) << "+-" << "+" << endl;
    cout << setfill(' ');

    while(gradeBook.is_open()){
        string studentFirst, studentLast, studentGrade, studentName;
        int studentNum;
        double studentPercent;

        gradeBook >> studentNum >> studentFirst >> studentLast >> studentPercent >> studentGrade;

        studentName = studentFirst + " " + studentLast;
        studentPercent = studentPercent * 100;

        cout << "| " << setw(15) << studentNum << "| " << setw(30) << studentName << "| " 
         << setprecision(5) << studentPercent << setw(4) << "%" << "| " << setw(10) << studentGrade << "|" << endl;
        cout << setfill('-') << setw(17) << "+-" << setw(32) << "+-" << setw(12) << "+-" << setw(12) << "+-" << "+" << endl;
        
        gradeBook.close();
    }
    return 0;
}