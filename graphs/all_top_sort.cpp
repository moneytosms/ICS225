#include <bits/stdc++.h>
using namespace std;

struct Graph {
  int V;
  vector<vector<int>> adj;
  vector<int> indegree;
};

// Counts all topological sorts using backtracking
// Time Complexity: O(V!)
// Space Complexity: O(V)
int countTopSorts(Graph &G, vector<int> &visited) {
  int count = 0;
  bool flag = false;

  for (int i = 0; i < G.V; i++) {
    // If node is unvisited and has no incoming edges, it can be placed next
    if (!visited[i] && G.indegree[i] == 0) {

      // choose: Mark as visited and decrement indegree of adjacent nodes
      visited[i] = 1;
      for (int v : G.adj[i])
        G.indegree[v]--;

      // explore: Recursively count valid topological sorts from this state
      count += countTopSorts(G, visited);

      // backtrack: Restore visited state and indegrees for other possibilities
      visited[i] = 0;
      for (int v : G.adj[i])
        G.indegree[v]++;

      flag = true;
    }
  }

  // base case: If no unvisited node with indegree 0 was found
  if (!flag) {
    // check if all nodes are used to ensure no cycles prevented sorting
    for (int i = 0; i < G.V; i++) {
      if (!visited[i])
        return 0; // cycle case
    }
    return 1; // valid ordering found
  }

  return count;
}
/*
Algorithm / Pseudocode:
countTopSorts(G, visited):
  count = 0
  flag = false
  for each node i in G:
    if i is unvisited and indegree of i is 0:
      mark i as visited
      decrement indegree of all neighbors of i
      count += countTopSorts(G, visited)
      restore indegree of all neighbors of i
      mark i as unvisited
      flag = true
  if not flag:
    if any node is unvisited return 0
    return 1
  return count
*/

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
