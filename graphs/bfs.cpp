#include <bits/stdc++.h>
using namespace std;

struct Graph {
  int V;
  vector<vector<int>> adj;
};

// Performs Breadth-First Search traversal
// Time Complexity: O(V + E)
// Space Complexity: O(V)
void bfs(Graph &G, int u, vector<int> &visited) {
  queue<int> q;
  q.push(u);

  // Process the queue until empty
  while (!q.empty()) {
    int v = q.front();
    q.pop();

    // Visit all adjacent unvisited nodes
    for (int w : G.adj[v]) {
      if (!visited[w]) {
        q.push(w);
        visited[w] = 1; // Mark as visited to avoid cycles and double queueing
      }
    }
  }
}
/*
Algorithm / Pseudocode:
bfs(G, u, visited):
  create an empty queue q
  enqueue u into q
  while q is not empty:
    dequeue a node v from q
    for each neighbor w of v:
      if w is not visited:
        enqueue w into q
        mark w as visited
*/

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
  bfs(G, 0, visited);

  return 0;
}
