package BinarySearch.2D;
import java.util.*;

public class PeakElementIn2D {

    /*
     * 🧠 Find the row index with the maximum value in a given column
     * --------------------------------------------------------------
     * Time Complexity: O(n)
     * Space Complexity: O(1)
     */
    public static int findMaxIndex(int[][] mat, int col) {
        int n = mat.length;
        int maxValue = -1;
        int index = -1;

        for (int i = 0; i < n; i++) {
            if (mat[i][col] > maxValue) {
                maxValue = mat[i][col];
                index = i;
            }
        }
        return index;
    }

    /*
     * 🚀 Binary Search on Columns to find a peak element
     * -------------------------------------------------
     * 🧠 INTUITION:
     * - At each column, find the row with the largest value.
     * - Compare with left & right neighbors.
     * - Move towards the direction with a larger neighbor.
     *
     * Time Complexity: O(n * log m)
     * Space Complexity: O(1)
     */
    public static int[] findPeakGrid(int[][] mat) {
        int n = mat.length;
        int m = mat[0].length;

        int low = 0, high = m - 1;

        while (low <= high) {
            int mid = low + (high - low) / 2;

            // Find the max element in column mid
            int maxRowInd = findMaxIndex(mat, mid);

            int leftVal = (mid - 1 >= 0) ? mat[maxRowInd][mid - 1] : -1;
            int rightVal = (mid + 1 < m) ? mat[maxRowInd][mid + 1] : -1;
            int curVal = mat[maxRowInd][mid];

            // If current is peak
            if (curVal > leftVal && curVal > rightVal) {
                return new int[]{maxRowInd, mid};
            }
            // Move to left half
            else if (curVal < leftVal) {
                high = mid - 1;
            }
            // Move to right half
            else {
                low = mid + 1;
            }
        }

        return new int[]{-1, -1}; // Not expected for valid input
    }

    /*
     * 🧪 Main for testing
     */
    public static void main(String[] args) {
        int[][] mat = {
                {10, 8, 10, 10},
                {14, 13, 12, 11},
                {15, 9, 11, 21},
                {16, 17, 19, 20}
        };

        int[] peak = findPeakGrid(mat);
        if (peak[0] != -1) {
            System.out.println("Peak found at: [" + peak[0] + ", " + peak[1] +
                    "] with value = " + mat[peak[0]][peak[1]]);
        } else {
            System.out.println("No peak found (invalid input).");
        }
    }
}
