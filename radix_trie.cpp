#include <bits/stdc++.h>
using namespace std;

struct RadixNode {
  map<string, RadixNode *> children;
  bool isEnd;

  RadixNode() { isEnd = false; }
};

class RadixTrie {
  RadixNode *root;

  // Find common prefix length
  int commonPrefix(string a, string b) {
    int i = 0;
    while (i < a.size() && i < b.size() && a[i] == b[i])
      i++;
    return i;
  }

public:
  RadixTrie() { root = new RadixNode(); }

  void insert(string word) {
    RadixNode *curr = root;

    while (true) {
      bool found = false;

      for (auto &p : curr->children) {
        string edge = p.first;
        int len = commonPrefix(edge, word);

        if (len == 0)
          continue;

        found = true;

        // Split edge
        if (len < edge.size()) {
          RadixNode *oldChild = p.second;
          string remainingEdge = edge.substr(len);

          RadixNode *newNode = new RadixNode();
          newNode->children[remainingEdge] = oldChild;

          curr->children.erase(edge);
          curr->children[edge.substr(0, len)] = newNode;

          p.second = newNode;
          curr = newNode;
        } else {
          curr = p.second;
        }

        word = word.substr(len);

        if (word.empty()) {
          curr->isEnd = true;
          return;
        }

        break;
      }

      if (!found) {
        curr->children[word] = new RadixNode();
        curr->children[word]->isEnd = true;
        return;
      }
    }
  }

  bool search(string word) {
    RadixNode *curr = root;

    while (!word.empty()) {
      bool found = false;

      for (auto &p : curr->children) {
        string edge = p.first;

        if (word.substr(0, edge.size()) == edge) {
          word = word.substr(edge.size());
          curr = p.second;
          found = true;
          break;
        }
      }

      if (!found)
        return false;
    }

    return curr->isEnd;
  }
};
