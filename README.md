# Algorithm Collections

This repository contains implementations of various algorithms and data structures in C++, categorized into logical directories.

## Directory Structure

*   `graphs/`: Contains graph algorithms including traversals, cycle detection, topological sorting, and strongly connected components.
    *   `all_top_sort.cpp`: All topological sorts using backtracking
    *   `bfs.cpp`: Breadth-First Search traversal
    *   `bridge-detection.cpp`: Bridge and SCC detection using Tarjan's algorithm
    *   `c_detect_print.cpp`: Cycle detection and printing using DFS
    *   `cycle_detection.cpp`: Cycle detection in an undirected graph using DFS
    *   `cycle_direct.cpp`: Cycle detection in a directed graph using DFS
    *   `dfs.cpp`: Depth-First Search traversal
    *   `kahns.cpp`: Topological sorting using Kahn's algorithm
    *   `kosaraju.cpp`: SCC detection using Kosaraju's algorithm
    *   `tarjan.cpp`: SCC detection using Tarjan's algorithm
*   `heaps/`: Contains various heap data structures implementations.
    *   `binomial_heap.cpp`: Binomial Heap implementation
    *   `fibonacci_heap.cpp`: Fibonacci Heap implementation
    *   `heap.cpp`: Min-Heap array implementation
    *   `heap_tree.cpp`: Min-Heap binary tree implementation
*   `strings/`: Contains string matching and storage algorithms.
    *   `radix_trie.cpp`: Radix Trie implementation
    *   `suffix_array.cpp`: Suffix Array construction and binary search
    *   `suffix_tree.cpp`: Suffix Tree construction and search
    *   `trie.cpp`: Standard Trie implementation
*   `trees/`: Contains implementations related to binary search trees and threaded binary trees.
    *   `bst.cpp`: Binary Search Tree basic operations
    *   `bst_inorder.cpp`: BST iterative inorder traversal
    *   `bst_to_tbt.cpp`: Conversion of BST to Threaded Binary Tree
    *   `single_tbt.cpp`: Right-Threaded Binary Search Tree operations
