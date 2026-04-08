#include <bits/stdc++.h>
using namespace std;

struct Node {
  int val;
  Node *left;
  Node *right;
  Node(int k) : val(k), left(nullptr), right(nullptr) {}
};

class BST {
public:
  // Inserts a value into the BST
  // Time Complexity: O(H) where H is the height of the tree (O(log N) average, O(N) worst)
  // Space Complexity: O(H) for recursion stack
  Node *insert(Node *node, int val) {
    if (node == nullptr) {
      return new Node(val); // create new node if empty spot found
    }
    if (val < node->val) {
      node->left = insert(node->left, val); // recurse left
    } else {
      node->right = insert(node->right, val); // recurse right
    }
    return node;
  }
  /*
  Algorithm / Pseudocode:
  insert(node, val):
    if node is null:
      return new Node(val)
    if val < node.val:
      node.left = insert(node.left, val)
    else:
      node.right = insert(node.right, val)
    return node
  */

  // Deletes a node from the BST
  // Time Complexity: O(H)
  // Space Complexity: O(H) for recursion stack
  Node* deleteNode(Node* root, int key) {
      // Base case: empty tree
      if (!root) return nullptr;
  
      // Step 1: Search for the node to delete
      if (key < root->val) {
          root->left = deleteNode(root->left, key);
      }
      else if (key > root->val) {
          root->right = deleteNode(root->right, key);
      }
      else {
          // Node found
  
          // Case 1: No left child
          if (!root->left) {
              Node* temp = root->right;
              delete root;  // free memory
              return temp;
          }
  
          // Case 2: No right child
          if (!root->right) {
              Node* temp = root->left;
              delete root;  // free memory
              return temp;
          }
  
          // Case 3: Two children
          // Find inorder successor (smallest node in right subtree)
          Node* succ = root->right;
          while (succ->left) {
              succ = succ->left;
          }
  
          // Copy successor value to current node
          root->val = succ->val;
  
          // Delete the successor node from right subtree
          root->right = deleteNode(root->right, succ->val);
      }
  
      // Return updated subtree
      return root;
  }
  /*
  Algorithm / Pseudocode:
  deleteNode(root, key):
    if root is null: return null
    if key < root.val: root.left = deleteNode(root.left, key)
    else if key > root.val: root.right = deleteNode(root.right, key)
    else: // node found
      if root.left is null:
        temp = root.right; delete root; return temp
      if root.right is null:
        temp = root.left; delete root; return temp
      // node has two children
      succ = min_value_node(root.right)
      root.val = succ.val
      root.right = deleteNode(root.right, succ.val)
    return root
  */

  // Calculates the height of the BST
  // Time Complexity: O(N)
  // Space Complexity: O(H) for recursion stack
  int height(Node *root) {
    return 1 + max(height(root->left), height(root->right));
  }

  // Calculates the depth of a given value in the BST
  // Time Complexity: O(H)
  // Space Complexity: O(H) for recursion stack
  int depth(Node *node, int val, int d = 0) {
    if (node == nullptr) {
      return -1;
    }
    if (val == node->val) {
      return d;
    } else if (val < node->val) {
      return depth(node->left, val, d + 1);
    } else {
      return depth(node->right, val, d + 1);
    }
  }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  BST bst;
  Node *root = nullptr;
  int n;
  cin >> n;
  for (int i = 0; i < n; i++) {
    int val;
    cin >> val;
    root = bst.insert(root, val);
  }
  int val;
  cin >> val;
  cout << bst.depth(root, val) << endl;
  cout << bst.height(root) << endl;

  return 0;
}
