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
  // Time Complexity: O(1) amortized
  // Space Complexity: O(1)
  void insert(int key) {
    // Create new node and add it to the root list without consolidating
    Node *x = new Node(key);
    insertIntoRootList(x);
    n++;
  }
  /*
  Algorithm / Pseudocode:
  insert(key):
    x = new Node(key)
    insertIntoRootList(x)
    n++
  */

  // FIND-MIN
  // Time Complexity: O(1)
  // Space Complexity: O(1)
  int findMin() {
    if (!min)
      return -1;
    return min->key;
  }

  // MELD (UNION)
  // Time Complexity: O(1)
  // Space Complexity: O(1)
  void meld(FibHeap &H2) {
    if (!H2.min)
      return;

    if (!min) {
      min = H2.min;
      n = H2.n;
      return;
    }

    // concatenate root lists by splicing the circular doubly linked lists
    Node *a = min;
    Node *b = H2.min;

    a->right->left = b->left;
    b->left->right = a->right;

    a->right = b;
    b->left = a;

    // update min pointer if necessary
    if (b->key < a->key)
      min = b;

    n += H2.n;
  }
  /*
  Algorithm / Pseudocode:
  meld(H2):
    if H2 is empty, return
    if current heap is empty, adopt H2's min and size
    else:
      splice H2's root list into current root list
      if H2's min is smaller than current min, update min pointer
      add H2's size to current size
  */

  // EXTRACT-MIN
  // Time Complexity: O(log N) amortized
  // Space Complexity: O(log N) auxillary from consolidate
  int extractMin() {
    Node *z = min;
    if (!z)
      return -1;

    // add all children of min node to the root list
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

    // remove z (old min) from root list
    z->left->right = z->right;
    z->right->left = z->left;

    if (z == z->right) {
      min = nullptr; // Heap is now empty
    } else {
      min = z->right;
      consolidate(); // Combine trees of equal degree
    }

    n--;
    return z->key;
  }
  /*
  Algorithm / Pseudocode:
  extractMin():
    z = min
    if z is null return -1
    for each child x of z:
      add x to root list
      set parent of x to null
    remove z from root list
    if z was the only node in root list:
      min = null
    else:
      min = z.right
      consolidate()
    n--
    return z.key
  */
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
