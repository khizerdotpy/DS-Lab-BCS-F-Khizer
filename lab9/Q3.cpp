#include <iostream>
using namespace std;

struct AvlNode
{
    int key;
    int heightVal;
    AvlNode *leftPtr;
    AvlNode *rightPtr;

    AvlNode(int k)
    {
        key = k;
        heightVal = 1;
        leftPtr = rightPtr = nullptr;
    }
};

int getHeight(AvlNode *n)
{
    return (n == nullptr ? 0 : n->heightVal);
}

int getBalanceFactor(AvlNode *n)
{
    if (n == nullptr)
        return 0;
    return getHeight(n->leftPtr) - getHeight(n->rightPtr);
}

void refreshHeight(AvlNode *n)
{
    int leftH = getHeight(n->leftPtr);
    int rightH = getHeight(n->rightPtr);
    n->heightVal = 1 + (leftH > rightH ? leftH : rightH);
}

AvlNode *rotateRight(AvlNode *y)
{
    AvlNode *x = y->leftPtr;
    AvlNode *t = x->rightPtr;

    x->rightPtr = y;
    y->leftPtr = t;

    refreshHeight(y);
    refreshHeight(x);
    return x;
}

AvlNode *rotateLeft(AvlNode *x)
{
    AvlNode *y = x->rightPtr;
    AvlNode *t = y->leftPtr;

    y->leftPtr = x;
    x->rightPtr = t;

    refreshHeight(x);
    refreshHeight(y);
    return y;
}

AvlNode *addValue(AvlNode *node, int val)
{
    if (node == nullptr)
        return new AvlNode(val);

    if (val < node->key)
        node->leftPtr = addValue(node->leftPtr, val);
    else if (val > node->key)
        node->rightPtr = addValue(node->rightPtr, val);
    else
        return node;

    refreshHeight(node);

    int bf = getBalanceFactor(node);

    if (bf > 1 && val < node->leftPtr->key)
        return rotateRight(node);

    if (bf < -1 && val > node->rightPtr->key)
        return rotateLeft(node);

    if (bf > 1 && val > node->leftPtr->key)
    {
        node->leftPtr = rotateLeft(node->leftPtr);
        return rotateRight(node);
    }

    if (bf < -1 && val < node->rightPtr->key)
    {
        node->rightPtr = rotateRight(node->rightPtr);
        return rotateLeft(node);
    }

    return node;
}

void showInorder(AvlNode *root)
{
    if (!root)
        return;
    showInorder(root->leftPtr);
    cout << root->key << " ";
    showInorder(root->rightPtr);
}

void showBalance(AvlNode *root)
{
    if (!root)
        return;
    showBalance(root->leftPtr);
    cout << "Node " << root->key << " has BF = " << getBalanceFactor(root) << endl;
    showBalance(root->rightPtr);
}

int main()
{
    AvlNode *root = nullptr;

    int arr[] = {40, 20, 10, 25, 50, 45, 60, 55};
    int n = 8;

    cout << "Inserting values into AVL tree:" << endl;
    for (int i = 0; i < n; i++)
        root = addValue(root, arr[i]);

    cout << endl << "Balance Factor of Each Node:" << endl;
    showBalance(root);

    cout << endl << "Height of Final Tree: " << getHeight(root) << endl;

    cout << endl << "Inorder Traversal of AVL Tree: ";
    showInorder(root);
    cout << endl;

    return 0;
}
