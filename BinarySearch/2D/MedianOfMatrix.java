package BinarySearch.2D;

import java.util.*;

public class MedianOfMatrix {

    // ---------------- BRUTE FORCE METHOD ----------------
    // Step 1: Flatten matrix → O(n * m)
    // Step 2: Sort → O(n * m * log(n * m))
    // Step 3: Return middle element
    static int medianBruteForce(int[][] matrix, int n, int m) {
        List<Integer> elements = new ArrayList<>();

        // Flatten the matrix
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                elements.add(matrix[i][j]);
            }
        }

        // Sort the array
        Collections.sort(elements);

        // Return the middle element
        return elements.get((n * m) / 2);
    }

    /*
     * Custom upper_bound
     * Returns index of first element > x
     */
    static int upperBound(int[] arr, int x, int n) {
        int low = 0, high = n - 1;
        int ans = n;

        while (low <= high) {
            int mid = (low + high) / 2;
            if (arr[mid] > x) {
                ans = mid;
                high = mid - 1;
            } else {
                low = mid + 1;
            }
        }
        return ans;
    }

    /*
     * Count number of elements ≤ mid in entire matrix
     */
    static int countSmallEqual(int[][] matrix, int n, int m, int mid) {
        int cnt = 0;
        for (int i = 0; i < n; i++) {
            cnt += upperBound(matrix[i], mid, m);
        }
        return cnt;
    }

    /*
     * Binary search on answer (Optimal approach)
     * Time: O(32 * n * log m)
     * Space: O(1)
     */
    static int median(int[][] matrix, int n, int m) {
        int low = Integer.MAX_VALUE;
        int high = Integer.MIN_VALUE;

        // Find global min and max
        for (int i = 0; i < n; i++) {
            low = Math.min(low, matrix[i][0]);
            high = Math.max(high, matrix[i][m - 1]);
        }

        int req = (n * m) / 2;

        while (low <= high) {
            int mid = low + (high - low) / 2;
            int count = countSmallEqual(matrix, n, m, mid);

            if (count <= req)
                low = mid + 1;
            else
                high = mid - 1;
        }

        return low;
    }

    // ---------------- MAIN METHOD ----------------
    public static void main(String[] args) {

        int[][] matrix = {
                {1, 3, 5},
                {2, 6, 9},
                {3, 6, 9}
        };

        int n = matrix.length;
        int m = matrix[0].length;

        int result = median(matrix, n, m);
        System.out.println("Median is: " + result);

        result = medianBruteForce(matrix, n, m);
        System.out.println("Median (brute-force) is: " + result);
    }
}
