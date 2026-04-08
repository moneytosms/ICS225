#include <bits/stdc++.h>
using namespace std;

struct Graph {
    int V;
    vector<vector<int>> adj;
};
 
set<vector<int>> uniqueCycles;
  
// Detects and prints cycles using Depth-First Search
// Time Complexity: O(V + E)
// Space Complexity: O(V)
void dfs(const Graph &G, int u, int parent,
         vector<int> &visited,
         vector<int> &path,
         vector<int> &inPath) {

    visited[u] = 1;
    path.push_back(u);
    inPath[u] = 1;

    for (int v : G.adj[u]) {
        if (v == parent) continue;

        if (!visited[v]) {
            dfs(G, v, u, visited, path, inPath);
        }
        else if (inPath[v]) {
            // Cycle found → extract cycle
            vector<int> cycle;
            auto it = find(path.begin(), path.end(), v);

            for (; it != path.end(); ++it)
                cycle.push_back(*it);

            // Normalize cycle (to avoid duplicates)
            vector<int> temp = cycle;
            sort(temp.begin(), temp.end());
            uniqueCycles.insert(temp);
        }
    }

    path.pop_back();
    inPath[u] = 0;
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

    vector<int> visited(V, 0), path, inPath(V, 0);

    for (int i = 0; i < V; i++) {
        if (!visited[i]) {
            dfs(G, i, -1, visited, path, inPath);
        }
    }

    cout << "Cycles found:\n";
    for (auto &cycle : uniqueCycles) {
        for (int node : cycle)
            cout << node << " ";
        cout << "\n";
    }

    return 0;
}