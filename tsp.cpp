#include <bits/stdc++.h>
using namespace std;

const int INF = INT_MAX;

int n;           // number of cities
int best_cost;   // best tour cost found so far
vector<int> best_path; // best tour path found so far

// Calculate the lower bound for branch and bound
// Time Complexity: O(N^2)
// Space Complexity: O(1)
int lowerBound(vector<vector<int>> &dist, vector<int> &path, vector<bool> &visited, int cur_cost) {
    int bound = cur_cost;

    // For each unvisited city, add the minimum outgoing edge
    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            int min_edge = INF;
            for (int j = 0; j < n; j++) {
                if (i != j && dist[i][j] != INF)
                    min_edge = min(min_edge, dist[i][j]);
            }
            if (min_edge != INF)
                bound += min_edge;
        }
    }

    return bound;
}
/*
Algorithm / Pseudocode:
lowerBound(dist, path, visited, cur_cost):
  bound = cur_cost
  for each city i not visited:
    min_edge = min outgoing edge from i
    bound += min_edge
  return bound
*/

// Branch and Bound recursive solver
// Time Complexity: O(N!) worst case, pruned significantly in practice
// Space Complexity: O(N) for recursion stack and path tracking
void branchAndBound(vector<vector<int>> &dist, vector<int> &path,
                    vector<bool> &visited, int cur_cost, int level) {
    // Base case: all cities visited, close the tour
    if (level == n) {
        int last  = path[level - 1];
        int start = path[0];

        // Check if return edge exists
        if (dist[last][start] != INF) {
            int total = cur_cost + dist[last][start];
            if (total < best_cost) {
                best_cost = total;
                best_path = path;
            }
        }
        return;
    }

    int cur_city = path[level - 1];

    // Try each unvisited city as the next step
    for (int next = 0; next < n; next++) {
        if (!visited[next] && dist[cur_city][next] != INF) {
            int new_cost = cur_cost + dist[cur_city][next];

            // Prune: skip if lower bound already exceeds best known cost
            visited[next] = true;
            path[level]   = next;

            int bound = lowerBound(dist, path, visited, new_cost);
            if (bound < best_cost)
                branchAndBound(dist, path, visited, new_cost, level + 1); // recurse deeper

            // Backtrack
            visited[next] = false;
            path[level]   = -1;
        }
    }
}
/*
Algorithm / Pseudocode:
branchAndBound(dist, path, visited, cur_cost, level):
  if level == n:
    total = cur_cost + dist[path[n-1]][path[0]]
    if total < best_cost:
      best_cost = total
      best_path = path
    return

  cur_city = path[level - 1]
  for each unvisited city next:
    if edge exists (cur_city -> next):
      new_cost = cur_cost + dist[cur_city][next]
      mark next as visited
      path[level] = next
      bound = lowerBound(...)
      if bound < best_cost:
        branchAndBound(..., new_cost, level + 1)
      unmark next (backtrack)
*/

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;

    // Read distance matrix
    vector<vector<int>> dist(n, vector<int>(n));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            cin >> dist[i][j];

    // Initialize tracking structures
    best_cost = INF;
    best_path.assign(n, -1);

    vector<bool> visited(n, false);
    vector<int>  path(n, -1);

    // Start tour from city 0
    visited[0] = true;
    path[0]    = 0;

    branchAndBound(dist, path, visited, 0, 1);

    // Output result
    cout << "Minimum tour cost: " << best_cost << "\n";
    cout << "Tour path: ";
    for (int city : best_path)
        cout << city << " ";
    cout << best_path[0] << "\n"; // return to start

    return 0;
}
