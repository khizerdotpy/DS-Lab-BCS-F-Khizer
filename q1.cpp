#include <iostream>
#include <algorithm>

using namespace std;

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

void update_key(int arr[], int N, int i, int new_val) {
    if (i >= N || i < 0) return;

    int old_val = arr[i];
    arr[i] = new_val;

    if (new_val > old_val) {
        while (i > 0 && arr[(i - 1) / 2] < arr[i]) {
            int parent = (i - 1) / 2;
            swap(arr[i], arr[parent]);
            i = parent;
        }
    } else if (new_val < old_val) {
        maxHeapify(arr, N, i);
    }
}

int delete_root(int arr[], int& N) {
    if (N <= 0) return -1;

    int root = arr[0];
    arr[0] = arr[N - 1];
    N--;
    
    maxHeapify(arr, N, 0);

    return root;
}

void print(int arr[], int N) {
    for (int i = 0; i < N; ++i)
        cout << arr[i] << " ";
    cout << "\n";
}

int main() {
    int arr[] = {8, 7, 6, 5, 4};
    int N = 5;

    cout << "Initial Max Heap: ";
    print(arr, N);

    update_key(arr, N, 4, 10);
    cout << "After update_key(4, 10): ";
    print(arr, N);

    int del_val = delete_root(arr, N);
    cout << "Deleted element: " << del_val << "\n";
    cout << "Heap after deletion: ";
    print(arr, N);

    return 0;
}
