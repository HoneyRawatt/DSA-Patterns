package Sorting;

import java.util.*;

// Merge Sort implementation in Java
public class MergeSort {

    /*
     * Time Complexity Intuition:
     * --------------------------
     * - The array is recursively divided into two halves → log₂(n) levels.
     * - At each level, merging takes O(n) time.
     *
     * Total Time Complexity:
     * Worst Case  : O(n log n)
     * Average Case: O(n log n)
     * Best Case   : O(n log n)
     *
     * Space Complexity Intuition:
     * ---------------------------
     * - A temporary array is used during each merge step.
     * - Extra space proportional to the size of the array is required.
     *
     * Space Complexity: O(n)
     */

    // Function to merge two sorted halves of the array
    static void merge(int[] arr, int low, int mid, int high) {

        // Temporary list to store merged elements
        ArrayList<Integer> temp = new ArrayList<>();

        int left = low;       // Pointer for left subarray
        int right = mid + 1;  // Pointer for right subarray

        // Merge elements from both halves in sorted order
        while (left <= mid && right <= high) {
            if (arr[left] < arr[right]) {
                temp.add(arr[left++]);
            } else {
                temp.add(arr[right++]);
            }
        }

        // Copy remaining elements from left half
        while (left <= mid) {
            temp.add(arr[left++]);
        }

        // Copy remaining elements from right half
        while (right <= high) {
            temp.add(arr[right++]);
        }

        // Copy merged elements back to original array
        for (int i = low; i <= high; i++) {
            arr[i] = temp.get(i - low);
        }
    }

    // Recursive merge sort function
    static void mergeSort(int[] arr, int low, int high) {

        // Base case: single element is already sorted
        if (low >= high) return;

        int mid = (low + high) / 2;

        // Sort left half
        mergeSort(arr, low, mid);

        // Sort right half
        mergeSort(arr, mid + 1, high);

        // Merge both halves
        merge(arr, low, mid, high);
    }

    public static void main(String[] args) {
        int[] arr = {64, 25, 12, 22, 11};

        mergeSort(arr, 0, arr.length - 1);

        System.out.print("Sorted array: ");
        for (int num : arr) {
            System.out.print(num + " ");
        }
    }
}
