package Traversal.BFS;

import java.util.*;

/*
Approach:
---------
We use BFS (Breadth-First Search) to simulate the rotting process.

1️⃣ All initially rotten oranges (value = 2) are added to a queue with time = 0.
2️⃣ Each rotten orange spreads rot to its 4-directionally adjacent fresh oranges.
3️⃣ Every newly rotten orange is added to the queue with time + 1.
4️⃣ We track:
    - total time taken
    - number of fresh oranges that became rotten
5️⃣ If any fresh orange remains unrotted, return -1.

Time Complexity:  O(N * M)
Space Complexity: O(N * M)
*/

public class RottingOranges {

    // Helper class to store row, column, and time
    static class Pair {
        int row, col, time;

        Pair(int row, int col, int time) {
            this.row = row;
            this.col = col;
            this.time = time;
        }
    }

    public static int orangeRotting(int[][] grid) {
        int n = grid.length;
        int m = grid[0].length;

        Queue<Pair> q = new LinkedList<>();
        int[][] vis = new int[n][m];

        int cntFresh = 0;

        // Step 1: Add all initially rotten oranges to the queue
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (grid[i][j] == 2) {
                    q.add(new Pair(i, j, 0));
                    vis[i][j] = 2;
                }
                if (grid[i][j] == 1) {
                    cntFresh++;
                }
            }
        }

        int time = 0; // Maximum time taken
        int cnt = 0;  // Count of fresh oranges that got rotten

        // Directions: up, right, down, left
        int[] delRow = {-1, 0, 1, 0};
        int[] delCol = {0, 1, 0, -1};

        // Step 2: BFS traversal
        while (!q.isEmpty()) {
            Pair curr = q.poll();
            int r = curr.row;
            int c = curr.col;
            int t = curr.time;

            time = Math.max(time, t);

            // Visit all 4 adjacent cells
            for (int i = 0; i < 4; i++) {
                int nRow = r + delRow[i];
                int nCol = c + delCol[i];

                // Check bounds and if the orange is fresh
                if (nRow >= 0 && nRow < n && nCol >= 0 && nCol < m &&
                        vis[nRow][nCol] != 2 && grid[nRow][nCol] == 1) {

                    q.add(new Pair(nRow, nCol, t + 1));
                    vis[nRow][nCol] = 2;
                    cnt++;
                }
            }
        }

        // Step 3: If all fresh oranges did not rot
        if (cnt != cntFresh) {
            return -1;
        }

        return time;
    }

    // Driver code
    public static void main(String[] args) {
        int[][] grid = {
                {2, 1, 1},
                {1, 1, 0},
                {0, 1, 1}
        };

        int result = orangeRotting(grid);
        System.out.println("Minimum time to rot all oranges: " + result);
    }
}

