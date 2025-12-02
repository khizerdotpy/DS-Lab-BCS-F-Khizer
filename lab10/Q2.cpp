#include <iostream>
using namespace std;

int getParentIndex(int idx)
{
    return (idx - 1) / 2;
}

int getLeftChildIndex(int idx)
{
    return 2 * idx + 1;
}

int getRightChildIndex(int idx)
{
    return 2 * idx + 2;
}

bool checkMaxHeap(int heapArr[], int size)
{
    for (int i = 0; i <= (size / 2) - 1; i++)
    {
        int leftIdx = getLeftChildIndex(i);
        int rightIdx = getRightChildIndex(i);

        if (leftIdx < size && heapArr[i] < heapArr[leftIdx])
            return false;

        if (rightIdx < size && heapArr[i] < heapArr[rightIdx])
            return false;
    }
    return true;
}

void heapify(int heapArr[], int size, int index)
{
    int largest = index;
    int leftIdx = getLeftChildIndex(index);
    int rightIdx = getRightChildIndex(index);

    if (leftIdx < size && heapArr[leftIdx] > heapArr[largest])
        largest = leftIdx;

    if (rightIdx < size && heapArr[rightIdx] > heapArr[largest])
        largest = rightIdx;

    if (largest != index)
    {
        swap(heapArr[index], heapArr[largest]);
        heapify(heapArr, size, largest);
    }
}

void buildMaxHeap(int heapArr[], int size)
{
    for (int i = (size / 2) - 1; i >= 0; i--)
        heapify(heapArr, size, i);
}

void heapSort(int heapArr[], int size)
{
    buildMaxHeap(heapArr, size);

    for (int i = size - 1; i > 0; i--)
    {
        swap(heapArr[0], heapArr[i]);
        heapify(heapArr, i, 0);
    }
}

void displayArray(int arr[], int size)
{
    for (int i = 0; i < size; i++)
        cout << arr[i] << " ";
    cout << endl;
}

int main()
{
    int heapArr[7] = {40, 25, 35, 10, 20, 30, 15};
    int size = 7;

    cout << "Is it a Max Heap? " << (checkMaxHeap(heapArr, size) ? "Yes" : "No") << endl;

    cout << "\n---------------- Displaying Original Array ----------------\n";
    displayArray(heapArr, size);

    heapSort(heapArr, size);

    cout << "\n---------------- Displaying Array after Heap Sort in Ascending Order ----------------\n";
    displayArray(heapArr, size);

    return 0;
}
