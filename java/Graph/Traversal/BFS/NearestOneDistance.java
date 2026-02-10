package Traversal.BFS;

import java.util.*;

/*
Problem Statement:
------------------
Given a binary matrix (grid) of size N x M containing only 0s and 1s,
find the distance of the nearest cell containing 1 for each cell.

Distance is measured using 4-directional movement:
Up, Right, Down, Left.

Approach:
---------
We use Multi-Source BFS.

1️⃣ All cells with value 1 are treated as sources.
2️⃣ Push all such cells into the queue with distance = 0.
3️⃣ Perform BFS simultaneously from all sources.
4️⃣ The first time a cell is visited gives the shortest distance
   to the nearest 1.
*/

public class NearestOneDistance {

    // Function to compute distance of nearest 1 for each cell
    public static int[][] nearest(int[][] grid) {

        int n = grid.length;        // number of rows
        int m = grid[0].length;     // number of columns

        // Visited matrix to track processed cells
        int[][] vis = new int[n][m];

        // Distance matrix to store result
        int[][] dis = new int[n][m];

        // Queue stores: {row, col, distance}
        Queue<int[]> q = new LinkedList<>();

        /*
            Step 1: Push all '1' cells into the queue
            These act as multiple BFS starting points.
        */
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (grid[i][j] == 1) {
                    q.offer(new int[]{i, j, 0});
                    vis[i][j] = 1; // mark as visited
                }
            }
        }

        // Direction arrays for 4-directional movement
        int[] delRow = {-1, 0, 1, 0}; // Up, Right, Down, Left
        int[] delCol = {0, 1, 0, -1};

        /*
            Step 2: BFS traversal
        */
        while (!q.isEmpty()) {

            int[] curr = q.poll();
            int row = curr[0];
            int col = curr[1];
            int dist = curr[2];

            // Store the distance for current cell
            dis[row][col] = dist;

            // Explore all 4 neighboring cells
            for (int i = 0; i < 4; i++) {
                int nrow = row + delRow[i];
                int ncol = col + delCol[i];

                // Check valid boundaries and if not visited
                if (nrow >= 0 && nrow < n &&
                    ncol >= 0 && ncol < m &&
                    vis[nrow][ncol] == 0) {

                    vis[nrow][ncol] = 1;
                    q.offer(new int[]{nrow, ncol, dist + 1});
                }
            }
        }

        return dis;
    }

    public static void main(String[] args) {

        int[][] grid = {
            {0, 1, 0},
            {0, 0, 1},
            {1, 0, 0}
        };

        int[][] ans = nearest(grid);

        System.out.println("Distance of nearest 1 for each cell:");
        for (int i = 0; i < ans.length; i++) {
            for (int j = 0; j < ans[0].length; j++) {
                System.out.print(ans[i][j] + " ");
            }
            System.out.println();
        }
    }
}

/*
--------------------------------------------
Time Complexity:
--------------------------------------------
O(N × M)
- Each cell is visited once.
- 4 directional checks per cell.

--------------------------------------------
Space Complexity:
--------------------------------------------
O(N × M)
- Visited matrix
- Distance matrix
- Queue in worst case
--------------------------------------------

Expected Output:
----------------
Distance of nearest 1 for each cell:
1 0 1
1 1 0
0 1 2
*/
