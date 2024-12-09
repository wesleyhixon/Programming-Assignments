#pragma once

#include "People.h"
#include <vector>

enum taskType{
    TAKE_ORDER,
    MAKE_ORDER,
    DELIVER_ORDER
};

class TaskManager{
private:
    vector<Task> taskQueue;
public:
    void queueTask(Task task);
    void incrementTasks();
};


class Task{
private:
    taskType type;
    int duration;
    menuItem order;
    Employee* assignedEmployee;
    Customer* assignedCustomer = nullptr;
public:
    Task(taskType typeInput, int durationInput, menuItem orderInput, Employee* employeeInput, Customer* customerInput = nullptr);
    ~Task();
};

