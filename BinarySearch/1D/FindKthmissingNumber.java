package BinarySearch.1D;

import java.util.*;
public class FindKthmissingNumber {
    /*
     * ------------------------------------------------------------
     * INTUITION (Linear Scan):
     * ------------------------------------------------------------
     * We walk through the array and compare each element with k.
     * If arr[i] <= k, it means one missing number is "pushed ahead",
     * so we increment k.
     * Once arr[i] > k, we stop because further elements won't affect k.
     *
     * Example:
     * arr = [2,3,4,7,11], k = 5
     * i=0 → arr[0]=2 <= 5 → k becomes 6
     * i=1 → arr[1]=3 <= 6 → k becomes 7
     * i=2 → arr[2]=4 <= 7 → k becomes 8
     * i=3 → arr[3]=7 <= 8 → k becomes 9
     * i=4 → arr[4]=11 > 9 → stop
     * Answer = 9
     *
     * ------------------------------------------------------------
     * TIME COMPLEXITY: O(n)
     * SPACE COMPLEXITY: O(1)
     * ------------------------------------------------------------
     */
    public static int findKthPositiveLinear(int[] arr, int k) {
        for (int i = 0; i < arr.length; i++) {
            if (arr[i] <= k) {
                k++;
            } else {
                break;
            }
        }
        return k;
    }

    /*
     * ------------------------------------------------------------
     * INTUITION (Binary Search):
     * ------------------------------------------------------------
     * In a perfect array [1,2,3,...], element at index i should be (i+1).
     * If arr[mid] != mid+1, then some numbers are missing.
     *
     * Missing numbers before index mid:
     * missing = arr[mid] - (mid + 1)
     *
     * If missing < k → kth missing lies to the right
     * If missing >= k → kth missing lies to the left
     *
     * Final Answer:
     * After binary search ends, kth missing number is:
     * high + k + 1
     *
     * ------------------------------------------------------------
     * TIME COMPLEXITY: O(log n)
     * SPACE COMPLEXITY: O(1)
     * ------------------------------------------------------------
     */
    public static int findKthPositiveBinary(int[] arr, int k) {
        int low = 0, high = arr.length - 1;

        while (low <= high) {
            int mid = low + (high - low) / 2;

            // Number of missing elements before index mid
            int missing = arr[mid] - (mid + 1);

            if (missing < k) {
                low = mid + 1;
            } else {
                high = mid - 1;
            }
        }

        // kth missing number
        return high + k + 1;
    }

    // Driver Code
    public static void main(String[] args) {
        int[] arr = {2, 3, 4, 7, 11};
        int k = 5;

        int resultBinary = findKthPositiveBinary(arr, k);
        System.out.println("Binary Search: " + k + "th missing number is: " + resultBinary);

        int resultLinear = findKthPositiveLinear(arr, k);
        System.out.println("Linear Search: " + k + "th missing number is: " + resultLinear);
    }
}
