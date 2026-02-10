#include <bits/stdc++.h>
using namespace std;

/*
=====================================================
Problem Statement:
=====================================================
You are given an N × M binary matrix `grid` where:
- 1 represents land
- 0 represents water

A land cell is called an **enclave** if it is NOT connected
to any boundary cell of the grid (directly or indirectly).

Your task is to count the total number of such land cells
that cannot reach the boundary.

Movement is allowed only in 4 directions:
Up, Right, Down, Left.
*/

/*
=====================================================
Intuition:
=====================================================
- Any land cell (1) connected to the boundary can escape,
  so it is NOT an enclave.
- Only land cells completely surrounded by water (or other land)
  and NOT touching the boundary are counted as enclaves.

Key idea:
➡ Instead of checking every land cell individually,
   we start BFS from all boundary land cells.
➡ Mark all land cells connected to the boundary as visited.
➡ Finally, count the land cells that were never visited.
*/

/*
=====================================================
Approach (BFS from Boundary):
=====================================================
1️⃣ Traverse the boundary of the grid.
2️⃣ Push all boundary land cells (value = 1) into a queue.
3️⃣ Perform BFS to mark all land cells connected to the boundary.
4️⃣ Count all land cells that are still unvisited → enclaves.
*/

// Function to count the number of land cells that cannot reach the boundary
int numberOfEnclaves(vector<vector<int>>& grid) {
    int n = grid.size();
    int m = grid[0].size();

    // Visited array to track boundary-connected land
    vector<vector<int>> vis(n, vector<int>(m, 0));

    queue<pair<int, int>> q;

    // Step 1: Push all boundary land cells into the queue
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {

            // Check if cell lies on boundary
            if (i == 0 || j == 0 || i == n - 1 || j == m - 1) {

                // If boundary cell is land
                if (grid[i][j] == 1) {
                    q.push({i, j});
                    vis[i][j] = 1;
                }
            }
        }
    }

    // Direction arrays for 4-directional movement
    int delrow[] = {-1, 0, 1, 0};
    int delcol[] = {0, 1, 0, -1};

    // Step 2: BFS traversal to mark all boundary-connected land
    while (!q.empty()) {
        int row = q.front().first;
        int col = q.front().second;
        q.pop();

        for (int i = 0; i < 4; i++) {
            int nrow = row + delrow[i];
            int ncol = col + delcol[i];

            // Check valid, unvisited land cell
            if (nrow >= 0 && nrow < n &&
                ncol >= 0 && ncol < m &&
                !vis[nrow][ncol] &&
                grid[nrow][ncol] == 1) {

                vis[nrow][ncol] = 1;
                q.push({nrow, ncol});
            }
        }
    }

    // Step 3: Count land cells that were never visited
    int cnt = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {

            // Unvisited land cell → enclave
            if (grid[i][j] == 1 && !vis[i][j])
                cnt++;
        }
    }

    return cnt;
}

int main() {
    vector<vector<int>> grid = {
        {0, 0, 0, 0},
        {1, 0, 1, 0},
        {0, 1, 1, 0},
        {0, 0, 0, 0}
    };

    cout << numberOfEnclaves(grid) << endl;
    return 0;
}

/*
=====================================================
Time & Space Complexity:
=====================================================

⏱ Time Complexity: O(N × M)
- Each cell is visited at most once during BFS.

📦 Space Complexity: O(N × M)
- Visited array
- Queue used in BFS
=====================================================
*/
