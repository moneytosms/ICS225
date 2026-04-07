#include <bits/stdc++.h>
using namespace std;

struct Graph {
  int V;
  vector<vector<int>> adj;
};

void bfs(Graph &G, int u, vector<int> &visited) {
  queue<int> q;
  q.push(u);
  while (!q.empty()) {
    int v = q.front();
    q.pop();

    for (int w : G.adj[v]) {
      if (!visited[w]) {
        q.push(w);
        visited[w] = 1;
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
