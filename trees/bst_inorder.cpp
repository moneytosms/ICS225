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
  // Time Complexity: O(H) where H is the tree height
  // Space Complexity: O(H) for recursion stack
  Node *insert(Node *node, int val) {
    if (node == nullptr) {
      return new Node(val);
    }
    if (val < node->val) {
      node->left = insert(node->left, val);
    } else {
      node->right = insert(node->right, val);
    }
    return node;
  }

  // Iterative inorder traversal
  // Time Complexity: O(N)
  // Space Complexity: O(H) for stack
  vector<int> inorder(Node *root) {
    stack<Node *> st;
    Node *curr = root;
    vector<int> res;

    while (curr || !st.empty()) {
      while (curr->left) {
        st.push(curr);
        curr = curr->left;
      }
      curr = st.top();
      st.pop();
      res.push_back(curr->val);
      curr = curr->right;
    }
    return res;
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

  vector<int> res = bst.inorder(root);
  for (int val : res) {
    cout << val << " ";
  }
  cout << "\n";

  return 0;
}
