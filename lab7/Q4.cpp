#include <iostream>
#include <string>
using namespace std;

class Product
{
public:
    string name;
    double price;
    string description;
    bool available;

    Product(const string &n, double p, const string &d, bool a) : name(n), price(p), description(d), available(a) {}

    void display() const
    {
        cout << name << " - $" << price;
        if (available)
            cout << " | In stock" << endl;
        else
            cout << " | Out of stock" << endl;
    }
};

int partition(Product arr[], int low, int high)
{
    int i = low, j = high;
    Product pivot = arr[low];
    while (i < j)
    {
        while (i <= high - 1 && arr[i].price <= pivot.price)
            i++;
        while (j >= low + 1 && arr[j].price > pivot.price)
            j--;

        if (i < j)
            swap(arr[i], arr[j]);
    }

    swap(arr[low], arr[j]);
    return j;
}

void quickSort(Product arr[], int start, int end)
{
    if (start >= end)
        return;

    int partitionIndex = partition(arr, start, end);
    quickSort(arr, start, partitionIndex - 1);
    quickSort(arr, partitionIndex + 1, end);
}

int main()
{
    const int size = 3;
    Product products[size] = {
        Product("Product 1", 10.99, "This is product 1.", true),
        Product("Product 2", 5.99, "This is product 2.", false),
        Product("Product 3", 2.99, "This is product 3.", true)
    };

    quickSort(products, 0, size - 1);

    cout << "Products sorted by price:" << endl;
    for (int i = 0; i < size; ++i)
    {
        products[i].display();
    }

    return 0;
}
