#include <bits/stdc++.h>
using namespace std;

// DFS function to detect a cycle in an undirected graph
bool dfs(int node, int parent, vector<int>& vis, vector<int> adj[]) {
    vis[node] = 1; // mark current node as visited
    for (auto adjnode : adj[node]) {
        // if the adjacent node is not visited, explore it recursively
        if (!vis[adjnode]) {
            if (dfs(adjnode, node, vis, adj))
                return true; // cycle found in recursion
        } 
        // if the adjacent node is already visited and not the parent → cycle detected
        else if (adjnode != parent) {
            return true;
        }
    }
    return false; // no cycle found in this path
}

// Function to check if the graph contains a cycle
bool isCycle(int V, vector<int> adj[]) {
    vector<int> vis(V, 0); // visited array, initially all 0

    for (int i = 0; i < V; i++) {
        if (!vis[i]) {
            // Run DFS for each unvisited node (handles disconnected components)
            if (dfs(i, -1, vis, adj))
                return true;
        }
    }
    return false; // no cycle found in any component
}

int main() {
    int V = 5;
    vector<int> adj[V];

    // Example undirected graph
    adj[0].push_back(1);
    adj[1].push_back(0);
    adj[1].push_back(2);
    adj[2].push_back(1);
    adj[2].push_back(3);
    adj[3].push_back(2);
    adj[3].push_back(4);
    adj[4].push_back(3);
    adj[4].push_back(1); // adds a cycle

    cout << (isCycle(V, adj) ? "Cycle Found" : "No Cycle") << endl;
    return 0;
}


// | Type      | Complexity | Explanation                                          |
// | --------- | ---------- | ---------------------------------------------------- |
// | **Time**  | `O(V + E)` | Each vertex & edge processed once                    |
// | **Space** | `O(V + E)` | For adjacency list + recursion stack + visited array |
