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
// Time Complexity: O(H) where H is tree height
// Space Complexity: O(H) for recursion stack
Node *insert(Node *root, int key) {
  if (!root)
    return new Node(key); // base case: empty spot found

  if (key < root->key)
    root->left = insert(root->left, key); // recurse left
  else
    root->right = insert(root->right, key); // recurse right

  return root;
}
/*
Algorithm / Pseudocode:
insert(root, key):
  if root is null:
    return new Node(key)
  if key < root.key:
    root.left = insert(root.left, key)
  else:
    root.right = insert(root.right, key)
  return root
*/

// Convert BST to threaded binary tree
// Time Complexity: O(N)
// Space Complexity: O(H) for recursion stack
void createThreads(Node *root, Node *&prev) {
  if (!root)
    return;

  // Process left subtree
  createThreads(root->left, prev);

  // Left thread: point to inorder predecessor
  if (!root->left) {
    root->lthread = true;
    root->left = prev;
  }

  // Right thread of previous node: point to inorder successor (current root)
  if (prev && !prev->right) {
    prev->rthread = true;
    prev->right = root;
  }

  // Update previous node to current node
  prev = root;

  // Process right subtree
  createThreads(root->right, prev);
}
/*
Algorithm / Pseudocode:
createThreads(root, prev):
  if root is null: return
  createThreads(root.left, prev)

  if root.left is null:
    root.lthread = true
    root.left = prev

  if prev is not null and prev.right is null:
    prev.rthread = true
    prev.right = root

  prev = root
  createThreads(root.right, prev)
*/

// Get leftmost node
// Time Complexity: O(H)
// Space Complexity: O(1)
Node *leftMost(Node *node) {
  while (node && !node->lthread)
    node = node->left;
  return node;
}

// Inorder traversal using threads
// Time Complexity: O(N)
// Space Complexity: O(1)
void inorder(Node *root) {
  // Start from the leftmost node
  Node *cur = leftMost(root);

  while (cur) {
    cout << cur->key << " ";

    // If there is a right thread, follow it to the inorder successor
    if (cur->rthread)
      cur = cur->right;
    // Otherwise, go to the leftmost node in the right subtree
    else
      cur = leftMost(cur->right);
  }
}
/*
Algorithm / Pseudocode:
inorder(root):
  cur = leftMost(root)
  while cur is not null:
    print cur.key
    if cur.rthread is true:
      cur = cur.right
    else:
      cur = leftMost(cur.right)
*/

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
