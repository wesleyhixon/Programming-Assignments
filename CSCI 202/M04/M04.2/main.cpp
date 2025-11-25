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
        int count = 0;
        nodeType<int>* first = nullptr;
        nodeType<int>* last = nullptr;

        const linkedListType& operator=(const linkedListType &other){
            if(other.count == 0){
                return *this;
            }
            for(auto* otherItr = other.first; otherItr != nullptr; otherItr = otherItr->link){
                nodeType<int>* temp = new nodeType<int>;
                temp->info = otherItr->info;

                if(first = nullptr){
                    first = temp;
                    last = temp;
                }
                else{
                    last->link = temp;
                    last = temp;
                    last->link = nullptr;
                }
            }

            return *this;
        }

        linkedListType(){

        }

        linkedListType(const linkedListType &other){
            if(other.count == 0){
                return;
            }

            for(auto* otherItr = other.first; otherItr != nullptr; otherItr = otherItr->link){
                nodeType<int>* temp = new nodeType<int>;
                temp->info = otherItr->info;

                if(first = nullptr){
                    first = temp;
                    last = temp;
                }
                else{
                    last->link = temp;
                    last = temp;
                }
            }
        }

        ~linkedListType(){
            initializeList();
        }

        void initializeList(){
            nodeType<int>* itr = first;
            
            while(itr != nullptr){
                nodeType<int>* temp = itr;
                itr = temp->link;
                delete temp;
            }
        }
        void insertFirst(int value){
            nodeType<int>* newNode = new nodeType<int>;
            newNode->info = value;
            count += 1;
            
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
            newNode->link = nullptr;
            count += 1;

            if(first == nullptr){
                first = last = newNode;
                return;
            }

            last->link = newNode;
            last = newNode;
        }
        void deleteFirst(){
            if(first == nullptr){
                return;
            }

            count -= 1;

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

            count -= 1;

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

        // Prints list
        void printList(){
            nodeType<int>* itr = first;
            while(itr != nullptr){
                std::cout << itr->info << ' ';
                itr = itr->link;
            }
        }

        void printList(nodeType<int>* head){
            auto* itr = head;
            while(itr != nullptr){
                std::cout << itr->info << ' ';
                itr = itr->link;
            }
        }

        // Sorts by swapping each node with the smallest node in the rest of the list
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

        // Returns middle element
        nodeType<int>* getMiddle(){
            if(first == nullptr || first->link == nullptr){
                return first;
            }

            nodeType<int>* slow = first;
            nodeType<int>* fast = first->link;

            while(fast != nullptr && fast->link != nullptr){
                slow = slow->link;
                fast = fast->link->link;
            }
            
            return slow;
        }

        // Returns the middle element given the first element of a linked list
        nodeType<int>* getMiddle(nodeType<int>* &firstElement){
            if(firstElement == nullptr || firstElement->link == nullptr){
                return firstElement;
            }

            nodeType<int>* slow = firstElement;
            nodeType<int>* fast = firstElement->link;

            while(fast != nullptr && fast->link != nullptr){
                slow = slow->link;
                fast = fast->link->link;
            }
            
            return slow;
        }

        // Merges two sorted lists
        nodeType<int>* merge(nodeType<int>* first1, nodeType<int>* first2){
            nodeType<int>* newHead, *lastMerged;

            if(first1 == nullptr){
                return first2;
            }
            if(first2 == nullptr){
                return first1;
            }

            if(first1->info < first2->info){
                newHead = first1;
                first1 = first1->link;
            }
            else{
                newHead = first2;
                first2 = first2->link;
            }

            lastMerged = newHead;

            while(first1 != nullptr && first2 != nullptr){

                
                if(first1->info < first2->info){
                    lastMerged->link = first1;
                    lastMerged = lastMerged->link;

                    first1 = first1->link;
                }
                else{
                    lastMerged->link = first2;
                    lastMerged = lastMerged->link;

                    first2 = first2->link;
                }
            }

            if(first1 == nullptr){
                lastMerged->link = first2;
            }
            else{
                lastMerged->link = first1;
            }

            return newHead;
        }

        void split(nodeType<int>* first1, nodeType<int>* &first2){
            // empty list or one element
            if(first1 == nullptr || first1->link == nullptr){
                first2 = nullptr;
                return;
            }

            auto* middle = getMiddle(first1);

            first2 = middle->link;

            // sever the lists
            middle->link = nullptr;
        }

        nodeType<int>* mergeSort(nodeType<int>* list){
            if(list == nullptr || list->link == nullptr){
                return list;
            }
            
            nodeType<int>* list2;

            split(list, list2);

            list = mergeSort(list);

            list2 = mergeSort(list2);

            return merge(list, list2);
        }

        void mergeSort(){
            if(first == nullptr || first->link == nullptr){
                return;
            }

            nodeType<int>* list1 = first;
            nodeType<int>* list2;

            split(first, list2);

            list1 = mergeSort(list1);
            list2 = mergeSort(list2);
            
            merge(list1, list2);
        }
        
};

int main(){
    bool running = true;

    while(running){
        linkedListType selectSortList, mergeSortList;
        bool valid = false;
        int numValues;
        int maxValue = 50000;
        
        while(!valid){
            std::cout << "Please enter the number of values you'd like to insert into the linked list (Maximum " << maxValue << "). Enter 0 to exit: ";
            std::cin >> numValues;
            if(numValues < 0 || numValues > maxValue || !std::cin){
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Please enter a number between 0 and " << maxValue << "." << std::endl;
            }
            else if(numValues == 0){
                running = false;
                valid = true;
            }
            else{
                valid = true;
            }
        }

        if(running == false) break;

        for(int i = 0; i < numValues; i++){
            int randomInt = rand() % 50000;
            selectSortList.insertLast(randomInt);
            mergeSortList.insertLast(randomInt);
        }

        

        // This time elapsed logic was taken from GeeksForGeeks.com

        auto start = std::chrono::high_resolution_clock::now();

        selectSortList.selectionSort();
        
        auto stop = std::chrono::high_resolution_clock::now();

        auto selectDuration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);


        std::cout << "The list has been select sorted. This took " << selectDuration.count() << " microseconds." << std::endl;



        start = std::chrono::high_resolution_clock::now();
        
        mergeSortList.mergeSort();

        stop = std::chrono::high_resolution_clock::now();

        auto mergeDuration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

        std::cout << "The list has been merge sorted. This took " << mergeDuration.count() << " microseconds." << std::endl;

    }

    return 0;
}