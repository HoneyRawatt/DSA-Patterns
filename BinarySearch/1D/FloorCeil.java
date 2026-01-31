package BinarySearch.1D;

import java.util.*;

// Ceil & Floor in a sorted array using Binary Search
public class FloorCeil{

    /*
     * Ceil:
     * -----
     * Smallest element in the array that is >= target
     *
     * Floor:
     * ------
     * Largest element in the array that is <= target
     *
     * Prerequisite:
     * -------------
     * Array must be sorted.
     *
     * Time Complexity:
     * ----------------
     * O(log n) for both ceil and floor
     * (binary search halves the search space each time)
     *
     * Space Complexity:
     * -----------------
     * O(1) → iterative binary search, no extra space
     */

    // Returns the CEIL value of target
    static int ceil(int[] arr, int target) {
        int low = 0;
        int high = arr.length - 1;

        while (low <= high) {
            int mid = low + (high - low) / 2;

            if (arr[mid] >= target) {
                high = mid - 1; // move left to find smaller >= target
            } else {
                low = mid + 1;
            }
        }

        // low points to the smallest element >= target
        return (low < arr.length) ? arr[low] : -1;
    }

    // Returns the FLOOR value of target
    static int floor(int[] arr, int target) {
        int low = 0;
        int high = arr.length - 1;

        while (low <= high) {
            int mid = low + (high - low) / 2;

            if (arr[mid] <= target) {
                low = mid + 1; // move right to find larger <= target
            } else {
                high = mid - 1;
            }
        }

        // high points to the largest element <= target
        return (high >= 0) ? arr[high] : -1;
    }

    public static void main(String[] args) {

        int[] arr = {1, 3, 5, 7, 9};

        System.out.println("Ceil of 6: " + ceil(arr, 6));   // 7
        System.out.println("Floor of 6: " + floor(arr, 6)); // 5
    }
}
