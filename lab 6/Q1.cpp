/* Task 1 – Basic Stack Implementation
    Implement a stack using arrays. Support the following operations:
    1. Push an element
    2. Pop an element
    3. Peek (top element)
    4. Display stack contents */

#include <iostream>
using namespace std;

#define MAX 50

class Stack {
    int arr[MAX];
    int top;

public:
    Stack() : top(-1) {}

    void push(int val){
        if(top >= MAX - 1){
            cout << "Stack overflow! Cannot push any further elements" << endl;
            return;
        }

        arr[++top] = val;
        cout << val << " has been pushed into the stack" << endl;
    }

    void pop(){
        if(top == -1){
            cout << "Stack underflow! No elements present in the stack to be popped" << endl;
            return;
        }

        int x = arr[top];
        top--;
        cout << x << " has been popped from the stack" << endl;
    }

    void peek() const {
        if(top == -1){
            cout << "Stack is empty! Nothing to peek" << endl;
            return;
        }

        cout << "Top element of the stack: " << arr[top] << endl;
    }

    void display() const {
        if(top == -1){
            cout << "Stack is empty!" << endl;
            return;
        }

        cout << "Contents of stack (top to bottom): ";
        for(int i = top; i >= 0; i--){
            cout << arr[i] << " ";
        }
        cout << endl;
    }

    void getSize() const {
        cout << "Current size of the stack: " << top + 1 << endl;
    }

    ~Stack() {}
};

int main(){
    Stack s;

    s.getSize();
    s.push(5);
    s.push(10);
    s.getSize();
    s.peek();
    cout << endl;

    s.push(15);
    s.push(20);
    s.pop();
    s.getSize();
    s.peek();
    cout << endl;

    s.push(30);
    s.push(40);
    s.peek();
    s.getSize();
    s.display();

    return 0;
}
