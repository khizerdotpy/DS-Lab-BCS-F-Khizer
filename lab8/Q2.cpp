#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

class FighterNode
{
public:
    int fighterID;
    string fighterName;
    int health;
    int attack;
    FighterNode *left;
    FighterNode *right;

    FighterNode(int id, string name, int hp, int ap) : fighterID(id), fighterName(name), health(hp), attack(ap), left(nullptr), right(nullptr) {}
};

class FighterBST
{
    FighterNode *root;

    FighterNode *getMin(FighterNode *node)
    {
        while (node && node->left)
            node = node->left;
        return node;
    }

    void inorderPrint(FighterNode *node)
    {
        if (!node) return;
        inorderPrint(node->left);
        cout << "\nID: " << node->fighterID << ", Name: " << node->fighterName
             << ", HP: " << node->health << ", AP: " << node->attack;
        inorderPrint(node->right);
    }

    FighterNode *insertNode(FighterNode *node, int id, string name, int hp, int ap)
    {
        if (!node)
            return new FighterNode(id, name, hp, ap);

        if (id < node->fighterID)
            node->left = insertNode(node->left, id, name, hp, ap);
        else if (id > node->fighterID)
            node->right = insertNode(node->right, id, name, hp, ap);

        return node;
    }

    FighterNode *deleteNode(FighterNode *node, int id)
    {
        if (!node) return nullptr;

        if (id < node->fighterID)
            node->left = deleteNode(node->left, id);
        else if (id > node->fighterID)
            node->right = deleteNode(node->right, id);
        else
        {
            if (!node->left)
            {
                FighterNode *temp = node->right;
                delete node;
                return temp;
            }
            else if (!node->right)
            {
                FighterNode *temp = node->left;
                delete node;
                return temp;
            }
            else
            {
                FighterNode *minNode = getMin(node->right);
                node->fighterID = minNode->fighterID;
                node->fighterName = minNode->fighterName;
                node->health = minNode->health;
                node->attack = minNode->attack;
                node->right = deleteNode(node->right, minNode->fighterID);
            }
        }
        return node;
    }

public:
    FighterBST() : root(nullptr) {}

    void addFighter(int id, string name, int hp, int ap)
    {
        root = insertNode(root, id, name, hp, ap);
    }

    void removeFighter(int id)
    {
        root = deleteNode(root, id);
    }

    FighterNode *getFirstFighter()
    {
        FighterNode *temp = root;
        if (!temp) return nullptr;
        while (temp->left)
            temp = temp->left;
        return temp;
    }

    void showTeam()
    {
        if (!root)
        {
            cout << "\n(Team is empty)";
            return;
        }
        inorderPrint(root);
        cout << endl;
    }

    FighterNode *getRoot()
    {
        return root;
    }
};

void fightRound(FighterBST &teamA, FighterBST &teamB, int round)
{
    cout << "\n========================\n";
    cout << "       ROUND " << round << "\n";
    cout << "========================\n";

    cout << "\n--- TEAM A ---";
    teamA.showTeam();
    cout << "\n--- TEAM B ---";
    teamB.showTeam();
    cout << endl;

    FighterNode *a = teamA.getFirstFighter();
    FighterNode *b = teamB.getFirstFighter();

    if (!a || !b) return;

    cout << "\nTeam A Frontline: " << a->fighterName << " (HP: " << a->health << ")";
    cout << "\nTeam B Frontline: " << b->fighterName << " (HP: " << b->health << ")\n";

    int damageA = a->attack + (rand() % 5);
    b->health -= damageA;
    cout << "Team A " << a->fighterName << " strikes " << b->fighterName
         << " for " << damageA << " damage!\n";

    if (b->health <= 0)
    {
        cout << "Team B " << b->fighterName << " has fallen!\n";
        teamB.removeFighter(b->fighterID);
        return;
    }

    int damageB = b->attack + (rand() % 5);
    a->health -= damageB;
    cout << "Team B " << b->fighterName << " counters for " << damageB << " damage!\n";

    if (a->health <= 0)
    {
        cout << "Team A " << a->fighterName << " is defeated!\n";
        teamA.removeFighter(a->fighterID);
    }
}

void battle(FighterBST &teamA, FighterBST &teamB)
{
    int round = 1;
    while (teamA.getRoot() && teamB.getRoot())
    {
        fightRound(teamA, teamB, round);
        round++;
    }

    if (!teamB.getRoot())
        cout << "\nTEAM A WINS THE BATTLE!\n";
    else
        cout << "\nTEAM B WINS THE BATTLE!\n";
}

int main()
{
    srand(time(NULL));

    FighterBST teamA, teamB;

    teamA.addFighter(10, "Warrior", 45, 8);
    teamA.addFighter(5, "Sniper", 30, 7);
    teamA.addFighter(15, "Sorcerer", 25, 10);
    teamA.addFighter(3, "Guardian", 50, 6);
    teamA.addFighter(8, "Assassin", 28, 9);

    teamB.addFighter(12, "Ogre", 22, 5);
    teamB.addFighter(6, "Berserker", 35, 8);
    teamB.addFighter(18, "Necromancer", 30, 9);
    teamB.addFighter(1, "Zombie", 20, 4);
    teamB.addFighter(9, "Behemoth", 55, 7);

    cout << "\n==== THE BATTLE BEGINS ====\n";
    battle(teamA, teamB);

    return 0;
}
