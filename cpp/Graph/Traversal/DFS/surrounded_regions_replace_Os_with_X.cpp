#include <bits/stdc++.h>
using namespace std;

/*
Problem Statement:
------------------
Given an N x M matrix consisting of characters 'X' and 'O',
capture all regions surrounded by 'X'.

A region is captured by flipping all 'O's into 'X's in that surrounded region.
An 'O' is NOT surrounded if it is connected to any 'O' on the boundary
(of the matrix) directly or indirectly.

Approach:
---------
1️⃣ Any 'O' connected to the boundary can NEVER be converted to 'X'.
2️⃣ Perform DFS from all boundary cells containing 'O'.
3️⃣ Mark all reachable 'O's from the boundary as visited (safe cells).
4️⃣ After DFS, all unvisited 'O's are surrounded → convert them to 'X'.
*/

/*
DFS Function:
-------------
Marks all 'O' cells connected to a boundary 'O' as visited.

Parameters:
- row, col : current cell
- vis      : visited matrix
- mat      : given board
- delrow   : direction array for row movement
- delcol   : direction array for column movement
*/
void dfs(int row, int col,
         vector<vector<int>>& vis,
         vector<vector<char>>& mat,
         int delrow[], int delcol[]) {

    // Mark current cell as visited
    vis[row][col] = 1;

    int n = mat.size();
    int m = mat[0].size();

    // Explore all 4 adjacent directions
    for (int i = 0; i < 4; i++) {
        int nrow = row + delrow[i];
        int ncol = col + delcol[i];

        // Check boundaries, visited status, and 'O' condition
        if (nrow >= 0 && nrow < n &&
            ncol >= 0 && ncol < m &&
            !vis[nrow][ncol] &&
            mat[nrow][ncol] == 'O') {

            dfs(nrow, ncol, vis, mat, delrow, delcol);
        }
    }
}

/*
Function: fill
---------------
Replaces all surrounded 'O's with 'X'.

Steps:
1️⃣ Run DFS from all boundary 'O's to mark safe cells.
2️⃣ Traverse the matrix:
   - If an 'O' is not visited → it is surrounded → convert to 'X'.
*/
vector<vector<char>> fill(int n, int m, vector<vector<char>>& mat) {

    // Visited matrix
    vector<vector<int>> vis(n, vector<int>(m, 0));

    // Direction vectors (Up, Right, Down, Left)
    int delrow[] = {-1, 0, 1, 0};
    int delcol[] = {0, 1, 0, -1};

    /*
        Step 1: DFS from boundary rows
    */
    for (int j = 0; j < m; j++) {
        // Top row
        if (!vis[0][j] && mat[0][j] == 'O')
            dfs(0, j, vis, mat, delrow, delcol);

        // Bottom row
        if (!vis[n - 1][j] && mat[n - 1][j] == 'O')
            dfs(n - 1, j, vis, mat, delrow, delcol);
    }

    /*
        Step 2: DFS from boundary columns
    */
    for (int i = 0; i < n; i++) {
        // Left column
        if (!vis[i][0] && mat[i][0] == 'O')
            dfs(i, 0, vis, mat, delrow, delcol);

        // Right column
        if (!vis[i][m - 1] && mat[i][m - 1] == 'O')
            dfs(i, m - 1, vis, mat, delrow, delcol);
    }

    /*
        Step 3: Replace all unvisited 'O's with 'X'
    */
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (!vis[i][j] && mat[i][j] == 'O') {
                mat[i][j] = 'X';
            }
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
Time Complexity:
-----------------------------------------
O(N × M)
- Each cell is visited at most once.

-----------------------------------------
Space Complexity:
-----------------------------------------
O(N × M)
- Visited matrix.
- DFS recursion stack in worst case.
-----------------------------------------
*/
