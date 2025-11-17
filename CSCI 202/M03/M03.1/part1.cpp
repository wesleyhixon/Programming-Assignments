#include <iostream>
#include <exception>
#include <algorithm>

/* 
Name: queue
Author: Wesley Hixon
Date Last Updated:11/16/2025
Purpose: Create a queue from an array
*/

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
class queueType : public queueADT<Type>{
    public:    
        const queueType<Type>& operator=(const queueType<Type> &other){
            if(this != &other){
                list = new Type[other.maxQueueSize];
                maxQueueSize = other.maxQueueSize;
                queueFront = other.queueFront;
                queueRear = other.queueRear;

                std::copy(other.list, other.list + maxQueueSize, list);
            }

            return *this;
        }
        bool isEmptyQueue() const{
            if(queueFront == queueRear){
                return true;
            }
            else{
                return false;
            }
        }
        bool isFullQueue() const{
            if(queueFront == (queueRear + 1) % maxQueueSize){
                return true;
            }
            else{
                return false;
            }
        }
        void initializeQueue(){
            list = new Type[maxQueueSize];
            queueFront = 0;
            queueRear = 0;
        }
        Type front() const{
            if(isEmptyQueue()) throw(std::runtime_error("Cannot access empty queue."));
            return list[queueFront + 1];
        }
        Type back() const{
            if(isEmptyQueue()) throw(std::runtime_error("Cannot access empty queue."));
            return list[queueRear];
        }
        void addQueue(const Type& element){
            if(isFullQueue()) throw(std::runtime_error("Cannot add to full queue."));
            queueRear = (queueRear + 1) % maxQueueSize;
            list[queueRear] = element;
        }
        void deleteQueue(){
            if(isEmptyQueue()) throw(std::runtime_error("Cannot delete from empty queue."));
            queueFront = (queueFront + 1) % maxQueueSize;
        }
        queueType(int queueSize = 100){
            maxQueueSize = queueSize + 1;
            initializeQueue();
        }
        queueType(const queueType<Type>& other) : 
            maxQueueSize(other.maxQueueSize), 
            queueFront(other.queueFront),
            queueRear(other.queueRear),
            list(new Type[maxQueueSize])
            {
                std::copy(other.list, other.list + maxQueueSize, list);
            }
        ~queueType(){
            delete[] list;
        }
    private:
        int maxQueueSize;
        int queueFront;
        int queueRear;
        Type *list;
};


int main(){
    queueType<int> queue(10);

    int i = 1;
    while(!queue.isFullQueue()){
        queue.addQueue(i);
        i++;
    }

    std::cout << "This is what's in the back of the queue: " << queue.back() << std::endl;

    queueType<int> queue2 = queue;
    std::cout << "This is what's in the queue: " << std::endl;

    while(!queue.isEmptyQueue()){
        std::cout << queue.front() << std::endl;
        queue.deleteQueue();
    }

    std::cout << "This is the second queue that was copied from the first queue: " << std::endl;

    while(!queue2.isEmptyQueue()){
        std::cout << queue2.front() << std::endl;
        queue2.deleteQueue();
    }
    return 0;
}