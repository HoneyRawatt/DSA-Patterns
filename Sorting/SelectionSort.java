package Sorting;

import java.util.*;

// Selection Sort implementation in Java
public class SelectionSort {

    /*
     * Time Complexity Intuition:
     * --------------------------
     * We use two nested loops.
     * - Outer loop runs (n - 1) times.
     * - Inner loop runs (n - i - 1) times for each i.
     * 
     * Total comparisons ≈ n(n - 1)/2 → O(n^2)
     * 
     * Best, Average, Worst case: O(n^2)
     * (Because selection sort always scans the remaining array fully)
     *
     * Space Complexity Intuition:
     * ---------------------------
     * - Sorting is done in-place.
     * - Only a few variables (i, j, mini) are used.
     * - No extra data structures are created.
     *
     * Space Complexity: O(1)
     */

    // Function to perform Selection Sort
    static void selectionSort(int[] arr) {
        int n = arr.length;

        // Move boundary of unsorted subarray
        for (int i = 0; i < n - 1; i++) {

            // Assume the current index holds the minimum value
            int mini = i;

            // Find the minimum element in the remaining unsorted part
            for (int j = i + 1; j < n; j++) {
                if (arr[j] < arr[mini]) {
                    mini = j;
                }
            }

            // Swap the found minimum element with the first element
            int temp = arr[mini];
            arr[mini] = arr[i];
            arr[i] = temp;
        }
    }

    public static void main(String[] args) {
        int[] arr = {64, 25, 12, 22, 11};

        selectionSort(arr); // Sort the array

        System.out.print("Sorted array: ");
        for (int num : arr) {
            System.out.print(num + " ");
        }
    }
}
