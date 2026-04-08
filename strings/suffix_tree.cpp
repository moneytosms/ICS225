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

        if (len < edge.size()) {
          Node *oldChild = p.second;
          string remainingEdge = edge.substr(len);

          Node *newNode = new Node();
          newNode->children[remainingEdge] = oldChild;

          curr->children.erase(edge);
          curr->children[edge.substr(0, len)] = newNode;

          curr = newNode;
        } else {
          curr = p.second;
        }

        suffix = suffix.substr(len);

        if (suffix.empty())
          return;

        break;
      }

      if (!found) {
        curr->children[suffix] = new Node();
        return;
      }
    }
  }

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

        if (edge.substr(0, len) == pattern.substr(0, len)) {
          if (pattern.size() <= edge.size())
            return true;

          pattern = pattern.substr(edge.size());
          curr = p.second;
          found = true;
          break;
        }
      }

      if (!found)
        return false;
    }

    return true;
  }
};
