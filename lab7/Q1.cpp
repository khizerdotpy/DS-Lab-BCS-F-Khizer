#include <iostream>
#include <string>
using namespace std;

struct Student
{
    string name;
    int score;
};

struct Node
{
    Student student;
    Node *next;

    Node(Student s, Node *n = nullptr) : student(s), next(n) {}
};

void insertNode(Node *&head, const Student &s)
{
    Node *newNode = new Node(s);

    if (!head)
    {
        head = newNode;
        return;
    }

    Node *curr = head;
    while (curr->next != nullptr)
        curr = curr->next;

    curr->next = newNode;
}

void displayList(Node *head)
{
    Node *curr = head;
    while (curr != nullptr)
    {
        cout << "Student Name: " << curr->student.name << " | Student Score: " << curr->student.score << endl;
        curr = curr->next;
    }
    cout << endl;
}

void clearBucket(Node *&head)
{
    Node *temp;
    while (head != nullptr)
    {
        temp = head;
        head = head->next;
        delete temp;
    }
}

int getMax(int arr[], int n)
{
    int mx = arr[0];
    for (int i = 1; i < n; i++)
        if (arr[i] > mx)
            mx = arr[i];
    return mx;
}

void radixSort(Node *&head, const int n)
{
    if (!head || !head->next)
        return;

    int maxNum = 100;
    int exp = 1;

    Node *buckets[10];

    while (maxNum / exp > 0)
    {
        for (int i = 0; i < 10; i++)
            buckets[i] = nullptr;

        Node *curr = head;
        for (int i = 0; i < n; i++)
        {
            int digit = (curr->student.score / exp) % 10;
            insertNode(buckets[digit], curr->student);
            curr = curr->next;
        }

        clearBucket(head);
        int idx = 0;
        for (int i = 0; i < 10; i++)
        {
            Node *temp = buckets[i];
            while (temp != nullptr)
            {
                insertNode(head, temp->student);
                idx++;
                temp = temp->next;
            }

            clearBucket(buckets[i]);
        }

        exp *= 10;
    }
}

Student *convertListToArray(Node *head, int n)
{
    Student *arr = new Student[n];
    Node *curr = head;
    int idx = 0;
    while (curr != nullptr)
    {
        arr[idx++] = curr->student;
        curr = curr->next;
    }

    return arr;
}

int binarySearch(const Student *arr, int n, const string &name, int score)
{
    int left = 0;
    int right = n - 1;

    while (left <= right)
    {
        int mid = (left + right) / 2;

        if (arr[mid].score == score)
        {
            if (arr[mid].name == name)
                return mid;

            int i = mid - 1;
            while (i >= left && arr[i].score == score)
            {
                if (arr[i].name == name)
                    return i;
                i--;
            }

            i = mid + 1;
            while (i <= right && arr[i].score == score)
            {
                if (arr[i].name == name)
                    return i;
                i++;
            }

            return -1;
        }
        else if (arr[mid].score < score)
            left = mid + 1;
        else
            right = mid - 1;
    }

    return -1;
}

void deleteRecord(Node *&head, const string &name, int score)
{
    Node *curr = head;
    Node *prev = nullptr;

    while (curr)
    {
        if (curr->student.name == name && curr->student.score == score)
        {
            if (!prev)
                head = curr->next;
            else
                prev->next = curr->next;

            delete curr;
            cout << "Record deleted successfully." << endl;
            return;
        }
        prev = curr;
        curr = curr->next;
    }

    cout << "Record not found." << endl;
}

int main()
{
    int n;
    cout << "Enter the number of students: ";
    cin >> n;
    cin.ignore();
    cout << endl;

    Node *head = nullptr;
    for (int i = 0; i < n; i++)
    {
        Student student;
        cout << "Enter the name of student " << (i + 1) << ": ";
        getline(cin, student.name);
        do
        {
            cout << "Enter the score out of 100 of student " << (i + 1) << ": ";
            cin >> student.score;
            cin.ignore();

            if (student.score < 0 || student.score > 100)
                cout << "Invalid score entered!" << endl;
        } while (student.score < 0 || student.score > 100);

        insertNode(head, student);
        cout << endl;
    }

    cout << "\n------------------ Displaying the original list ------------------\n";
    displayList(head);

    radixSort(head, n);

    cout << "\n------------------ Displaying the sorted list ------------------\n";
    displayList(head);

    string name;
    int score;
    cout << "\nEnter name & score to search and delete: ";
    getline(cin, name);
    cin >> score;

    Student *arr = convertListToArray(head, n);
    int idx = binarySearch(arr, n, name, score);

    if (idx != -1)
    {
        deleteRecord(head, name, score);

        cout << "\n------------------ Updated List ------------------\n";
        displayList(head);
    }
    else
    {
        cout << endl
             << "Record not found. No deletion performed." << endl;
    }

    return 0;
}
