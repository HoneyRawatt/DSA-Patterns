#include <bits/stdc++.h>
using namespace std;

/*
-------------------------------
🔹 DISJOINT SET UNION (Union-Find)
-------------------------------
Intuition:
We use DSU to group connected nodes into a single "set".
Whenever two nodes are connected (adj[i][j] == 1), 
we perform a union operation to merge their sets.

At the end, the number of provinces (connected components)
is equal to the number of unique parent nodes.
*/

class DisjointSet {
    vector<int> parent, size;

public:
    // 🔧 Constructor
    // Initializes parent[i] = i and size[i] = 1
    DisjointSet(int n) {
        size.resize(n + 1, 1);
        parent.resize(n + 1);
        for (int i = 0; i <= n; i++) parent[i] = i;
    }

    /*
    ---------------------------------
    🔍 findPar(node)
    ---------------------------------
    Intuition:
    - Finds the "ultimate parent" (representative) of a node.
    - Uses PATH COMPRESSION → directly links every visited node to root.
      → Greatly flattens the structure.

    Time Complexity: O(α(N)) ≈ constant (Inverse Ackermann)
    Space Complexity: O(1)
    */
    int findPar(int node) {
        if (node == parent[node]) return node;
        return parent[node] = findPar(parent[node]);  // path compression
    }

    /*
    ---------------------------------
    🔗 unionBySize(u, v)
    ---------------------------------
    Intuition:
    - Connects two sets by linking smaller set’s root under the larger one.
      → Keeps tree shallow for efficiency.

    Time Complexity: O(α(N)) ≈ constant
    Space Complexity: O(1)
    */
    void unionBySize(int u, int v) {
        int ulp_u = findPar(u);
        int ulp_v = findPar(v);
        if (ulp_u == ulp_v) return;  // already in same set

        // Attach smaller tree under larger
        if (size[ulp_u] < size[ulp_v]) {
            parent[ulp_u] = ulp_v;
            size[ulp_v] += size[ulp_u];
        } else {
            parent[ulp_v] = ulp_u;
            size[ulp_u] += size[ulp_v];
        }
    }
};

/*
---------------------------------
🏙️ numProvinces(adj, V)
---------------------------------
Intuition:
- Given adjacency matrix, use DSU to merge directly or indirectly connected cities.
- Finally, count how many "ultimate parents" exist = number of provinces.

Steps:
1. Traverse upper triangle of adj matrix (since it's undirected).
2. For every edge (i, j) where adj[i][j] == 1, do unionBySize(i, j).
3. Count how many nodes are their own parent.

Time Complexity: 
  - Outer loops → O(V²)
  - Each DSU operation → O(α(N)) ≈ constant
  => Total ≈ O(V²)

Space Complexity:
  - DSU arrays: O(V)
  - Adjacency matrix: O(V²)
  => Total ≈ O(V²)
*/
int numProvinces(vector<vector<int>> &adj, int V) {
    DisjointSet ds(V);

    for (int i = 0; i < V; i++) {
        for (int j = i + 1; j < V; j++) {  // avoid duplicate edges
            if (adj[i][j] == 1) {
                ds.unionBySize(i, j);
            }
        }
    }

    int cnt = 0;
    for (int i = 0; i < V; i++) {
        if (ds.findPar(i) == i) cnt++;
    }
    return cnt;
}

/*
---------------------------------
🧭 main() — Example driver
---------------------------------
Input:
  V = 3
  adj = [
    [1, 1, 0],
    [1, 1, 0],
    [0, 0, 1]
  ]

Explanation:
  - City 0 ↔ 1 are connected → one province.
  - City 2 is isolated → second province.
Output: 2
*/
int main() {
    int V = 3;
    vector<vector<int>> adj = {
        {1, 1, 0},
        {1, 1, 0},
        {0, 0, 1}
    };

    cout << "Number of Provinces: " << numProvinces(adj, V) << endl;

    return 0;
}

/*
---------------------------------
🧩 TOTAL COMPLEXITY SUMMARY
---------------------------------
DisjointSet Constructor:  O(V)
findPar():                O(α(N)) ≈ constant
unionBySize():            O(α(N)) ≈ constant
numProvinces():           O(V²)
---------------------------------
✅ Total Time:  O(V²)
✅ Total Space: O(V²)
---------------------------------
*/
