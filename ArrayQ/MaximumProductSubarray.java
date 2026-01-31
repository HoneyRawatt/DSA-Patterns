import java.util.*;

public class MaximumProductSubarray {

    /*
    ====================================================
    OPTIMAL APPROACH (Prefix & Suffix Product)
    ====================================================

    Intuition:
    ----------
    - Negative numbers can flip the sign of the product
    - Zero breaks subarrays
    - So we compute:
        1) Prefix product from left to right
        2) Suffix product from right to left
    - Reset product to 1 whenever it becomes 0
    - The maximum of prefix and suffix at each step
      gives the maximum product subarray

    Time Complexity:  O(n)
    Space Complexity: O(1)
    */
    public static int subarraysMaxProductOptimal(int[] arr) {
        int prefix = 1;
        int suffix = 1;
        int maxi = Integer.MIN_VALUE;
        int n = arr.length;

        for (int i = 0; i < n; i++) {
            if (prefix == 0) prefix = 1;
            if (suffix == 0) suffix = 1;

            prefix *= arr[i];
            suffix *= arr[n - i - 1];

            maxi = Math.max(maxi, Math.max(prefix, suffix));
        }
        return maxi;
    }

    /*
    ====================================================
    BRUTE FORCE APPROACH
    ====================================================

    Intuition:
    ----------
    - Try every possible subarray
    - Compute product and track maximum

    Time Complexity:  O(n^2)
    Space Complexity: O(1)
    */
    public static int subarraysMaxProductBrute(int[] arr) {
        int n = arr.length;
        int maxi = Integer.MIN_VALUE;

        for (int i = 0; i < n; i++) {
            int product = 1;
            for (int j = i; j < n; j++) {
                product *= arr[j];
                maxi = Math.max(maxi, product);
            }
        }
        return maxi;
    }

    /*
    ====================================================
    MAIN METHOD
    ====================================================
    */
    public static void main(String[] args) {
        int[] arr = {2, 3, -2, 4}; // Expected output: 6

        System.out.println("Brute: " + subarraysMaxProductBrute(arr));
        System.out.println("Optimal: " + subarraysMaxProductOptimal(arr));
    }
}
