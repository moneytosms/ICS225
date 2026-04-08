#include <bits/stdc++.h>
using namespace std;

struct Graph {
    int V;
    vector<vector<int>> adj;
    vector<int> indegree;
    vector<int> topsort;
};

// Computes topological sort using Kahn's algorithm
// Time Complexity: O(V + E)
// Space Complexity: O(V)
void bfs(Graph &G) {
    queue<int> q;

    // Step 1: push all nodes with indegree 0
    for (int i = 0; i < G.V; i++) {
        if (G.indegree[i] == 0) {
            q.push(i);
        }
    }

    // Step 2: process queue
    while (!q.empty()) {
        int v = q.front();
        q.pop();

        G.topsort.push_back(v);  // add here

        for (int w : G.adj[v]) {
            G.indegree[w]--;     // always decrement

            if (G.indegree[w] == 0) {
                q.push(w);
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int V, E;
    cin >> V >> E;

    Graph G;
    G.V = V;
    G.adj.resize(V);
    G.indegree.assign(V, 0);

    for (int i = 0; i < E; i++) {
        int u, v;
        cin >> u >> v;
        G.adj[u].push_back(v);
        G.indegree[v]++;
    }

    bfs(G);

    // Cycle check
    if (G.topsort.size() != V) {
        cout << "Cycle exists\n";
        return 0;
    }

    for (auto x : G.topsort) {
        cout << x << " ";
    }

    return 0;
}