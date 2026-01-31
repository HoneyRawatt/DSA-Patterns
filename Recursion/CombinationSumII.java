package Recursion;

import java.util.*;

public class CombinationSumII{

    /*
    ====================================================
    INTUITION:
    ----------------------------------------------------
    - We want all unique combinations whose sum = target.
    - Each element can be used AT MOST once.
    - Since the array may contain duplicates:
        → Sort the array first
        → Skip duplicate elements at the same recursion level
    - Use a for-loop instead of pick / not-pick recursion.
    - If current element > target, stop further exploration
      (because array is sorted).
    ====================================================
    */

    static void findCombo(int ind, int[] arr, int n, int target,
                          List<List<Integer>> ans, List<Integer> ds) {

        // Base case: valid combination found
        if (target == 0) {
            ans.add(new ArrayList<>(ds));
            return;
        }

        for (int i = ind; i < n; i++) {

            // Skip duplicates at the same recursion level
            if (i > ind && arr[i] == arr[i - 1]) continue;

            // Pruning: no need to proceed further
            if (arr[i] > target) break;

            // PICK current element
            ds.add(arr[i]);
            findCombo(i + 1, arr, n, target - arr[i], ans, ds);

            // BACKTRACK
            ds.remove(ds.size() - 1);
        }
    }

    public static void main(String[] args) {

        int[] arr = {1, 1, 1, 2, 2};
        int target = 4;
        int n = arr.length;

        // Sorting is mandatory to handle duplicates
        Arrays.sort(arr);

        List<List<Integer>> ans = new ArrayList<>();
        List<Integer> ds = new ArrayList<>();

        findCombo(0, arr, n, target, ans, ds);

        // Print all unique combinations
        for (List<Integer> list : ans) {
            for (int num : list) {
                System.out.print(num + " ");
            }
            System.out.println();
        }
    }
}


// ⏱️ Time Complexity
// O(2^n * k)
// n = number of elements
// Each subset explored once
// Copying a valid combination costs O(k)
// Pruning + duplicate skipping reduces actual runtime

// 📦 Space Complexity
// O(k)
// k = maximum depth of recursion
// Output space not counted