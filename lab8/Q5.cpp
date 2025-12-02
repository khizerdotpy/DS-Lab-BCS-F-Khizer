#include <iostream>
#include <climits>
using namespace std;

class TreeNode
{
public:
    int value;
    TreeNode *left;
    TreeNode *right;

    TreeNode(int v) : value(v), left(nullptr), right(nullptr) {}
};

class BinarySearchTree
{
    TreeNode *root;

    TreeNode *insertNode(TreeNode *curr, int val)
    {
        if (curr == nullptr)
            return new TreeNode(val);

        if (val < curr->value)
            curr->left = insertNode(curr->left, val);
        else if (val > curr->value)
            curr->right = insertNode(curr->right, val);

        return curr;
    }

    bool validateBST(TreeNode *curr, TreeNode *minNode, TreeNode *maxNode)
    {
        if (curr == nullptr)
            return true;

        if (minNode && curr->value <= minNode->value)
            return false;

        if (maxNode && curr->value >= maxNode->value)
            return false;

        return validateBST(curr->left, minNode, curr) &&
               validateBST(curr->right, curr, maxNode);
    }

    void inorder(TreeNode *curr)
    {
        if (!curr)
            return;
        inorder(curr->left);
        cout << curr->value << " ";
        inorder(curr->right);
    }

public:
    BinarySearchTree() : root(nullptr) {}

    void buildFromArray(int arr[], int size)
    {
        root = nullptr;
        for (int i = 0; i < size; i++)
            root = insertNode(root, arr[i]);
    }

    bool isValid()
    {
        return validateBST(root, nullptr, nullptr);
    }

    void printInOrder()
    {
        inorder(root);
        cout << endl;
    }

    void setRoot(TreeNode *r)
    {
        root = r;
    }

    TreeNode *getRoot()
    {
        return root;
    }
};

int main()
{
    int data1[] = {12, 7, 25, 3, 9};
    int size1 = 5;

    BinarySearchTree bst1;
    bst1.buildFromArray(data1, size1);

    cout << "Example 1 - Inorder Traversal: ";
    bst1.printInOrder();

    if (bst1.isValid())
        cout << "Status: Valid BST\n\n";
    else
        cout << "Status: NOT a Valid BST\n\n";

    TreeNode *A = new TreeNode(30);
    TreeNode *B = new TreeNode(10);
    TreeNode *C = new TreeNode(40);
    TreeNode *D = new TreeNode(50);

    A->left = B;
    A->right = C;
    B->left = D;

    BinarySearchTree bst2;
    bst2.setRoot(A);

    cout << "Example 2 - Inorder Traversal: ";
    bst2.printInOrder();

    if (bst2.isValid())
        cout << "Status: Valid BST\n";
    else
        cout << "Status: NOT a Valid BST\n";

    return 0;
}
