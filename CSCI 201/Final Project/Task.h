#pragma once

#include "People.h"
#include <vector>

enum taskType{
    TAKE_ORDER,
    MAKE_ORDER,
    DELIVER_ORDER
};

enum taskStatus{
    WAITING,
    STARTED,
    IN_PROGRESS,
    COMPLETE,
    READY_FOR_DELETION
};

class Task{
private:
    taskType type;
    taskStatus status = WAITING;
    int duration;
    int timeElapsed = 0;
    menuItem order;
    Employee* assignedEmployee;
    Customer* assignedCustomer = nullptr;
public:
    Task(taskType typeInput, menuItem orderInput, Employee* employeeInput = nullptr, Customer* customerInput = nullptr);
    void assignEmployee(Employee* inputEmployee);
    Customer* getCustomer();
    Employee* getEmployee();
    menuItem getOrder();
    taskType getType();
    taskStatus getStatus();
    void setStatus(taskStatus inputStatus);
    void completeTask();
    void updateTask();
    string toString();

    friend ostream& operator<<(ostream& os, Task inputTask);
};

class TaskManager{
private:
    vector<Task> taskQueue;
public:
    void queueTask(Task task);
    vector<Task> updateQueue();
    vector<Task> getQueue();
};

