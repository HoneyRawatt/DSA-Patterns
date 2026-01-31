package BitManipulation;

import java.util.ArrayList;
import java.util.List;

public class SubsetsBitMask {

    /*
     Intuition:
     - An array of size n has exactly 2^n subsets.
     - We use bit masking to generate all subsets.
     - Numbers from 0 to (2^n - 1) act as masks.
     - If the i-th bit in the mask is set, we include arr[i] in the subset.

     Example:
     arr = {1, 2, 3}
     mask = 5 -> binary 101
     => include arr[0] and arr[2] -> {1, 3}
    */
    public static List<List<Integer>> subsets(int[] arr) {
        int n = arr.length;
        List<List<Integer>> ans = new ArrayList<>();

        // Total subsets = 2^n
        for (int mask = 0; mask < (1 << n); mask++) {
            List<Integer> list = new ArrayList<>();

            // Check each bit position
            for (int i = 0; i < n; i++) {
                // If i-th bit is set, include arr[i]
                if ((mask & (1 << i)) != 0) {
                    list.add(arr[i]);
                }
            }
            ans.add(list);
        }
        return ans;
    }

    /*
     Time Complexity:
     - There are 2^n subsets.
     - For each subset, we check n bits.
     - Total Time Complexity: O(n * 2^n)

     Space Complexity:
     - Output space: O(n * 2^n) to store all subsets.
     - Auxiliary space (excluding output): O(n) for temporary list.
    */

    // Optional main method for testing
    public static void main(String[] args) {
        int[] arr = {1, 2, 3};

        List<List<Integer>> result = subsets(arr);

        System.out.println(result);
    }
}
