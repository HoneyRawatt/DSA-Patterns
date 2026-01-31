#include <bits/stdc++.h>
using namespace std;

// =======================
// 🔹 Prim’s Algorithm for MST (with path output)
// =======================
// Time Complexity: O(E log V)
// → Each edge may be inserted into the min-heap, 
//    and each heap operation (push/pop) costs log V.

// Space Complexity: O(V + E)
// → For adjacency list, visited array, and min-heap.


// Convert edge list → adjacency list to store {neighbor, weight} pairs.

// Use a min-heap to always pick the smallest edge that connects a new vertex to the growing MST.

// Keep a visited array to ensure you don’t revisit nodes.

// For every new node added to MST:

// Add its edge to the path list (except the first dummy edge).

// Add all its neighbors (not yet visited) to the heap.

// Continue until all vertices are visited.

class Solution {
public:
    vector<pair<int, int>> spanningTree(int V, vector<vector<int>>& edges) {
        // Step 1: Convert edge list -> adjacency list
        vector<vector<pair<int, int>>> adj(V); // {adjNode, weight}
        for (auto it : edges) {
            int u = it[0];
            int v = it[1];
            int wt = it[2];
            adj[u].push_back({v, wt});
            adj[v].push_back({u, wt});
        }

        // Step 2: Min-heap -> {weight, {node, parent}}
        priority_queue<pair<int, pair<int, int>>,
                       vector<pair<int, pair<int, int>>>,
                       greater<pair<int, pair<int, int>>>> pq;

        vector<int> vis(V, 0); // visited array
        pq.push({0, {0, -1}}); // Start with node 0, weight 0, parent -1
        int sum = 0;           // Total MST weight
        vector<pair<int, int>> path; // To store MST edges

        // Step 3: Prim’s Algorithm
        while (!pq.empty()) {
            auto it = pq.top();
            pq.pop();

            int wt = it.first;
            int node = it.second.first;
            int parent = it.second.second;

            // Skip if already visited
            if (vis[node]) continue;

            vis[node] = 1;
            sum += wt;

            // Record the edge (ignore the first dummy -1 edge)
            if (parent != -1)
                path.push_back({parent, node});

            // Explore adjacent nodes
            for (auto nbr : adj[node]) {
                int adjNode = nbr.first;
                int edW = nbr.second;
                if (!vis[adjNode]) {
                    pq.push({edW, {adjNode, node}});
                }
            }
        }

        cout << "Total Weight of MST: " << sum << endl;
        return path;
    }
};

// =======================
// 🔹 Main Function
// =======================
int main() {
    int V = 3, E = 3;
    vector<vector<int>> edges = {{0, 1, 5}, {1, 2, 3}, {0, 2, 1}};

    Solution obj;
    vector<pair<int, int>> mstEdges = obj.spanningTree(V, edges);

    cout << "Edges in MST:\n";
    for (auto it : mstEdges) {
        cout << it.first << " - " << it.second << endl;
    }

    return 0;
}
