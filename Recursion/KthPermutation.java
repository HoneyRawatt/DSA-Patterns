package Recursion;

import java.util.*;

class KthPermutation{

    /*
    ============================
    INTUITION
    ============================
    - There are n! permutations of numbers from 1 to n.
    - Each number contributes (n-1)! permutations starting with it.
    - Instead of generating all permutations (which is expensive),
      we directly calculate the k-th permutation using factorial math.
    - We convert k to 0-based indexing.
    - At each step:
        • Decide which number should be placed next
        • Remove it from the list
        • Reduce the problem size
    */

    // Function to return the kth permutation of numbers from 1 to n
    public static String getPermutation(int n, int k) {

        int fact = 1;
        List<Integer> numbers = new ArrayList<>();

        // Step 1: Compute (n-1)! and store numbers 1 to n
        for (int i = 1; i < n; i++) {
            fact *= i;
            numbers.add(i);
        }
        numbers.add(n);

        // Convert k to 0-based index
        k = k - 1;

        StringBuilder ans = new StringBuilder();

        // Step 2: Pick digits one by one
        while (!numbers.isEmpty()) {

            int index = k / fact;
            ans.append(numbers.get(index));
            numbers.remove(index);

            if (numbers.isEmpty()) break;

            k = k % fact;
            fact = fact / numbers.size();
        }

        return ans.toString();
    }

    // Driver code
    public static void main(String[] args) {

        int n = 4, k = 17;

        String result = getPermutation(n, k);
        System.out.println("The " + k + "th permutation of numbers from 1 to " + n + " is: " + result);
    }
}

/*
============================
TIME & SPACE COMPLEXITY
============================

Time Complexity:
- We perform n iterations.
- Removing an element from ArrayList costs O(n).
- Overall Time Complexity: O(n^2)

Space Complexity:
- List to store numbers: O(n)
- StringBuilder: O(n)
- Overall Space Complexity: O(n)
*/
