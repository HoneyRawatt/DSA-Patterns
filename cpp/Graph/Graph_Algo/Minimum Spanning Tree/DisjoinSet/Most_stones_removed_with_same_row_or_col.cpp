#include <bits/stdc++.h>
using namespace std;

/*
-----------------------------------------------------
🔹 INTUITION
-----------------------------------------------------
We are given stones placed on a 2D grid at coordinates (row, col).

We can remove a stone if there exists another stone in the same row or column.
The goal is to remove as many stones as possible, leaving at least one stone
per connected component (group of stones connected via rows/columns).

👉 Observation:
Each connected group of stones can be treated as a graph component.
We can remove (size_of_component - 1) stones from each group.

So, total stones that can be removed =
   total_stones - number_of_connected_components.

We use **Disjoint Set Union (DSU / Union-Find)** to efficiently merge stones
that are in the same row or column.
-----------------------------------------------------
*/


/*
-----------------------------------------------------
🔹 DISJOINT SET (Union-Find)
-----------------------------------------------------
Used to group stones that are connected via rows or columns.

Features:
✅ Path Compression → optimizes find operation
✅ Union by Size    → merges smaller component into larger one
-----------------------------------------------------
*/
class DisjoinSet {
public:
    vector<int> parent, size;

    DisjoinSet(int n) {
        parent.resize(n);
        size.resize(n, 1);
        for (int i = 0; i < n; i++) parent[i] = i;
    }

    // 🔍 Find ultimate parent (with path compression)
    int findPar(int node) {
        if (node == parent[node]) return node;
        return parent[node] = findPar(parent[node]);
    }

    // 🔗 Union by size (merge smaller tree under larger one)
    void unionBySize(int u, int v) {
        int ulp_u = findPar(u);
        int ulp_v = findPar(v);
        if (ulp_u == ulp_v) return;

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
🔹 removeStones()
-----------------------------------------------------
Steps:
1️⃣ Find max row and max column index among all stones.
2️⃣ Create a DSU for (max_row + max_col + 2) nodes
    → because we treat each row and column as a node.
3️⃣ For each stone (r, c):
     - Treat `r` as one node
     - Treat `c + max_row + 1` as another node (offset column)
     - Union both (they belong to the same component)
4️⃣ Count number of unique parent nodes (connected components).
5️⃣ Result = total_stones - connected_components

⏱️ Time Complexity:
   → O(N * α(N))   (for N stones, α = inverse Ackermann ≈ constant)
💾 Space Complexity:
   → O(R + C)      (for DSU parent and size arrays)
-----------------------------------------------------
*/
class Solution {
public:
    int removeStones(vector<vector<int>>& stones) {
        int maxrow = 0, maxcol = 0;

        // Find maximum row and column index
        for (auto &it : stones) {
            maxrow = max(maxrow, it[0]);
            maxcol = max(maxcol, it[1]);
        }

        // +2 ensures we have enough space for offset columns
        DisjoinSet ds(maxrow + maxcol + 2);
        unordered_map<int, int> stoneNodes;

        // Union all stones (row-node and column-node)
        for (auto &it : stones) {
            int noderow = it[0];
            int nodecol = it[1] + maxrow + 1; // offset columns to avoid overlap
            ds.unionBySize(noderow, nodecol);
            stoneNodes[noderow] = 1;
            stoneNodes[nodecol] = 1;
        }

        // Count how many unique parents (connected components)
        int cnt = 0;
        for (auto &it : stoneNodes) {
            if (ds.findPar(it.first) == it.first)
                cnt++;
        }

        // Total removable stones = total stones - number of components
        return stones.size() - cnt;
    }
};


/*
-----------------------------------------------------
🧭 MAIN FUNCTION (Driver)
-----------------------------------------------------
Example:
Input:
stones = [[0,0], [0,1], [1,0], [1,2], [2,1], [2,2]]
Output:
5

Explanation:
There are 6 stones and 1 connected component.
You can remove 5 stones and keep one per component.
-----------------------------------------------------
*/
int main() {
    vector<vector<int>> stones = {
        {0, 0}, {0, 1}, {1, 0}, {1, 2}, {2, 1}, {2, 2}
    };

    Solution sol;
    cout << "Maximum stones that can be removed: "
         << sol.removeStones(stones) << endl;

    return 0;
}


/*
-----------------------------------------------------
📊 COMPLEXITY SUMMARY
-----------------------------------------------------
DSU Constructor: O(R + C)
findPar():        O(α(N)) ≈ constant
unionBySize():    O(α(N)) ≈ constant
Main Loop:        O(N * α(N))
Count Parents:    O(R + C)
-----------------------------------------------------
✅ Total Time:  O(N)
✅ Total Space: O(R + C)
-----------------------------------------------------
*/
