#include <bits/stdc++.h>
using namespace std;

// DFS to mark all 'O's connected to boundary
void dfs(int row, int col, vector<vector<int>>& vis, vector<vector<char>>& mat, int delrow[], int delcol[]) {
    vis[row][col] = 1;
    int n = mat.size();
    int m = mat[0].size();

    for (int i = 0; i < 4; i++) {
        int nrow = row + delrow[i];
        int ncol = col + delcol[i];
        if (nrow >= 0 && nrow < n && ncol >= 0 && ncol < m && !vis[nrow][ncol] && mat[nrow][ncol] == 'O') {
            dfs(nrow, ncol, vis, mat, delrow, delcol);
        }
    }
}

// Main function to replace surrounded 'O's with 'X'
vector<vector<char>> fill(int n, int m, vector<vector<char>>& mat) {
    vector<vector<int>> vis(n, vector<int>(m, 0));
    int delrow[] = {-1, 0, 1, 0};
    int delcol[] = {0, 1, 0, -1};

    // Step 1: DFS from boundary 'O's
    for (int j = 0; j < m; j++) {
        if (!vis[0][j] && mat[0][j] == 'O') dfs(0, j, vis, mat, delrow, delcol);
        if (!vis[n - 1][j] && mat[n - 1][j] == 'O') dfs(n - 1, j, vis, mat, delrow, delcol);
    }

    for (int i = 0; i < n; i++) {
        if (!vis[i][0] && mat[i][0] == 'O') dfs(i, 0, vis, mat, delrow, delcol);
        if (!vis[i][m - 1] && mat[i][m - 1] == 'O') dfs(i, m - 1, vis, mat, delrow, delcol);
    }

    // Step 2: Replace unvisited 'O's with 'X'
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (!vis[i][j] && mat[i][j] == 'O') mat[i][j] = 'X';
        }
    }

    return mat;
}

int main() {
    vector<vector<char>> mat = {
        {'X', 'X', 'X', 'X'},
        {'X', 'O', 'O', 'X'},
        {'X', 'X', 'O', 'X'},
        {'X', 'O', 'X', 'X'}
    };

    int n = mat.size();
    int m = mat[0].size();

    vector<vector<char>> ans = fill(n, m, mat);

    cout << "Modified Matrix:\n";
    for (auto row : ans) {
        for (auto ch : row) cout << ch << " ";
        cout << endl;
    }

    return 0;
}

/*
-----------------------------------------
⏱️ Time Complexity: O(N * M)
- Each cell visited at most once by DFS.

💾 Space Complexity: O(N * M)
- For visited matrix.
- Recursion stack can go up to O(N*M) in worst case.
-----------------------------------------
*/
