package Recursion;
import java.util.*;

public class CombinationSum{

    /*
    ====================================================
    INTUITION:
    ----------------------------------------------------
    - At every index, we have two choices:
        1) PICK the element (if it does not exceed target)
           → stay on the same index (repetition allowed)
        2) NOT PICK the element
           → move to next index
    - When we reach index == n:
        - If target == 0, we found a valid combination
    ====================================================
    */

    static void findCombo(int ind, int[] arr, int n, int target,
                          List<List<Integer>> ans, List<Integer> ds) {

        // Base case
        if (ind == n) {
            if (target == 0) {
                ans.add(new ArrayList<>(ds)); // store copy
            }
            return;
        }

        // PICK the element (repetition allowed)
        if (arr[ind] <= target) {
            ds.add(arr[ind]);
            findCombo(ind, arr, n, target - arr[ind], ans, ds);
            ds.remove(ds.size() - 1); // backtrack
        }

        // NOT PICK the element
        findCombo(ind + 1, arr, n, target, ans, ds);
    }

    public static void main(String[] args) {

        int[] arr = {5, 3, 4, 1};
        int n = arr.length;
        int target = 4;

        List<List<Integer>> ans = new ArrayList<>();
        List<Integer> ds = new ArrayList<>();

        findCombo(0, arr, n, target, ans, ds);

        // Print all combinations
        for (List<Integer> list : ans) {
            for (int num : list) {
                System.out.print(num + " ");
            }
            System.out.println();
        }
    }
}
