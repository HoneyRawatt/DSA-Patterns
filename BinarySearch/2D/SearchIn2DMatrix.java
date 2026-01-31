package BinarySearch.2D;

import java.util.*;

public class SearchIn2DMatrix {

    /*
     * Brute-force: Check every element.
     * Time: O(n * m)
     * Space: O(1)
     */
    public static boolean searchElementBrute(int[][] mat, int target) {
        int n = mat.length, m = mat[0].length;

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (mat[i][j] == target)
                    return true;
            }
        }
        return false;
    }

    /*
     * Binary search on 1D array.
     * Time: O(log m)
     * Space: O(1)
     */
    public static boolean binarySearch(int[] arr, int target) {
        int low = 0, high = arr.length - 1;

        while (low <= high) {
            int mid = low + (high - low) / 2;

            if (arr[mid] == target)
                return true;
            else if (arr[mid] > target)
                high = mid - 1;
            else
                low = mid + 1;
        }
        return false;
    }

    /*
     * Better search with row filtering
     * --------------------------------
     * - Only search rows where target can exist
     *   using first and last element of each row.
     *
     * Time:
     *   Best: O(n + log m)
     *   Worst: O(n * log m)
     * Space: O(1)
     */
    public static boolean searchElementBetter(int[][] mat, int target) {
        int n = mat.length, m = mat[0].length;

        for (int i = 0; i < n; i++) {
            if (mat[i][0] <= target && mat[i][m - 1] >= target) {
                if (binarySearch(mat[i], target))
                    return true;
            }
        }
        return false;
    }

    /*
     * Optimal approach: Treat 2D matrix as sorted 1D array
     * -----------------------------------------------------
     * Condition:
     * - Each row is sorted
     * - First element of next row > last element of previous row
     *
     * Time: O(log(n * m))
     * Space: O(1)
     */
    public static boolean searchMatrix(int[][] matrix, int target) {
        int n = matrix.length, m = matrix[0].length;
        int low = 0, high = n * m - 1;

        while (low <= high) {
            int mid = low + (high - low) / 2;
            int row = mid / m;
            int col = mid % m;

            if (matrix[row][col] == target)
                return true;
            else if (matrix[row][col] < target)
                low = mid + 1;
            else
                high = mid - 1;
        }
        return false;
    }

    /*
     * Driver Code
     */
    public static void main(String[] args) {
        int[][] matrix = {
                {1, 3, 5, 7},
                {10, 11, 16, 20},
                {23, 30, 34, 50}
        };

        Scanner sc = new Scanner(System.in);
        System.out.print("Enter element to search: ");
        int target = sc.nextInt();

        System.out.println("\n--- Brute Force ---");
        System.out.println(searchElementBrute(matrix, target) ? "Found" : "Not Found");

        System.out.println("\n--- Better (Row-wise Binary Search) ---");
        System.out.println(searchElementBetter(matrix, target) ? "Found" : "Not Found");

        System.out.println("\n--- Optimal (Matrix as 1D) ---");
        System.out.println(searchMatrix(matrix, target) ? "Found" : "Not Found");

        sc.close();
    }
}
