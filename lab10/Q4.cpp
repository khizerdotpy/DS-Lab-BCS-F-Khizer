#include <iostream>
using namespace std;

int getLeftChild(int index)
{
    return 2 * index + 1;
}

int getRightChild(int index)
{
    return 2 * index + 2;
}

void maxHeapify(int heap[], int size, int index)
{

    int largest = index;
    int leftChild = getLeftChild(index);
    int rightChild = getRightChild(index);

    if (leftChild < size && heap[leftChild] > heap[largest])
        largest = leftChild;

    if (rightChild < size && heap[rightChild] > heap[largest])
        largest = rightChild;

    if (largest != index)
    {
        int temp = heap[index];
        heap[index] = heap[largest];
        heap[largest] = temp;

        maxHeapify(heap, size, largest);
    }
}

void buildMaxHeap(int heap[], int size)
{

    for (int i = (size / 2) - 1; i >= 0; i--)
    {
        maxHeapify(heap, size, i);
    }
}

int main()
{
    int n;
    int heapArr[100];

    cout << "Enter the number of elements: ";
    cin >> n;

    cout << "Enter the heap elements below:" << endl;
    for (int i = 0; i < n; i++)
    {
        cin >> heapArr[i];
    }

    buildMaxHeap(heapArr, n);

    cout << "Converted Max Heap: ";
    for (int i = 0; i < n; i++)
    {
        cout << heapArr[i] << " ";
    }

    return 0;
}
