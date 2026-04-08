#include <bits/stdc++.h>
using namespace std;

struct Node {
  map<string, Node *> children;
};

class SuffixTree {
  Node *root;

  int commonPrefix(string a, string b) {
    int i = 0;
    while (i < a.size() && i < b.size() && a[i] == b[i])
      i++;
    return i;
  }

  // Time Complexity: O(N^2) for inserting all suffixes
  // Space Complexity: O(N^2)
  void insertSuffix(string suffix) {
    Node *curr = root;

    while (true) {
      bool found = false;

      for (auto &p : curr->children) {
        string edge = p.first;
        int len = commonPrefix(edge, suffix);

        if (len == 0)
          continue;

        found = true;

        // If prefix match is partial, split the edge
        if (len < edge.size()) {
          Node *oldChild = p.second;
          string remainingEdge = edge.substr(len);

          Node *newNode = new Node();
          newNode->children[remainingEdge] = oldChild;

          curr->children.erase(edge);
          curr->children[edge.substr(0, len)] = newNode;

          curr = newNode;
        } else {
          // Full edge matched, move to child node
          curr = p.second;
        }

        // Consume the matched part of the suffix
        suffix = suffix.substr(len);

        if (suffix.empty())
          return;

        break;
      }

      // If no edges share a prefix, create a new edge
      if (!found) {
        curr->children[suffix] = new Node();
        return;
      }
    }
  }
  /*
  Algorithm / Pseudocode:
  insertSuffix(suffix):
    curr = root
    while true:
      find edge in curr.children sharing prefix with suffix
      if found:
        if prefix length < edge length:
          split edge
        curr = newly split node or child node
        suffix = remaining suffix after match
        if suffix is empty: return
      else:
        add new edge with remaining suffix
        return
  */

public:
  // Time Complexity: O(N^3) naive construction
  // Space Complexity: O(N^2)
  SuffixTree(string text) {
    root = new Node();

    for (int i = 0; i < text.size(); i++) {
      insertSuffix(text.substr(i));
    }
  }

  // Time Complexity: O(M) where M is pattern length
  // Space Complexity: O(1)
  bool search(string pattern) {
    Node *curr = root;

    while (!pattern.empty()) {
      bool found = false;

      for (auto &p : curr->children) {
        string edge = p.first;

        int len = min(edge.size(), pattern.size());

        // Check if the edge matches the pattern prefix
        if (edge.substr(0, len) == pattern.substr(0, len)) {
          // If the pattern is fully matched within this edge
          if (pattern.size() <= edge.size())
            return true;

          // Consume matched part and move to child
          pattern = pattern.substr(edge.size());
          curr = p.second;
          found = true;
          break;
        }
      }

      if (!found)
        return false; // mismatch
    }

    return true;
  }
  /*
  Algorithm / Pseudocode:
  search(pattern):
    curr = root
    while pattern is not empty:
      find edge from curr that matches prefix of pattern
      if found:
        if pattern is exhausted within edge: return true
        pattern = pattern without matched edge
        curr = child node
      else:
        return false
    return true
  */
};
