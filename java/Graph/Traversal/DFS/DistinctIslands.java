import java.util.*;

/*
=====================================================
Problem Statement:
=====================================================
You are given a binary grid of size N × M where:
- 1 represents land
- 0 represents water

An island is formed by connecting adjacent land cells
(connected 4-directionally).

Two islands are considered DISTINCT if their shapes are different.
Translation is allowed (i.e., shifting an island does not change its shape),
but rotation and reflection are NOT allowed.

Your task is to count the number of distinct island shapes.
*/

/*
=====================================================
Intuition:
=====================================================
- To compare island shapes independent of their positions,
  we store each island using RELATIVE coordinates.
- For every island, we pick its first cell as a reference (row0, col0).
- All other cells in that island are stored as (row - row0, col - col0).
- This normalizes the shape, making comparison easy.

Key idea:
➡ Same-shaped islands will produce identical relative-coordinate lists.
➡ Different shapes will produce different lists.
*/

public class DistinctIslands {

    /*
    =====================================================
    DFS Function:
    =====================================================
    Purpose:
    - Traverse an island using DFS.
    - Store the island's shape using relative coordinates.

    Time Complexity (per DFS call):
    - O(size_of_island)

    Space Complexity (per DFS call):
    - O(size_of_island) due to recursion stack
    */
    static void dfs(int row, int col,
                    int[][] grid,
                    int[][] vis,
                    List<int[]> shape,
                    int row0, int col0) {

        vis[row][col] = 1;

        // Store relative position (shape representation)
        shape.add(new int[]{row - row0, col - col0});

        // Direction vectors: Up, Right, Down, Left
        int[] delRow = {-1, 0, 1, 0};
        int[] delCol = {0, 1, 0, -1};

        int n = grid.length;
        int m = grid[0].length;

        // Explore all 4 adjacent directions
        for (int i = 0; i < 4; i++) {
            int nrow = row + delRow[i];
            int ncol = col + delCol[i];

            // Check valid, unvisited land cell
            if (nrow >= 0 && nrow < n &&
                ncol >= 0 && ncol < m &&
                vis[nrow][ncol] == 0 &&
                grid[nrow][ncol] == 1) {

                dfs(nrow, ncol, grid, vis, shape, row0, col0);
            }
        }
    }

    /*
    =====================================================
    Function: countDistinctIslands
    =====================================================
    Purpose:
    - Traverse the grid and identify all islands.
    - Store each island's shape using relative coordinates.
    - Use a set to keep only unique island shapes.
    */
    static int countDistinctIslands(int[][] grid) {
        int n = grid.length;
        int m = grid[0].length;

        // Set to store unique island shapes
        Set<List<String>> set = new HashSet<>();

        // Visited matrix
        int[][] vis = new int[n][m];

        // Traverse all cells
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {

                // Start DFS for each unvisited land cell
                if (vis[i][j] == 0 && grid[i][j] == 1) {
                    List<int[]> shape = new ArrayList<>();
                    dfs(i, j, grid, vis, shape, i, j);

                    // Convert shape to string list for hashing
                    List<String> encoded = new ArrayList<>();
                    for (int[] p : shape) {
                        encoded.add(p[0] + "," + p[1]);
                    }

                    set.add(encoded);
                }
            }
        }

        return set.size();
    }

    /*
    =====================================================
    Overall Time & Space Complexity:
    =====================================================

    ⏱ Time Complexity:
    - O(N × M) — each cell visited once

    📦 Space Complexity:
    - O(N × M) — visited matrix + recursion stack + shape storage
    */

    public static void main(String[] args) {
        int[][] grid = {
            {1, 1, 0, 0, 0},
            {1, 0, 0, 0, 0},
            {0, 0, 0, 1, 1},
            {0, 0, 0, 1, 0}
        };

        System.out.println(
            "Number of distinct islands: " + countDistinctIslands(grid)
        );
    }
}
