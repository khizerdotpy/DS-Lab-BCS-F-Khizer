#include <iostream>
using namespace std;

struct TreeNode
{
    int value;
    TreeNode *leftChild;
    TreeNode *rightChild;
    int heightLevel;

    TreeNode(int v)
    {
        value = v;
        leftChild = rightChild = nullptr;
        heightLevel = 1;
    }
};

class AVLTree
{
private:
    TreeNode *rootNode;

    int getHeight(TreeNode *node)
    {
        return (node == nullptr) ? 0 : node->heightLevel;
    }

    void refreshHeight(TreeNode *node)
    {
        int leftH = getHeight(node->leftChild);
        int rightH = getHeight(node->rightChild);
        node->heightLevel = 1 + (leftH > rightH ? leftH : rightH);
    }

    TreeNode *rotateLeft(TreeNode *oldRoot)
    {
        TreeNode *newRoot = oldRoot->rightChild;
        TreeNode *temp = newRoot->leftChild;

        newRoot->leftChild = oldRoot;
        oldRoot->rightChild = temp;

        refreshHeight(oldRoot);
        refreshHeight(newRoot);

        return newRoot;
    }

    TreeNode *addNode(TreeNode *current, int val)
    {
        if (current == nullptr)
            return new TreeNode(val);

        if (val < current->value)
            current->leftChild = addNode(current->leftChild, val);
        else if (val > current->value)
            current->rightChild = addNode(current->rightChild, val);
        else
            return current;

        refreshHeight(current);
        return current;
    }

    void showInOrder(TreeNode *node)
    {
        if (node == nullptr)
            return;

        showInOrder(node->leftChild);
        cout << node->value << " ";
        showInOrder(node->rightChild);
    }

public:
    AVLTree() { rootNode = nullptr; }

    void insertValue(int v)
    {
        rootNode = addNode(rootNode, v);
    }

    void applyLeftRotation()
    {
        rootNode = rotateLeft(rootNode);
    }

    void printTree()
    {
        showInOrder(rootNode);
        cout << endl;
    }
};

int main()
{
    AVLTree myTree;
    int items[] = {50, 30, 70, 20, 40, 60, 80, 55};
    int n = 8;

    cout << "Inserting values into AVL Tree..." << endl;
    for (int i = 0; i < n; i++)
        myTree.insertValue(items[i]);

    cout << endl << "Applying left rotation on the root..." << endl;
    myTree.applyLeftRotation();

    cout << "Inorder Traversal After Rotation: ";
    myTree.printTree();

    return 0;
}
