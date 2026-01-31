package BinarySearch.2D;

import java.util.*;

public class SearchInSortedMatrix {

    /*
     * Brute-force: Check every element.
     * Time: O(n * m)
     * Space: O(1)
     */
    public static int[] searchElementBrute(int[][] mat, int target) {
        int n = mat.length;
        int m = mat[0].length;

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (mat[i][j] == target)
                    return new int[]{i, j};
            }
        }
        return new int[]{-1, -1};
    }

    /*
     * Binary search on 1D row.
     * Time: O(log m)
     * Space: O(1)
     */
    public static int binarySearch(int[] arr, int target) {
        int low = 0, high = arr.length - 1;

        while (low <= high) {
            int mid = low + (high - low) / 2;

            if (arr[mid] == target)
                return mid;
            else if (arr[mid] > target)
                high = mid - 1;
            else
                low = mid + 1;
        }
        return -1;
    }

    /*
     * Better search with row filtering + binary search
     * Time: O(n * log m)
     * Space: O(1)
     */
    public static int[] searchElementBetter(int[][] mat, int target) {
        int n = mat.length;

        for (int i = 0; i < n; i++) {
            int j = binarySearch(mat[i], target);
            if (j != -1)
                return new int[]{i, j};
        }
        return new int[]{-1, -1};
    }

    /*
     * Optimal search from top-right corner
     * Time: O(n + m)
     * Space: O(1)
     */
    public static int[] searchMatrix(int[][] matrix, int target) {
        int n = matrix.length;
        int m = matrix[0].length;

        int row = 0, col = m - 1;

        while (row < n && col >= 0) {
            if (matrix[row][col] == target)
                return new int[]{row, col};
            else if (matrix[row][col] < target)
                row++;
            else
                col--;
        }
        return new int[]{-1, -1};
    }

    public static void main(String[] args) {
        int[][] matrix = {
                {1, 3, 5, 7},
                {10, 11, 16, 20},
                {23, 30, 34, 60}
        };

        Scanner sc = new Scanner(System.in);
        System.out.print("Enter element to search: ");
        int target = sc.nextInt();

        System.out.println("\n--- Brute Force ---");
        int[] res1 = searchElementBrute(matrix, target);
        if (res1[0] != -1)
            System.out.println("Found at: [" + res1[0] + ", " + res1[1] + "]");
        else
            System.out.println("Not Found");

        System.out.println("\n--- Better (Row-wise Binary Search) ---");
        int[] res2 = searchElementBetter(matrix, target);
        if (res2[0] != -1)
            System.out.println("Found at: [" + res2[0] + ", " + res2[1] + "]");
        else
            System.out.println("Not Found");

        System.out.println("\n--- Optimal (Top-Right Search) ---");
        int[] res3 = searchMatrix(matrix, target);
        if (res3[0] != -1)
            System.out.println("Found at: [" + res3[0] + ", " + res3[1] + "]");
        else
            System.out.println("Not Found");

        sc.close();
    }
}

