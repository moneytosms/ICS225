#include <bits/stdc++.h>
using namespace std;

struct Node {
  int key, degree;
  Node *parent, *child, *left, *right;
  bool mark;

  Node(int k) {
    key = k;
    degree = 0;
    parent = child = nullptr;
    left = right = this;
    mark = false;
  }
};

class FibHeap {
private:
  Node *min;
  int n;

  // Insert node into root list
  void insertIntoRootList(Node *x) {
    if (!min) {
      min = x;
    } else {
      x->left = min;
      x->right = min->right;
      min->right->left = x;
      min->right = x;

      if (x->key < min->key)
        min = x;
    }
  }

  // Link y under x
  void link(Node *y, Node *x) {
    // remove y from root list
    y->left->right = y->right;
    y->right->left = y->left;

    // make y child of x
    y->parent = x;
    if (!x->child) {
      x->child = y;
      y->left = y->right = y;
    } else {
      y->left = x->child;
      y->right = x->child->right;
      x->child->right->left = y;
      x->child->right = y;
    }

    x->degree++;
    y->mark = false;
  }

  // Consolidate after extract-min
  void consolidate() {
    int D = log2(n) + 2;
    vector<Node *> A(D, nullptr);

    vector<Node *> roots;
    Node *curr = min;

    if (!curr)
      return;

    do {
      roots.push_back(curr);
      curr = curr->right;
    } while (curr != min);

    for (Node *w : roots) {
      Node *x = w;
      int d = x->degree;

      while (A[d]) {
        Node *y = A[d];
        if (x->key > y->key)
          swap(x, y);

        link(y, x);
        A[d] = nullptr;
        d++;
      }

      A[d] = x;
    }

    min = nullptr;

    for (Node *x : A) {
      if (x) {
        x->left = x->right = x;
        if (!min)
          min = x;
        else
          insertIntoRootList(x);
      }
    }
  }

public:
  FibHeap() {
    min = nullptr;
    n = 0;
  }

  // makeHeap is just constructor

  // INSERT
  void insert(int key) {
    Node *x = new Node(key);
    insertIntoRootList(x);
    n++;
  }

  // FIND-MIN
  int findMin() {
    if (!min)
      return -1;
    return min->key;
  }

  // MELD (UNION)
  void meld(FibHeap &H2) {
    if (!H2.min)
      return;

    if (!min) {
      min = H2.min;
      n = H2.n;
      return;
    }

    // concatenate root lists
    Node *a = min;
    Node *b = H2.min;

    a->right->left = b->left;
    b->left->right = a->right;

    a->right = b;
    b->left = a;

    if (b->key < a->key)
      min = b;

    n += H2.n;
  }

  // EXTRACT-MIN
  int extractMin() {
    Node *z = min;
    if (!z)
      return -1;

    // add children to root list
    if (z->child) {
      Node *x = z->child;
      vector<Node *> children;

      do {
        children.push_back(x);
        x = x->right;
      } while (x != z->child);

      for (Node *c : children) {
        c->parent = nullptr;
        insertIntoRootList(c);
      }
    }

    // remove z from root list
    z->left->right = z->right;
    z->right->left = z->left;

    if (z == z->right) {
      min = nullptr;
    } else {
      min = z->right;
      consolidate();
    }

    n--;
    return z->key;
  }
};

int main() {
  FibHeap H1, H2;

  H1.insert(10);
  H1.insert(3);

  H2.insert(7);
  H2.insert(1);

  H1.meld(H2);

  cout << "Min: " << H1.findMin() << "\n";

  cout << "Extracted Min: " << H1.extractMin() << "\n";

  cout << "New Min: " << H1.findMin() << "\n";

  return 0;
}
