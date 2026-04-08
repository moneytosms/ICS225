#include <bits/stdc++.h>
using namespace std;

struct Graph {
  int V;
  vector<vector<int>> adj;
  vector<int> disc, low;
  vector<bool> in_stack;
  stack<int> st;
  int timer;
};

// Detects SCCs using Tarjan's algorithm
// Time Complexity: O(V + E)
// Space Complexity: O(V)
void tarjan(Graph &G, int u) {
  // Initialize discovery time and low link value
  G.disc[u] = G.low[u] = G.timer++;
  G.st.push(u);
  G.in_stack[u] = true;

  for (int v : G.adj[u]) {
    if (G.disc[v] == -1) {
      // Tree edge: v is unvisited, recurse and update low value
      tarjan(G, v);
      G.low[u] = min(G.low[u], G.low[v]);
    } else if (G.in_stack[v]) {
      // Back edge: v is in stack, update low value using disc time of v
      G.low[u] = min(G.low[u], G.disc[v]);
    }
  }

  // If node is root of SCC, pop all nodes from stack
  if (G.low[u] == G.disc[u]) {
    cout << "SCC: ";
    while (true) {
      int v = G.st.top();
      G.st.pop();
      G.in_stack[v] = false;
      cout << v << " ";
      if (v == u)
        break;
    }
    cout << "\n";
  }
}
/*
Algorithm / Pseudocode:
tarjan(G, u):
  disc[u] = low[u] = timer++
  push u to stack, in_stack[u] = true
  for each neighbor v of u:
    if v is unvisited:
      tarjan(G, v)
      low[u] = min(low[u], low[v])
    else if in_stack[v]:
      low[u] = min(low[u], disc[v])
  if low[u] == disc[u]:
    do:
      v = pop from stack
      in_stack[v] = false
      print v
    while v != u
*/

int main() {
  int V, E;
  cin >> V >> E;

  Graph G;
  G.V = V;
  G.adj.resize(V);
  G.disc.assign(V, -1);
  G.low.assign(V, -1);
  G.in_stack.assign(V, false);
  G.timer = 0;

  for (int i = 0; i < E; i++) {
    int u, v;
    cin >> u >> v;
    G.adj[u].push_back(v);
  }

  for (int i = 0; i < V; i++) {
    if (G.disc[i] == -1)
      tarjan(G, i);
  }

  return 0;
}
