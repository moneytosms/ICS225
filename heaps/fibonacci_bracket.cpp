#include <bits/stdc++.h>
using namespace std;
struct Node {
  int val;
  vector<Node *> children;
};
Node *parse(const string &s, int &pos) {
  int val = 0;
  while (pos < s.length() && isdigit(s[pos])) {
    val = val * 10 + (s[pos] - '0');
    pos++;
  }
  Node *node = new Node{val, {}};
  if (pos < s.length() && s[pos] == '(') {
    pos++;
    if (pos < s.length() && s[pos] == ')') {
      pos++;
    } else {
      while (pos < s.length() && s[pos] != ')') {
        node->children.push_back(parse(s, pos));
        if (pos < s.length() && s[pos] == ',') {
          pos++;
        }
      }
      if (pos < s.length() && s[pos] == ')') {
        pos++;
      }
    }
  }
  return node;
}
string to_bracket_string(Node *node) {
  string res = to_string(node->val);
  if (!node->children.empty()) {
    res += "(";
    for (int i = 0; i < (int)node->children.size(); i++) {
      res += to_bracket_string(node->children[i]);
      if (i + 1 < (int)node->children.size())
        res += ",";
    }
    res += ")";
  }
  return res;
}
int main() {
  int n;
  if (!(cin >> n))
    return 0;
  vector<Node *> roots;
  for (int i = 0; i < n; i++) {
    string s;
    cin >> s;
    int pos = 0;
    roots.push_back(parse(s, pos));
  }
  if (roots.empty())
    return 0;
  int min_idx = 0;
  for (int i = 1; i < (int)roots.size(); i++) {
    if (roots[i]->val < roots[min_idx]->val) {
      min_idx = i;
    }
  }
  Node *min_node = roots[min_idx];
  vector<Node *> next_roots;
  for (int i = 0; i < (int)roots.size(); i++) {
    if (i != min_idx) {
      next_roots.push_back(roots[i]);
    }
  }
  for (Node *child : min_node->children) {
    next_roots.push_back(child);
  }
  vector<Node *> degree_map(100, nullptr);
  for (Node *curr : next_roots) {
    int d = curr->children.size();
    while (degree_map[d] != nullptr) {
      Node *other = degree_map[d];
      if (curr->val > other->val) {
        swap(curr, other);
      }
      curr->children.insert(curr->children.begin(), other);
      degree_map[d] = nullptr;
      d++;
    }
    degree_map[d] = curr;
  }
  vector<Node *> final_roots;
  for (int i = 0; i < 100; i++) {
    if (degree_map[i] != nullptr) {
      final_roots.push_back(degree_map[i]);
    }
  }
  if (final_roots.empty())
    return 0;
  sort(final_roots.begin(), final_roots.end(),
       [](Node *a, Node *b) { return a->val < b->val; });
  int new_min_val = final_roots[0]->val;
  int new_min_idx = 0;
  for (int i = 1; i < (int)final_roots.size(); i++) {
    if (final_roots[i]->val < new_min_val) {
      new_min_val = final_roots[i]->val;
      new_min_idx = i;
    }
  }
  cout << new_min_val << "\n";
  for (int i = 0; i < (int)final_roots.size(); i++) {
    int idx = (new_min_idx + i) % final_roots.size();
    cout << to_bracket_string(final_roots[idx]) << "\n";
  }
  return 0;
}
