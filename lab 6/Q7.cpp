/* Task 7 – Application of Stack & Queue (Advanced)
Design a job scheduling system where:
1. Processes (with IDs & priorities) arrive and are stored in a queue.
2. Execution order is determined using a stack (LIFO execution of high-priority tasks).
3. Demonstrate how both queue (arrival order) and stack (execution handling) are
combined. */

#include <iostream>
using namespace std;

const int MAX = 100;

class Queue {
    int arr[MAX];
    int front, rear;
public:
    Queue() { front = rear = -1; }

    bool isEmpty() { return (front == -1 || front > rear); }
    bool isFull() { return rear == MAX - 1; }

    void enqueue(int value) {
        if (isFull()) {
            cout << "Queue Overflow!\n";
            return;
        }
        if (front == -1) front = 0;
        arr[++rear] = value;
    }

    int dequeue() {
        if (isEmpty()) {
            cout << "Queue Underflow!\n";
            return -1;
        }
        return arr[front++];
    }

    int peek() {
        if (isEmpty()) return -1;
        return arr[front];
    }

    void reset() { front = rear = -1; }

    void display() {
        if (isEmpty()) {
            cout << "Queue is empty\n";
            return;
        }
        cout << "Queue: ";
        for (int i = front; i <= rear; i++)
            cout << arr[i] << " ";
        cout << endl;
    }

    friend class JobScheduler; // allow access for scheduler
};

class Stack {
    int arr[MAX];
    int top;
public:
    Stack() { top = -1; }

    bool isEmpty() { return (top == -1); }
    bool isFull() { return (top == MAX - 1); }

    void push(int value) {
        if (isFull()) {
            cout << "Stack Overflow!\n";
            return;
        }
        arr[++top] = value;
    }

    int pop() {
        if (isEmpty()) {
            cout << "Stack Underflow!\n";
            return -1;
        }
        return arr[top--];
    }

    void display() {
        if (isEmpty()) {
            cout << "Stack is empty\n";
            return;
        }
        cout << "Stack: ";
        for (int i = top; i >= 0; i--)
            cout << arr[i] << " ";
        cout << endl;
    }
};

struct Process {
    int id;
    int priority;
};

class JobScheduler {
    Queue arrivalQueue;
    Stack executionStack;

public:
    void run() {
        cout << "=== Job Scheduling System ===\n\n";

        Process processes[] = {
            {101, 2}, {102, 1}, {103, 3}, {104, 2}, {105, 3}
        };

        cout << "1. Processes arriving (stored in queue):\n";
        for (int i = 0; i < 5; i++) {
            arrivalQueue.enqueue(processes[i].id * 10 + processes[i].priority);
            cout << "Process " << processes[i].id
                 << " (Priority " << processes[i].priority << ") arrived\n";
        }
        arrivalQueue.display();

        cout << "\n2. Transferring high priority tasks to stack:\n";
        int highest_priority = 0;

        // find highest priority
        for (int i = arrivalQueue.front; i <= arrivalQueue.rear; i++) {
            int process_data = arrivalQueue.arr[i];
            int priority = process_data % 10;
            if (priority > highest_priority)
                highest_priority = priority;
        }
        cout << "Highest priority found: " << highest_priority << endl;

        Queue remainingQueue;

        while (!arrivalQueue.isEmpty()) {
            int process_data = arrivalQueue.dequeue();
            int processId = process_data / 10;
            int priority = process_data % 10;

            if (priority == highest_priority) {
                executionStack.push(process_data);
                cout << "High priority process " << processId << " pushed to stack\n";
            } else {
                remainingQueue.enqueue(process_data);
            }
        }

        cout << "\n3. Execution order (LIFO) from stack:\n";
        executionStack.display();

        cout << "\n4. Executing processes:\n";
        while (!executionStack.isEmpty()) {
            int process_data = executionStack.pop();
            int processId = process_data / 10;
            int priority = process_data % 10;
            cout << "Executing Process " << processId << " (Priority " << priority << ")\n";
        }

        cout << "\n5. Remaining lower priority processes in queue:\n";
        remainingQueue.display();

        cout << "\n=== End of Simulation ===\n";
    }
};

int main() {
    JobScheduler js;
    js.run();
    return 0;
}
