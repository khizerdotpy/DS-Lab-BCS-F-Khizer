#include <iostream>
using namespace std;

#define SIZE 15
class Node
{
public:
    int rollNum;
    string name;

    Node(int r, string n) : rollNum(r), name(n) {}
};

class HashTable
{
    Node *table[SIZE];

    int hash(int key)
    {
        return key % SIZE;
    }

public:
    HashTable()
    {
        for (int i = 0; i < SIZE; i++)
        {
            table[i] = nullptr;
        }
    }

    void insert(int rollNo, const string &name)
    {
        int index = hash(rollNo);
        int i = 0;

        while (i < SIZE)
        {
            int newIndex = (index + i * i) % SIZE;

            if (table[newIndex] == nullptr)
            {
                table[newIndex] = new Node(rollNo, name);
                return;
            }
            else if (table[newIndex]->rollNum == rollNo)
            {
                table[newIndex]->name = name;
                return;
            }

            i++;
        }
        cout << "Error: Table full!" << endl;
    }

    void search(int rollNo)
    {
        int index = hash(rollNo);
        int i = 0;

        while (i < SIZE)
        {
            int newIndex = (index + i * i) % SIZE;

            if (table[newIndex] && table[newIndex]->rollNum == rollNo)
            {
                cout << "[" << newIndex << "]: Name: " << table[newIndex]->name << endl;
                return;
            }

            i++;
        }
        cout << "Record not found!" << endl;
    }
};

int main()
{
    HashTable students;

    students.insert(101, "Rayyan");
    students.insert(102, "Hammad");
    students.insert(102, "Usaid");
    students.insert(303, "Fadil");
    students.insert(418, "Murtaza");
    students.insert(567, "Zain");

    students.search(102);

    return 0;
}
