#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <algorithm>
using namespace std;

struct Edge
{
    int to;
    int weight;
};

int main()
{
    int N = 6;
    vector<vector<Edge>> adj(N);

    auto addEdge = [&](char u, char v, int w)
    {
        int a = u - 'A';
        int b = v - 'A';
        adj[a].push_back({b, w});
        adj[b].push_back({a, w});
    };

    addEdge('B', 'A', 4);
    addEdge('B', 'C', 9);
    addEdge('A', 'D', 8);
    addEdge('C', 'D', 6);
    addEdge('C', 'E', 14);
    addEdge('D', 'F', 4);
    addEdge('E', 'F', 3);

    int src = 'B' - 'A';
    int dest = 'E' - 'A';

    vector<int> dist(N, INT_MAX);
    vector<int> parent(N, -1);
    dist[src] = 0;

    using pii = pair<int, int>;
    priority_queue<pii, vector<pii>, greater<pii>> pq;
    pq.push({0, src});

    while (!pq.empty())
    {
        auto [d, u] = pq.top();
        pq.pop();

        if (d > dist[u])
            continue;

        for (auto e : adj[u])
        {
            int v = e.to;
            int w = e.weight;

            if (dist[v] > dist[u] + w)
            {
                dist[v] = dist[u] + w;
                parent[v] = u;
                pq.push({dist[v], v});
            }
        }
    }

    vector<char> path;
    for (int at = dest; at != -1; at = parent[at])
        path.push_back('A' + at);

    reverse(path.begin(), path.end());

    cout << "Shortest distance from B to E: " << dist[dest] << endl;

    cout << "Path: ";
    for (char c : path)
        cout << c << " ";
    cout << endl;

    return 0;
}
