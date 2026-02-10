package Traversal.DFS;


/*
====================================================
PROBLEM STATEMENT (Flood Fill):
====================================================
You are given a 2D image represented by integers.

Given:
- image    : 2D grid of pixel values
- sr, sc   : starting row and column
- newColor : color to fill

Recolor the starting pixel and all 4-directionally
connected pixels having the same initial color.

This is a classic GRAPH + DFS problem.
====================================================
*/

public class FloodFill {

    /*
    ----------------------------------------------------
    DFS Function
    ----------------------------------------------------
    Purpose:
    - Performs Depth First Search (DFS) to recolor
      all connected pixels with the same initial color.

    Parameters:
    - row, col : current pixel position
    - ans      : result image (acts as visited + output)
    - image    : original image
    - newColor : color to apply
    - delRow   : row direction array (up, right, down, left)
    - delCol   : column direction array
    - iniColor : original color at starting pixel

    Logic:
    - Change current pixel to newColor
    - Explore 4-directionally connected neighbors
    ----------------------------------------------------
    */
    static void dfs(int row, int col, int[][] ans, int[][] image,
                    int newColor, int[] delRow, int[] delCol, int iniColor) {

        // Recolor current pixel
        ans[row][col] = newColor;

        int n = image.length;
        int m = image[0].length;

        // Traverse in 4 directions
        for (int i = 0; i < 4; i++) {
            int nrow = row + delRow[i];
            int ncol = col + delCol[i];

            // Check boundaries and color condition
            if (nrow >= 0 && nrow < n &&
                ncol >= 0 && ncol < m &&
                image[nrow][ncol] == iniColor &&
                ans[nrow][ncol] != newColor) {

                dfs(nrow, ncol, ans, image, newColor, delRow, delCol, iniColor);
            }
        }
    }

    /*
    ----------------------------------------------------
    floodFill Function
    ----------------------------------------------------
    Purpose:
    - Initializes DFS and returns the final recolored image

    Steps:
    1. Store initial color
    2. Copy original image into ans
    3. Define direction arrays
    4. Start DFS from (sr, sc)
    ----------------------------------------------------
    */
    static int[][] floodFill(int[][] image, int sr, int sc, int newColor) {

        int iniColor = image[sr][sc];
        int n = image.length;
        int m = image[0].length;

        // Copy image to result array
        int[][] ans = new int[n][m];
        for (int i = 0; i < n; i++) {
            ans[i] = image[i].clone();
        }

        // Direction arrays: up, right, down, left
        int[] delRow = {-1, 0, 1, 0};
        int[] delCol = {0, 1, 0, -1};

        // Start DFS
        dfs(sr, sc, ans, image, newColor, delRow, delCol, iniColor);

        return ans;
    }

    /*
    ----------------------------------------------------
    Main Function
    ----------------------------------------------------
    */
    public static void main(String[] args) {

        int[][] image = {
            {1, 1, 1},
            {1, 1, 0},
            {1, 0, 1}
        };

        int sr = 1, sc = 1, newColor = 2;

        int[][] result = floodFill(image, sr, sc, newColor);

        // Print the updated image
        for (int[] row : result) {
            for (int val : row) {
                System.out.print(val + " ");
            }
            System.out.println();
        }
    }
}

/*
====================================================
INTUITION:
====================================================
- All pixels connected to the starting pixel
  having the same color must be recolored.
- DFS helps explore all such connected pixels.

====================================================
TIME COMPLEXITY:
====================================================
Let N = number of rows, M = number of columns

Time Complexity: O(N * M)
(each cell visited once)

====================================================
SPACE COMPLEXITY:
====================================================
- Result image: O(N * M)
- Recursion stack (worst case): O(N * M)

Total Space Complexity: O(N * M)
====================================================
*/
