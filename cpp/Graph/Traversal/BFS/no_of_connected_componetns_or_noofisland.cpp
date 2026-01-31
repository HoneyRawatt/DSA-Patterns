#include <bits/stdc++.h>
using namespace std;

// BFS to traverse the whole island
void bfs(int row, int col, vector<vector<int>>& vis, vector<vector<char>>& grid) {
    vis[row][col] = 1;
    queue<pair<int, int>> q;
    q.push({row, col});
    int n = grid.size();
    int m = grid[0].size();

    while (!q.empty()) {
        int r = q.front().first;
        int c = q.front().second;
        q.pop();

        // Visit all 8 neighbors
        for (int delrow = -1; delrow <= 1; delrow++) {
            for (int delcol = -1; delcol <= 1; delcol++) {
                int nrow = r + delrow;  // use r, c not row, col
                int ncol = c + delcol;
                if (nrow >= 0 && nrow < n && ncol >= 0 && ncol < m &&
                    grid[nrow][ncol] == '1' && !vis[nrow][ncol]) {
                    vis[nrow][ncol] = 1;
                    q.push({nrow, ncol});
                }
            }
        }
    }
}

// Function to count number of islands
int numsislands(vector<vector<char>>& grid) {
    int n = grid.size();
    int m = grid[0].size();
    int cnt = 0;  // initialize island count
    vector<vector<int>> vis(n, vector<int>(m, 0));

    for (int row = 0; row < n; row++) {
        for (int col = 0; col < m; col++) {
            if (!vis[row][col] && grid[row][col] == '1') {
                cnt++;
                bfs(row, col, vis, grid);
            }
        }
    }

    return cnt;
}

int main() {
    vector<vector<char>> grid = {
        {'1','1','0','0'},
        {'1','1','0','0'},
        {'0','0','1','0'},
        {'0','0','0','1'}
    };

    cout << "Number of islands: " << numsislands(grid) << endl;
}


// | Function      | Time Complexity | Space Complexity |
// | ------------- | --------------- | ---------------- |
// | `bfs`         | O(n * m)        | O(n * m)         |
// | `numsislands` | O(n * m)        | O(n * m)         |
// | `main`        | O(n * m)        | O(n * m)         |
//  O(n * m)+O(n * m)=O(n∗m)