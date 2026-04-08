#include <bits/stdc++.h>
using namespace std;

struct Graph {
  int V;
  vector<vector<int>> adj;
  vector<int> disc, low;
  vector<bool> in_stack;
  stack<int> st;
  int timer;
  vector<pair<int, int>> bridges;
};

// Detects bridges and Strongly Connected Components (SCC) using Tarjan's algorithm
// Time Complexity: O(V + E)
// Space Complexity: O(V)
void tarjan(Graph &G, int u) {
  // Initialize discovery time and low value
  G.disc[u] = G.low[u] = G.timer++;
  G.st.push(u);
  G.in_stack[u] = true;

  for (int v : G.adj[u]) {
    if (G.disc[v] == -1) {
      // If v is not visited, recursively call tarjan and update low value
      tarjan(G, v);
      G.low[u] = min(G.low[u], G.low[v]);

      // If the lowest vertex reachable from v is below u in DFS tree, then u-v is a bridge
      if (G.low[v] > G.disc[u]) {
        G.bridges.push_back({u, v});
      }
    }
    else if (G.in_stack[v]) {
      // Update low value if v is already in stack
      G.low[u] = min(G.low[u], G.disc[v]);
    }
  }

  // If u is a head node, pop the stack and print the SCC
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
      if low[v] > disc[u]:
        add (u, v) to bridges
    else if in_stack[v]:
      low[u] = min(low[u], disc[v])
  if low[u] == disc[u]: // SCC root found
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

for (auto &bridge : G.bridges) {
  cout << "Bridge: " << bridge.first << " - " << bridge.second << "\n";
}


  for (int i = 0; i < V; i++) {
    if (G.disc[i] == -1)
      tarjan(G, i);
  }

  return 0;
}
