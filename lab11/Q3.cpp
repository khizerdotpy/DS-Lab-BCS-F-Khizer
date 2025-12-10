#include <iostream>
#include <list>
#include <string>
using namespace std;

#define SIZE 50

class Node
{
public:
    string key;
    string value;
    Node *next;

    Node(string k, const string &v)
    {
        key = k;
        value = v;
        next = nullptr;
    }
};

class HashTable
{

    list<Node> table[SIZE];
    int hash(string key)
    {
        int sum = 0;
        for (char i : key)
        {
            sum += i;
        }
        return sum % SIZE;
    }

public:
    void insert(const string &k, const string &v)
    {
        int index = hash(k);
        for (auto &p : table[index])
        {
            if (p.key == k)
            {
                p.value = v;
                return;
            }
        }

        table[index].push_front(Node(k, v));
    }

    Node *search(string key)
    {
        int index = hash(key);
        for (auto &p : table[index])
        {
            if (p.key == key)
            {
                return &p;
            }
        }

        return nullptr;
    }

    void remove(string key)
    {
        int index = hash(key);
        for (auto i = table[index].begin(); i != table[index].end(); i++)
        {
            if (i->key == key)
            {
                table[index].erase(i);
                cout << "Key " << key << " deleted successfully!" << endl;
                return;
            }
        }

        cout << "Error: Key not found!" << endl;
    }

    void display()
    {
        for (int i = 0; i < SIZE; i++)
        {
            if (!table[i].empty())
            {
                cout << "Index " << i << ": ";
                for (auto &temp : table[i])
                    cout << "(" << temp.key << ", " << temp.value << ") ";

                cout << endl;
            }
        }
    }
};

int main()
{
    HashTable table;

    table.insert("AB", "FASTNU");
    table.insert("CD", "CS");
    table.insert("EF", "SE");

    Node *result = table.search("CD");
    if (result)
        cout << "Key CD found! Value: " << result->value << endl;
    else
        cout << "Key CD not found" << endl;

    table.remove("EF");

    cout << endl << "Displaying Hash Table:" << endl;
    table.display();

    return 0;
}
