#include <iostream>
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
private:
    Node *table[SIZE];
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
    HashTable()
    {
        for (int i = 0; i < SIZE; i++)
        {
            table[i] = nullptr;
        }
    }
    
    void insert(string key, const string &v)
    {
        int index = hash(key);
        Node* curr = table[index];
        
        while(curr)
        {
            if(curr->key == key)
            {
                curr->value = v;
                return;
            }
            curr = curr->next;
        }
        
        Node* newNode = new Node(key, v);
        newNode->next = table[index];
        table[index] = newNode;
    }
    
    Node *search(string key)
    {
        int index = hash(key);
        Node *curr = table[index];

        while (curr != nullptr)
        {
            if (curr->key == key)
                return curr;

            curr = curr->next;
        }

        return nullptr;
    }
};

int main()
{
    HashTable table;
    table.insert("A", "aaaaaa");
    table.insert("B", "bbbbb");
    table.insert("C", "ccccc");
    table.insert("A", "zzzzz");

    Node *target = table.search("A");
    if (target)
    {
        cout << "Found:" << endl << "Key: " << target->key << endl << "Value: " << target->value << endl;
    }

    return 0;
}
