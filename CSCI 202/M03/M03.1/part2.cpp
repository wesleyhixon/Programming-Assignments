#include <iostream>
#include <exception>

/* 
Name: linked queue
Author: Wesley Hixon
Date Last Updated:11/16/2025
Purpose: Create a queue with a linked list
*/


template <class Type>
class nodeType{
    public:
        Type info;
        nodeType<Type>* link;
};

template <class Type>
class queueADT
{
    virtual bool isEmptyQueue() const = 0;
    virtual bool isFullQueue() const = 0;
    virtual void initializeQueue() = 0;
    virtual Type front() const = 0;
    virtual Type back() const = 0;
    virtual void addQueue(const Type& element) = 0;
    virtual void deleteQueue() = 0;
};


template <class Type>
class linkedQueueType : public queueADT<Type>{
    public:    
        const linkedQueueType<Type>& operator=(const linkedQueueType<Type> &other){
            if(this != &other){
                initializeQueue();

                nodeType<Type> *otherIterator;
                otherIterator = other.queueFront;

                while(otherIterator != nullptr){
                    addQueue(otherIterator->info);
                    otherIterator = otherIterator->link;
                }
            }

            return *this;
        }
        bool isEmptyQueue() const{
            if(queueFront == nullptr){
                return true;
            }
            else{
                return false;
            }
        }
        bool isFullQueue() const{
            return false;
        }
        void initializeQueue(){
            nodeType<Type> *temp;

            while(queueFront != nullptr){
                temp = queueFront;
                queueFront = queueFront->link;
                delete temp;
            }
            queueRear = nullptr;
        }
        Type front() const{
            if(isEmptyQueue()) throw(std::runtime_error("Cannot access empty queue."));
            return queueFront->info;
        }
        Type back() const{
            if(isEmptyQueue()) throw(std::runtime_error("Cannot access empty queue."));
            return queueRear->info;
        }
        void addQueue(const Type& element){
            nodeType<Type> *temp = new nodeType<Type>;
            temp->info = element;

            if(isEmptyQueue()){
                queueFront = temp;
                queueRear = temp;
            }
            else{
                queueRear->link = temp;
                queueRear = temp;
            }
        }
        void deleteQueue(){
            if(isEmptyQueue()) throw(std::runtime_error("Cannot delete from empty queue."));
            
            nodeType<Type> *temp = queueFront;
            queueFront = queueFront->link;
            delete temp;
        }
        linkedQueueType(){
            initializeQueue();
        }
        linkedQueueType(const linkedQueueType<Type>& other){
            initializeQueue();

            nodeType<Type> *otherIterator;
            otherIterator = other.queueFront;

            while(otherIterator != nullptr){
                addQueue(otherIterator->info);
                otherIterator = otherIterator->link;
            }
        }
        ~linkedQueueType(){
            initializeQueue();
        }
    private:
        nodeType<Type> *queueFront = nullptr;
        nodeType<Type> *queueRear = nullptr;
};



int main(){
    linkedQueueType<int> queue;
    for(int i = -10; i < 0; i++){
        queue.addQueue(i);
    }
    
    linkedQueueType<int> otherQueue = queue;

    std::cout<< "This is your queue: " << std::endl;

    while(!queue.isEmptyQueue()){
        std::cout << queue.front() << std::endl;
        queue.deleteQueue();
    }

    std::cout << "This is the queue which was copied from the first queue." << std::endl;

    while(!otherQueue.isEmptyQueue()){
        std::cout << otherQueue.front() << std::endl;
        otherQueue.deleteQueue();
    }
    return 0;
}