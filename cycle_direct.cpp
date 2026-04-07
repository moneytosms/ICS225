#include <bits/stdc++.h>
using namespace std;

struct Graph {
  int V, E;
  vector<vector<int>> adj;
  vector<int> state;
  vector<int> visited;
};

bool dfs(Graph &G, int u) {
  G.state[u] = 1;
  for (int v : G.adj[u]) {
    if (G.state[v] == 0) {
      if (dfs(G, v))
        return true;
    } else if (G.state[v] == 1) {
      return true;
    }
  }
  G.state[u] = -1;
  return false;
}

bool hasCycle(Graph &G) {
  for (int i = 0; i < G.V; i++) {
    if (G.state[i] == 0) {
      if (dfs(G, i))
        return true;
    }
  }
  return false;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int n, m;
  cin >> n >> m;
  Graph G;
  G.V = n;
  G.E = m;
  G.adj.resize(n);
  G.state.resize(n, 0); // 0 = unvisited, 1 = in-stack, -1 = done
  G.visited.resize(n, 0);

  while (m--) {
    int u, v;
    cin >> u >> v;
    G.adj[u].push_back(v);
  }

  if (hasCycle(G))
    cout << "Cycle detected\n";
  else
    cout << "No cycle\n";

  return 0;
}
