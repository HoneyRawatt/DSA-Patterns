#include <bits/stdc++.h>
using namespace std;

/*
=====================================================
DFS helper function to detect a cycle
=====================================================

We use a **3-state visited array**:
0 → unvisited
1 → completely processed (DFS finished)
2 → currently in DFS recursion path

👉 If we ever visit a node that is already in state `2`,
   it means we found a **back edge**, hence a cycle.
*/
bool dfscheck(int node, vector<int> adj[], vector<int>& vis) {

    // Mark current node as part of the current DFS path
    vis[node] = 2;

    // Traverse all adjacent nodes
    for (auto it : adj[node]) {

        // If the adjacent node is unvisited
        if (vis[it] == 0) {
            // Recur DFS on that node
            if (dfscheck(it, adj, vis))
                return true; // cycle detected in deeper call
        }
        // If the adjacent node is already in current DFS path
        else if (vis[it] == 2) {
            // Back edge found → cycle exists
            return true;
        }
    }

    // After exploring all neighbors, mark node as fully processed
    vis[node] = 1;

    // No cycle found from this node
    return false;
}

/*
=====================================================
Function to check cycle in a directed graph
=====================================================

- Handles **disconnected graphs**
- Calls DFS from every unvisited node
*/
bool isCycle(int V, vector<int> adj[]) {

    // Visited array:
    // 0 = unvisited, 1 = processed, 2 = in current DFS path
    vector<int> vis(V, 0);

    // Check all components of the graph
    for (int i = 0; i < V; i++) {
        if (vis[i] == 0) {
            if (dfscheck(i, adj, vis))
                return true; // cycle found
        }
    }

    // No cycle found in any component
    return false;
}

// ---------------- MAIN FUNCTION ----------------
int main() {

    int V = 4;
    vector<int> adj[V];

    /*
        Example Directed Graph:
        0 → 1 → 2
        ↑         |
        └─────────┘

        Node 3 is isolated
    */

    adj[0] = {1};
    adj[1] = {2};
    adj[2] = {0};  // creates a cycle
    adj[3] = {};   // isolated node

    // Check if cycle exists
    if (isCycle(V, adj))
        cout << "Graph contains a cycle" << endl;
    else
        cout << "Graph does not contain a cycle" << endl;

    return 0;
}

/*
=====================================================
Time Complexity:
=====================================================
O(V + E)
- Each vertex is visited once
- Each edge is checked once during DFS

=====================================================
Space Complexity:
=====================================================
O(V)
- Visited array
- Recursion stack (worst case)
*/
