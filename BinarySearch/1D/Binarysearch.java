package BinarySearch.1D;

import java.util.*;

// Binary Search implementation in Java
public class Binarysearch {

    /*
     * Binary Search Prerequisite:
     * ---------------------------
     * The array MUST be sorted.
     */

    /*
     * Time Complexity Intuition (Iterative & Recursive):
     * --------------------------------------------------
     * At each step, the search space is reduced to half.
     *
     * Time Complexity:
     * Best Case   : O(1)    (target found at mid)
     * Average Case: O(log n)
     * Worst Case  : O(log n)
     *
     * Space Complexity:
     * -----------------
     * Iterative Version : O(1)  (no recursion stack)
     * Recursive Version : O(log n) (due to recursion stack)
     */

    // Iterative Binary Search
    static int iterativeBinarySearch(int[] arr, int target) {

        int low = 0;
        int high = arr.length - 1;

        while (low <= high) {

            // Prevents integer overflow
            int mid = low + (high - low) / 2;

            if (arr[mid] == target) {
                return mid + 1; // 1-based index (same as C++ code)
            } 
            else if (arr[mid] < target) {
                low = mid + 1; // Search right half
            } 
            else {
                high = mid - 1; // Search left half
            }
        }

        return -1; // Element not found
    }

    // Recursive Binary Search
    static int recursiveBinarySearch(int[] arr, int low, int high, int target) {

        // Base case: element not found
        if (low > high) return -1;

        int mid = low + (high - low) / 2;

        if (arr[mid] == target) {
            return mid + 1; // 1-based index
        } 
        else if (arr[mid] < target) {
            // Search right half
            return recursiveBinarySearch(arr, mid + 1, high, target);
        } 
        else {
            // Search left half
            return recursiveBinarySearch(arr, low, mid - 1, target);
        }
    }

    public static void main(String[] args) {

        int[] arr = {2, 4, 6, 8, 10, 12, 14}; // Sorted array
        Scanner sc = new Scanner(System.in);

        System.out.print("Enter target element to search: ");
        int target = sc.nextInt();

        // Iterative Binary Search
        int resultIter = iterativeBinarySearch(arr, target);
        if (resultIter != -1)
            System.out.println("Iterative: Element found at position (1-based index): " + resultIter);
        else
            System.out.println("Iterative: Element not found.");

        // Recursive Binary Search
        int resultRec = recursiveBinarySearch(arr, 0, arr.length - 1, target);
        if (resultRec != -1)
            System.out.println("Recursive: Element found at position (1-based index): " + resultRec);
        else
            System.out.println("Recursive: Element not found.");
    }
}

