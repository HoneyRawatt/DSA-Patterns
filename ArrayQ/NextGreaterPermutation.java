import java.util.*;

public class NextGreaterPermutation {

    static int[] nextGreaterPermutation(int[] arr) {
        int n = arr.length;
        int indx = -1;

        // Step 1: Find first index from right where arr[i] < arr[i + 1]
        for (int i = n - 2; i >= 0; i--) {
            if (arr[i] < arr[i + 1]) {
                indx = i;
                break;
            }
        }

        // Step 2: If no such index found, reverse entire array
        if (indx == -1) {
            reverse(arr, 0, n - 1);
            return arr;
        }

        // Step 3: Find smallest element greater than arr[indx] from right
        for (int i = n - 1; i > indx; i--) {
            if (arr[i] > arr[indx]) {
                swap(arr, i, indx);
                break;
            }
        }

        // Step 4: Reverse the subarray after indx
        reverse(arr, indx + 1, n - 1);

        return arr;
    }

    // Utility method to reverse array from l to r
    static void reverse(int[] arr, int l, int r) {
        while (l < r) {
            swap(arr, l, r);
            l++;
            r--;
        }
    }

    // Utility method to swap elements
    static void swap(int[] arr, int i, int j) {
        int temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
    }

    public static void main(String[] args) {
        int[] arr = {1, 2, 3, 2, 1};

        System.out.print("Original permutation: ");
        for (int num : arr) {
            System.out.print(num + " ");
        }

        nextGreaterPermutation(arr);

        System.out.print("\nNext greater permutation: ");
        for (int num : arr) {
            System.out.print(num + " ");
        }
    }
}
