#include <iostream>
#include <limits>
#include <algorithm>
#include <chrono>


template <class Type>
class nodeType{
    public:
        Type info;
        nodeType<Type>* link;
};

class linkedListType{
    public:
        int count;
        nodeType<int>* first = nullptr;
        nodeType<int>* last = nullptr;
        void insertFirst(int value){
            nodeType<int>* newNode = new nodeType<int>;
            newNode->info = value;
            
            if(first == nullptr){
                first = newNode;
                last = newNode;
                return;
            }

            newNode->link = first;
            first = newNode;
        }
        void insertLast(int value){
            nodeType<int>* newNode = new nodeType<int>;
            newNode->info = value;

            if(first == nullptr){
                first = newNode;
                last = newNode;
                return;
            }

            last->link = newNode;
            last = newNode;
        }
        void deleteFirst(){
            if(first == nullptr){
                return;
            }

            if(first == last){
                delete first;
                first = last = nullptr;
                return;
            }

            auto* temp = first;
            first = temp->link;
            delete temp;
        }
        void deleteLast(){

            if(first == nullptr){
                return;
            }
            if(first == last){
                delete first;
                first = last = nullptr;
                return;
            }

            auto* prev = first;
            while(prev->link != last){
                prev = prev->link;
            }

            delete last;
            last = prev;
            last->link = nullptr;
        }

        void print(){
            nodeType<int>* itr = first;
            while(itr != nullptr){
                std::cout << itr->info << ' ';
                itr = itr->link;
            }
        }
        void selectionSort(){
            for(auto* itr = first; itr != nullptr; itr = itr->link){
                auto* minPtr = itr;


                for(auto* comparisonItr = itr->link; comparisonItr != nullptr; comparisonItr = comparisonItr->link){
                    if(comparisonItr->info < minPtr->info){
                        minPtr = comparisonItr;
                    }
                }

                std::swap(itr->info, minPtr->info);
            }
        }

        void mergeSort(){

        }
        
        linkedListType(){

        }

        linkedListType(const linkedListType& other){
            
            for(auto* otherItr = other.first; otherItr != nullptr; otherItr = otherItr->link){
                
            }
        }

        ~linkedListType(){
            nodeType<int>* itr = first;
            
            while(itr != nullptr){
                nodeType<int>* temp = itr;
                itr = temp->link;
                delete temp;
            }
        }
};

int main(){
    linkedListType selectSortList, mergeSortList;

    bool valid = false;
    int numValues;
    while(!valid){
        std::cout << "Please enter the number of values you'd like to insert into the linked list (Maximum 5000): ";
        std::cin >> numValues;
        if(numValues < 1 || numValues > 5000 || !std::cin){
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Please enter a number between 1 and 5000." << std::endl;
        }
        else{
            valid = true;
        }
    }

    for(int i = 0; i < numValues; i++){
        int randomInt = rand() % 5000;
        selectSortList.insertLast(randomInt);
        mergeSortList.insertLast(randomInt);
    }

    

    // This time elapsed logic was taken from GeeksForGeeks.com

    auto start = std::chrono::high_resolution_clock::now();

    selectSortList.selectionSort();
    
    auto stop = std::chrono::high_resolution_clock::now();

    auto selectDuration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);


    std::cout << "The list has been select sorted. This took " << selectDuration.count() << " microseconds." << std::endl;

    return 0;
}