#include <iostream>
#include <algorithm>

using namespace std;

bool isMaxHeap(int arr[], int N) {
    for (int i = 0; i <= (N / 2) - 1; i++) {
        int l = 2 * i + 1;
        if (l < N && arr[i] < arr[l]) {
            return false;
        }

        int r = 2 * i + 2;
        if (r < N && arr[i] < arr[r]) {
            return false;
        }
    }
    return true;
}

void maxHeapify(int arr[], int N, int i) {
    int largest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;

    if (l < N && arr[l] > arr[largest])
        largest = l;

    if (r < N && arr[r] > arr[largest])
        largest = r;

    if (largest != i) {
        swap(arr[i], arr[largest]);
        maxHeapify(arr, N, largest);
    }
}

void sort_ascending(int arr[], int N) {
    for (int i = N - 1; i > 0; i--) {
        swap(arr[0], arr[i]);
        maxHeapify(arr, i, 0);
    }
}

void print(int arr[], int N) {
    for (int i = 0; i < N; ++i)
        cout << arr[i] << " ";
    cout << "\n";
}

int main() {
    int arr1[] = {8, 7, 6, 5, 4};
    int N1 = 5;

    cout << "Array 1: ";
    print(arr1, N1);
    if (isMaxHeap(arr1, N1)) {
        cout << "Array 1 is a Max Heap.\n";
        sort_ascending(arr1, N1);
        cout << "Array 1 sorted (ascending): ";
        print(arr1, N1);
    } else {
        cout << "Array 1 is not a Max Heap.\n";
    }

    cout << "---\n";

    int arr2[] = {1, 2, 3, 4, 5};
    int N2 = 5;

    cout << "Array 2: ";
    print(arr2, N2);
    if (isMaxHeap(arr2, N2)) {
        cout << "Array 2 is a Max Heap.\n";
    } else {
        cout << "Array 2 is not a Max Heap.\n";
    }

    return 0;
}
