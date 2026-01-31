#include <bits/stdc++.h>
using namespace std;

// DFS helper to detect cycle and mark safe nodes
bool dfscheck(int node, vector<int> adj[], vector<int>& vis, vector<int>& check) {
    vis[node] = 2;       // node is in current DFS path
    check[node] = 0;     // assume unsafe initially

    for (auto it : adj[node]) {
        if (vis[it] == 0) {
            if (dfscheck(it, adj, vis, check)) {
                check[node] = 0; // part of cycle
                return true;
            }
        } 
        else if (vis[it] == 2) { // back edge found → cycle
            check[node] = 0;
            return true;
        }
    }

    vis[node] = 1;   // mark as processed
    check[node] = 1; // node is safe (no cycle through it)
    return false;
}

// Function to return all eventual safe nodes
vector<int> eventualSafeNodes(int V, vector<int> adj[]) {
    vector<int> vis(V, 0);
    vector<int> check(V, 0);
    vector<int> safeNodes;

    // Run DFS for all unvisited nodes
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

    // Example: graph from LeetCode 802 - Eventual Safe States
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
🔹 Time Complexity: O(V + E)
   - Each node and edge is visited once in DFS.
🔹 Space Complexity: O(V)
   - For vis[], check[], and recursion stack.
*/
