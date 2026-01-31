#include <bits/stdc++.h>
using namespace std;

// Function to count the number of land cells that cannot reach the boundary
int numberOfEnclaves(vector<vector<int>>& grid) {
    int n = grid.size();
    int m = grid[0].size();

    vector<vector<int>> vis(n, vector<int>(m, 0));
    queue<pair<int, int>> q;

    // Step 1: Push all boundary land cells (1s) into the queue
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (i == 0 || j == 0 || i == n - 1 || j == m - 1) {
                if (grid[i][j] == 1) {
                    q.push({i, j});
                    vis[i][j] = 1;
                }
            }
        }
    }

    // Step 2: BFS traversal from all boundary-connected 1s
    int delrow[] = {-1, 0, 1, 0};
    int delcol[] = {0, 1, 0, -1};

    while (!q.empty()) {
        int row = q.front().first;
        int col = q.front().second;
        q.pop();

        for (int i = 0; i < 4; i++) {
            int nrow = row + delrow[i];
            int ncol = col + delcol[i];

            // Check valid and unvisited land cells
            if (nrow >= 0 && nrow < n && ncol >= 0 && ncol < m &&
                !vis[nrow][ncol] && grid[nrow][ncol] == 1) {
                vis[nrow][ncol] = 1;
                q.push({nrow, ncol});
            }
        }
    }

    // Step 3: Count unvisited land cells (enclaves)
    int cnt = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
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


// ⏱ Time & Space Complexity

// Time Complexity: O(N × M)
// → Each cell is visited once.

// Space Complexity: O(N × M)
// → For the vis array and BFS queue.