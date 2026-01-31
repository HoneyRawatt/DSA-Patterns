package Sorting;

import java.util.*;

// Quick Sort implementation in Java
public class QuickSort {

    /*
     * Time Complexity Intuition:
     * --------------------------
     * Best Case: O(n log n)
     * - Pivot divides the array into two nearly equal halves.
     *
     * Average Case: O(n log n)
     * - Random distribution of elements around pivot.
     *
     * Worst Case: O(n^2)
     * - Occurs when the array is already sorted or reverse sorted
     *   and a bad pivot (first or last element) is chosen.
     *
     * Space Complexity Intuition:
     * ---------------------------
     * - Sorting is done in-place.
     * - Extra space is used only by the recursion stack.
     *
     * Space Complexity: O(log n) on average
     * Worst Case Space: O(n) (skewed recursion tree)
     */

    // Partition function (same logic as C++ version)
    static int partition(int[] arr, int low, int high) {

        int pivot = arr[low]; // Choosing first element as pivot
        int i = low;
        int j = high;

        // Rearranging elements around pivot
        while (i < j) {

            // Move i to the right until an element greater than pivot is found
            while (i <= high - 1 && arr[i] <= pivot) {
                i++;
            }

            // Move j to the left until an element less than or equal to pivot is found
            while (j >= low + 1 && arr[j] > pivot) {
                j--;
            }

            // Swap elements if pointers haven't crossed
            if (i < j) {
                int temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }

        // Place pivot in its correct position
        int temp = arr[low];
        arr[low] = arr[j];
        arr[j] = temp;

        return j; // Pivot index
    }

    // QuickSort function
    static void quickSort(int[] arr, int low, int high) {

        // Base condition
        if (low < high) {

            // Partition the array
            int partitionIndex = partition(arr, low, high);

            // Sort left subarray
            quickSort(arr, low, partitionIndex - 1);

            // Sort right subarray
            quickSort(arr, partitionIndex + 1, high);
        }
    }

    public static void main(String[] args) {
        int[] arr = {64, 25, 12, 22, 11};

        quickSort(arr, 0, arr.length - 1);

        System.out.print("Sorted array: ");
        for (int num : arr) {
            System.out.print(num + " ");
        }
    }
}

