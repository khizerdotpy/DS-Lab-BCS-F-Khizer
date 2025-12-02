/* Task 4 – Circular Queue
Implement a circular queue using arrays. Handle the following conditions correctly:
1. Enqueue when rear wraps around
2. Dequeue when front moves ahead
3. Prevent overflow when queue is full */

#include <iostream>
using namespace std;

#define MAX 5

class CircularQueue {
    int arr[MAX];
    int start, end;
    int currentSize;

public:
    CircularQueue() : start(-1), end(-1), currentSize(0) {}

    void enqueue(int val){
        if(isFull()){
            cout << "Queue overflow! Cannot enqueue anymore elements into the queue" << endl;
            return;
        }

        if(currentSize == 0){
            start = 0;
            end = 0;
        }
        else{
            end = (end + 1) % MAX;
        }

        arr[end] = val;
        currentSize++;
        cout << val << " has been enqueued into the queue" << endl;
    }

    void dequeue(){
        if(isEmpty()){
            cout << "Queue underflow! No elements present in the queue to be dequeued" << endl;
            return;
        }

        int val = arr[start];
        if(currentSize == 1){
            start = -1;
            end = -1;
        }
        else{
            start = (start + 1) % MAX;
        }
        
        currentSize--;
        cout << val << " has been dequeued from the queue" << endl;
    }

    void peek() const {
        if(isEmpty()){
            cout << "Queue is empty! Nothing to peek" << endl;
            return;
        }

        cout << "Starting element of the queue: " << arr[start] << endl;
    }

    bool isEmpty() const {
        return currentSize == 0;
    }

    bool isFull() const {
        return currentSize == MAX;
    }

    void getSize() const {
        cout << "Current size of the queue: " << currentSize << endl;
    }

    void display() const {
        if(isEmpty()){
            cout << "Queue is empty!" << endl;
            return;
        }

        cout << "Contents of the queue (start to end): ";
        for(int i = 0; i < currentSize; i++){
            cout << arr[(start + i) % MAX] << " ";
        }
        cout << endl;
    }

    ~CircularQueue() {}
};

int main(){
    CircularQueue q;

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
    q.enqueue(50);
    q.peek();
    q.getSize();
    cout << "Is queue empty? " << (q.isEmpty() ? "Yes" : "No") << endl;
    q.display();

    return 0;
}
