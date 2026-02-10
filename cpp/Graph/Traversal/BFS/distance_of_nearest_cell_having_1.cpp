#include <bits/stdc++.h>
using namespace std;

/*
Problem Statement:
------------------
Given a binary matrix (grid) of size N x M consisting of 0s and 1s,
for each cell containing 0, find the distance to the nearest cell
that contains 1.

Distance is measured as the minimum number of steps required to move
from one cell to another, where movement is allowed only in
4 directions: Up, Right, Down, Left.

Approach:
---------
We use Multi-Source BFS (Breadth First Search).

1️⃣ All cells containing '1' are considered as starting points (sources).
2️⃣ Push all '1' cells into the queue with distance = 0.
3️⃣ Perform BFS simultaneously from all sources.
4️⃣ For each cell, the first time it is visited gives the shortest
   distance to the nearest '1'.

This works because BFS explores nodes level-by-level.
*/

vector<vector<int>> nearest(vector<vector<int>> grid) {

    int n = grid.size();        // number of rows
    int m = grid[0].size();     // number of columns

    // Visited matrix to avoid revisiting cells
    vector<vector<int>> vis(n, vector<int>(m, 0));

    // Distance matrix to store answer
    vector<vector<int>> dis(n, vector<int>(m, 0));

    // Queue for BFS: {{row, col}, distance}
    queue<pair<pair<int, int>, int>> q;

    /*
        Step 1: Push all cells with value '1' into the queue.
        These act as multiple BFS sources.
    */
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (grid[i][j] == 1) {
                q.push({{i, j}, 0}); // distance of '1' to itself is 0
                vis[i][j] = 1;       // mark visited
            }
        }
    }

    // Direction vectors for 4-directional movement
    int delrow[4] = {-1, 0, 1, 0}; // Up, Right, Down, Left
    int delcol[4] = {0, 1, 0, -1};

    /*
        Step 2: Perform BFS traversal
    */
    while (!q.empty()) {

        // Get current cell and its distance
        int row = q.front().first.first;
        int col = q.front().first.second;
        int step = q.front().second;
        q.pop();

        // Store shortest distance for this cell
        dis[row][col] = step;

        // Explore all 4 adjacent cells
        for (int i = 0; i < 4; i++) {
            int nrow = row + delrow[i];
            int ncol = col + delcol[i];

            // Check boundaries and if cell is not visited
            if (nrow >= 0 && nrow < n &&
                ncol >= 0 && ncol < m &&
                !vis[nrow][ncol]) {

                vis[nrow][ncol] = 1;             // mark as visited
                q.push({{nrow, ncol}, step + 1}); // increase distance
            }
        }
    }

    // Return the distance matrix
    return dis;
}

/*
--------------------------------------------
Time Complexity:
--------------------------------------------
O(N × M)
- Every cell is inserted into the queue at most once.
- For each cell, we check 4 directions.
- Total operations ≈ 4 × N × M → O(N × M)

--------------------------------------------
Space Complexity:
--------------------------------------------
O(N × M)
- Visited matrix: O(N × M)
- Distance matrix: O(N × M)
- Queue (worst case): O(N × M)
--------------------------------------------
*/

int main() {

    vector<vector<int>> grid = {
        {0, 1, 0},
        {0, 0, 1},
        {1, 0, 0}
    };

    vector<vector<int>> ans = nearest(grid);

    cout << "Distance of nearest 1 for each cell:\n";
    for (auto row : ans) {
        for (auto val : row) {
            cout << val << " ";
        }
        cout << "\n";
    }

    return 0;
}

/*
Expected Output:
----------------
Distance of nearest 1 for each cell:
1 0 1
1 1 0
0 1 2
*/
