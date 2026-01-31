package BinarySearch.1D;

import java.util.*;

public class FirstandLastOccurence {
    /*
     * Time Complexity (all methods):
     * ------------------------------
     * O(log n) → binary search
     *
     * Space Complexity:
     * -----------------
     * O(1) → iterative, no extra space
     */

    // Lower Bound:
    // First index where arr[index] >= target
    static int lowerBound(int[] arr, int target) {
        int low = 0;
        int high = arr.length - 1;
        int lb = arr.length;

        while (low <= high) {
            int mid = low + (high - low) / 2;

            if (arr[mid] >= target) {
                lb = mid;
                high = mid - 1;
            } else {
                low = mid + 1;
            }
        }
        return lb;
    }

    // Upper Bound (last occurrence version):
    // Last index where arr[index] == target
    static int upperBound(int[] arr, int target) {
        int low = 0;
        int high = arr.length - 1;
        int ub = arr.length;

        while (low <= high) {
            int mid = low + (high - low) / 2;

            if (arr[mid] > target) {
                ub = mid;
                high = mid - 1;
            } else {
                low = mid + 1;
            }
        }
        return ub - 1;
    }

    // Custom Binary Search — First Occurrence
    static int firstOcc(int[] arr, int target) {
        int low = 0, high = arr.length - 1;
        int first = -1;

        while (low <= high) {
            int mid = low + (high - low) / 2;

            if (arr[mid] == target) {
                first = mid;
                high = mid - 1; // move left
            } else if (arr[mid] < target) {
                low = mid + 1;
            } else {
                high = mid - 1;
            }
        }
        return first;
    }

    // Custom Binary Search — Last Occurrence
    static int lastOcc(int[] arr, int target) {
        int low = 0, high = arr.length - 1;
        int last = -1;

        while (low <= high) {
            int mid = low + (high - low) / 2;

            if (arr[mid] == target) {
                last = mid;
                low = mid + 1; // move right
            } else if (arr[mid] < target) {
                low = mid + 1;
            } else {
                high = mid - 1;
            }
        }
        return last;
    }

    public static void main(String[] args) {

        int[] arr = {1, 2, 4, 4, 4, 7, 9};
        Scanner sc = new Scanner(System.in);

        System.out.print("Enter target: ");
        int target = sc.nextInt();

        // Using lower & upper bound
        int lb = lowerBound(arr, target);
        int ub = upperBound(arr, target);

        if (lb == arr.length || arr[lb] != target) {
            lb = ub = -1;
        }

        System.out.println("\nUsing lower_bound / upper_bound:");
        System.out.println("First index: " + lb);
        System.out.println("Last index : " + ub);

        // Using custom binary search
        int first = firstOcc(arr, target);
        int last = lastOcc(arr, target);

        System.out.println("\nUsing custom binary search:");
        System.out.println("First index: " + first);
        System.out.println("Last index : " + last);
    }
}
