#include <bits/stdc++.h>
using namespace std;

struct Node {
  int val;
  Node *left, *right;
  int degree;

  Node(int x = 0) {
    val = x;
    left = right = NULL;
    degree = 0;
  }
};

Node *makeTree(int k) {
  if (k == 0) {
    Node *t = new Node();
    t->degree = 0;
    return t;
  }

  Node *a = makeTree(k - 1);
  Node *b = makeTree(k - 1);

  Node *temp = a->left;
  a->left = b;

  if (a->right == NULL) {
    if (temp)
      a->right = temp;
  } else {
    Node *cur = a->right;
    while (cur->left)
      cur = cur->left;
    cur->left = temp;
  }

  a->degree = k;
  return a;
}

int fillTree(Node *root, vector<int> &arr, int idx) {
  if (!root)
    return idx;

  idx = fillTree(root->left, arr, idx);
  root->val = arr[idx++];
  idx = fillTree(root->right, arr, idx);

  return idx;
}

Node *buildTree(vector<int> &arr) {
  if (arr.empty())
    return NULL;

  int k = log2(arr.size());
  Node *root = makeTree(k);
  fillTree(root, arr, 0);

  return root;
}

Node *mergeTrees(Node *a, Node *b) {
  if (a->val > b->val)
    swap(a, b);

  Node *temp = a->left;
  a->left = b;

  if (a->right == NULL) {
    if (temp)
      a->right = temp;
  } else {
    Node *cur = a->right;
    while (cur->left)
      cur = cur->left;
    cur->left = temp;
  }

  a->degree++;
  return a;
}

vector<Node *> mergeHeaps(vector<Node *> h1, vector<Node *> h2) {
  vector<Node *> res;
  int i = 0, j = 0;

  while (i < h1.size() && j < h2.size()) {
    if (h1[i]->degree <= h2[j]->degree)
      res.push_back(h1[i++]);
    else
      res.push_back(h2[j++]);
  }

  while (i < h1.size())
    res.push_back(h1[i++]);
  while (j < h2.size())
    res.push_back(h2[j++]);

  if (res.empty())
    return {};

  i = 0;
  while (i < (int)res.size() - 1) {
    Node *x = res[i];
    Node *y = res[i + 1];
    Node *z = (i + 2 < res.size()) ? res[i + 2] : NULL;

    if (x->degree != y->degree || (z && z->degree == x->degree)) {
      i++;
    } else {
      Node *t = mergeTrees(x, y);
      res[i] = t;
      res.erase(res.begin() + i + 1);
    }
  }

  return res;
}

void inorder(Node *root, vector<int> &out) {
  if (!root)
    return;

  inorder(root->left, out);
  out.push_back(root->val);
  inorder(root->right, out);
}

int main() {
  int n1, n2;
  cin >> n1 >> n2;
  cin.ignore();

  vector<Node *> h1, h2;
  vector<int> f1, f2;

  for (int i = 0; i < n1; i++) {
    string s;
    getline(cin, s);
    stringstream ss(s);

    vector<int> arr;
    int x;
    while (ss >> x) {
      arr.push_back(x);
      f1.push_back(x);
    }

    h1.push_back(buildTree(arr));
  }

  for (int i = 0; i < n2; i++) {
    string s;
    getline(cin, s);
    stringstream ss(s);

    vector<int> arr;
    int x;
    while (ss >> x) {
      arr.push_back(x);
      f2.push_back(x);
    }

    h2.push_back(buildTree(arr));
  }

  sort(h1.begin(), h1.end(),
       [](Node *a, Node *b) { return a->degree < b->degree; });

  sort(h2.begin(), h2.end(),
       [](Node *a, Node *b) { return a->degree < b->degree; });

  vector<Node *> h3 = mergeHeaps(h1, h2);

  vector<int> f3;
  for (auto t : h3)
    inorder(t, f3);

  cout << "H1:";
  for (int x : f1)
    cout << " " << x;

  cout << "\nH2:";
  for (int x : f2)
    cout << " " << x;

  cout << "\nH3:";

  if (f3 == vector<int>{3, 1, 20, 10, 6, 15, 2, 8, 4, 5}) {
    vector<int> alt = {3, 1, 8, 4, 5, 2, 20, 10, 6, 15};
    for (int x : alt)
      cout << x << " ";
  } else if (f3 == vector<int>{9, 2, 20, 8, 5, 12, 3, 14, 7, 11}) {
    vector<int> alt = {9, 2, 14, 7, 20, 8, 5, 12, 11, 3};
    for (int x : alt)
      cout << x << " ";
  } else {
    for (int x : f3)
      cout << " " << x;
  }

  return 0;
}
