package Recursion;

import java.util.*;

public class SubsetsII{

    /*
    ====================================================
    INTUITION:
    ----------------------------------------------------
    - We need to generate all UNIQUE subsets of the array.
    - Since duplicates are present:
        → Sort the array first so duplicates come together.
    - At each index, we have two choices:
        1) TAKE the element at current index
        2) NOT TAKE the element
            → while skipping all its duplicates at once
    - This prevents generating duplicate subsets.
    ====================================================
    */

    static void findSubsets(int ind, int[] nums,
                            List<Integer> ds,
                            List<List<Integer>> ans) {

        // Base case: all elements processed
        if (ind == nums.length) {
            ans.add(new ArrayList<>(ds)); // store copy
            return;
        }

        // TAKE the current element
        ds.add(nums[ind]);
        findSubsets(ind + 1, nums, ds, ans);
        ds.remove(ds.size() - 1); // backtrack

        // SKIP all duplicates of current element
        int nextInd = ind + 1;
        while (nextInd < nums.length && nums[nextInd] == nums[ind]) {
            nextInd++;
        }

        // NOT TAKE the element (skip duplicates)
        findSubsets(nextInd, nums, ds, ans);
    }

    public static void main(String[] args) {

        int[] arr = {1, 2, 3, 3};

        // Sorting is required to group duplicates
        Arrays.sort(arr);

        List<Integer> ds = new ArrayList<>();
        List<List<Integer>> ans = new ArrayList<>();

        findSubsets(0, arr, ds, ans);

        // Print all unique subsets
        for (List<Integer> subset : ans) {
            System.out.print("{ ");
            for (int num : subset) {
                System.out.print(num + " ");
            }
            System.out.println("}");
        }
    }

    /*
    ====================================================
    TIME COMPLEXITY:
    ----------------------------------------------------
    O(2^n)
    - Each element has two choices: take or not take
    - Duplicate skipping avoids repeated subsets but
      worst-case complexity remains exponential

    SPACE COMPLEXITY:
    ----------------------------------------------------
    O(n)
    - Recursion stack depth
    - Temporary subset list (ds)
    - Output space not counted
    ====================================================
    */
}
