#include "People.h"
#include "Task.h"
#include <vector>
#include <cmath>
#include <iostream>

using namespace std;


// Adds task to task queue
void TaskManager::queueTask(Task task){
    taskQueue.push_back(task);
}

// Updates task queue and returns a vector of new tasks to be assigned to an employee
vector<Task> TaskManager::updateQueue(){
    vector<Task> newTasks;

    // Iterate through task queue
    for(auto itr = taskQueue.begin(); itr != taskQueue.end();){

        // Check if task completed and update the task
        itr->updateTask();
        
        taskStatus status = itr->getStatus();

        // Erase 
        if(status == READY_FOR_DELETION){
            itr = taskQueue.erase(itr);
            continue;
        }

        // If task not completed, go to next task
        if(status != COMPLETE){
            itr++;
            continue;
        }
        

        // If task is completed, start building the next task
        taskType oldTaskType = itr->getType();
        taskType newTaskType;

        // Create new task type based on previous
        switch(oldTaskType){
            case taskType::TAKE_ORDER:
                newTaskType = taskType::MAKE_ORDER;
                break;
            case taskType::MAKE_ORDER:
                newTaskType = taskType::DELIVER_ORDER;
                break;
        }
        
        // If task still has steps, create a new task which is next in sequence
        // Otherwise, just mark it for deletion
        if(oldTaskType == TAKE_ORDER || oldTaskType == MAKE_ORDER){
            Customer* customer = itr->getCustomer();
            menuItem order = customer->getOrder();
            
            Task newTask(newTaskType, order, nullptr, customer);

            newTasks.push_back(newTask);
            itr->setStatus(READY_FOR_DELETION);
        }
        else if(oldTaskType == DELIVER_ORDER){
            itr->setStatus(READY_FOR_DELETION);
        }
        
        itr++;
        
    }

    return newTasks;
}

vector<Task> TaskManager::getQueue(){return taskQueue;}

// Task constructor, assigns employee and sets duration if employee is input
Task::Task(taskType typeInput, menuItem orderInput, Employee* employeeInput, Customer* customerInput): 
type(typeInput), 
order(orderInput),
assignedEmployee(employeeInput),
assignedCustomer(customerInput)
{
    if(assignedEmployee == nullptr){
        return;
    }
    // Assign employee and adjust duration
    else{
        assignEmployee(employeeInput);
    }

}

// Updates time elapsed and returns true if task completed
void Task::updateTask(){
    timeElapsed += 5;

    // Updates status
    if(status == STARTED){
        status = IN_PROGRESS;
    }

    if(timeElapsed == duration){
        completeTask();
    }
}

// Updates employee and customer status
void Task::completeTask(){
    assignedEmployee->toggleBusyStatus();
    status = COMPLETE;

    // Change customer status
    if(type == TAKE_ORDER){
        assignedCustomer->placeOrder();
    }
    if(type == DELIVER_ORDER){
        assignedCustomer->receiveOrder();
    }

    return;
}

// Tasktype
taskType Task::getType(){return type;}

// Status operations
taskStatus Task::getStatus(){return status;}
void Task::setStatus(taskStatus inputStatus){status = inputStatus;}

// Order
menuItem Task::getOrder(){return order;}

// Get employee and customer
Employee* Task::getEmployee(){return assignedEmployee;}
Customer* Task::getCustomer(){return assignedCustomer;}

// Assigns employee and adjusts duration
void Task::assignEmployee(Employee* inputEmployee){

    assignedEmployee = inputEmployee;
    assignedEmployee->toggleBusyStatus();
    status = STARTED;

    adjustDuration();

    // Change the customer's status to being served, if not already
    if(assignedCustomer->getBeingServedStatus() == false){
        assignedCustomer->setBeingServed();
    }
    
}

void Task::adjustDuration(){
    // Default durations of tasks
    int durationPlaceOrder = 5;
    int durationMakeOrder = order.timeToMake;   // Depends on menu item
    int durationDeliverOrder = 10;

    // Getting employee speed and cooking speed
    double employeeSpeed = assignedEmployee->getWorkingSpeed();
    double adjustedDuration;

    // Adjusting duration
    if(type == TAKE_ORDER || type == DELIVER_ORDER){
        adjustedDuration = durationPlaceOrder * employeeSpeed;
    }
    else if(type == MAKE_ORDER){
        adjustedDuration = durationMakeOrder * employeeSpeed;
    }

    // This will round the duration to nearest multiple of 5
    int roundedDuration = round(adjustedDuration / 5) * 5;
    duration = roundedDuration;

}

string Task::toString(){
    string statusText;
    string taskString;
    string employeeString;
    string taskTag;
    
    employeeString = assignedEmployee->getName();

    

    switch(status){
            case WAITING:
                return string("Error: No Employee Assigned");
            case STARTED:
                statusText = " has started ";
                taskTag = "[ACTION] ";
                break;
            case IN_PROGRESS:
                statusText = " is still ";
                break;
            case COMPLETE: case READY_FOR_DELETION:
                statusText = " has finished ";
                taskTag = "[COMPLETE] ";
                break;
            
        }

        switch(type){
            case TAKE_ORDER:
                employeeString += " (Waiter)";
                statusText += "taking ";
                break;
            case MAKE_ORDER:
                employeeString += " (Cook)";
                statusText += "making ";
                break;
            case DELIVER_ORDER:
                employeeString += " (Waiter)";
                statusText += "delivering ";
                break;
        }

    taskString = taskTag + employeeString + statusText + assignedCustomer->getName() + "'s order of " + order.itemName;
    return taskString;
}

ostream& operator<<(ostream& os, Task inputTask){
    os << inputTask.toString();
    return os;
}