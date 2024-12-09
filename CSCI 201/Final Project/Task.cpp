#include "People.h"
#include "Task.h"
#include <vector>

enum taskType{
    PLACE_ORDER,
    MAKE_ORDER,
    DELIVER_ORDER
};

class TaskManager{
private:
    vector<Task> taskQueue;
public:
    void queueTask(taskType type, int duration, Employee* employee, Customer* customer = nullptr);
    void updateQueue();
};




Task::Task(taskType typeInput, int durationInput, menuItem orderInput, Employee* employeeInput, Customer* customerInput = nullptr): 
type(typeInput), 
duration(durationInput),
order(orderInput),
assignedEmployee(employeeInput),
assignedCustomer(customerInput)
{
assignedEmployee->toggleBusyStatus();

if(type == PLACE_ORDER){
    assignedCustomer->placeOrder();
}
if(type == MAKE_ORDER){

}
}