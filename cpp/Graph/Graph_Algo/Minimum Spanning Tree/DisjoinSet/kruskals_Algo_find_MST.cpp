#include <bits/stdc++.h>
using namespace std;

/*
📘 Intuition:
We’re using Disjoint Set Union (DSU) to efficiently detect cycles while building
the Minimum Spanning Tree (MST) using Kruskal’s algorithm.

Kruskal’s algorithm sorts all edges by weight and adds the smallest edge
that doesn’t form a cycle — DSU helps quickly check whether two nodes are already connected.
*/

class DisjoinSet {
    vector<int>parent, size;

public:
    // 🧩 Constructor: initialize parent, rank, and size
    DisjoinSet(int n) {
        size.resize(n + 1, 1);
        parent.resize(n + 1);
        for (int i = 0; i <= n; i++) parent[i] = i;
    }

    // 🔍 Find with path compression
    int findPar(int node) {
        if (node == parent[node]) return node;
        return parent[node] = findPar(parent[node]); // Path Compression
    }
    /*
    🕒 Time: O(α(N))  — α = inverse Ackermann function (≈ constant in practice)
    💾 Space: O(1) auxiliary
    ⚙️ Intuition: Path compression flattens the structure of the tree,
                  so subsequent lookups are nearly O(1).
    */

    // 🔗 Union by size
    void unionBySize(int u, int v) {
        int ulp_u = findPar(u);
        int ulp_v = findPar(v);
        if (ulp_u == ulp_v) return; // already connected

        if (size[ulp_u] < size[ulp_v]) {
            parent[ulp_u] = ulp_v;
            size[ulp_v] += size[ulp_u];
        } else {
            parent[ulp_v] = ulp_u;
            size[ulp_u] += size[ulp_v];
        }
    }
    /*
    🕒 Time: O(α(N))
    💾 Space: O(1)
    ⚙️ Intuition: Always attach the smaller tree under the larger one.
                  Keeps the tree shallow → faster future finds.
    */
};


// 🧮 Kruskal’s Algorithm for Minimum Spanning Tree
int spanningTree(int V, vector<vector<int>> adj[]) {
    vector<pair<int, pair<int, int>>> edges;

    // 🔹 Step 1: Convert adjacency list to edge list
    for (int i = 0; i < V; i++) {
        for (auto it : adj[i]) {
            int adjNode = it[0];
            int wt = it[1];
            int node = i;
            edges.push_back({wt, {node, adjNode}});
        }
    }

    // 🔹 Step 2: Sort edges by weight (smallest first)
    sort(edges.begin(), edges.end());
    /*
    🕒 Sorting Time: O(E log E)
    💾 Space: O(E)
    ⚙️ Intuition: We pick edges in increasing order of weight for MST.
    */

    DisjoinSet ds(V);
    int mstWt = 0;

    // 🔹 Step 3: Iterate over edges
    for (auto it : edges) {
        int wt = it.first;
        int u = it.second.first;
        int v = it.second.second;

        // Add edge if it doesn't form a cycle
        if (ds.findPar(u) != ds.findPar(v)) {
            mstWt += wt;
            ds.unionBySize(u, v);
        }
    }

    return mstWt;
    /*
    🕒 Overall Time Complexity:
       = O(E log E) [sorting edges] + O(E * α(N)) [DSU ops]
       ≈ O(E log E)
    💾 Space Complexity: O(V + E)
       (for DSU + edge list + recursion stack)
    ⚙️ Intuition: Kruskal picks smallest-weight edges
                  and uses DSU to efficiently avoid cycles.
    */
}


// 🧠 Example usage
int main() {
    int V = 5;
    vector<vector<int>> adj[V];

    // Example edges (u, v, weight)
    vector<tuple<int, int, int>> edges = {
        {0, 1, 2}, {0, 3, 6}, {1, 2, 3},
        {1, 3, 8}, {1, 4, 5}, {2, 4, 7}
    };

    // Build adjacency list (undirected)
    for (auto [u, v, w] : edges) {
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }

    cout << "MST Weight: " << spanningTree(V, adj) << endl;
    return 0;
}
