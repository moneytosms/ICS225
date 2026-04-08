#include <bits/stdc++.h>
using namespace std;

struct TrieNode {
    TrieNode* child[26];
    bool isEnd;

    TrieNode() {
        isEnd = false;
        for (int i = 0; i < 26; i++) child[i] = nullptr;
    }
};

class Trie {
    TrieNode* root;

public:
    Trie() {
        root = new TrieNode();
    }

    // Inserts a word into the trie
    // Time Complexity: O(L) where L is length of word
    // Space Complexity: O(L)
    void insert(string word) {
        TrieNode* curr = root;
        for (char c : word) {
            int idx = c - 'a'; // Get index (0-25) for character
            if (!curr->child[idx])
                curr->child[idx] = new TrieNode(); // Create node if missing
            curr = curr->child[idx]; // Move down the trie
        }
        curr->isEnd = true; // Mark end of word
    }
    /*
    Algorithm / Pseudocode:
    insert(word):
      curr = root
      for each char c in word:
        if curr does not have child for c:
          create child node
        curr = child for c
      mark curr as end of word
    */

    // Searches for a word in the trie
    // Time Complexity: O(L) where L is length of word
    // Space Complexity: O(1)
    bool search(string word) {
        TrieNode* curr = root;
        for (char c : word) {
            int idx = c - 'a';
            if (!curr->child[idx]) return false; // Path breaks, word not found
            curr = curr->child[idx];
        }
        return curr->isEnd; // Return true only if it's a complete word
    }
    /*
    Algorithm / Pseudocode:
    search(word):
      curr = root
      for each char c in word:
        if curr does not have child for c:
          return false
        curr = child for c
      return curr.isEnd
    */
};