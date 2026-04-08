#include <bits/stdc++.h>
using namespace std;

// Build suffix array (simple version)
// Time Complexity: O(N^2 log N)
// Space Complexity: O(N^2)
vector<int> buildSA(string s) {
    int n = s.size();
    vector<pair<string, int>> suffixes;

    // Generate all suffixes with their original starting indices
    for (int i = 0; i < n; i++) {
        suffixes.push_back({s.substr(i), i});
    }

    // Sort suffixes lexicographically
    sort(suffixes.begin(), suffixes.end());

    // Extract just the indices to form the suffix array
    vector<int> sa;
    for (auto &p : suffixes)
        sa.push_back(p.second);

    return sa;
}
/*
Algorithm / Pseudocode:
buildSA(s):
  create list of suffixes
  for i from 0 to len(s) - 1:
    add (s.substring(i), i) to suffixes
  sort suffixes alphabetically
  return list of indices from sorted suffixes
*/

// Compare pattern with suffix
// Time Complexity: O(M) where M is pattern length
// Space Complexity: O(1)
int compare(string &text, int pos, string &pat) {
    int n = text.size(), m = pat.size();

    for (int i = 0; i < m; i++) {
        if (pos + i >= n) return -1; // Suffix is shorter than pattern

        if (text[pos + i] < pat[i]) return -1; // Suffix comes before pattern
        if (text[pos + i] > pat[i]) return 1;  // Suffix comes after pattern
    }

    return 0; // Prefix match
}
/*
Algorithm / Pseudocode:
compare(text, pos, pat):
  for i from 0 to len(pat) - 1:
    if pos+i >= len(text): return -1
    if text[pos+i] < pat[i]: return -1
    if text[pos+i] > pat[i]: return 1
  return 0
*/

// Binary search in suffix array
// Time Complexity: O(M log N)
// Space Complexity: O(1)
bool search(string &text, vector<int> &sa, string &pat) {
    int l = 0, r = sa.size() - 1;

    // Standard binary search over sorted suffix indices
    while (l <= r) {
        int mid = (l + r) / 2;

        int res = compare(text, sa[mid], pat);

        if (res == 0)
            return true; // Pattern is a prefix of this suffix
        else if (res < 0)
            l = mid + 1; // Pattern is lexicographically greater
        else
            r = mid - 1; // Pattern is lexicographically smaller
    }

    return false;
}
/*
Algorithm / Pseudocode:
search(text, sa, pat):
  l = 0, r = len(sa) - 1
  while l <= r:
    mid = (l + r) / 2
    res = compare(text, sa[mid], pat)
    if res == 0: return true
    if res < 0: l = mid + 1
    else: r = mid - 1
  return false
*/

int main() {
    string text = "banana";
    vector<int> sa = buildSA(text);

    string pattern = "ana";

    if (search(text, sa, pattern))
        cout << "Pattern found\n";
    else
        cout << "Pattern not found\n";

    return 0;
}