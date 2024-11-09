#include <iostream>
#include <iomanip>
#include <string>
#include <cctype>
#include <stdexcept>
#include <array>
#include <vector>

using namespace std;

void getData(array<int, 16>& grades);
int highScore(const array<int, 16>& grades);
int lowScore(const array<int, 16>& grades);
int averageScore(const array<int, 16>& grades);

int main(){
    array<int, 16> grades;
    getData(grades);

    int maxIndex = highScore(grades);
    int minIndex = lowScore(grades);
    int average = averageScore(grades);

    cout << endl << "Quiz Grades Report:" << endl;

    for(int i = 0; i < 16; i++){
        cout << "\tModule " << i + 1 << ": " << grades[i] << endl;
    }

    cout << "Average grade: " << average << endl;
    cout << "Your lowest score was in Module " << minIndex + 1 << " with a " << grades[minIndex] << "." << endl;
    cout << "Your highest score was in Module " << maxIndex + 1 << " with a " << grades[maxIndex] << "." << endl;
    return 0;
}

// Accept quiz scores for 16 weeks and stores in template array
void getData(array<int, 16>& grades){
    int moduleIndex = 0;
    bool valid = false;

    for(moduleIndex; moduleIndex < 16; moduleIndex++){
        cout << "Please enter the quiz grade for Module " << moduleIndex + 1 << ": " << endl;

        valid = false;
        while(!valid){
            try{
                cin >> grades[moduleIndex];

                if(cin.fail() || grades[moduleIndex] < 0){
                    cin.clear();
                    cin.ignore(10000, '\n');
                    throw(runtime_error("Please enter a valid grade of at least 0."));
                }
                valid = true;
            }catch(const exception& e){
                cerr << endl << e.what() << endl;
            }
        }
    }
    return;
}

// Returns the index of the highest score in grades array
int highScore(const array<int, 16>& grades){
    int max = 0;
    int maxIndex = 0;

    for(int i = 0; i < 16; i++){
        if(grades[i] > max){
            max = grades[i];
            maxIndex = i;
        }
    }

    return maxIndex;
}

// Returns the index of the lowest score in grades array
int lowScore(const array<int, 16>& grades){
    int min = grades[0];
    int minIndex = 0;

    for(int i = 0; i < 16; i++){
        if(grades[i] < min){
            min = grades[i];
            minIndex = i;
        }
    }

    return minIndex;
}

int averageScore(const array<int, 16>& grades){
    int average;
    int sum = 0;

    for(int i = 0; i < 16; i++){
        sum += grades[i];
    }

    average = sum/16;
    return average;
}