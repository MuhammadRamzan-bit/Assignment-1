#include <iostream>
#include <string>

using namespace std;

struct Task {
    int taskId;
    string description;
    int priority;
    Task* next;
};

struct TaskList {
private:
    Task* head;

public:
    TaskList() {
        head = NULL;
    }

    ~TaskList() {
        while (head) {
            Task* temp = head;
            head = head->next;
            delete temp;
        }
    }
	// Method to create a new task node in linked list
    void addTask(int id, string desc, int priority) {
        Task* newTask = new Task;
        newTask->taskId = id;
        newTask->description = desc;
        newTask->priority = priority;
        newTask->next = NULL;
		// Insert the new task at the correct position based on priority
        if (head == NULL || head->priority < priority) {
            newTask->next = head;
            head = newTask;
        } else {
            Task* current = head;
            while (current->next != NULL && current->next->priority <= priority) {
                current = current->next;
            }
            newTask->next = current->next;
            current->next = newTask;
        }
    }
	//Method to remove the highest priority task of the linked list 
    void removeHighestPriorityTask() {
        if (head == NULL) {
            cout << "No tasks to remove." << endl;
            return;
        }
        Task* removed_task = head;
        head = head->next;
        cout << "Removed task with ID: " << removed_task->taskId << ", Description: " << removed_task->description << endl;
        delete removed_task;
    }
	//Method to remove a task with a specific ID from linked list
    void removeTaskById(int id) {
        if (head == NULL) {
            cout << "No tasks to remove." << endl;
            return;
        }

        if (head->taskId == id) {
            Task* removed_task = head;
            head = head->next;
            cout << "Removed task with ID: " << id << endl;
            delete removed_task;
            return;
        }

        Task* current = head;
        while (current->next != NULL && current->next->taskId != id) {
            current = current->next;
        }

        if (current->next == NULL) {
            cout << "Task with ID: " << id << " not found." << endl;
        } else {
            Task* removed_task = current->next;
            current->next = current->next->next;
            cout << "Removed task with ID: " << id << endl;
            delete removed_task;
        }
    }
	//Method to print all tasks in the linked list
    void viewTasks() {
        if (head == NULL) {
            cout << "No tasks available." << endl;
            return;
        }
        Task* current = head;
        cout << "Tasks:" << endl;
        while (current) {
            cout << "Task ID: " << current->taskId
                 << ", Description: " << current->description 
                 << ", Priority: " << current->priority << endl;
            current = current->next;
        }
    }
};

int main() {
    TaskList taskList;

    do {
        cout << endl << "Task Management System" << endl;
        cout << "----------------------" << endl;
        cout << "1. Add a new task" << endl;
        cout << "2. View all tasks" << endl;
        cout << "3. Remove the highest priority task" << endl;
        cout << "4. Remove a task by ID" << endl;
        cout << "5. Exit" << endl;
        cout << endl << "Enter your choice: ";
        
        int choice;
        cin >> choice;
		//using switch statement to get the task which will be perform by user
        switch (choice) {
            case 1: {
                int id, priority;
                string desc;

                cout << "Enter task ID: ";
                cin >> id;
                cout << "Enter task description: ";
                cin.ignore();
                getline(cin, desc);
                cout << "Enter priority: ";
                cin >> priority;

                taskList.addTask(id, desc, priority);
                break;
            }
            //In this case user can view all tasks that are store in linked list
            case 2:
                taskList.viewTasks();
                break;
            //In this case user remove highest priority task from linked list
            case 3:
                taskList.removeHighestPriorityTask();
                break;
            //In this case user can remove task from linked list by task id
            case 4: {
                int id;
                cout << "Enter task ID to remove: ";
                cin >> id;
                taskList.removeTaskById(id);
                break;
            }
            //In this case user can exit the system
            case 5:
                cout << "Exiting..." << endl;
                return 0;
            //If user give wrong input     
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (true);

    return 0;
}
