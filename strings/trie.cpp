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
            int idx = c - 'a';
            if (!curr->child[idx])
                curr->child[idx] = new TrieNode();
            curr = curr->child[idx];
        }
        curr->isEnd = true;
    }

    // Searches for a word in the trie
    // Time Complexity: O(L) where L is length of word
    // Space Complexity: O(1)
    bool search(string word) {
        TrieNode* curr = root;
        for (char c : word) {
            int idx = c - 'a';
            if (!curr->child[idx]) return false;
            curr = curr->child[idx];
        }
        return curr->isEnd;
    }
};