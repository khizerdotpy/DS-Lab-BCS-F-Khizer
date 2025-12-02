#include <iostream>
using namespace std;

int getParent(int i)
{
    return (i - 1) / 2;
}

int getLeft(int i)
{
    return 2 * i + 1;
}

int getRight(int i)
{
    return 2 * i + 2;
}

void heapifyDown(int heapArr[], int heapSize, int index)
{
    int largest = index;
    int leftIdx = getLeft(index);
    int rightIdx = getRight(index);

    if (leftIdx < heapSize && heapArr[leftIdx] > heapArr[largest])
        largest = leftIdx;

    if (rightIdx < heapSize && heapArr[rightIdx] > heapArr[largest])
        largest = rightIdx;

    if (largest != index)
    {
        int temp = heapArr[index];
        heapArr[index] = heapArr[largest];
        heapArr[largest] = temp;

        heapifyDown(heapArr, heapSize, largest);
    }
}

void createMaxHeap(int heapArr[], int heapSize)
{
    for (int i = (heapSize / 2) - 1; i >= 0; i--)
    {
        heapifyDown(heapArr, heapSize, i);
    }
}

int findKthLargest(int heapArr[], int heapSize, int k)
{
    createMaxHeap(heapArr, heapSize);

    for (int i = heapSize - 1; i >= heapSize - k + 1; i--)
    {
        int temp = heapArr[0];
        heapArr[0] = heapArr[i];
        heapArr[i] = temp;

        heapifyDown(heapArr, i, 0);
    }

    return heapArr[0];
}

int main()
{
    int n, k;

    cout << "Enter the number of elements: ";
    cin >> n;

    int arr[100];
    cout << "Enter " << n << " integers below:" << endl;

    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];
    }

    cout << "Enter the kth value: ";
    cin >> k;

    cout << "kth largest element is: " << findKthLargest(arr, n, k) << endl;

    return 0;
}
