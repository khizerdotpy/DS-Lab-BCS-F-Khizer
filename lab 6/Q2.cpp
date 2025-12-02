/* Task 2 – Stack with Linked List
Implement a stack using linked lists. Demonstrate its use with a real-life example (e.g., browser history navigation). */

#include <iostream>
using namespace std;

class Node {
public:
    string data;
    Node *next;

    Node(string val) : data(val), next(nullptr) {}
};

class Stack {
    Node *top;
    int size;

public:
    Stack() : top(nullptr), size(0) {}

    void push(string val){
        Node *newNode = new Node(val);
        newNode->next = top;
        top = newNode;
        size++;
        cout << val << " has been pushed into the stack" << endl;
    }

    void pop(){
        if(size == 0){
            cout << "Stack underflow! No elements present in the stack to be popped" << endl;
            return;
        }

        string x = top->data;
        Node *delNode = top;
        top = top->next;
        delete delNode;
        size--;
        cout << x << " has been popped from the stack" << endl;
    }

    void peek() const {
        if(size == 0){
            cout << "Stack is empty! Nothing to peek" << endl;
            return;
        }

        cout << "Top element of the stack: " << top->data << endl;
    }

    void getSize() const {
        cout << "Current size of the stack: " << size << endl;
    }

    void display() const {
        if(size == 0){
            cout << "Stack is empty!" << endl;
            return;
        }

        Node *curr = top;
        cout << "Contents of the stack (top to bottom): " << endl;
        while(curr != nullptr){
            cout << curr->data << " => ";
            curr = curr->next;
        }
        cout << "THE END" << endl;
    }

    ~Stack(){
        Node *curr = top;
        while(curr != nullptr){
            Node *delNode = curr;
            curr = curr->next;
            delete delNode;
        }
    }
};

int main(){
    Stack s;

    s.getSize();
    s.push("Page 1");
    s.push("Page 2");
    s.getSize();
    s.peek();
    cout << endl;

    s.push("Page 3");
    s.push("Page 4");
    s.pop();
    s.getSize();
    s.peek();
    cout << endl;

    s.push("Page 5");
    s.push("Page 6");
    s.peek();
    s.getSize();
    s.display();

    return 0;
}
