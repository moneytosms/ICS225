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

  // Inserts a string into the Radix Trie
  // Time Complexity: O(L) where L is the length of the string
  // Space Complexity: O(L)
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

        // Split edge if there is a partial match
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
          // Full match on edge, move to child node
          curr = p.second;
        }

        // Reduce word by matched prefix
        word = word.substr(len);

        if (word.empty()) {
          curr->isEnd = true;
          return;
        }

        break;
      }

      // If no matching prefix on any edge, create new edge
      if (!found) {
        curr->children[word] = new RadixNode();
        curr->children[word]->isEnd = true;
        return;
      }
    }
  }
  /*
  Algorithm / Pseudocode:
  insert(word):
    curr = root
    while true:
      find edge in curr.children sharing prefix with word
      if shared prefix found:
        if prefix length < edge length:
          split edge by creating a new intermediate node
        curr = child node of matched prefix
        word = remainder of word after prefix
        if word is empty:
          mark curr as end of word
          return
      else:
        add new edge from curr with remaining word
        mark new node as end of word
        return
  */

  // Searches for a string in the Radix Trie
  // Time Complexity: O(L) where L is the length of the string
  // Space Complexity: O(1)
  bool search(string word) {
    RadixNode *curr = root;

    while (!word.empty()) {
      bool found = false;

      // Look for an edge that perfectly matches the prefix of word
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
        return false; // mismatch
    }

    return curr->isEnd;
  }
  /*
  Algorithm / Pseudocode:
  search(word):
    curr = root
    while word is not empty:
      find edge from curr that exactly matches prefix of word
      if found:
        remove matched prefix from word
        curr = child node
      else:
        return false
    return curr.isEnd
  */
};
