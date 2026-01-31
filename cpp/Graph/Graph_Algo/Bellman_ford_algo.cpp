#include <bits/stdc++.h>
using namespace std;

/*
Intuition:
------------
The Bellman-Ford algorithm is used to find the shortest path from a single source to 
all vertices in a weighted graph (can have negative weights).

It works by repeatedly relaxing all edges (V-1) times.
Relaxation means: if the current known distance to a vertex 'v' can be improved by 
going through 'u', then update it.

After (V-1) relaxations, if we can still relax any edge, it means there's a negative 
weight cycle.

Steps:
1. Initialize all distances as infinity, except source S = 0.
2. Relax all edges (V-1) times.
3. Check for negative weight cycles by one more relaxation.

Time Complexity:  O(V * E)
Space Complexity: O(V)
*/

vector<int> bellman_ford(int V, vector<vector<int>>& edges, int S) {
    // Step 1: Initialize distances
    vector<int> dist(V, 1e9);
    dist[S] = 0;

    // Step 2: Relax all edges (V-1) times
    for (int i = 0; i < V - 1; i++) {
        for (auto it : edges) {
            int u = it[0];
            int v = it[1];
            int wt = it[2];
            if (dist[u] != 1e9 && dist[u] + wt < dist[v]) {
                dist[v] = dist[u] + wt;
            }
        }
    }

    // Step 3: Check for negative weight cycle
    for (auto it : edges) {
        int u = it[0];
        int v = it[1];
        int wt = it[2];
        if (dist[u] != 1e9 && dist[u] + wt < dist[v]) {
            return {-1}; // Negative cycle detected
        }
    }

    return dist;
}

// ----------------------
// Driver Code (Example)
// ----------------------
int main() {
    int V = 5; // Number of vertices
    vector<vector<int>> edges = {
        {0, 1, -1},
        {0, 2, 4},
        {1, 2, 3},
        {1, 3, 2},
        {1, 4, 2},
        {3, 2, 5},
        {3, 1, 1},
        {4, 3, -3}
    };

    int S = 0;
    vector<int> ans = bellman_ford(V, edges, S);

    if (ans.size() == 1 && ans[0] == -1) {
        cout << "Negative weight cycle detected\n";
    } else {
        cout << "Shortest distances from source " << S << ":\n";
        for (int i = 0; i < V; i++) {
            cout << "Node " << i << " -> " << ans[i] << "\n";
        }
    }

    return 0;
}
