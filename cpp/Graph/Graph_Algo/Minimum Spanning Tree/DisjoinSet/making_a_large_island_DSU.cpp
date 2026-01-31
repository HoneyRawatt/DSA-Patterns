#include <bits/stdc++.h>
using namespace std;

/*
-----------------------------------------------------
🔹 DISJOINT SET UNION (Union-Find)
-----------------------------------------------------
Used to efficiently group connected land cells (1's) into components.
-----------------------------------------------------
Time Complexity:
- findPar(): O(α(N)) ≈ constant
- unionBySize(): O(α(N)) ≈ constant
-----------------------------------------------------
Space Complexity: O(N²)
- parent[] and size[] arrays of size N²
-----------------------------------------------------
*/
class DisjointSet {
public:
    vector<int> parent, size;

    DisjointSet(int n) {
        parent.resize(n);
        size.resize(n, 1);
        for (int i = 0; i < n; i++) parent[i] = i;
    }

    int findPar(int node) {
        if (node == parent[node]) return node;
        return parent[node] = findPar(parent[node]); // Path compression
    }

    void unionBySize(int u, int v) {
        int ulp_u = findPar(u);
        int ulp_v = findPar(v);
        if (ulp_u == ulp_v) return; // already in same set
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
⚙️ Helper Function: isValid()
-----------------------------------------------------
Checks if a cell (r, c) lies inside the grid.

Time Complexity: O(1)
Space Complexity: O(1)
-----------------------------------------------------
*/
bool isValid(int r, int c, int n) {
    return (r >= 0 && r < n && c >= 0 && c < n);
}

/*
-----------------------------------------------------
🏝️ Function: MaxConnection(grid)
-----------------------------------------------------
Intuition:
We first connect all existing '1's into components using DSU.
Then for each '0' cell, we check its 4 neighbors.
If those neighbors belong to different components, we sum their sizes.
The result = max of all possible sums (including flipping one 0→1).

Steps:
1️⃣ Build components of all 1s using DSU.
2️⃣ For each 0 cell:
    - Check 4 directions.
    - Collect unique neighboring component parents.
    - Sum their sizes + 1 (for flipped cell).
    - Track max size.
3️⃣ If grid is full of 1s, return total component size.
-----------------------------------------------------
Time Complexity:
- Building DSU: O(N² * α(N))
- Checking zeros: O(N² * 4 * α(N)) ≈ O(N²)
✅ Total: O(N²)

Space Complexity: O(N²)
- DSU arrays + grid + visited info
-----------------------------------------------------
*/
int MaxConnection(vector<vector<int>>& grid) {
    int n = grid.size();
    DisjointSet ds(n * n);
    int dr[] = {-1, 0, 1, 0};
    int dc[] = {0, 1, 0, -1};

    // Step 1️⃣: Connect all '1's into components
    for (int row = 0; row < n; row++) {
        for (int col = 0; col < n; col++) {
            if (grid[row][col] == 0) continue;
            for (int ind = 0; ind < 4; ind++) {
                int adjr = row + dr[ind];
                int adjc = col + dc[ind];
                if (isValid(adjr, adjc, n) && grid[adjr][adjc] == 1) {
                    int nodeNo = row * n + col;
                    int adjNodeNo = adjr * n + adjc;
                    ds.unionBySize(nodeNo, adjNodeNo);
                }
            }
        }
    }

    // Step 2️⃣: Try flipping each 0 → 1
    int mx = 0;
    for (int row = 0; row < n; row++) {
        for (int col = 0; col < n; col++) {
            if (grid[row][col] == 1) continue;
            set<int> components;

            for (int ind = 0; ind < 4; ind++) {
                int adjr = row + dr[ind];
                int adjc = col + dc[ind];
                if (isValid(adjr, adjc, n) && grid[adjr][adjc] == 1) {
                    components.insert(ds.findPar(adjr * n + adjc));
                }
            }

            int sizeTotal = 1; // include flipped cell
            for (auto it : components) {
                sizeTotal += ds.size[it];
            }
            mx = max(mx, sizeTotal);
        }
    }

    // Step 3️⃣: If no 0 exists (all 1s)
    for (int cellNo = 0; cellNo < n * n; cellNo++) {
        mx = max(mx, ds.size[ds.findPar(cellNo)]);
    }

    return mx;
}

/*
-----------------------------------------------------
🧭 main() — Example
-----------------------------------------------------
Input:
grid = {
  {1, 1, 0},
  {1, 0, 1},
  {0, 1, 0}
}
Output:
5
Explanation:
Flipping grid[1][1] connects 5 cells into one island.
-----------------------------------------------------
*/
int main() {
    vector<vector<int>> grid = {
        {1, 1, 0},
        {1, 0, 1},
        {0, 1, 0}
    };

    cout << "Largest Island Size After One Flip: " << MaxConnection(grid) << endl;
    return 0;
}
