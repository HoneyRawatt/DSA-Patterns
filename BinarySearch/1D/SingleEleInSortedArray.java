package BinarySearch.1D;
import java.util.*;
public class SingleEleInSortedArray {

    // Brute-force approach
    // Time Complexity: O(n)
    // Space Complexity: O(1)
    // Idea: Compare each element with its neighbors
    static int findSingleElementBrute(int[] arr) {
        int n = arr.length;

        // Edge cases
        if (n == 1) return arr[0];
        if (arr[0] != arr[1]) return arr[0];
        if (arr[n - 1] != arr[n - 2]) return arr[n - 1];

        // Check middle elements
        for (int i = 1; i < n - 1; i++) {
            if (arr[i] != arr[i - 1] && arr[i] != arr[i + 1]) {
                return arr[i];
            }
        }
        return -1; // For valid input, this won't happen
    }

    // Optimized Binary Search approach
    // Time Complexity: O(log n)
    // Space Complexity: O(1)
    //
    // Intuition:
    // - Before the single element → pairs start at EVEN index
    // - After the single element  → pairs start at ODD index
    static int findSingleElement(int[] arr) {
        int n = arr.length;
        int low = 0, high = n - 1;

        // Edge cases
        if (n == 1) return arr[0];
        if (arr[0] != arr[1]) return arr[0];
        if (arr[n - 1] != arr[n - 2]) return arr[n - 1];

        low++;
        high--;

        while (low <= high) {
            int mid = low + (high - low) / 2;

            // Unique element check
            if (arr[mid] != arr[mid - 1] && arr[mid] != arr[mid + 1])
                return arr[mid];

            // Decide search direction using index parity
            if ((mid % 2 == 0 && arr[mid] == arr[mid + 1]) ||
                (mid % 2 == 1 && arr[mid] == arr[mid - 1])) {
                low = mid + 1;   // Single element on right
            } else {
                high = mid - 1;  // Single element on left
            }
        }
        return -1;
    }

    // Driver code
    public static void main(String[] args) {
        int[] arr = {1, 1, 2, 2, 3, 4, 4, 5, 5};

        System.out.println("Single element (brute): " + findSingleElementBrute(arr));
        System.out.println("Single element (binary search): " + findSingleElement(arr));
    }
}
