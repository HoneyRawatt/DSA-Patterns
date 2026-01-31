package StackQ;

import java.util.*;

public class RemoveKDigits {

    /*
    =====================================================
    PROBLEM STATEMENT:
    -----------------------------------------------------
    Given a string `s` representing a non-negative integer
    and an integer `k`, remove exactly `k` digits from `s`
    such that the resulting number is the smallest possible.

    Leading zeros are not allowed unless the result is "0".
    =====================================================
    */

    /*
    ===============================
    Greedy + Monotonic Stack Approach
    ===============================
    Intuition:
    - To minimize the number, smaller digits should appear earlier
    - Maintain a monotonic increasing stack
    - If current digit < stack top, removing the stack top
      results in a smaller number
    - If removals remain after traversal, remove digits from the end

    Time Complexity: O(n)
    Space Complexity: O(n)
    */
    public static String removeKdigits(String s, int k) {
        Stack<Character> st = new Stack<>();
        int n = s.length();

        // Traverse all digits
        for (int i = 0; i < n; i++) {
            char curr = s.charAt(i);

            // Remove larger digits from the left
            while (!st.isEmpty() && k > 0 && st.peek() > curr) {
                st.pop();
                k--;
            }

            // Push current digit
            st.push(curr);
        }

        // If removals are still left, remove from the end
        while (k > 0 && !st.isEmpty()) {
            st.pop();
            k--;
        }

        // Build result from stack
        StringBuilder res = new StringBuilder();
        while (!st.isEmpty()) {
            res.append(st.pop());
        }
        res.reverse();

        // Remove leading zeros
        while (res.length() > 1 && res.charAt(0) == '0') {
            res.deleteCharAt(0);
        }

        // Handle empty result
        if (res.length() == 0) return "0";

        return res.toString();
    }

    /*
    ===============================
    Main Method
    ===============================
    */
    public static void main(String[] args) {
        String s = "1432219";
        int k = 3;

        System.out.println(removeKdigits(s, k)); 
        // Expected Output: "1219"
    }
}
