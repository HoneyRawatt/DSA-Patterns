#include <bits/stdc++.h>
using namespace std;

/*
-----------------------------------------------------
🔹 DISJOINT SET UNION (Union-Find)
-----------------------------------------------------
Used to efficiently merge connected lands into islands.
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
        return parent[node] = findPar(parent[node]);
    }

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
⚙️ Helper: Check if neighbor is within grid bounds
-----------------------------------------------------
*/
bool isValid(int r, int c, int n, int m) {
    return (r >= 0 && r < n && c >= 0 && c < m);
}

/*
-----------------------------------------------------
⚡ numOfIslands(n, m, operators)
-----------------------------------------------------
Each operator adds land at (row, col).
We dynamically track islands using DSU.

Steps:
1️⃣ Convert 2D coordinates (r,c) to a 1D node: r * m + c
2️⃣ If already land, push current count and continue
3️⃣ Mark new cell as land, increment island count
4️⃣ Check 4 neighbors (up, right, down, left):
    - If neighbor is land and belongs to different set → union them
      and decrement island count
5️⃣ Push the island count after processing each operator
-----------------------------------------------------
*/
vector<int> numOfIslands(int n, int m, vector<vector<int>>& operators) {
    DisjointSet ds(n * m);
    vector<vector<int>> vis(n, vector<int>(m, 0));
    vector<int> ans;
    int cnt = 0;

    int dr[] = {-1, 0, 1, 0};
    int dc[] = {0, 1, 0, -1};

    for (auto& it : operators) {
        int row = it[0], col = it[1];

        // Already land — push current island count and skip
        if (vis[row][col] == 1) {
            ans.push_back(cnt);
            continue;
        }

        vis[row][col] = 1;
        cnt++;

        int nodeNo = row * m + col;

        // Check 4 directions
        for (int ind = 0; ind < 4; ind++) {
            int adjr = row + dr[ind];
            int adjc = col + dc[ind];
            if (isValid(adjr, adjc, n, m)) {
                if (vis[adjr][adjc] == 1) {
                    int adjNode = adjr * m + adjc;
                    if (ds.findPar(nodeNo) != ds.findPar(adjNode)) {
                        cnt--;
                        ds.unionBySize(nodeNo, adjNode);
                    }
                }
            }
        }
        ans.push_back(cnt);
    }
    return ans;
}

/*
-----------------------------------------------------
🧭 main() — Example
-----------------------------------------------------
Input:
n = 4, m = 5
operators = [[1,1],[0,1],[3,3],[3,4]]

Output:
[1,1,2,2]
*/
int main() {
    int n = 4, m = 5;
    vector<vector<int>> operators = {{1, 1}, {0, 1}, {3, 3}, {3, 4}};

    vector<int> res = numOfIslands(n, m, operators);
    cout << "Island count after each operation: ";
    for (auto x : res) cout << x << " ";
    cout << endl;
    return 0; 
}


// | Operation     | Time                                    | Space  | Explanation                         |
// | ------------- | --------------------------------------- | ------ | ----------------------------------- |
// | Each operator | O(α(N))                                 | O(1)   | DSU operations                      |
// | Total         | O(K * α(N))                             | O(N*M) | K = # of operators, N*M = grid size |
// | α(N)          | Inverse Ackermann, practically constant |        |                                     |
