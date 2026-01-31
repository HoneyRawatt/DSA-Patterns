package Recursion;

import java.util.*;

public class SubsetSum{

    /*
    ====================================================
    INTUITION:
    ----------------------------------------------------
    - We want to compute the sum of all possible subsets.
    - At each index, we have two choices:
        1) Pick the element (add to current sum)
        2) Do NOT pick the element
    - When we reach the end of array, store the sum in result list.
    - Finally, sort the list to get sums in ascending order.
    ====================================================
    */

    static void subsetSum(int ind, int sum, int[] arr, List<Integer> ans) {
        // Base case: all elements processed
        if (ind == arr.length) {
            ans.add(sum);
            return;
        }

        // PICK the current element
        subsetSum(ind + 1, sum + arr[ind], arr, ans);

        // NOT PICK the current element
        subsetSum(ind + 1, sum, arr, ans);
    }

    public static void main(String[] args) {
        int[] arr = {3, 1, 4};
        List<Integer> ans = new ArrayList<>();

        subsetSum(0, 0, arr, ans);

        // Sort sums in ascending order
        Collections.sort(ans);

        // Print all subset sums
        for (int s : ans) {
            System.out.print(s + " ");
        }
    }
}

// ⏱️ Time Complexity
// O(2^n)
// Each element has two choices (pick / not pick)
// Total subsets = 2^n

// 📦 Space Complexity
// O(n)
// Maximum recursion depth = n
// Auxiliary space for current recursion
// Output list ans not counted in auxiliary space


