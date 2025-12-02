#include <iostream>
using namespace std;

class TreeNode
{
public:
    int data;
    TreeNode *left;
    TreeNode *right;

    TreeNode(int d) : data(d), left(nullptr), right(nullptr) {}
};

class BinarySearchTree
{
    TreeNode *root;

public:
    BinarySearchTree() : root(nullptr) {}

    TreeNode *findMin(TreeNode *curr)
    {
        while (curr && curr->left != nullptr)
        {
            curr = curr->left;
        }
        return curr;
    }

    void constructBST(int arr[], int size)
    {
        root = nullptr;
        for (int i = 0; i < size; i++)
            root = insertNode(root, arr[i]);
    }

    TreeNode *insertNode(TreeNode *curr, int val)
    {
        if (curr == nullptr)
            return new TreeNode(val);

        if (val < curr->data)
            curr->left = insertNode(curr->left, val);
        else if (val > curr->data)
            curr->right = insertNode(curr->right, val);

        return curr;
    }

    void inorderTraversal(TreeNode *curr)
    {
        if (curr == nullptr)
            return;
        inorderTraversal(curr->left);
        cout << curr->data << " ";
        inorderTraversal(curr->right);
    }

    void preorderTraversal(TreeNode *curr)
    {
        if (curr == nullptr)
            return;
        cout << curr->data << " ";
        preorderTraversal(curr->left);
        preorderTraversal(curr->right);
    }

    void postorderTraversal(TreeNode *curr)
    {
        if (curr == nullptr)
            return;
        postorderTraversal(curr->left);
        postorderTraversal(curr->right);
        cout << curr->data << " ";
    }

    TreeNode *searchNode(TreeNode *curr, int key)
    {
        if (curr == nullptr)
            return nullptr;

        if (curr->data == key)
            return curr;
        else if (key < curr->data)
            return searchNode(curr->left, key);
        else
            return searchNode(curr->right, key);
    }

    TreeNode *deleteNode(TreeNode *curr, int key)
    {
        if (curr == nullptr)
            return nullptr;

        if (key < curr->data)
            curr->left = deleteNode(curr->left, key);

        else if (key > curr->data)
            curr->right = deleteNode(curr->right, key);

        else
        {
            if (curr->left == nullptr)
            {
                TreeNode *temp = curr->right;
                delete curr;
                return temp;
            }
            else if (curr->right == nullptr)
            {
                TreeNode *temp = curr->left;
                delete curr;
                return temp;
            }
            else
            {
                TreeNode *minNode = findMin(curr->right);
                curr->data = minNode->data;
                curr->right = deleteNode(curr->right, minNode->data);
            }
        }
        return curr;
    }

    TreeNode *getRoot()
    {
        return root;
    }
};

int main()
{
    int arr[50];
    int n;

    cout << "Enter the number of elements: ";
    cin >> n;

    cout << "Enter numbers to insert in BST:" << endl;
    for (int i = 0; i < n; i++)
        cin >> arr[i];

    BinarySearchTree BST;
    BST.constructBST(arr, n);

    cout << "\nPreorder: ";
    BST.preorderTraversal(BST.getRoot());

    cout << "\nPostorder: ";
    BST.postorderTraversal(BST.getRoot());

    cout << "\nInorder: ";
    BST.inorderTraversal(BST.getRoot());

    int delVal;
    cout << endl << "Enter a data to delete: ";
    cin >> delVal;
    BST.deleteNode(BST.getRoot(), delVal);

    cout << endl << "Inorder After Deletion: ";
    BST.inorderTraversal(BST.getRoot());

    int value;
    cout << endl << "Enter a value to search: ";
    cin >> value;

    if (BST.searchNode(BST.getRoot(), value))
        cout << "Value Found!";
    else
        cout << "Value Not Found!";

    return 0;
}
