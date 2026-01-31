package Recursion;
import java.util.*;

public class SubsequencesSumK{

    /*
    ====================================================
    1️⃣ COUNT subsequences with sum = K
    ====================================================
    INTUITION:
    ----------------------------------------------------
    - For every element, we have two choices:
        1) Pick it (add to sum)
        2) Do NOT pick it
    - When we reach the end (index == n),
      check if current sum equals target.
    - Return 1 if valid, else 0.
    - Total count = left + right recursion.
    ====================================================
    */

    static int countSubseqK(int ind, int s, int[] arr, int sum, int n) {
        if (ind == n) {
            return (s == sum) ? 1 : 0;
        }

        // PICK
        s += arr[ind];
        int left = countSubseqK(ind + 1, s, arr, sum, n);

        // NOT PICK (backtrack sum)
        s -= arr[ind];
        int right = countSubseqK(ind + 1, s, arr, sum, n);

        return left + right;
    }

    /*
    ====================================================
    2️⃣ PRINT ONLY ONE subsequence with sum = K
    ====================================================
    INTUITION:
    ----------------------------------------------------
    - Same pick / not-pick recursion
    - As soon as one valid subsequence is found,
      return true and stop further recursion.
    ====================================================
    */

    static boolean onlyOneSubseqK(int ind, List<Integer> ds, int s,
                                  int[] arr, int sum, int n) {

        if (ind == n) {
            if (s == sum) {
                for (int x : ds) System.out.print(x + " ");
                System.out.println();
                return true;
            }
            return false;
        }

        // PICK
        ds.add(arr[ind]);
        s += arr[ind];
        if (onlyOneSubseqK(ind + 1, ds, s, arr, sum, n)) return true;

        // BACKTRACK
        ds.remove(ds.size() - 1);
        s -= arr[ind];

        // NOT PICK
        if (onlyOneSubseqK(ind + 1, ds, s, arr, sum, n)) return true;

        return false;
    }

    /*
    ====================================================
    3️⃣ PRINT ALL subsequences with sum = K
    ====================================================
    INTUITION:
    ----------------------------------------------------
    - Explore all pick / not-pick paths
    - Print subsequence whenever sum == K at base case
    ====================================================
    */

    static void allSubseqK(int ind, List<Integer> ds, int s,
                           int[] arr, int sum, int n) {

        if (ind == n) {
            if (s == sum) {
                for (int x : ds) System.out.print(x + " ");
                System.out.println();
            }
            return;
        }

        // PICK
        ds.add(arr[ind]);
        s += arr[ind];
        allSubseqK(ind + 1, ds, s, arr, sum, n);

        // BACKTRACK
        ds.remove(ds.size() - 1);
        s -= arr[ind];

        // NOT PICK
        allSubseqK(ind + 1, ds, s, arr, sum, n);
    }

    public static void main(String[] args) {

        int n = 4;
        int[] arr = {5, 3, 4, 1};
        int sum = 4;

        List<Integer> ds = new ArrayList<>();

        // Print all subsequences with sum = K
        allSubseqK(0, ds, 0, arr, sum, n);

        // Count subsequences
        // System.out.println(countSubseqK(0, 0, arr, sum, n));

        // Print only one subsequence
        // onlyOneSubseqK(0, ds, 0, arr, sum, n);
    }
}
