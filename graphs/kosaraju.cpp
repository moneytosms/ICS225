#include <bits/stdc++.h>
using namespace std;

struct Graph {
  int V;
  vector<vector<int>> adj, transpose;
  vector<int> visited;
  stack<int> st;
};

// First DFS (fill stack)
// Time Complexity: O(V + E)
// Space Complexity: O(V)
void dfs1(Graph &G, int u) {
  G.visited[u] = 1;
  for (int v : G.adj[u]) {
    if (!G.visited[v])
      dfs1(G, v);
  }
  G.st.push(u);
}

// Second DFS (print SCC)
// Time Complexity: O(V + E)
// Space Complexity: O(V)
void dfs2(Graph &G, int u) {
  G.visited[u] = 1;
  cout << u << " ";
  for (int v : G.transpose[u]) {
    if (!G.visited[v])
      dfs2(G, v);
  }
}

// Transpose graph
// Time Complexity: O(V + E)
// Space Complexity: O(V + E)
void buildTranspose(Graph &G) {
  G.transpose.resize(G.V);
  for (int u = 0; u < G.V; u++) {
    for (int v : G.adj[u]) {
      G.transpose[v].push_back(u);
    }
  }
}

// Kosaraju Algorithm to find SCCs
// Time Complexity: O(V + E)
// Space Complexity: O(V + E)
void kosaraju(Graph &G) {
  // Step 1: DFS to fill stack
  for (int i = 0; i < G.V; i++) {
    if (!G.visited[i])
      dfs1(G, i);
  }

  // Step 2: Transpose
  buildTranspose(G);

  // Step 3: DFS on transpose
  fill(G.visited.begin(), G.visited.end(), 0);

  while (!G.st.empty()) {
    int u = G.st.top();
    G.st.pop();

    if (!G.visited[u]) {
      dfs2(G, u);
      cout << "\n"; // one SCC
    }
  }
}

int main() {
  int V, E;
  cin >> V >> E;

  Graph G;
  G.V = V;
  G.adj.resize(V);
  G.visited.resize(V, 0);

  for (int i = 0; i < E; i++) {
    int u, v;
    cin >> u >> v;
    G.adj[u].push_back(v);
  }

  kosaraju(G);
}
