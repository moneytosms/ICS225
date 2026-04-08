#include <bits/stdc++.h>
using namespace std;

struct Node {
    int key, degree;
    Node *parent, *child, *sibling;

    Node(int k) {
        key = k;
        degree = 0;
        parent = child = sibling = nullptr;
    }
};

class BinomialHeap {
private:
    Node* head;

    // Link two binomial trees
    void linkTrees(Node* y, Node* z) {
        y->parent = z;
        y->sibling = z->child;
        z->child = y;
        z->degree++;
    }

    // Merge root lists (by degree)
    Node* mergeLists(Node* h1, Node* h2) {
        if (!h1) return h2;
        if (!h2) return h1;

        Node* head = nullptr;
        Node* tail = nullptr;

        if (h1->degree <= h2->degree) {
            head = h1;
            h1 = h1->sibling;
        } else {
            head = h2;
            h2 = h2->sibling;
        }

        tail = head;

        while (h1 && h2) {
            if (h1->degree <= h2->degree) {
                tail->sibling = h1;
                h1 = h1->sibling;
            } else {
                tail->sibling = h2;
                h2 = h2->sibling;
            }
            tail = tail->sibling;
        }

        tail->sibling = (h1) ? h1 : h2;

        return head;
    }

    // Union heaps
    Node* unionHeap(Node* h1, Node* h2) {
        Node* newHead = mergeLists(h1, h2);
        if (!newHead) return nullptr;

        Node* prev = nullptr;
        Node* curr = newHead;
        Node* next = curr->sibling;

        while (next) {
            if ((curr->degree != next->degree) ||
                (next->sibling && next->sibling->degree == curr->degree)) {
                prev = curr;
                curr = next;
            } else {
                if (curr->key <= next->key) {
                    curr->sibling = next->sibling;
                    linkTrees(next, curr);
                } else {
                    if (!prev)
                        newHead = next;
                    else
                        prev->sibling = next;

                    linkTrees(curr, next);
                    curr = next;
                }
            }
            next = curr->sibling;
        }

        return newHead;
    }

public:
    BinomialHeap() { 
        head = nullptr;
    }

    // Insert
    // Time Complexity: O(log N)
    // Space Complexity: O(1)
    void insert(int key) {
        Node* temp = new Node(key);
        head = unionHeap(head, temp);
    }

    // Get minimum
    // Time Complexity: O(log N)
    // Space Complexity: O(1)
    int getMin() {
        if (!head) return -1;

        Node* curr = head;
        int mn = curr->key;

        while (curr) {
            mn = min(mn, curr->key);
            curr = curr->sibling;
        }
        return mn;
    }

    // Extract minimum
    // Time Complexity: O(log N)
    // Space Complexity: O(1) auxiliary
    int extractMin() {
        if (!head) return -1;

        Node *minNode = head, *minPrev = nullptr;
        Node *curr = head, *prev = nullptr;

        int mn = curr->key;

        while (curr) {
            if (curr->key < mn) {
                mn = curr->key;
                minNode = curr;
                minPrev = prev;
            }
            prev = curr;
            curr = curr->sibling;
        }

        // Remove minNode
        if (minPrev)
            minPrev->sibling = minNode->sibling;
        else
            head = minNode->sibling;

        // Reverse children
        Node* child = minNode->child;
        Node* rev = nullptr;

        while (child) {
            Node* next = child->sibling;
            child->sibling = rev;
            child->parent = nullptr;
            rev = child;
            child = next;
        }

        head = unionHeap(head, rev);

        return mn;
    }

    // Print heap (for debugging)
    void print() {
        Node* curr = head;
        while (curr) {
            cout << "B" << curr->degree << ": ";
            printTree(curr);
            cout << "\n";
            curr = curr->sibling;
        }
    }

    void printTree(Node* root) {
        if (!root) return;
        cout << root->key << " ";
        printTree(root->child);
        printTree(root->sibling);
    }
};

int main() {
    BinomialHeap h;

    h.insert(10);
    h.insert(20);
    h.insert(5);
    h.insert(30);

    cout << "Min: " << h.getMin() << "\n";

    cout << "Extracted Min: " << h.extractMin() << "\n";

    cout << "New Min: " << h.getMin() << "\n";

    return 0;
}