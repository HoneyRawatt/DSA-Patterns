package Recursion;

import java.util.*;

public class Permutations{

    /*
    ====================================================
    INTUITION (Using Frequency Array):
    ----------------------------------------------------
    - We want to generate all UNIQUE permutations.
    - Since duplicates may exist:
        → Sort the array first.
    - Use a frequency array to track which elements
      are already used in the current permutation.
    - To avoid duplicate permutations:
        → If current element is same as previous AND
          previous has not been used, skip it.
    ====================================================
    */

    static void printAllPermu(List<Integer> ds, int[] arr,
                              List<List<Integer>> ans, boolean[] used) {

        // Base case: one permutation formed
        if (ds.size() == arr.length) {
            ans.add(new ArrayList<>(ds));
            return;
        }

        for (int i = 0; i < arr.length; i++) {

            // Skip already used elements
            if (used[i]) continue;

            // Skip duplicates
            if (i > 0 && arr[i] == arr[i - 1] && !used[i - 1]) continue;

            // PICK
            ds.add(arr[i]);
            used[i] = true;

            printAllPermu(ds, arr, ans, used);

            // BACKTRACK
            used[i] = false;
            ds.remove(ds.size() - 1);
        }
    }

    /*
    ====================================================
    OPTIMIZED PERMUTATION (Swap Method)
    ----------------------------------------------------
    - No extra frequency array
    - Fix one position and swap remaining elements
    - Generates ALL permutations (duplicates included)
    ====================================================
    */

    static void printAllPermuOptimized(int ind, int[] arr,
                                       List<List<Integer>> ans) {

        if (ind == arr.length) {
            List<Integer> temp = new ArrayList<>();
            for (int x : arr) temp.add(x);
            ans.add(temp);
            return;
        }

        for (int i = ind; i < arr.length; i++) {
            swap(arr, ind, i);
            printAllPermuOptimized(ind + 1, arr, ans);
            swap(arr, ind, i); // backtrack
        }
    }

    static void swap(int[] arr, int i, int j) {
        int temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
    }

    public static void main(String[] args) {

        int[] arr = {1, 1, 2};

        // Sorting is mandatory to handle duplicates
        Arrays.sort(arr);

        List<List<Integer>> ans = new ArrayList<>();
        List<Integer> ds = new ArrayList<>();
        boolean[] used = new boolean[arr.length];

        printAllPermu(ds, arr, ans, used);

        // Print all unique permutations
        for (List<Integer> perm : ans) {
            for (int num : perm) {
                System.out.print(num + " ");
            }
            System.out.println();
        }
    }

    /*
    ====================================================
    TIME COMPLEXITY:
    ----------------------------------------------------
    O(n! * n)
    - n! permutations
    - Copying each permutation costs O(n)

    SPACE COMPLEXITY:
    ----------------------------------------------------
    O(n)
    - Recursion stack
    - Frequency array
    - Temporary permutation list
    - Output space not counted
    ====================================================
    */
}
