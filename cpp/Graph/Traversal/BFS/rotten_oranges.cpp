#include <bits/stdc++.h>
using namespace std;

/*
Approach:
---------
We use a BFS (Breadth-First Search) to simulate the rotting process of oranges.

1️⃣ Each rotten orange acts as a source and starts infecting adjacent fresh oranges.
2️⃣ We push all initially rotten oranges (value = 2) into a queue with time = 0.
3️⃣ Then, for each rotten orange, we check its 4 adjacent cells:
    - If a neighbor is fresh (value = 1), it becomes rotten, 
      and we push it into the queue with time + 1.
4️⃣ We track the total time taken to rot all oranges and the count of fresh oranges.
5️⃣ If after BFS some fresh oranges are left, return -1; otherwise, return total time.

Time Complexity:  O(N * M)
    - Each cell is visited at most once.

Space Complexity: O(N * M)
    - We use a queue and a visited matrix of size N x M.

*/

int orangeRotting(vector<vector<int>> &grid) {
    int n = grid.size();
    int m = grid[0].size();

    queue<pair<pair<int, int>, int>> q; // {{row, col}, time}
    vector<vector<int>> vis(n, vector<int>(m, 0));

    int cntfresh = 0;

    // Step 1: Initialize queue with all initially rotten oranges
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (grid[i][j] == 2) {
                q.push({{i, j}, 0});
                vis[i][j] = 2;
            } else {
                vis[i][j] = 0;
            }
            if (grid[i][j] == 1)
                cntfresh++;
        }
    }

    int tm = 0;   // Maximum time taken to rot all oranges
    int cnt = 0;  // Count of fresh oranges that got rotten

    int delrow[] = {-1, 0, 1, 0};
    int delcol[] = {0, 1, 0, -1};

    // Step 2: BFS traversal
    while (!q.empty()) {
        int r = q.front().first.first;
        int c = q.front().first.second;
        int t = q.front().second;
        q.pop();

        tm = max(tm, t);

        // Check all 4 directions
        for (int i = 0; i < 4; i++) {
            int nrow = r + delrow[i];
            int ncol = c + delcol[i];

            // If within bounds and the orange is fresh
            if (nrow >= 0 && nrow < n && ncol >= 0 && ncol < m &&
                vis[nrow][ncol] != 2 && grid[nrow][ncol] == 1) {

                q.push({{nrow, ncol}, t + 1});
                vis[nrow][ncol] = 2;
                cnt++;
            }
        }
    }

    // Step 3: If not all fresh oranges rotted
    if (cnt != cntfresh)
        return -1;

    return tm;
}

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
