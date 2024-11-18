#include <bits/stdc++.h>
using namespace std;

class Graph
{
    int V;
    list<int> *adj;

    bool DLS(int v, int target, int limit, vector<int>& path, vector<bool>& visited);

public:
    Graph(int V);
    void addEdge(int v, int w);
    bool IDDFS(int v, int target, int max_depth);
};

Graph::Graph(int V)
{
    this->V = V;
    adj = new list<int>[V];
}

void Graph::addEdge(int v, int w)
{
    adj[v].push_back(w);
}

bool Graph::DLS(int src, int target, int limit, vector<int>& path, vector<bool>& visited)
{
    path.push_back(src);
    visited[src] = true;

    if (src == target)
    {
        cout << "Path to target: ";
        for (int node : path)
            cout << node << " ";
        cout << endl;
        return true;
    }

    if (limit <= 0)
    {
        path.pop_back();
        visited[src] = false;
        return false;
    }

    bool found = false;
    for (auto i = adj[src].begin(); i != adj[src].end(); ++i)
    {
        if (!visited[*i])
        {
            if (DLS(*i, target, limit-1, path, visited))
            {
                found = true;
                break;
            }
        }
    }

    path.pop_back();
    visited[src] = false;

    return found;
}

bool Graph::IDDFS(int src, int target, int max_depth)
{
    vector<int> path;
    vector<bool> visited(V, false);

    for (int i = 1; i <= max_depth; i++)
    {
        if (DLS(src, target, i, path, visited) == true)
            return true;
    }

    return false;
}

int main()
{
    int V, E;
    cout << "Enter the number of vertices: ";
    cin >> V;

    Graph g(V);

    cout << "Enter the number of edges: ";
    cin >> E;

    cout << "Enter the edges (u v) where u and v are connected by an edge:" << endl;
    for (int i = 0; i < E; i++) {
        int u, v;
        cin >> u >> v;
        g.addEdge(u, v);
        // For undirected graph, add the reverse edge as well
        g.addEdge(v, u);
    }

    int src, target, maxDepth;
    cout << "Enter the source node: ";
    cin >> src;

    cout << "Enter the target node: ";
    cin >> target;

    cout << "Enter the maximum depth for IDDFS: ";
    cin >> maxDepth;

    if (g.IDDFS(src, target, maxDepth) == true)
        cout << "Target is reachable from source within max depth" << endl;
    else
        cout << "Target is NOT reachable from source within max depth" << endl;

    return 0;
}

/*
Enter the number of vertices: 5
Enter the number of edges: 4
Enter the edges (u v) where u and v are connected by an edge:
0 1
0 2
1 3
1 4
Enter the source node: 0
Enter the target node: 3
Enter the maximum depth for IDDFS: 3
*/