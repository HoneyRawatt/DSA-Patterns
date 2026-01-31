package StackQ;

import java.util.*;

public class MaximalRectangle {

    /*
    =====================================================
    PROBLEM STATEMENT (Largest Rectangle in Histogram):
    -----------------------------------------------------
    Given an array representing heights of histogram bars,
    find the area of the largest rectangle that can be formed.

    This method is used as a helper for solving
    the "Maximal Rectangle in a Binary Matrix" problem.
    =====================================================
    */

    /*
    ===============================
    Optimal Histogram Solution
    ===============================
    Intuition:
    - Use a monotonic increasing stack storing indices
    - When a smaller height appears, rectangles using
      previous heights must end here
    - Width = NSE - PSE - 1

    Time Complexity: O(n)
    Space Complexity: O(n)
    */
    public static int longestRectangleOptimal(int[] arr) {
        int n = arr.length;
        Stack<Integer> st = new Stack<>();
        int maxArea = 0;

        for (int i = 0; i < n; i++) {
            // Maintain increasing stack
            while (!st.isEmpty() && arr[st.peek()] > arr[i]) {
                int ele = st.pop();          // height index
                int nse = i;                 // next smaller element index
                int pse = st.isEmpty() ? -1 : st.peek(); // previous smaller

                maxArea = Math.max(
                    maxArea,
                    arr[ele] * (nse - pse - 1)
                );
            }
            st.push(i);
        }

        // Process remaining bars
        while (!st.isEmpty()) {
            int ele = st.pop();
            int nse = n;
            int pse = st.isEmpty() ? -1 : st.peek();

            maxArea = Math.max(
                maxArea,
                arr[ele] * (nse - pse - 1)
            );
        }

        return maxArea;
    }

    /*
    =====================================================
    PROBLEM STATEMENT (Maximal Rectangle in Binary Matrix):
    -----------------------------------------------------
    Given a binary matrix filled with 0s and 1s,
    find the largest rectangle containing only 1s.
    =====================================================
    */

    /*
    ===============================
    Maximal Rectangle Solution
    ===============================
    Intuition:
    - Treat each row as the base of a histogram
    - Build column-wise prefix sums of consecutive 1s
    - Apply histogram logic for each row

    Time Complexity: O(n * m)
    Space Complexity: O(n * m)
    */
    public static int maximalRectangle(int[][] mat) {
        int n = mat.length;
        if (n == 0) return 0;
        int m = mat[0].length;

        int maxArea = 0;
        int[][] psum = new int[n][m];

        // Build column-wise prefix sums
        for (int j = 0; j < m; j++) {
            int sum = 0;
            for (int i = 0; i < n; i++) {
                if (mat[i][j] == 0) sum = 0;
                else sum++;
                psum[i][j] = sum;
            }
        }

        // Apply largest rectangle in histogram for each row
        for (int i = 0; i < n; i++) {
            maxArea = Math.max(
                maxArea,
                longestRectangleOptimal(psum[i])
            );
        }

        return maxArea;
    }

    /*
    ===============================
    Main Method
    ===============================
    */
    public static void main(String[] args) {
        int[][] mat = {
            {1, 0, 1, 0, 0},
            {1, 0, 1, 1, 1},
            {1, 1, 1, 1, 1},
            {1, 0, 0, 1, 0}
        };

        System.out.println(maximalRectangle(mat)); // Expected Output: 6
    }
}

