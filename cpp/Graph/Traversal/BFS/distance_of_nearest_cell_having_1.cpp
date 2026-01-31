#include <bits/stdc++.h>
using namespace std;

/*
    Function: nearest
    Purpose : For each cell in a binary grid, find the distance to the nearest cell containing 1.
    Approach: Multi-source BFS (Breadth First Search)
*/

vector<vector<int>> nearest(vector<vector<int>> grid) {
    int n = grid.size();
    int m = grid[0].size();

    // visited and distance matrices
    vector<vector<int>> vis(n, vector<int>(m, 0));
    vector<vector<int>> dis(n, vector<int>(m, 0));

    // Queue will store: {{row, col}, distance}
    queue<pair<pair<int, int>, int>> q;

    // Step 1: Push all '1' cells into the queue as starting points (multi-source BFS)
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (grid[i][j] == 1) {
                q.push({{i, j}, 0});
                vis[i][j] = 1; // mark all 1's as visited
            }
        }
    }

    // Step 2: Direction vectors for Up, Right, Down, Left
    int delrow[4] = {-1, 0, 1, 0};
    int delcol[4] = {0, 1, 0, -1};

    // Step 3: Perform BFS
    while (!q.empty()) {
        int row = q.front().first.first;
        int col = q.front().first.second;
        int step = q.front().second;
        q.pop();

        // store the distance for this cell
        dis[row][col] = step;

        // check all 4 directions
        for (int i = 0; i < 4; i++) {
            int nrow = row + delrow[i];
            int ncol = col + delcol[i];

            // check valid cell and not visited
            if (nrow >= 0 && nrow < n && ncol >= 0 && ncol < m && !vis[nrow][ncol]) {
                vis[nrow][ncol] = 1;
                q.push({{nrow, ncol}, step + 1});
            }
        }
    }

    return dis;
}

/*
--------------------------------------------
🕒 Time Complexity:
    O(N × M)
    → Each cell is pushed and popped from the queue at most once.
    → Checking 4 directions per cell = O(4 × N × M) ≈ O(N × M)

💾 Space Complexity:
    O(N × M)
    → For visited matrix + distance matrix + queue (in worst case)
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
Distance of nearest 1 for each cell:
1 0 1
1 1 0
0 1 2
*/
