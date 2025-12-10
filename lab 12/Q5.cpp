#include <iostream>
#include <vector>
#include <queue>
using namespace std;

const int NODECOUNT = 6;

void setupGraph(vector<int> graph[], int matrix[NODECOUNT][NODECOUNT])
{
    for (int r = 0; r < NODECOUNT; r++)
        for (int c = 0; c < NODECOUNT; c++)
            matrix[r][c] = 0;

    vector<pair<int, int>> links = {
        {1, 4}, {2, 4}, {2, 5}, {3, 5}, {4, 5}};

    for (auto edge : links)
    {
        int a = edge.first;
        int b = edge.second;

        graph[a].push_back(b);
        graph[b].push_back(a);

        matrix[a][b] = 1;
        matrix[b][a] = 1;
    }
}

void BFS(int startNode, vector<int> graph[])
{
    vector<bool> visited(NODECOUNT, false);
    queue<int> q;

    visited[startNode] = true;
    q.push(startNode);

    cout << "BFS traversal starting at " << startNode << ": ";

    while (!q.empty())
    {
        int curr = q.front();
        q.pop();

        cout << curr << " ";

        for (int next : graph[curr])
        {
            if (!visited[next])
            {
                visited[next] = true;
                q.push(next);
            }
        }
    }
    cout << endl;
}

void depthFirstHelper(int node, vector<int> graph[], vector<bool> &visited)
{
    visited[node] = true;
    cout << node << " ";

    for (int nxt : graph[node])
    {
        if (!visited[nxt])
            depthFirstHelper(nxt, graph, visited);
    }
}

void DFS(int startNode, vector<int> graph[])
{
    vector<bool> visited(NODECOUNT, false);

    cout << "DFS traversal starting at " << startNode << ": ";
    depthFirstHelper(startNode, graph, visited);
    cout << endl;
}

int main()
{
    vector<int> adjacencyList[NODECOUNT];
    int adjacencyMatrix[NODECOUNT][NODECOUNT];

    setupGraph(adjacencyList, adjacencyMatrix);

    cout << "Adjacency List:" << endl;
    for (int i = 1; i < NODECOUNT; i++)
    {
        cout << i << ": ";
        for (int val : adjacencyList[i])
            cout << val << " ";
        cout << endl;
    }

    cout << endl << "Adjacency Matrix:" << endl;
    for (int r = 1; r < NODECOUNT; r++)
    {
        for (int c = 1; c < NODECOUNT; c++)
            cout << adjacencyMatrix[r][c] << " ";
        cout << endl;
    }

    BFS(1, adjacencyList);
    DFS(1, adjacencyList);

    return 0;
}
