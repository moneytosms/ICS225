#include <bits/stdc++.h>
using namespace std;

struct Graph {
    int V;
    vector<vector<int>> adj;
};

// Detects cycle in an undirected graph using Depth-First Search
// Time Complexity: O(V + E)
// Space Complexity: O(V)
bool dfs(const Graph &G, int u, int parent, vector<int> &visited) {
    visited[u] = 1;

    for (int v : G.adj[u]) {
        if (!visited[v]) {
            if (dfs(G, v, u, visited))
                return true;
        }
        else if (v != parent) {
            // Visited node that is not parent → cycle detected
            return true;
        }
    }
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int V, E;
    cin >> V >> E;

    Graph G;
    G.V = V;
    G.adj.resize(V);

    for (int i = 0; i < E; i++) {
        int u, v;
        cin >> u >> v;
        G.adj[u].push_back(v);
        G.adj[v].push_back(u);
    }

    vector<int> visited(V, 0);
    bool hasCycle = false;

    // Handle disconnected graph
    for (int i = 0; i < V; i++) {
        if (!visited[i]) {
            if (dfs(G, i, -1, visited)) {
                hasCycle = true;
                break;
            }
        }
    }

    if (hasCycle)
        cout << "Cycle detected\n";
    else
        cout << "No cycle\n";

    return 0;
}