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
    // These nodes have no prerequisites
    for (int i = 0; i < G.V; i++) {
        if (G.indegree[i] == 0) {
            q.push(i);
        }
    }

    // Step 2: process queue
    while (!q.empty()) {
        int v = q.front();
        q.pop();

        G.topsort.push_back(v);  // Add node to topological order

        // Decrease indegree of adjacent nodes
        // If a node's indegree becomes 0, all its prerequisites are met
        for (int w : G.adj[v]) {
            G.indegree[w]--;     // always decrement

            if (G.indegree[w] == 0) {
                q.push(w);
            }
        }
    }
}
/*
Algorithm / Pseudocode:
bfs(G):
  create queue q
  for each node i in G:
    if indegree of i == 0:
      enqueue i into q
  while q is not empty:
    v = dequeue from q
    add v to topological_sort_list
    for each neighbor w of v:
      decrement indegree of w
      if indegree of w == 0:
        enqueue w into q
*/

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