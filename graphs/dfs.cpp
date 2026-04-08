#include <bits/stdc++.h>
using namespace std;

struct Graph {
    int V;
    vector<vector<int>> adj;
};

// Performs Depth-First Search traversal
// Time Complexity: O(V + E)
// Space Complexity: O(V)
void dfs(const Graph &G,int u, vector<int> &visited){
  if(!visited[u]){
    visited[u] = 1; // Mark current node as visited
    // Recursively visit all unvisited neighbors
    for(int v :G.adj[u]){
      dfs(G,v,visited);
    }
  }
}
/*
Algorithm / Pseudocode:
dfs(G, u, visited):
  if u is not visited:
    mark u as visited
    for each neighbor v of u:
      dfs(G, v, visited)
*/

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int V, E;
    cin >> V >> E;
    Graph G;
    G.V = V;
    G.adj.resize(V);
    for(int i = 0; i < E; i++) {
        int u, v;
        cin >> u >> v;
        G.adj[u].push_back(v);
        G.adj[v].push_back(u);
    }
    vector<int> visited(V, 0);
    dfs(G, 0, visited);    

    return 0;
}