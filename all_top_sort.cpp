#include <bits/stdc++.h>
using namespace std;

struct Graph {
  int V;
  vector<vector<int>> adj;
  vector<int> indegree;
};

int countTopSorts(Graph &G, vector<int> &visited) {
  int count = 0;
  bool flag = false;

  for (int i = 0; i < G.V; i++) {
    if (!visited[i] && G.indegree[i] == 0) {

      // choose
      visited[i] = 1;
      for (int v : G.adj[i])
        G.indegree[v]--;

      // explore
      count += countTopSorts(G, visited);

      // backtrack
      visited[i] = 0;
      for (int v : G.adj[i])
        G.indegree[v]++;

      flag = true;
    }
  }

  // ✅ base case
  if (!flag) {
    // check if all nodes are used
    for (int i = 0; i < G.V; i++) {
      if (!visited[i])
        return 0; // cycle case
    }
    return 1; // valid ordering
  }

  return count;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int V, E;
  cin >> V >> E;

  Graph G;
  G.V = V;
  G.adj.assign(V, {});
  G.indegree.assign(V, 0);

  for (int i = 0; i < E; i++) {
    int u, v;
    cin >> u >> v;
    G.adj[u].push_back(v);
    G.indegree[v]++;
  }

  vector<int> visited(V, 0);
  cout << countTopSorts(G, visited) << '\n';

  return 0;
}
