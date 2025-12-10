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

class Dictionary
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
    Dictionary()
    {
        for (int i = 0; i < SIZE; i++)
        {
            table[i] = nullptr;
        }
    }
    void Add_Record(string k, const string &v)
    {
        int index = hash(k);
        Node *curr = table[index];

        while (curr != nullptr)
        {
            if (curr->key == k)
                curr->value = v;
                return;

            curr = curr->next;
        }

        Node *newNode = new Node(k, v);
        newNode->next = table[index];
        table[index] = newNode;
    }

    Node *Word_Search(string key)
    {
        int index = hash(key);
        Node *curr = table[index];

        while (curr)
        {
            if (curr->key == key)
                return curr;

            curr = curr->next;
        }

        return nullptr;
    }

    void Delete_Record(string key)
    {
        int index = hash(key);
        Node *curr = table[index];
        Node *prev = nullptr;

        while (curr)
        {
            if (curr->key == key)
            {
                if (prev == nullptr)
                    table[index] = curr->next;
                else
                    prev->next = curr->next;

                delete curr;
                cout << "Key " << key << " deleted successfully!" << endl;
                return;
            }

            prev = curr;
            curr = curr->next;
        }
        cout << "Error: Key not found!" << endl;
    }

    void Print_Dictionary()
    {
        for (int i = 0; i < SIZE; i++)
        {
            if (table[i] != nullptr)
            {
                Node *temp = table[i];
                cout << "Index " << i << ": ";

                while (temp)
                {
                    cout << "(" << temp->key << ", " << temp->value << ") ";
                    temp = temp->next;
                }
                cout << endl;
            }
        }
    }
};

int main()
{
    Dictionary dict;

    dict.Add_Record("AB", "FASTNU");
    dict.Add_Record("CD", "CS");
    dict.Add_Record("EF", "SE");

    Node *find = dict.Word_Search("AB");
    if (find)
    {
        cout << "Key AB found | Value: " << find->value << endl;
    }
    else
    {
        cout << "Key AB not found!" << endl;
    }

    dict.Delete_Record("EF");
    cout << endl << "Displaying the Dictionary:" << endl;
    dict.Print_Dictionary();
    return 0;
}
