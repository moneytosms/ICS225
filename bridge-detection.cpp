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

void tarjan(Graph &G, int u) {
  G.disc[u] = G.low[u] = G.timer++;
  G.st.push(u);
  G.in_stack[u] = true;

  for (int v : G.adj[u]) {
    if (G.disc[v] == -1) {
      tarjan(G, v);
      G.low[u] = min(G.low[u], G.low[v]);
      if (G.low[v] > G.disc[u]) {
        G.bridges.push_back({u, v});
      }
    }
    else if (G.in_stack[v]) {
      G.low[u] = min(G.low[u], G.disc[v]);
    }
  }

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
