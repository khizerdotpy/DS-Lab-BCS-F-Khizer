#include <iostream>
#include <algorithm>

using namespace std;

void minHeapify(int arr[], int N, int i) {
    int smallest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;

    if (l < N && arr[l] < arr[smallest])
        smallest = l;

    if (r < N && arr[r] < arr[smallest])
        smallest = r;

    if (smallest != i) {
        swap(arr[i], arr[smallest]);
        minHeapify(arr, N, smallest);
    }
}

int kthLargest(int arr[], int N, int K) {
    if (K > N || K <= 0) return -1; 

    int min_heap[K];

    for (int i = 0; i < K; i++) {
        min_heap[i] = arr[i];
    }

    for (int i = (K / 2) - 1; i >= 0; i--) {
        minHeapify(min_heap, K, i);
    }

    for (int i = K; i < N; i++) {
        if (arr[i] > min_heap[0]) {
            min_heap[0] = arr[i];
            minHeapify(min_heap, K, 0);
        }
    }
    return min_heap[0];
}

int main() {
    int arr1[] = {1, 23, 12, 9, 30, 2, 50};
    int N1 = 7;
    int K1 = 3;

    cout << "Input 1: {1, 23, 12, 9, 30, 2, 50}, K = 3. Expected: 23\n";
    int result1 = kthLargest(arr1, N1, K1);
    cout << "Result: " << result1 << "\n";

    cout << "---\n";
    
    int arr2[] = {12, 3, 5, 7, 19};
    int N2 = 5;
    int K2 = 2;

    cout << "Input 2: {12, 3, 5, 7, 19}, K = 2. Expected: 12\n";
    int result2 = kthLargest(arr2, N2, K2);
    cout << "Result: " << result2 << "\n";

    return 0;
}
