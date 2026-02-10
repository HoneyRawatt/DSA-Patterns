import java.util.*;

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
public class SurroundedRegions {

    /*
     DFS Function:
     -------------
     Marks all 'O' cells connected to a boundary 'O' as visited.
    */
    static void dfs(int row, int col,
                    int[][] vis,
                    char[][] mat,
                    int[] delRow,
                    int[] delCol) {

        vis[row][col] = 1;

        int n = mat.length;
        int m = mat[0].length;

        // Explore all 4 directions
        for (int i = 0; i < 4; i++) {
            int nrow = row + delRow[i];
            int ncol = col + delCol[i];

            if (nrow >= 0 && nrow < n &&
                ncol >= 0 && ncol < m &&
                vis[nrow][ncol] == 0 &&
                mat[nrow][ncol] == 'O') {

                dfs(nrow, ncol, vis, mat, delRow, delCol);
            }
        }
    }

    /*
     Function: fill
     ---------------
     Replaces all surrounded 'O's with 'X'.
    */
    static char[][] fill(int n, int m, char[][] mat) {

        int[][] vis = new int[n][m];

        // Direction vectors: Up, Right, Down, Left
        int[] delRow = {-1, 0, 1, 0};
        int[] delCol = {0, 1, 0, -1};

        // Step 1: DFS from boundary rows
        for (int j = 0; j < m; j++) {
            // Top row
            if (vis[0][j] == 0 && mat[0][j] == 'O') {
                dfs(0, j, vis, mat, delRow, delCol);
            }

            // Bottom row
            if (vis[n - 1][j] == 0 && mat[n - 1][j] == 'O') {
                dfs(n - 1, j, vis, mat, delRow, delCol);
            }
        }

        // Step 2: DFS from boundary columns
        for (int i = 0; i < n; i++) {
            // Left column
            if (vis[i][0] == 0 && mat[i][0] == 'O') {
                dfs(i, 0, vis, mat, delRow, delCol);
            }

            // Right column
            if (vis[i][m - 1] == 0 && mat[i][m - 1] == 'O') {
                dfs(i, m - 1, vis, mat, delRow, delCol);
            }
        }

        // Step 3: Convert surrounded 'O' to 'X'
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (vis[i][j] == 0 && mat[i][j] == 'O') {
                    mat[i][j] = 'X';
                }
            }
        }

        return mat;
    }

    public static void main(String[] args) {

        char[][] mat = {
            {'X', 'X', 'X', 'X'},
            {'X', 'O', 'O', 'X'},
            {'X', 'X', 'O', 'X'},
            {'X', 'O', 'X', 'X'}
        };

        int n = mat.length;
        int m = mat[0].length;

        char[][] ans = fill(n, m, mat);

        System.out.println("Modified Matrix:");
        for (char[] row : ans) {
            for (char ch : row) {
                System.out.print(ch + " ");
            }
            System.out.println();
        }
    }
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
