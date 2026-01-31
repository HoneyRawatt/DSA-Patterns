#include <bits/stdc++.h>
using namespace std;

/*
-------------------------------------------
    🔗 DISJOINT SET UNION (Union-Find)
-------------------------------------------

Intuition:
-----------
We maintain disjoint (non-overlapping) sets.
Each node belongs to exactly one set.

Operations:
  1️⃣ findpar(x): Find the "ultimate parent" (representative) of node x.
  2️⃣ unionByRank(x, y): Merge two sets based on tree height (rank).
  3️⃣ unionBySize(x, y): Merge two sets based on size (number of nodes).

Optimizations:
 - Path Compression → makes find operation nearly O(1)
 - Union by Rank / Size → keeps trees balanced
*/

class DisjoinSet {
    vector<int> rank, parent, size;

public:
    // Constructor: initialize rank, parent, size arrays
    DisjoinSet(int n) {
        rank.resize(n + 1, 0);
        size.resize(n + 1, 1);
        parent.resize(n + 1);
        for (int i = 0; i <= n; i++) parent[i] = i;
    }

    // 🔍 Find ultimate parent (with path compression)
    int findpar(int node) {
        if (node == parent[node]) return node;
        return parent[node] = findpar(parent[node]); // path compression
    }
    // ⏱️ O(α(N)) per call (α = inverse Ackermann, practically constant)
    // 💾 O(1) auxiliary space

    // 🔗 Union two sets by rank (tree height)
    void unionByRank(int u, int v) {
        int ulp_u = findpar(u);
        int ulp_v = findpar(v);
        if (ulp_u == ulp_v) return; // already in same set

        if (rank[ulp_u] < rank[ulp_v]) {
            parent[ulp_u] = ulp_v;
        } 
        else if (rank[ulp_v] < rank[ulp_u]) {
            parent[ulp_v] = ulp_u;
        } 
        else {
            parent[ulp_v] = ulp_u;
            rank[ulp_u]++;
        }
    }
    // ⏱️ O(α(N)) | 💾 O(1)

    // 🔗 Union two sets by size (number of elements)
    void unionBySize(int u, int v) {
        int ulp_u = findpar(u);
        int ulp_v = findpar(v);
        if (ulp_u == ulp_v) return; // already in same set

        if (size[ulp_u] < size[ulp_v]) {
            parent[ulp_u] = ulp_v;
            size[ulp_v] += size[ulp_u];
        } 
        else {
            parent[ulp_v] = ulp_u;
            size[ulp_u] += size[ulp_v];
        }
    }
    // ⏱️ O(α(N)) | 💾 O(1)
};

// -----------------------------------------------------------
// 🧠 MAIN FUNCTION DEMO
// -----------------------------------------------------------
int main() {
    int n = 7; // number of nodes
    DisjoinSet ds(n);

    // ✅ Union some nodes (connect components)
    ds.unionBySize(1, 2);
    ds.unionBySize(2, 3);
    ds.unionBySize(4, 5);
    ds.unionBySize(6, 7);
    ds.unionBySize(5, 6);

    // 🔍 Test connectivity using findpar()
    if (ds.findpar(3) == ds.findpar(7))
        cout << "3 and 7 are in the SAME component\n";
    else
        cout << "3 and 7 are in DIFFERENT components\n";

    // ✅ Union the two components
    ds.unionBySize(3, 7);

    // 🔍 Test again
    if (ds.findpar(3) == ds.findpar(7))
        cout << "Now 3 and 7 are in the SAME component\n";
    else
        cout << "3 and 7 are still in DIFFERENT components\n";

    return 0;
}

/*
-------------------------------------------
🧩 OUTPUT:
3 and 7 are in DIFFERENT components
Now 3 and 7 are in the SAME component

-------------------------------------------
⚙️ TIME & SPACE COMPLEXITY:
-------------------------------------------
Initialization:  O(N)
Find / Union:    O(α(N)) ≈ O(1)
Total:           O(N + Q·α(N)) for Q operations
Space:           O(N)
-------------------------------------------
*/
