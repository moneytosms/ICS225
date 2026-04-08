#include <bits/stdc++.h>
using namespace std;

struct Node {
  int key;
  Node *left, *right;
  bool lthread, rthread;

  Node(int k) {
    key = k;
    left = right = nullptr;
    lthread = rthread = false;
  }
};

// Insert into BST
Node *insert(Node *root, int key) {
  if (!root)
    return new Node(key);

  if (key < root->key)
    root->left = insert(root->left, key);
  else
    root->right = insert(root->right, key);

  return root;
}

// Convert to threaded tree
void createThreads(Node *root, Node *&prev) {
  if (!root)
    return;

  createThreads(root->left, prev);

  // Left thread
  if (!root->left) {
    root->lthread = true;
    root->left = prev;
  }

  // Right thread of previous node
  if (prev && !prev->right) {
    prev->rthread = true;
    prev->right = root;
  }

  prev = root;

  createThreads(root->right, prev);
}

// Get leftmost node
Node *leftMost(Node *node) {
  while (node && !node->lthread)
    node = node->left;
  return node;
}

// Inorder traversal using threads
void inorder(Node *root) {
  Node *cur = leftMost(root);

  while (cur) {
    cout << cur->key << " ";

    if (cur->rthread)
      cur = cur->right;
    else
      cur = leftMost(cur->right);
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  cin >> n;

  Node *root = nullptr;

  for (int i = 0; i < n; i++) {
    int x;
    cin >> x;
    root = insert(root, x);
  }

  Node *prev = nullptr;
  createThreads(root, prev);

  // Final right thread
  if (prev && !prev->right) {
    prev->rthread = true;
    prev->right = nullptr;
  }

  inorder(root);

  return 0;
}
