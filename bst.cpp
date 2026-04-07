#include <bits/stdc++.h>
using namespace std;

struct Node{
  int val;
  Node* left;
  Node* right;
};

class BST{
  public:
    Node* insert(Node* node, int val) {
      if (node == nullptr) {
        return new Node{val, nullptr, nullptr};
      }
      if (val < node->val) {
        node->left = insert(node->left, val);
      } else {
        node->right = insert(node->right, val);
      }
      return node;
    }
    
    Node* deleteNode(Node* node, int val) {
      if (node == nullptr) {
        return nullptr;
      }
      if (val < node->val) {
        node->left = deleteNode(node->left, val);
      } else if (val > node->val) {
        node->right = deleteNode(node->right, val);
      } else {
        if (node->left == nullptr) {
          return node->right;
        } else if (node->right == nullptr) {
          return node->left;
        }
        Node* minNode = node->right;
        while (minNode->left != nullptr) {
          minNode = minNode->left;
        }
        node->val = minNode->val;
        node->right = deleteNode(node->right, minNode->val);
      }
      return node;
    }
    
    int height(Node* root){
      return 1 + max(height(root->left),height(root->right));
    }
    
    int depth(Node* node, int val, int d = 0) {
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
    Node* root = nullptr;
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