#include <bits/stdc++.h>
using namespace std;

/*
🎯 GOAL:
Find the shortest distance from the source node `src` to all other vertices
in a weighted graph using Dijkstra’s Algorithm.

🧩 Given:
`adj` is a 2D vector where each element is of the form [u, v, w]
meaning there is an edge from node u → v with weight w.
The graph can be undirected, so we’ll also consider v → u.
*/

// Dijkstra’s Algorithm (works directly on edge list)
class Solution {
  public:
    vector<int> dijkstra(int V, vector<vector<int>> &adj, int src) {
        // Step 1️⃣: Initialize distance array
        vector<int> dist(V, 1e9);  // large number as infinity
        dist[src] = 0;

        // Step 2️⃣: Min-heap (priority queue) storing {distance, node}
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        pq.push({0, src});

        // Step 3️⃣: Standard Dijkstra loop
        while (!pq.empty()) {
            int dis = pq.top().first;   // current known shortest distance
            int node = pq.top().second; // current node
            pq.pop();

            // Step 4️⃣: Relax all edges starting from this node
            for (auto &edge : adj) {
                int u = edge[0];
                int v = edge[1];
                int w = edge[2];

                // Forward direction (u → v)
                if (u == node && dis + w < dist[v]) {
                    dist[v] = dis + w;
                    pq.push({dist[v], v});
                }

                // Reverse direction (v → u) — because graph is undirected
                if (v == node && dis + w < dist[u]) {
                    dist[u] = dis + w;
                    pq.push({dist[u], u});
                }
            }
        }

        // Step 5️⃣: Return all shortest distances
        return dist;
    }
};

// 🧪 Driver Code
int main() {
    int V = 6;
    vector<vector<int>> edges = {
        {0, 1, 4},
        {0, 2, 4},
        {1, 2, 2},
        {2, 3, 3},
        {2, 4, 1},
        {2, 5, 6},
        {3, 5, 2},
        {4, 5, 3}
    };

    int src = 0;
    Solution obj;
    vector<int> result = obj.dijkstra(V, edges, src);

    cout << "Shortest distances from node " << src << ":\n";
    for (int i = 0; i < V; i++)
        cout << "Node " << i << " -> " << result[i] << "\n";

    return 0;
}

/*
🧠 ALGORITHM EXPLANATION:
----------------------------------
1️⃣  Initialize all distances as infinity (1e9), except `src = 0`.
2️⃣  Use a min-heap to always pick the node with the smallest distance.
3️⃣  For every edge [u, v, w], if u == current node → relax v.
4️⃣  If the graph is undirected, also relax the reverse edge (v == node).
5️⃣  Continue until all reachable nodes are processed.

📈 TIME COMPLEXITY:
----------------------------------
- For each node, we iterate over all edges (E edges total).
- Each push/pop in the priority queue takes O(log V).
- ⏱️ O(E × log V × possible relaxations) ≈ O(E × log V)
  But since we’re not using adjacency lists, it’s closer to O(V × E).

📦 SPACE COMPLEXITY:
----------------------------------
- Distance array: O(V)
- Priority queue:  O(V)
- Input edges:     O(E)
✅ Total: O(V + E)
*/
