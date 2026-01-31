package Sorting;
import java.util.*;

// Insertion Sort implementation in Java
public class InsertionSort {

    /*
     * Worst Case Time Complexity: O(n^2)
     * ---------------------------------
     * Occurs when the array is sorted in reverse order.
     * Each new element is compared and shifted across the entire sorted part.
     *
     * Best Case Time Complexity: O(n)
     * -------------------------------
     * Occurs when the array is already sorted.
     * The while loop never executes (early stopping).
     *
     * Average Case Time Complexity: O(n^2)
     *
     * Space Complexity: O(1)
     * ----------------------
     * In-place sorting.
     * Only constant extra space is used.
     */

    static void insertionSort(int[] arr) {
        int n = arr.length;

        // Start from the first index and expand the sorted portion
        for (int i = 0; i < n; i++) {

            int j = i;

            // Move current element left until it is in the correct position
            while (j > 0 && arr[j - 1] > arr[j]) {

                // Swap adjacent elements
                int temp = arr[j];
                arr[j] = arr[j - 1];
                arr[j - 1] = temp;

                j--;
            }
        }
    }

    public static void main(String[] args) {
        int[] arr = {64, 25, 12, 22, 11};

        insertionSort(arr); // Sort the array

        System.out.print("Sorted array: ");
        for (int num : arr) {
            System.out.print(num + " ");
        }
    }
}
