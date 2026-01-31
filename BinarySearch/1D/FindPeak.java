package BinarySearch.1D;

import java.util.*;
public class FindPeak {

    // Binary Search approach
    // Time Complexity: O(log n)
    // Space Complexity: O(1)
    //
    // Intuition:
    // - A peak element is greater than its neighbors
    // - If the slope is rising, a peak lies on the right
    // - If the slope is falling, a peak lies on the left
    static int findPeak(int[] arr) {
        int n = arr.length;

        // Edge cases
        if (n == 1) return 0;
        if (arr[0] > arr[1]) return 0;
        if (arr[n - 1] > arr[n - 2]) return n - 1;

        int low = 1, high = n - 2;

        while (low <= high) {
            int mid = low + (high - low) / 2;

            // Check if mid is a peak
            if (arr[mid] > arr[mid - 1] && arr[mid] > arr[mid + 1])
                return mid;

            // Increasing slope → move right
            if (arr[mid] > arr[mid - 1])
                low = mid + 1;
            else
                high = mid - 1; // Decreasing slope → move left
        }
        return -1; // Should never happen
    }

    // Linear search approach
    // Time Complexity: O(n)
    // Space Complexity: O(1)
    static int findPeakLinear(int[] arr) {
        int n = arr.length;

        // Edge cases
        if (n == 1) return 0;
        if (arr[0] >= arr[1]) return 0;
        if (arr[n - 1] >= arr[n - 2]) return n - 1;

        // Check middle elements
        for (int i = 1; i < n - 1; i++) {
            if (arr[i] >= arr[i - 1] && arr[i] >= arr[i + 1])
                return i;
        }
        return -1;
    }

    // Driver code
    public static void main(String[] args) {
        int[] arr = {1, 3, 20, 4, 1, 0};

        int peakIndex = findPeak(arr);

        if (peakIndex != -1)
            System.out.println("Peak element is " + arr[peakIndex] + " at index " + peakIndex);
        else
            System.out.println("No peak element found");
    }
}

