#include <iostream>
using namespace std;

// ─────────────────────────────────────────────────────────────────────────────
// Node
// ─────────────────────────────────────────────────────────────────────────────
struct Node {
  int key;
  Node *left;
  Node *right;
  bool rightThread; // true  → right points to inorder successor (thread)
                    // false → right points to a real child

  explicit Node(int k)
      : key(k), left(nullptr), right(nullptr), rightThread(false) {}
};

// ─────────────────────────────────────────────────────────────────────────────
// Right-Threaded Binary Search Tree
//
//  Every null right pointer is replaced by a thread to the node's inorder
//  successor, enabling O(1)-space inorder traversal without a stack.
// ─────────────────────────────────────────────────────────────────────────────
class TBT {
public:
  Node *root;

  TBT() : root(nullptr) {}

  // ── Helpers ────────────────────────────────────────────────────────────────

  // Leftmost (smallest) node in subtree rooted at `node`.
  Node *leftmost(Node *node) {
    while (node && node->left)
      node = node->left;
    return node;
  }

  // Rightmost node in subtree rooted at `node`.
  // In a right-threaded BST the rightmost node always has rightThread = true
  // (its right pointer is a thread to its inorder successor, not a real child).
  Node *rightmostOf(Node *node) {
    while (!node->rightThread)
      node = node->right;
    return node;
  }

  // ── Insert ─────────────────────────────────────────────────────────────────
  // Time Complexity: O(H) where H is tree height
  // Space Complexity: O(1)
  Node *insert(Node *root, int key) {
    Node *curr = root;
    Node *parent = nullptr;

    while (curr) {
      if (key == curr->key)
        return root; // duplicate – silently ignore
      parent = curr;
      if (key < curr->key) {
        if (!curr->left)
          break; // left slot is free
        curr = curr->left;
      } else {
        if (curr->rightThread)
          break; // right slot is a thread, not a child
        curr = curr->right;
      }
    }

    Node *node = new Node(key);

    if (!parent) { // first node in the tree
      root = node;
    } else if (key < parent->key) {
      node->right = parent; // thread to inorder successor (parent)
      node->rightThread = true;
      parent->left = node;
    } else {
      node->right = parent->right; // inherit parent's old thread / nullptr
      node->rightThread = true;
      parent->right = node;
      parent->rightThread = false; // parent now has a real right child
    }

    return root;
  }

  // ── Remove ─────────────────────────────────────────────────────────────────
  // Time Complexity: O(H)
  // Space Complexity: O(1)
  //
  // Four structural cases:
  //
  //  1. Leaf              (!left &&  rightThread)
  //  2. Only left subtree ( left &&  rightThread)
  //  3. Only right subtree(!left && !rightThread)
  //  4. Two children      ( left && !rightThread)
  //
  Node *remove(Node *root, int key) {
    Node *parent = nullptr;
    Node *curr = root;
    bool isLeft = false; // is curr the left child of parent?

    // ── 1. Locate the node ──────────────────────────────────────────────────
    while (curr) {
      if (key == curr->key)
        break;
      parent = curr;
      if (key < curr->key) {
        isLeft = true;
        curr = curr->left;
      } else {
        if (curr->rightThread) {
          curr = nullptr;
          break;
        } // thread → not found
        isLeft = false;
        curr = curr->right;
      }
    }

    if (!curr) {
      cout << key << " not found – nothing removed.\n";
      return root;
    }

    // ── 2. Case: Two children ───────────────────────────────────────────────
    //    Replace node's key with its inorder successor's key, then delete the
    //    successor (which is guaranteed to have no left child).
    if (curr->left && !curr->rightThread) {

      Node *succParent = curr;
      Node *succ = curr->right;
      while (succ->left) { // descend to leftmost of right subtree
        succParent = succ;
        succ = succ->left;
      }

      curr->key = succ->key; // overwrite with successor's value

      // succ has no left child; it is either a leaf or has only a right
      // subtree.
      if (succ->rightThread) {
        // succ is a leaf ────────────────────────────────────────────────────
        if (succParent == curr)
          curr->right = succ->right, curr->rightThread = true;
        // succ was curr's direct right child; curr inherits succ's thread.
        else
          succParent->left = nullptr;
        // succ was reached via left links; its inorder successor is succParent.
      } else {
        // succ has only a right subtree ──────────────────────────────────────
        if (succParent == curr)
          curr->right = succ->right; // curr->rightThread already false
        else
          succParent->left = succ->right;
      }

      delete succ;
      return root;
    }

    // ── 3. Case: Leaf ───────────────────────────────────────────────────────
    if (!curr->left && curr->rightThread) {
      if (!parent)
        root = nullptr;
      else if (isLeft)
        parent->left = nullptr;
      else {
        parent->right = curr->right; // parent inherits the thread
        parent->rightThread = true;
      }
      delete curr;
      return root;
    }

    // ── 4. Case: Only right subtree ─────────────────────────────────────────
    if (!curr->left && !curr->rightThread) {
      if (!parent)
        root = curr->right;
      else if (isLeft)
        parent->left = curr->right;
      else
        parent->right = curr->right; // parent->rightThread stays false
      delete curr;
      return root;
    }

    // ── 5. Case: Only left subtree ──────────────────────────────────────────
    //    The rightmost node in the left subtree was threading to curr.
    //    Re-point that thread to curr's inorder successor before unlinking.
    {
      Node *rm = rightmostOf(curr->left);
      rm->right = curr->right; // redirect thread past the deleted node

      if (!parent)
        root = curr->left;
      else if (isLeft)
        parent->left = curr->left;
      else {
        parent->right = curr->left;
        parent->rightThread = false;
      }
      delete curr;
      return root;
    }
  }

  // ── Inorder traversal ──────────────────────────────────────────────────────
  // Time Complexity: O(N)
  // Space Complexity: O(1)
  void inorder(Node *root) {
    Node *curr = leftmost(root);
    while (curr) {
      cout << curr->key << " ";
      curr = curr->rightThread ? curr->right : leftmost(curr->right);
    }
  }

  // ── Search ─────────────────────────────────────────────────────────────────
  // Time Complexity: O(H)
  // Space Complexity: O(1)
  Node *search(Node *root, int key) {
    Node *curr = root;
    while (curr) {
      if (key == curr->key)
        return curr;
      if (key < curr->key) {
        curr = curr->left;
      } else {
        if (curr->rightThread)
          return nullptr;
        curr = curr->right;
      }
    }
    return nullptr;
  }
};

// ─────────────────────────────────────────────────────────────────────────────
// Main – demonstrates all four deletion cases
//
//  Starting tree  :  1  3  4  5  6  7  8
//
//  Delete  6  → leaf              (left child,  no children)
//  Delete  7  → only right child  (8 remains after 6 removed)
//  Delete  4  → leaf              (right child, no children)
//  Delete  3  → only left child   (1 remains after 4 removed)
//  Delete  5  → two children      (root deletion)
//  Delete 99  → not found
// ─────────────────────────────────────────────────────────────────────────────
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  TBT tree;
  int keys[] = {5, 3, 7, 1, 4, 6, 8};

  cout << "Inserting   : ";
  for (int k : keys) {
    tree.root = tree.insert(tree.root, k);
    cout << k << " ";
  }
  cout << "\n";

  cout << "Inorder     : ";
  tree.inorder(tree.root); // 1 3 4 5 6 7 8
  cout << "\n\n";

  // ── Case 1a: Leaf – left child ────────────────────────────────────────────
  cout << "Delete  6 (leaf – left child of 7)\n";
  tree.root = tree.remove(tree.root, 6);
  cout << "Inorder     : ";
  tree.inorder(tree.root); // 1 3 4 5 7 8
  cout << "\n\n";

  // ── Case 3: Only right subtree ───────────────────────────────────────────
  cout << "Delete  7 (only right subtree – right child of 5)\n";
  tree.root = tree.remove(tree.root, 7);
  cout << "Inorder     : ";
  tree.inorder(tree.root); // 1 3 4 5 8
  cout << "\n\n";

  // ── Case 1b: Leaf – right child ───────────────────────────────────────────
  cout << "Delete  4 (leaf – right child of 3)\n";
  tree.root = tree.remove(tree.root, 4);
  cout << "Inorder     : ";
  tree.inorder(tree.root); // 1 3 5 8
  cout << "\n\n";

  // ── Case 2: Only left subtree ─────────────────────────────────────────────
  cout << "Delete  3 (only left subtree – left child of 5)\n";
  tree.root = tree.remove(tree.root, 3);
  cout << "Inorder     : ";
  tree.inorder(tree.root); // 1 5 8
  cout << "\n\n";

  // ── Case 4: Two children (root deletion) ──────────────────────────────────
  cout << "Delete  5 (two children – root)\n";
  tree.root = tree.remove(tree.root, 5);
  cout << "Inorder     : ";
  tree.inorder(tree.root); // 1 8
  cout << "\n\n";

  // ── Key not found ─────────────────────────────────────────────────────────
  cout << "Delete 99 (not in tree)\n";
  tree.root = tree.remove(tree.root, 99);
  cout << "Inorder     : ";
  tree.inorder(tree.root); // 1 8 (unchanged)
  cout << "\n";

  return 0;
}
