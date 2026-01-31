package BinarySearch.1D;

import java.util.*;

// Lower Bound & Upper Bound using Binary Search
public class LowerUpperBound{

    /*
     * Time Complexity (Both lower & upper bound):
     * -------------------------------------------
     * Each function uses binary search.
     * The search space is halved every iteration.
     *
     * Time Complexity: O(log n)
     *
     * Space Complexity:
     * -----------------
     * Iterative approach → no recursion stack.
     *
     * Space Complexity: O(1)
     */

    // Lower Bound:
    // Returns the first index where arr[index] >= target
    static int lowerBound(int[] arr, int target) {
        int low = 0;
        int lb = arr.length;        // default insert position
        int high = arr.length - 1;

        while (low <= high) {
            int mid = low + (high - low) / 2;

            if (arr[mid] >= target) {
                lb = mid;           // possible lower bound
                high = mid - 1;     // move left to find smaller index
            } else {
                low = mid + 1;
            }
        }
        return lb;
    }

    // Upper Bound:
    // Returns the first index where arr[index] > target
    static int upperBound(int[] arr, int target) {
        int low = 0;
        int ub = arr.length;        // default insert position
        int high = arr.length - 1;

        while (low <= high) {
            int mid = low + (high - low) / 2;

            if (arr[mid] > target) {
                ub = mid;           // possible upper bound
                high = mid - 1;     // move left
            } else {
                low = mid + 1;
            }
        }
        return ub;
    }

    public static void main(String[] args) {

        int[] arr = {1, 2, 4, 4, 4, 7, 9};
        Scanner sc = new Scanner(System.in);

        System.out.print("Enter target: ");
        int target = sc.nextInt();

        int lb = lowerBound(arr, target);
        int ub = upperBound(arr, target);

        System.out.println("Lower Bound index: " + lb);
        System.out.println("Upper Bound index: " + ub);

        // Count occurrences of target
        if (lb == arr.length || arr[lb] != target) {
            System.out.println("Target not found");
        } else {
            System.out.println("Target occurs " + (ub - lb) + " times");
        }
    }
}
