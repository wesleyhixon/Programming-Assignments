#include <iostream>
#include <iomanip>
#include <thread>
#include <chrono>
#include "Restaurant.h"
#include "Task.h"

using namespace std;


string getStringInput(){
    string userInput;
    
    bool valid = false;
    while(!valid){

        // Clear leftover newline character
        if(cin.peek() == '\n'){ 
            cin.ignore();
        }

        getline(cin, userInput);
        if(!cin){
            cerr << "Please enter a valid input." << endl;
            cin.clear();
            cin.ignore(10000, '\n');
        }else{
            valid = true;
        }
    }

    return userInput;
}

double generateRandomDouble(double lowerBound, double upperBound){
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<double> dis(lowerBound, upperBound);
    return dis(gen);
}


vector<string> randomNames = {
    "Olivia", "Liam", "Emma", "Noah", "Ava", "William", "Sophia", "James", "Isabella", 
    "Benjamin", "Mia", "Lucas", "Charlotte", "Henry", "Amelia", "Alexander", "Evelyn", 
    "Michael", "Harper", "Ethan", "Luna", "Daniel", "Ella", "Matthew", "Scarlett", 
    "David", "Victoria", "Joseph", "Chloe", "Samuel", "Grace", "Jackson", "Zoey", 
    "Sebastian", "Lily", "Aiden", "Penelope", "Caleb", "Hannah", "Mason", "Aria", 
    "Luke", "Audrey", "Nathan", "Nora", "Logan", "Riley", "Dylan", "Violet", "Owen"
};


Restaurant::Restaurant(string inputName): name(inputName){};

// Hires waiters and cooks
void Restaurant::hireEmployees(){
    
    // Calculate number of employees from initial capital and wages
    int numEmployees = 5;
    int maxCooks = numEmployees - 1;
    
    // Get number of cooks
    cout << endl << " ---Hiring Employees--- " << endl;
    cout << "How many cooks would you like to hire? (Maximum " << maxCooks << "): ";

    int numCooks = getNumInput<int>(1, maxCooks);
    
    int maxWaiters = numEmployees - numCooks;

    // Get number of waiters
    cout << "How many waiters would you like to hire? (Maximum " + to_string(maxWaiters) + "): ";
    int numServers = getNumInput<int>(1, maxWaiters);

    cout << endl << " ---Generating Employees--- " << endl;
    cout << "Cooks: " << numCooks << endl;
    cout << "Waiters: " << numServers << endl;
    // Generate cooks
    for(int i = 0; i < numCooks; i++){
        int randomNameIndex = rand() % 50;
        string newName = randomNames[randomNameIndex];

        double randomSpeed = generateRandomDouble(0.5, 1.5);

        Employee newCook(newName, randomSpeed, COOK);

        cooks.push_back(newCook);
    }

    // Generate waiters
    for(int i = 0; i < numServers; i++){
        int randomNameIndex = rand() % 50;
        string newName = randomNames[randomNameIndex];

        double randomSpeed = generateRandomDouble(0.5, 1.5);

        Employee newWaiter(newName, randomSpeed, WAITER);

        waiters.push_back(newWaiter);
    }

    // Employees make 10 bucks an hour
    int hourlyWage = 10;
    double wages = (numCooks + numServers) * hourlyWage;

    budget.setEmployeeWages(wages);

};


// Creates 15 new customers with random names and orders
// Then, adds them to vector
void Restaurant::initializeCustomers(){
    int numCustomers = 20;

    for(int i = 0; i < numCustomers; i++){
        // Gets a random name
        int randomNameIndex = rand() % 50;
        string newName = randomNames[randomNameIndex];

        // Gets a random menu item
        int randomMenuItemIndex = rand() % menu.size();
        menuItem randomMenuItem = menu[randomMenuItemIndex];

        // create new customer with random name and order
        Customer newCustomer(newName, randomMenuItem);

        customers.push_back(newCustomer);
    }
}
void Restaurant::setName(string inputName){name = inputName;}
string Restaurant::getName(){return name;}


void Restaurant::printBudget(){
    cout << endl << " ---Budget--- " << endl;
    cout << budget << endl;
}


// Simulates day
// Day is 5 hours long
// Simulation is updated every 5 minutes, time is 1 minute increments
// Task completion is rounded to nearest 5 minutes


void Restaurant::simulateDay(){
    cout << endl << " ---Beginning Simulation--- " << endl;

    // 1 - 2 customers walk up to counter (25% chance)
    int orderRate = 25;

    int hours = 5;
    int minutes = hours * 60;

    for(int time = 0; time < minutes; time += 5){

        // First, update queue
        vector<Task> newTasks = manager.updateQueue();

        // Assign employees to new tasks
        for(auto itr = newTasks.begin(); itr != newTasks.end();){
            Employee* freeEmployee;

            auto newTask = *itr;

            if(newTask.getType() == DELIVER_ORDER){
                freeEmployee = getFreeEmployee(waiters);
            }
            else{
                freeEmployee = getFreeEmployee(cooks);
            }

            // If no free employees for this task, skip it
            if(freeEmployee == nullptr){
                itr++;
                continue;
            }

            newTask.assignEmployee(freeEmployee);
            manager.queueTask(newTask);
            
            newTasks.erase(itr);
        }

        
        // 25% chance customer orders
        bool customerOrders = (rand() % 100) < orderRate;

        // Adds customers to the line for ordering
        if(customerOrders){
            int maxCustomers = 2;
            int numCustomers = (rand() % maxCustomers) + 1;
            int customersAdded = 0;
            for(auto itr = customers.begin(); itr != customers.end(); itr++){
                if(customersAdded == numCustomers){
                    break;
                }
                // If customer is being served, skip them
                if(itr->getBeingServedStatus() == true){
                    continue;
                }

                // Convert iterator to pointer
                Customer* customerPtr = &(*itr);

                // If they aren't being served, add them to the line of customers waiting to be served
                customersWaiting.push_back(customerPtr);
                customersAdded++;
            }
            customerOrders = false;
        }

        // Take customer orders
        for(auto itr = customersWaiting.begin(); itr != customersWaiting.end();){
            Employee* freeWaiter = getFreeEmployee(waiters);
            Customer* customer = *itr;

            // In case there are no free waiters
            if(freeWaiter == nullptr){
                break;
            }

            takeOrder(customer, freeWaiter);
            customersWaiting.erase(itr);
        }

        outputEvents(time);

        // Wait a 1 second between steps
        this_thread::sleep_for(chrono::seconds(1));



    }

    
}

void Restaurant::outputEvents(int time){
    int hour = time / 60;
    int minute = time % 60;

    vector<Task*> takingOrders;
    vector<Task*> cookingOrders;
    vector<Task*> deliveringOrders;

    // Outputting time
    cout << endl << "Time: " << setw(2) << setfill('0') << hour << ":" << setw(2) << setfill('0') << minute << endl;

    this_thread::sleep_for(chrono::milliseconds(500));

    vector<Task> queue = manager.getQueue();

    // Separate the tasks into types
    for(auto itr = queue.begin(); itr != queue.end(); itr++){
        Task* task = &(*itr);

        if(itr->getStatus() == IN_PROGRESS){
            continue;
        }

        switch(itr->getType()){
            case TAKE_ORDER:
                takingOrders.push_back(task);
                break;
            case MAKE_ORDER:
                cookingOrders.push_back(task);
                break;
            case DELIVER_ORDER:
                deliveringOrders.push_back(task);
                break;
        }
    }

    // If no events, don't print anything
    bool noEvents = takingOrders.empty() && cookingOrders.empty() && deliveringOrders.empty();

    if(noEvents){
        return;
    }

    // Print each type

    printEventCategory(takingOrders, TAKE_ORDER);
    printEventCategory(cookingOrders, MAKE_ORDER);
    printEventCategory(deliveringOrders, DELIVER_ORDER);

    return;
}

void Restaurant::printEventCategory(vector<Task*> category, taskType type){
    string categoryText;

    switch(type){
        case TAKE_ORDER:
            categoryText = " - Taking Orders: ";
            break;
        case MAKE_ORDER:
            categoryText = " - Making Orders: ";
            break;
        case DELIVER_ORDER:
            categoryText = " - Delivering Orders: ";
            break;
    }


    if(category.empty() == false){
        this_thread::sleep_for(chrono::milliseconds(200));
        cout << endl << categoryText << endl;
    }
    for(auto itr = category.begin(); itr != category.end(); itr++){
        this_thread::sleep_for(chrono::milliseconds(200));
        Task* task = *itr;
        cout << "  - " << *task << endl;
    }
}

// Creates menu of 1 - 5 items with user input
void Restaurant::setMenu(){
    cout << endl << " ---Menu Creation--- " << endl;
    cout << "Now, create 1 - 5 menu items for your menu." << endl;

    cout << "How many items would you like to create? ";

    int numMenuItems = getNumInput<int>(1,5);

    for(int i = 0; i < numMenuItems; i++){
        cout << endl << "Enter a name for menu item number " << i + 1 << ": ";
        string itemName = getStringInput();

        cout << "Enter a price for this item between 5 and 20 dollars: ";
        double itemCost = getNumInput<double>(5, 20);

        cout << "Enter how many minutes (between 10 and 30) it takes to make this item: ";
        int timeToMake = getNumInput<int>(10,30);

        menuItem newMenuItem;
        newMenuItem.itemName = itemName;
        newMenuItem.itemPrice = itemCost;
        newMenuItem.ingredientCost = itemCost * .30;    // Ingredient cost is 30% of price
        newMenuItem.timeToMake = timeToMake;

        // Adds menu item to menu
        menu.push_back(newMenuItem);
    }

    cout << "Here is your new menu:" << endl;
    for(auto itr = menu.begin(); itr != menu.end(); itr++){
        int itemNum = distance(menu.begin(), itr) + 1;

        cout << itemNum << ". " << itr->itemName << endl;
        cout << "   - Cost: " << itr->itemPrice << endl;
        cout << "   - Ingredient Cost: " << itr->ingredientCost << endl;
        cout << "   - Time to make: " << itr->timeToMake << " minutes" << endl;
    }
}


// Starts a customer's order
void Restaurant::takeOrder(Customer* assignedCustomer, Employee* assignedEmployee){
    menuItem order = assignedCustomer->getOrder();

    Task newOrder(TAKE_ORDER, order, assignedEmployee, assignedCustomer);

    budget.addRevenue(order.itemPrice);
    budget.addFoodCost(order.ingredientCost);

    manager.queueTask(newOrder);
}


// Returns a free employee from an employee vector
Employee* Restaurant::getFreeEmployee(vector<Employee>& employees){
    // Iterates through employees to find a free employee
    for(auto& employee: employees){
        if(employee.getBusyStatus() == false){
            Employee* employeePtr = &employee;
            return employeePtr;
        }
    }
    // If none found, return nullptr
    return nullptr;

}

