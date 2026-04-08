#include <bits/stdc++.h>
using namespace std;

struct Node {
  int data;
  Node *left, *right, *parent;

  Node(int val) {
    data = val;
    left = right = parent = nullptr;
  }
};

class MinHeap {
  Node *root;
  queue<Node *> q; // helps maintain complete binary tree

public:
  MinHeap() { root = nullptr; }

  void insert(int val) {
    Node *newNode = new Node(val);

    if (!root) {
      root = newNode;
      q.push(root);
      return;
    }

    Node *temp = q.front();

    if (!temp->left) {
      temp->left = newNode;
      newNode->parent = temp;
      q.push(newNode);
    } else if (!temp->right) {
      temp->right = newNode;
      newNode->parent = temp;
      q.push(newNode);
      q.pop(); // this node now has 2 children
    }

    heapify_up(newNode);
  }

  void heapify_up(Node *node) {
    while (node->parent && node->data < node->parent->data) {
      swap(node->data, node->parent->data);
      node = node->parent;
    }
  }

  void heapify_down(Node *node) {
    while (node) {
      Node *smallest = node;

      if (node->left && node->left->data < smallest->data)
        smallest = node->left;

      if (node->right && node->right->data < smallest->data)
        smallest = node->right;

      if (smallest != node) {
        swap(node->data, smallest->data);
        node = smallest;
      } else
        break;
    }
  }

  int getMin() {
    if (!root)
      return -1;
    return root->data;
  }

  void extractMin() {
    if (!root)
      return;

    Node *last = nullptr;
    queue<Node *> tempQ;
    tempQ.push(root);

    // Find last node (level order)
    while (!tempQ.empty()) {
      last = tempQ.front();
      tempQ.pop();
      if (last->left)
        tempQ.push(last->left);
      if (last->right)
        tempQ.push(last->right);
    }

    // Replace root value with last node
    root->data = last->data;

    // Remove last node
    Node *parent = last->parent;
    if (parent->right == last)
      parent->right = nullptr;
    else
      parent->left = nullptr;

    delete last;

    heapify_down(root);
  }

  void levelOrder() {
    if (!root)
      return;
    queue<Node *> tempQ;
    tempQ.push(root);

    while (!tempQ.empty()) {
      Node *cur = tempQ.front();
      tempQ.pop();

      cout << cur->data << " ";

      if (cur->left)
        tempQ.push(cur->left);
      if (cur->right)
        tempQ.push(cur->right);
    }
    cout << "\n";
  }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  MinHeap h;

  int n;
  cin >> n;

  for (int i = 0; i < n; i++) {
    int x;
    cin >> x;
    h.insert(x);
  }

  cout << "Level order: ";
  h.levelOrder();

  cout << "Min: " << h.getMin() << "\n";

  h.extractMin();

  cout << "After extract: ";
  h.levelOrder();

  return 0;
}
