#include <iostream>
using namespace std;

struct Runner
{
    string name;
    int finishTime;
};

void merge(Runner arr[], int low, int mid, int high)
{
    Runner *temp = new Runner[high - low + 1];
    int left = low, right = mid + 1;
    int idx = 0;
    while (left <= mid && right <= high)
    {
        if (arr[left].finishTime <= arr[right].finishTime)
            temp[idx++] = arr[left++];
        else
            temp[idx++] = arr[right++];
    }

    while (left <= mid)
        temp[idx++] = arr[left++];

    while (right <= high)
        temp[idx++] = arr[right++];

    for (int i = low; i <= high; i++)
        arr[i] = temp[i - low];

    delete[] temp;
}

void mergeSort(Runner arr[], int start, int end)
{
    if (start >= end)
        return;

    int mid = start + (end - start) / 2;
    mergeSort(arr, start, mid);
    mergeSort(arr, mid + 1, end);
    merge(arr, start, mid, end);
}

int main()
{
    const int size = 10;
    Runner runners[size];

    for (int i = 0; i < size; i++)
    {
        cout << "Enter name and finish time for runner " << i + 1 << ": ";
        cin >> runners[i].name >> runners[i].finishTime;
    }

    mergeSort(runners, 0, size - 1);

    cout << "\nTop 5 fastest runners:" << endl;
    for (int i = 0; i < 5; i++)
    {
        cout << i + 1 << ". " << runners[i].name << " - " << runners[i].finishTime << " seconds" << endl;
    }

    return 0;
}
