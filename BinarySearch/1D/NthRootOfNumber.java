package BinarySearch.1D;

public class NthRootOfNumber {

    // Helper function to compare mid^n with m
    // Returns:
    // 1 -> mid^n == m (perfect match)
    // 0 -> mid^n < m  (too small)
    // 2 -> mid^n > m  (too large)
    static int powerCompare(int mid, int n, int m) {
        long ans = 1;

        for (int i = 1; i <= n; i++) {
            ans *= mid;

            // Early stopping to avoid overflow
            if (ans > m)
                return 2;
        }

        if (ans == m) return 1;
        return 0;
    }

    // Binary Search approach
    // Time Complexity: O(n log m)
    // Space Complexity: O(1)
    //
    // Intuition:
    // - The nth root lies between 1 and m
    // - Use binary search to reduce search space
    // - Compare mid^n with m safely using long
    static int findNthRoot(int n, int m) {
        int low = 1, high = m;

        while (low <= high) {
            int mid = low + (high - low) / 2;
            int result = powerCompare(mid, n, m);

            if (result == 1)
                return mid;          // Exact nth root found
            else if (result == 0)
                low = mid + 1;       // mid^n is too small
            else
                high = mid - 1;      // mid^n is too large
        }
        return -1; // No perfect nth root exists
    }

    // Linear Search approach
    // Time Complexity: O(m * n)
    // Space Complexity: O(1)
    //
    // Used only for understanding / brute force
    static int nthRootLinear(int n, int m) {
        for (int x = 1; x <= m; x++) {
            long power = 1;

            for (int i = 1; i <= n; i++) {
                power *= x;
                if (power > m) break;
            }

            if (power == m)
                return x;
        }
        return -1;
    }

    // Driver code
    public static void main(String[] args) {
        int n = 3, m = 27;

        System.out.println("The " + n + "th root of " + m + " is: " + findNthRoot(n, m));
    }
}
