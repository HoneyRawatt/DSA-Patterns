package Traversal.BFS;
import java.util.*;

/*
====================================================
PROBLEM STATEMENT:
====================================================
You are given a 2D grid consisting of:
- '1' → land
- '0' → water

An island is formed by connecting adjacent land cells.
Connections are allowed in ALL 8 directions:
- Up, Down, Left, Right
- 4 Diagonals

Your task is to count the total number of islands.
====================================================
*/

public class NumberOfIslands {

    /*
    ----------------------------------------------------
    BFS Function
    ----------------------------------------------------
    Purpose:
    - Performs Breadth First Search (BFS) to traverse
      an entire island starting from a given cell.

    Parameters:
    - row, col : starting cell coordinates
    - vis      : visited matrix
    - grid     : input grid

    Logic:
    - Mark starting cell as visited
    - Push it into queue
    - Explore all 8 neighboring cells
    - Visit and enqueue unvisited land cells
    ----------------------------------------------------
    */
    static void bfs(int row, int col, int[][] vis, char[][] grid) {
        int n = grid.length;
        int m = grid[0].length;

        Queue<int[]> q = new LinkedList<>();
        q.add(new int[]{row, col});
        vis[row][col] = 1;

        while (!q.isEmpty()) {
            int[] cell = q.poll();
            int r = cell[0];
            int c = cell[1];

            // Traverse all 8 directions
            for (int delRow = -1; delRow <= 1; delRow++) {
                for (int delCol = -1; delCol <= 1; delCol++) {
                    int nrow = r + delRow;
                    int ncol = c + delCol;

                    // Check bounds and if it's unvisited land
                    if (nrow >= 0 && nrow < n &&
                        ncol >= 0 && ncol < m &&
                        grid[nrow][ncol] == '1' &&
                        vis[nrow][ncol] == 0) {

                        vis[nrow][ncol] = 1;
                        q.add(new int[]{nrow, ncol});
                    }
                }
            }
        }
    }

    /*
    ----------------------------------------------------
    numIslands Function
    ----------------------------------------------------
    Purpose:
    - Counts the total number of islands in the grid

    Approach:
    - Traverse the grid cell by cell
    - If an unvisited land cell is found:
        - Increment island count
        - Perform BFS to mark all connected land
    ----------------------------------------------------
    */
    static int numIslands(char[][] grid) {
        int n = grid.length;
        int m = grid[0].length;

        int[][] vis = new int[n][m];
        int count = 0;

        for (int row = 0; row < n; row++) {
            for (int col = 0; col < m; col++) {
                if (vis[row][col] == 0 && grid[row][col] == '1') {
                    count++;              // new island found
                    bfs(row, col, vis, grid);
                }
            }
        }

        return count;
    }

    /*
    ----------------------------------------------------
    Main Function
    ----------------------------------------------------
    */
    public static void main(String[] args) {
        char[][] grid = {
            {'1','1','0','0'},
            {'1','1','0','0'},
            {'0','0','1','0'},
            {'0','0','0','1'}
        };

        System.out.println("Number of islands: " + numIslands(grid));
    }
}

/*
====================================================
INTUITION:
====================================================
- Each island is a connected component of '1's.
- BFS helps explore all land cells connected to a
  starting land cell.
- Every time BFS starts from an unvisited land cell,
  we discover a new island.

====================================================
TIME COMPLEXITY:
====================================================
Let n = number of rows, m = number of columns

- Each cell is visited once.
- BFS processes each cell once.

Time Complexity: O(n * m)

====================================================
SPACE COMPLEXITY:
====================================================
- Visited matrix: O(n * m)
- Queue (worst case): O(n * m)

Total Space Complexity: O(n * m)
====================================================
*/

