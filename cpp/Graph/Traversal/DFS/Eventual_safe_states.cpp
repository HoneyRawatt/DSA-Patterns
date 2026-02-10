#include <bits/stdc++.h>
using namespace std;

/*
=====================================================
Problem Statement:
=====================================================
You are given a directed graph with V vertices
(numbered from 0 to V-1) and an adjacency list `adj`.

A node is called an **eventual safe node** if:
- Every possible path starting from this node
  eventually ends at a terminal node (a node with
  no outgoing edges).
- No path starting from this node leads to a cycle.

Your task is to return all the eventual safe nodes
of the graph in increasing order.

This problem is commonly known as:
➡ LeetCode 802 – Eventual Safe States
=====================================================
*/

/*
=====================================================
DFS helper function
Purpose:
- Detect cycles in a directed graph
- Mark nodes as safe or unsafe using DFS coloring

vis states:
0 → unvisited
1 → fully processed (safe or unsafe determined)
2 → currently in DFS path (used to detect cycles)

check array:
1 → safe node
0 → unsafe node (part of or leads to a cycle)
=====================================================
*/
bool dfscheck(int node, vector<int> adj[],
              vector<int>& vis, vector<int>& check) {

    // Mark current node as being in the DFS recursion path
    vis[node] = 2;

    // Assume node is unsafe initially
    check[node] = 0;

    // Explore all outgoing edges
    for (auto it : adj[node]) {

        // If neighbor is unvisited
        if (vis[it] == 0) {
            if (dfscheck(it, adj, vis, check)) {
                // Cycle found downstream → current node unsafe
                check[node] = 0;
                return true;
            }
        }
        // If neighbor is already in current DFS path → cycle
        else if (vis[it] == 2) {
            check[node] = 0;
            return true;
        }
    }

    // No cycle found from this node
    vis[node] = 1;   // mark as fully processed
    check[node] = 1; // mark as safe

    return false;
}

/*
=====================================================
Function: eventualSafeNodes
Purpose:
- Runs DFS for each node
- Identifies nodes that do not lead to any cycle
=====================================================
*/
vector<int> eventualSafeNodes(int V, vector<int> adj[]) {

    vector<int> vis(V, 0);    // DFS state array
    vector<int> check(V, 0);  // Safe/unsafe marker
    vector<int> safeNodes;

    // Run DFS for all nodes (handles disconnected graph)
    for (int i = 0; i < V; i++) {
        if (vis[i] == 0) {
            dfscheck(i, adj, vis, check);
        }
    }

    // Collect all safe nodes
    for (int i = 0; i < V; i++) {
        if (check[i] == 1)
            safeNodes.push_back(i);
    }

    return safeNodes;
}

// ---------------- MAIN FUNCTION ----------------
int main() {

    int V = 7;
    vector<int> adj[V];

    /*
        Example Graph:
        0 → 1 → 3 → 0   (cycle)
        ↓
        2 → 5          (safe)
        4 → 5          (safe)
        6              (safe)
    */

    adj[0] = {1, 2};
    adj[1] = {2, 3};
    adj[2] = {5};
    adj[3] = {0};
    adj[4] = {5};
    adj[5] = {};
    adj[6] = {};

    vector<int> result = eventualSafeNodes(V, adj);

    cout << "Safe Nodes: ";
    for (auto node : result)
        cout << node << " ";
    cout << endl;

    return 0;
}

/*
=====================================================
Time Complexity:
=====================================================
O(V + E)
- Each vertex is processed once
- Each edge is visited once

=====================================================
Space Complexity:
=====================================================
O(V)
- vis[] and check[] arrays
- DFS recursion stack
=====================================================
*/
