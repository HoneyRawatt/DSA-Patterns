package Sorting;

import java.util.*;

// Bubble Sort implementation in Java
public class BubbleSort {

    /*
     * Worst Case Time Complexity: O(n^2)
     * ---------------------------------
     * Occurs when the array is in reverse order.
     * For each pass, we compare adjacent elements across the array.
     *
     * Best Case Time Complexity: O(n)
     * -------------------------------
     * Occurs when the array is already sorted.
     * Due to the didSwap flag, the algorithm stops after the first pass.
     *
     * Average Case Time Complexity: O(n^2)
     *
     * Space Complexity: O(1)
     * ----------------------
     * In-place sorting.
     * Only a few variables are used (i, j, didSwap).
     */

    static void bubbleSort(int[] arr) {
        int n = arr.length;

        // Outer loop controls number of passes
        for (int i = n - 1; i >= 0; i--) {

            // Flag to check if any swap happened in this pass
            boolean didSwap = false;

            // Compare adjacent elements up to index i
            for (int j = 0; j <= i - 1; j++) {
                if (arr[j] > arr[j + 1]) {
                    // Swap if elements are in wrong order
                    int temp = arr[j];
                    arr[j] = arr[j + 1];
                    arr[j + 1] = temp;
                    didSwap = true;
                }
            }

            // If no swaps occurred, array is already sorted
            if (!didSwap) break;
        }
    }

    public static void main(String[] args) {
        int[] arr = {64, 25, 12, 22, 11};

        bubbleSort(arr); // Sort the array

        System.out.print("Sorted array: ");
        for (int num : arr) {
            System.out.print(num + " ");
        }
    }
}
