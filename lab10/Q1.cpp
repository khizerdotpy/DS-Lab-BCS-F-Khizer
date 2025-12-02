#include <iostream>
using namespace std;

int heapArr[100];
int heapLength = 0;

int getParent(int index)
{
    return (index - 1) / 2;
}
int getLeftChild(int index)
{
    return 2 * index + 1;
}

int getRightChild(int index)
{
    return 2 * index + 2;
}

void heapifyDownwards(int index)
{
    int largestIndex = index;
    int leftIndex = getLeftChild(index);
    int rightIndex = getRightChild(index);

    if (leftIndex < heapLength && heapArr[leftIndex] > heapArr[largestIndex])
        largestIndex = leftIndex;

    if (rightIndex < heapLength && heapArr[rightIndex] > heapArr[largestIndex])
        largestIndex = rightIndex;

    if (largestIndex != index)
    {
        swap(heapArr[index], heapArr[largestIndex]);
        heapifyDownwards(largestIndex);
    }
}

void heapifyUpwards(int index)
{
    while (index != 0 && heapArr[getParent(index)] < heapArr[index])
    {
        swap(heapArr[index], heapArr[getParent(index)]);
        index = getParent(index);
    }
}

void insertHeap(int value)
{
    heapArr[heapLength] = value;
    heapifyUpwards(heapLength++);
}

void displayHeap()
{
    for (int i = 0; i < heapLength; i++)
        cout << heapArr[i] << " ";
    cout << endl;
}

void updateHeapKey(int index, int newValue)
{
    int oldValue = heapArr[index];
    heapArr[index] = newValue;

    if (newValue > oldValue)
        heapifyUpwards(index);
    else
        heapifyDownwards(index);
}

void deleteHeapKey(int index)
{
    heapArr[index] = heapArr[--heapLength];
    heapifyUpwards(index);
    heapifyDownwards(index);
}

int main()
{
    insertHeap(15);
    insertHeap(22);
    insertHeap(10);
    insertHeap(5);
    insertHeap(18);

    cout << "Initial Max Heap: ";
    displayHeap();

    updateHeapKey(2, 25);
    cout << "Max Heap after Updation of index 2: ";
    displayHeap();

    deleteHeapKey(0);
    cout << "Max Heap after deletion of root: ";
    displayHeap();

    return 0;
}
