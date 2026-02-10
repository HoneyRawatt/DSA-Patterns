#include <bits/stdc++.h>
using namespace std;

/*
Approach:
---------
We detect a cycle in an undirected graph using BFS.

1️⃣ For every unvisited node, we start a BFS traversal.
2️⃣ Each queue element stores {currentNode, parentNode}.
3️⃣ While traversing:
    - If an adjacent node is already visited
    - AND it is NOT the parent of the current node
      → a cycle exists.
4️⃣ If BFS finishes for all components without finding such a case,
   then the graph has no cycle.

Time Complexity:  O(V + E)
Space Complexity: O(V)
*/

// BFS helper function to detect cycle starting from a source node
bool detect(int src, vector<int> adj[], int vis[]) {

    // Mark the source node as visited
    vis[src] = 1;

    // Queue stores pair of (node, parent)
    queue<pair<int, int>> q;

    // Push source node with parent as -1 (no parent)
    q.push({src, -1});

    // BFS traversal
    while (!q.empty()) {

        // Get front element of queue
        int node = q.front().first;
        int parent = q.front().second;
        q.pop();

        // Traverse all adjacent nodes
        for (auto adjacentNode : adj[node]) {

            // If adjacent node is not visited, visit it
            if (!vis[adjacentNode]) {
                vis[adjacentNode] = 1;
                q.push({adjacentNode, node});
            }
            // If adjacent node is visited and is not the parent,
            // then a cycle is detected
            else if (adjacentNode != parent) {
                return true;
            }
        }
    }

    // No cycle found in this BFS traversal
    return false;
}

// Function to check cycle in entire graph
bool isCycle(int V, vector<int> adj[]) {

    // Visited array to track visited vertices
    int vis[V] = {0};

    // Check each connected component
    for (int i = 0; i < V; i++) {

        // If node is not visited, perform BFS
        if (!vis[i]) {
            if (detect(i, adj, vis))
                return true;
        }
    }

    // No cycle found in any component
    return false;
}

int main() {

    int V = 5;
    vector<int> adj[V];

    /*
        Example Graph:
        0 - 1 - 2
            |   |
            ----3

        Cycle exists: 1 → 2 → 3 → 1
    */

    // Adding edges (undirected graph)
    adj[0].push_back(1);
    adj[1].push_back(0);

    adj[1].push_back(2);
    adj[2].push_back(1);

    adj[2].push_back(3);
    adj[3].push_back(2);

    adj[3].push_back(1); // Back edge creates a cycle
    adj[1].push_back(3);

    // Check if cycle exists
    if (isCycle(V, adj))
        cout << "Cycle Detected!" << endl;
    else
        cout << "No Cycle Found." << endl;

    return 0;
}
