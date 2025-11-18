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

void convert_to_max_heap(int arr[], int N) {

    for (int i = (N / 2) - 1; i >= 0; i--) {
        maxHeapify(arr, N, i);
    }
}

void print(int arr[], int N) {
    for (int i = 0; i < N; ++i)
        cout << arr[i] << " ";
    cout << "\n";
}

int main() {
    int arr[] = {3, 5, 9, 6, 8, 20, 10, 12, 18, 9};
    int N = 10;

    cout << "Initial Min Heap array: ";
    print(arr, N);

    convert_to_max_heap(arr, N);

    cout << "Converted Max Heap array. Expected: {20, 18, 10, 12, 9, 9, 3, 5, 6, 8}\n";
    cout << "Result: ";
    print(arr, N);
    
    return 0;
}
