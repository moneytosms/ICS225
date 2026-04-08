#include <bits/stdc++.h>
using namespace std;

class MinHeap {
    vector<int> heap;

    // Heapify up (for insert)
    // Time Complexity: O(log N)
    // Space Complexity: O(1)
    void heapify_up(int i) {
        while (i > 0) {
            int parent = (i - 1) / 2;
            if (heap[parent] > heap[i]) {
                swap(heap[parent], heap[i]);
                i = parent;
            } else break;
        }
    }

    // Heapify down (for delete)
    // Time Complexity: O(log N)
    // Space Complexity: O(1)
    void heapify_down(int i) {
        int n = heap.size();
        while (true) {
            int left = 2 * i + 1;
            int right = 2 * i + 2;
            int smallest = i;

            if (left < n && heap[left] < heap[smallest])
                smallest = left;

            if (right < n && heap[right] < heap[smallest])
                smallest = right;

            if (smallest != i) {
                swap(heap[i], heap[smallest]);
                i = smallest;
            } else break;
        }
    }

public:
    // Insert element
    // Time Complexity: O(log N)
    // Space Complexity: O(1)
    void insert(int val) {
        heap.push_back(val);
        heapify_up(heap.size() - 1);
    }

    // Get minimum element
    // Time Complexity: O(1)
    // Space Complexity: O(1)
    int getMin() {
        if (heap.empty()) return -1;
        return heap[0];
    }

    // Remove minimum element
    // Time Complexity: O(log N)
    // Space Complexity: O(1)
    void extractMin() {
        if (heap.empty()) return;

        heap[0] = heap.back();
        heap.pop_back();
        heapify_down(0);
    }

    // Print heap
    void print() {
        for (int x : heap) cout << x << " ";
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

    cout << "Heap elements: ";
    h.print();

    cout << "Min element: " << h.getMin() << "\n";

    h.extractMin();

    cout << "After extracting min: ";
    h.print();

    return 0;
}