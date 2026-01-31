#include <bits/stdc++.h>
using namespace std;

// DFS helper to detect cycle in a directed graph using 3-state coloring
bool dfscheck(int node, vector<int> adj[], vector<int>& vis) {
    vis[node] = 2; // mark node as "in current DFS path"

    for (auto it : adj[node]) {
        if (vis[it] == 0) { // unvisited
            if (dfscheck(it, adj, vis)) return true;
        }
        else if (vis[it] == 2) { // back edge detected
            return true;
        }
    }

    vis[node] = 1; // mark node as fully processed
    return false;
}

// Function to detect cycle in a directed graph
bool isCycle(int V, vector<int> adj[]) {
    vector<int> vis(V, 0); // 0 = unvisited, 1 = processed, 2 = in current DFS path
    for (int i = 0; i < V; i++) {
        if (vis[i] == 0) {
            if (dfscheck(i, adj, vis)) return true;
        }
    }
    return false;
}

// ---------------- MAIN FUNCTION ----------------
int main() {
    int V = 4;
    vector<int> adj[V];

    // Example: graph with a cycle 0->1->2->0
    adj[0] = {1};
    adj[1] = {2};
    adj[2] = {0};
    adj[3] = {}; // isolated node

    if (isCycle(V, adj))
        cout << "Graph contains a cycle" << endl;
    else
        cout << "Graph does not contain a cycle" << endl;

    return 0;
}

/*
Time Complexity: O(V + E)
    - Each vertex is visited once
    - Each edge is checked once

Space Complexity: O(V)
    - For visited array
    - Recursion stack can go up to O(V)
*/
 