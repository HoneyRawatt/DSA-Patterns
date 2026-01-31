package BinarySearch.2D;

import java.util.*;

public class RowWithMaximumOnes {

    /*
     * Custom lower bound function
     * Returns the first index where arr[index] >= x
     *
     * Time Complexity: O(log m)
     * Space Complexity: O(1)
     */
    public static int lowerBound(int[] arr, int n, int x) {
        int low = 0, high = n - 1;

        while (low <= high) {
            int mid = (low + high) / 2;
            if (arr[mid] >= x)
                high = mid - 1;
            else
                low = mid + 1;
        }
        return low;
    }

    /*
     * Approach 1: Binary Search (Rows are sorted)
     * -------------------------------------------
     * - Find first occurrence of 1 using lower bound
     * - Number of ones = m - index
     *
     * Time Complexity: O(n * log m)
     * Space Complexity: O(1)
     */
    public static int rowWithMax1s(int[][] matrix, int n, int m) {
        int maxCount = 0;
        int index = -1;

        for (int i = 0; i < n; i++) {
            int countOnes = m - lowerBound(matrix[i], m, 1);
            if (countOnes > maxCount) {
                maxCount = countOnes;
                index = i;
            }
        }
        return index;
    }

    /*
     * Approach 2: General Case (No sorting assumption)
     * -------------------------------------------------
     * - Count number of 1s using summation
     *
     * Time Complexity: O(n * m)
     * Space Complexity: O(1)
     */
    public static int[] rowAndMaximumOnes(int[][] mat) {
        int n = mat.length;
        int m = mat[0].length;

        int maxCount = 0;
        int index = -1;

        for (int i = 0; i < n; i++) {
            int countOnes = 0;
            for (int j = 0; j < m; j++) {
                countOnes += mat[i][j];
            }

            if (countOnes > maxCount) {
                maxCount = countOnes;
                index = i;
            }
        }
        return new int[]{index, maxCount};
    }

        /*
     * 🚀 OPTIMAL APPROACH (Top-Right Traversal)
     * -----------------------------------------
     * 🧠 INTUITION:
     * - Rows are sorted (0s then 1s).
     * - Start from top-right corner.
     * - If matrix[row][col] == 1:
     *      -> move left (more 1s possible in same row)
     *      -> update answer row
     * - If matrix[row][col] == 0:
     *      -> move down (this row cannot have more 1s)
     *
     * Time Complexity: O(n + m)
     * Space Complexity: O(1)
     */
    public static int rowWithMax1sOptimal(int[][] mat) {
        int n = mat.length;
        int m = mat[0].length;

        int row = 0;
        int col = m - 1;
        int ans = -1;

        while (row < n && col >= 0) {
            if (mat[row][col] == 1) {
                ans = row;   // current row has more 1s
                col--;       // move left
            } else {
                row++;       // move down
            }
        }
        return ans;
    }

    /*
     * Driver Code
     */
    public static void main(String[] args) {
        int[][] mat = {
                {0, 0, 0, 1},
                {0, 1, 1, 1},
                {0, 0, 1, 1},
                {0, 0, 0, 0}
        };

        int n = mat.length;
        int m = mat[0].length;

        // For sorted rows (binary search)
        int index = rowWithMax1s(mat, n, m);
        System.out.println("Row with max 1s (binary search): " + index);

        // For general case
        int[] result = rowAndMaximumOnes(mat);
        System.out.println("Row with max 1s (accumulate): " +
                result[0] + " with count = " + result[1]);
    }
}
