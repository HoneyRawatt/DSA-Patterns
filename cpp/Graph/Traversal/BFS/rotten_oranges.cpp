#include <bits/stdc++.h>
using namespace std;

/*
====================================================
PROBLEM STATEMENT (Rotting Oranges):
====================================================
You are given a 2D grid where:
- 0 represents an empty cell
- 1 represents a fresh orange
- 2 represents a rotten orange

Every minute, a rotten orange can rot its
4-directionally adjacent fresh oranges.

Return the minimum time required to rot all oranges.
If it is impossible to rot all oranges, return -1.

This is a classic MULTI-SOURCE BFS problem.
====================================================
*/

/*
====================================================
APPROACH:
====================================================
We use Breadth First Search (BFS) to simulate
the rotting process level by level (minute by minute).

1️⃣ Each rotten orange is treated as a source.
2️⃣ Push all initially rotten oranges into a queue
   with time = 0.
3️⃣ From each rotten orange, rot all adjacent
   fresh oranges and push them into the queue
   with time + 1.
4️⃣ Track:
   - Total time taken
   - Number of fresh oranges rotted
5️⃣ If all fresh oranges are rotted → return time
   Else → return -1
====================================================
*/

/*
----------------------------------------------------
Function: orangeRotting
----------------------------------------------------
Parameters:
- grid : 2D matrix representing the orange grid

Returns:
- Minimum time to rot all oranges
- -1 if impossible
----------------------------------------------------
*/
int orangeRotting(vector<vector<int>> &grid) {
    int n = grid.size();        // number of rows
    int m = grid[0].size();     // number of columns

    // Queue stores: {{row, col}, time}
    queue<pair<pair<int, int>, int>> q;

    // Visited matrix to mark rotten oranges
    vector<vector<int>> vis(n, vector<int>(m, 0));

    int cntfresh = 0;  // total number of fresh oranges

    /*
    ------------------------------------------------
    Step 1: Push all initially rotten oranges
    ------------------------------------------------
    */
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (grid[i][j] == 2) {
                q.push({{i, j}, 0});  // rotten orange with time = 0
                vis[i][j] = 2;
            } else {
                vis[i][j] = 0;
            }

            if (grid[i][j] == 1)
                cntfresh++;          // count fresh oranges
        }
    }

    int tm = 0;   // maximum time taken
    int cnt = 0;  // number of fresh oranges that got rotten

    // Direction arrays: up, right, down, left
    int delrow[] = {-1, 0, 1, 0};
    int delcol[] = {0, 1, 0, -1};

    /*
    ------------------------------------------------
    Step 2: BFS Traversal
    ------------------------------------------------
    */
    while (!q.empty()) {
        int r = q.front().first.first;
        int c = q.front().first.second;
        int t = q.front().second;
        q.pop();

        tm = max(tm, t);  // update maximum time

        // Explore all 4 adjacent cells
        for (int i = 0; i < 4; i++) {
            int nrow = r + delrow[i];
            int ncol = c + delcol[i];

            // Check bounds and if the orange is fresh
            if (nrow >= 0 && nrow < n &&
                ncol >= 0 && ncol < m &&
                vis[nrow][ncol] != 2 &&
                grid[nrow][ncol] == 1) {

                // Rot the fresh orange
                q.push({{nrow, ncol}, t + 1});
                vis[nrow][ncol] = 2;
                cnt++;
            }
        }
    }

    /*
    ------------------------------------------------
    Step 3: Final Check
    ------------------------------------------------
    */
    // If not all fresh oranges were rotted
    if (cnt != cntfresh)
        return -1;

    return tm;
}

/*
----------------------------------------------------
Main Function
----------------------------------------------------
*/
int main() {
    vector<vector<int>> grid = {
        {2, 1, 1},
        {1, 1, 0},
        {0, 1, 1}
    };

    int result = orangeRotting(grid);
    cout << "Minimum time to rot all oranges: " << result << endl;

    return 0;
}

/*
====================================================
INTUITION:
====================================================
- Each rotten orange spreads rot to its neighbors.
- BFS naturally processes cells level by level,
  making it ideal for time-based simulations.
- Multi-source BFS ensures all initial rotten
  oranges spread simultaneously.

====================================================
TIME COMPLEXITY:
====================================================
Let N = number of rows, M = number of columns

- Each cell is visited at most once.

Time Complexity: O(N * M)

====================================================
SPACE COMPLEXITY:
====================================================
- Visited matrix: O(N * M)
- Queue (worst case): O(N * M)

Total Space Complexity: O(N * M)
====================================================
*/
