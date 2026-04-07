#include <bits/stdc++.h>
using namespace std;

struct Graph {
    int V;
    vector<vector<int>> adj;
};

void dfs(const Graph &G,int u, vector<int> &visited){
  if(!visited[u]){
    visited[u] = 1;
    for(int v :G.adj[u]){
      dfs(G,v,visited);
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