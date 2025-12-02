#include <iostream>
using namespace std;

struct AvlNode
{
    int value;
    AvlNode *leftChild;
    AvlNode *rightChild;
    int h;

    AvlNode(int v)
    {
        value = v;
        leftChild = rightChild = nullptr;
        h = 1;
    }
};

int getHeight(AvlNode *n)
{
    return (n ? n->h : 0);
}

void refresh(AvlNode *n)
{
    int lh = getHeight(n->leftChild);
    int rh = getHeight(n->rightChild);
    n->h = 1 + (lh > rh ? lh : rh);
}

int getBF(AvlNode *n)
{
    return getHeight(n->leftChild) - getHeight(n->rightChild);
}

AvlNode *rotateRight(AvlNode *y)
{
    AvlNode *x = y->leftChild;
    AvlNode *t = x->rightChild;

    x->rightChild = y;
    y->leftChild = t;

    refresh(y);
    refresh(x);
    return x;
}

AvlNode *rotateLeft(AvlNode *x)
{
    AvlNode *y = x->rightChild;
    AvlNode *t = y->leftChild;

    y->leftChild = x;
    x->rightChild = t;

    refresh(x);
    refresh(y);
    return y;
}

AvlNode *insertNode(AvlNode *root, int v)
{
    if (root == nullptr)
        return new AvlNode(v);

    if (v < root->value)
        root->leftChild = insertNode(root->leftChild, v);
    else if (v > root->value)
        root->rightChild = insertNode(root->rightChild, v);
    else
        return root;
    refresh(root);

    int bf = getBF(root);

    if (bf > 1 && v < root->leftChild->value)
        return rotateRight(root);

    if (bf < -1 && v > root->rightChild->value)
        return rotateLeft(root);

    if (bf > 1 && v > root->leftChild->value)
    {
        root->leftChild = rotateLeft(root->leftChild);
        return rotateRight(root);
    }

    if (bf < -1 && v < root->rightChild->value)
    {
        root->rightChild = rotateRight(root->rightChild);
        return rotateLeft(root);
    }

    return root;
}

void findKSmall(AvlNode *root, int &k, int &ans)
{
    if (!root)
        return;

    findKSmall(root->leftChild, k, ans);

    if (--k == 0)
    {
        ans = root->value;
        return;
    }

    findKSmall(root->rightChild, k, ans);
}

void findKLarge(AvlNode *root, int &k, int &ans)
{
    if (!root)
        return;

    findKLarge(root->rightChild, k, ans);

    if (--k == 0)
    {
        ans = root->value;
        return;
    }

    findKLarge(root->leftChild, k, ans);
}

int main()
{
    AvlNode *root = nullptr;

    int data[] = {30, 15, 45, 10, 20, 40, 50, 18};
    int size = 8;

    for (int i = 0; i < size; i++)
        root = insertNode(root, data[i]);

    int kSmall = 3, kLarge = 2;
    int smallest = -1, largest = -1;

    findKSmall(root, kSmall, smallest);
    findKLarge(root, kLarge, largest);

    cout << "3rd Smallest Element: " << smallest << endl;
    cout << "2nd Largest Element: " << largest << endl;

    cout << "Height of Left Subtree = " << getHeight(root->leftChild) << endl;
    cout << "Height of Right Subtree = " << getHeight(root->rightChild) << endl;

    return 0;
}
