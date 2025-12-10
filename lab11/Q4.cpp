#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

struct PairData {
    int a;
    int b;
};

void findPairs(vector<int> &arr) {
    unordered_map<int, PairData> sumMap;

    int n = arr.size();

    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            int sum = arr[i] + arr[j];

            if (sumMap.find(sum) != sumMap.end())
            {
                PairData prev = sumMap[sum];

                if (prev.a != arr[i] && prev.a != arr[j] &&
                    prev.b != arr[i] && prev.b != arr[j])
                {
                    cout << "(" << prev.a << " + " << prev.b << ") = ("
                         << arr[i] << " + " << arr[j] << ")" << endl;
                    return;
                }
            }
            else
            {
                sumMap[sum] = {arr[i], arr[j]};
            }
        }
    }

    cout << "No Pairs Found!" << endl;
}

int main()
{
    vector<int> arr1 = {3, 4, 7, 1, 2, 9, 8};
    vector<int> arr2 = {3, 4, 7, 1, 12, 9};
    vector<int> arr3 = {65, 30, 7, 90, 1, 9, 8};

    cout << "Test 1: ";
    findPairs(arr1);

    cout << "Test 2: ";
    findPairs(arr2);

    cout << "Test 3: ";
    findPairs(arr3);

    return 0;
}
