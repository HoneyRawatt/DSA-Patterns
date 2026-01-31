package BinarySearch.1D;

import java.util.*;

public class MinInRotatedStortedArray {
    /*
     * Time Complexity: O(log n) on average
     * Worst Case with duplicates: O(n) (due to boundary shrinking)
     * Space Complexity: O(1)
     */


    // 1) Find number of rotations in rotated sorted array (with duplicates)
    static int findRotationCount(int[] arr) {
        int low = 0, high = arr.length - 1;
        int index = -1;
        int minVal = Integer.MAX_VALUE;

        while (low <= high) {
            int mid = low + (high - low) / 2;

            // Track the minimum
            if (arr[mid] < minVal) {
                minVal = arr[mid];
                index = mid;
            }

            // If boundary values are equal, shrink range
            if (arr[low] == arr[mid] && arr[mid] == arr[high]) {
                low++;
                high--;
                continue;
            }

            // Left half sorted
            if (arr[low] <= arr[mid]) {
                // Check left edge for minimum
                if (arr[low] < minVal) {
                    minVal = arr[low];
                    index = low;
                }
                low = mid + 1;
            }
            // Right half sorted
            else {
                // Check mid for minimum
                if (arr[mid] < minVal) {
                    minVal = arr[mid];
                    index = mid;
                }
                high = mid - 1;
            }
        }

        return index;
    }

    // 2) Find minimum element in rotated sorted array (no duplicates)
    static int minElementUnique(int[] arr) {
        int low = 0, high = arr.length - 1;
        int ans = Integer.MAX_VALUE;

        while (low <= high) {
            int mid = low + (high - low) / 2;

            // If subarray is already sorted
            if (arr[low] <= arr[high]) {
                ans = Math.min(ans, arr[low]);
                break;
            }

            // Left half is sorted
            if (arr[low] <= arr[mid]) {
                ans = Math.min(ans, arr[low]);
                low = mid + 1;
            }
            // Right half is sorted
            else {
                ans = Math.min(ans, arr[mid]);
                high = mid - 1;
            }
        }
        return ans;
    }

    // 3) Find minimum element in rotated sorted array (with duplicates)
    static int minElementWithDuplicates(int[] arr) {
        int low = 0, high = arr.length - 1;
        int ans = Integer.MAX_VALUE;

        while (low <= high) {
            int mid = low + (high - low) / 2;

            // Always update with current low
            ans = Math.min(ans, arr[low]);

            // If boundaries and mid are same, shrink
            if (arr[low] == arr[mid] && arr[mid] == arr[high]) {
                low++;
                high--;
                continue;
            }

            // Left half sorted
            if (arr[low] <= arr[mid]) {
                ans = Math.min(ans, arr[low]);
                low = mid + 1;
            }
            // Right half sorted
            else {
                ans = Math.min(ans, arr[mid]);
                high = mid - 1;
            }
        }
        return ans;
    }

    public static void main(String[] args) {

        int[] uniqueArr = {4, 5, 6, 7, 0, 1, 2}; // No duplicates
        int[] dupArr = {2, 2, 2, 0, 1, 2};       // With duplicates
        int[] arr = {15, 18, 2, 3, 6, 12};

        System.out.println("Array is rotated " + findRotationCount(arr) + " times.");
        System.out.println("Minimum (unique): " + minElementUnique(uniqueArr));         // 0
        System.out.println("Minimum (duplicates): " + minElementWithDuplicates(dupArr)); // 0
    }
}

