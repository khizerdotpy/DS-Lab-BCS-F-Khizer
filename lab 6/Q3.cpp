/* Task 3 – Simple Queue Implementation
Implement a linear queue using arrays with the following operations:
1. Enqueue
2. Dequeue
3. Display queue contents
4. Check if queue is empty/full */

#include <iostream>
using namespace std;

#define MAX 50

class Queue {
    int arr[MAX];
    int start, end;

public:
    Queue() : start(-1), end(-1) {}

    void enqueue(int val){
        if(isFull()){
            cout << "Queue overflow! Cannot enqueue anymore elements" << endl;
            return;
        }

        if(start == -1) start++;
        arr[++end] = val;
        cout << val << " has been enqueued into the queue" << endl;
    }

    void dequeue(){
        if(isEmpty()){
            cout << "Queue underflow! No elements present in the queue to be dequeued" << endl;
            return;
        }

        int x = arr[start];

        if(start == end){
            start = -1;
            end = -1;
        }
        else{
            start++;
        }

        cout << x << " has been dequeued from the queue" << endl;
    }

    void peek() const {
        if(isEmpty()){
            cout << "Queue is empty! Nothing to peek" << endl;
            return;
        }

        cout << "Starting element of the queue: " << arr[start] << endl;
    }

    void getSize() const {
        if(isEmpty()){
            cout << "Current size of the queue: 0" << endl;
        }
        else{
            cout << "Current size of the queue: " << (end - start + 1) << endl;
        }
    }

    bool isEmpty() const {
        return (start == -1 || start > end);
    }

    bool isFull() const {
        return (end == MAX - 1);
    }

    void display() const {
        if(isEmpty()){
            cout << "Queue is empty!" << endl;
            return;
        }

        cout << "Contents of the queue (start to end): ";
        for(int i = start; i <= end; i++){
            cout << arr[i] << " ";
        }
        cout << endl;
    }

    ~Queue() {}
};

int main(){
    Queue q;

    q.getSize();
    cout << "Is queue empty? " << (q.isEmpty() ? "Yes" : "No") << endl;
    q.enqueue(5);
    q.enqueue(10);
    q.getSize();
    q.peek();
    cout << endl;

    q.enqueue(15);
    q.enqueue(20);
    q.dequeue();
    q.getSize();
    q.peek();
    cout << endl;

    q.enqueue(30);
    q.enqueue(40);
    q.peek();
    q.getSize();
    cout << "Is queue empty? " << (q.isEmpty() ? "Yes" : "No") << endl;
    q.display();

    return 0;
}
