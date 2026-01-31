#include <bits/stdc++.h>
using namespace std;

/*
-----------------------------------------------------
🔹 DISJOINT SET UNION (Union-Find)
-----------------------------------------------------
Intuition:
We represent each node as part of a "set".
- If two nodes are directly or indirectly connected, they belong to the same set.
- Each set is represented by one "ultimate parent".
We use:
1️⃣ Path Compression (findPar) → flattens structure for near O(1) queries
2️⃣ Union by Size → attaches smaller set under larger one
*/

class DisjoinSet {
public:
    vector<int> parent, size;

    // 🔧 Constructor
    DisjoinSet(int n) {
        size.resize(n + 1, 1);
        parent.resize(n + 1);
        for (int i = 0; i <= n; i++) parent[i] = i;
    }

    /*
    --------------------------------------------
    🔍 findPar(node)
    --------------------------------------------
    Returns the "ultimate parent" (representative) of the node.
    Uses path compression for efficiency.

    ⏱️ Time: O(α(N)) ≈ constant
    💾 Space: O(1)
    */
    int findPar(int node) {
        if (node == parent[node]) return node;
        return parent[node] = findPar(parent[node]);
    }

    /*
    --------------------------------------------
    🔗 unionBySize(u, v)
    --------------------------------------------
    Merges two components by size — smaller under larger.

    ⏱️ Time: O(α(N))
    💾 Space: O(1)
    */
    void unionBySize(int u, int v) {
        int ulp_u = findPar(u);
        int ulp_v = findPar(v);
        if (ulp_u == ulp_v) return;  // already in same component

        // Attach smaller tree under larger tree
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
-----------------------------------------------------
⚡ Solve(n, edges)
-----------------------------------------------------
Given `n` nodes and a list of `edges`, 
find the minimum number of operations to connect all components
into one connected network.

Operation allowed:
➡️ Remove an existing extra edge (redundant connection)
   and connect two previously disconnected components.

Steps:
1️⃣ Traverse all edges.
   - If both nodes already share the same parent → it's an extra edge.
   - Otherwise, union them (connect their components).
2️⃣ Count number of connected components.
3️⃣ To connect all components, we need (components - 1) edges.
4️⃣ If we have enough extra edges, return (components - 1), else -1.

Example:
Input:
n = 4
edges = [[0,1], [0,2], [1,2]]
Extra edge = [1,2]
Components = 2
Output = 1 (use extra edge to connect last node)
*/
int Solve(int n, vector<vector<int>> &edges) {
    DisjoinSet ds(n);

    int cntExtras = 0;
    for (auto &it : edges) {
        int u = it[0];
        int v = it[1];
        if (ds.findPar(u) == ds.findPar(v)) {
            // This edge forms a cycle → it's extra
            cntExtras++;
        } else {
            ds.unionBySize(u, v);
        }
    }

    int cntComponents = 0;
    for (int i = 0; i < n; i++) {
        if (ds.parent[i] == i) cntComponents++;
    }

    int needed = cntComponents - 1;
    if (cntExtras >= needed) return needed;
    return -1;
}

/*
-----------------------------------------------------
🧭 main() — Example driver
-----------------------------------------------------
Input:
n = 4
edges = [[0,1], [0,2], [1,2]]
Output: 1

Explanation:
There are 2 components: {0,1,2} and {3}
1 extra edge ([1,2]) is enough to connect all.
*/
int main() {
    int n = 4;
    vector<vector<int>> edges = {
        {0, 1}, {0, 2}, {1, 2}
    };

    cout << "Minimum operations to connect network: "
         << Solve(n, edges) << endl;

    return 0;
}

/*
-----------------------------------------------------
📊 COMPLEXITY SUMMARY
-----------------------------------------------------
DSU Constructor: O(n)
findPar():        O(α(N)) ≈ constant
unionBySize():    O(α(N)) ≈ constant
Loop over edges:  O(E * α(N))
Count components: O(N)
-----------------------------------------------------
✅ Total Time:  O(E + N)
✅ Total Space: O(N)
-----------------------------------------------------
*/
