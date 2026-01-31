package StackQ;

import java.util.Stack;
import java.util.Arrays;

public class LargestRectangleHistogram {

    /*
    =====================================================
    PROBLEM STATEMENT:
    -----------------------------------------------------
    Given an array representing heights of histogram bars,
    find the area of the largest rectangle that can be
    formed inside the histogram.

    Each bar has:
    - Width = 1
    - Height = arr[i]

    Return the maximum rectangular area possible.
    =====================================================
    */

    /*
    =====================================================
    FUNCTION: findNextSmaller
    -----------------------------------------------------
    Finds the index of the nearest smaller element
    to the RIGHT for each bar.

    If none exists, index = n
    =====================================================
    */
    static int[] findNextSmaller(int[] arr) {
        int n = arr.length;
        int[] nse = new int[n];
        Stack<Integer> st = new Stack<>(); // stores indices

        // Traverse from right to left
        for (int i = n - 1; i >= 0; i--) {

            // Remove bars taller or equal to current bar
            while (!st.isEmpty() && arr[st.peek()] >= arr[i]) {
                st.pop();
            }

            // If stack empty → no smaller element
            nse[i] = st.isEmpty() ? n : st.peek();

            // Push current index
            st.push(i);
        }
        return nse;
    }

    /*
    =====================================================
    FUNCTION: findPrevSmaller
    -----------------------------------------------------
    Finds the index of the nearest smaller element
    to the LEFT for each bar.

    If none exists, index = -1
    =====================================================
    */
    static int[] findPrevSmaller(int[] arr) {
        int n = arr.length;
        int[] pse = new int[n];
        Stack<Integer> st = new Stack<>(); // stores indices

        // Traverse from left to right
        for (int i = 0; i < n; i++) {

            // Remove bars taller than current bar
            while (!st.isEmpty() && arr[st.peek()] > arr[i]) {
                st.pop();
            }

            // If stack empty → no smaller element
            pse[i] = st.isEmpty() ? -1 : st.peek();

            // Push current index
            st.push(i);
        }
        return pse;
    }

    /*
    =====================================================
    BRUTE FORCE (USING NSE + PSE):
    -----------------------------------------------------
    Time Complexity: O(n)
    Space Complexity: O(n)
    =====================================================
    */
    static int longestRectangleBrute(int[] arr) {
        int[] nse = findNextSmaller(arr);
        int[] pse = findPrevSmaller(arr);
        int maxArea = 0;

        // Calculate max area for each bar
        for (int i = 0; i < arr.length; i++) {
            int width = nse[i] - pse[i] - 1;
            maxArea = Math.max(maxArea, arr[i] * width);
        }
        return maxArea;
    }

    /*
    =====================================================
    OPTIMAL APPROACH (SINGLE PASS STACK):
    -----------------------------------------------------
    - Uses a monotonic increasing stack
    - Calculates area when smaller element is found

    Time Complexity: O(n)
    Space Complexity: O(n)
    =====================================================
    */
    static int longestRectangleOptimal(int[] arr) {
        int n = arr.length;
        Stack<Integer> st = new Stack<>();
        int maxArea = 0;

        // Traverse histogram
        for (int i = 0; i < n; i++) {

            // Process bars taller than current
            while (!st.isEmpty() && arr[st.peek()] > arr[i]) {
                int ele = st.pop();
                int nse = i;
                int pse = st.isEmpty() ? -1 : st.peek();
                maxArea = Math.max(maxArea, arr[ele] * (nse - pse - 1));
            }
            st.push(i);
        }

        // Process remaining bars
        while (!st.isEmpty()) {
            int ele = st.pop();
            int nse = n;
            int pse = st.isEmpty() ? -1 : st.peek();
            maxArea = Math.max(maxArea, arr[ele] * (nse - pse - 1));
        }

        return maxArea;
    }

    /*
    =====================================================
    MAIN FUNCTION
    =====================================================
    */
    public static void main(String[] args) {
        int[] heights = {2, 1, 5, 6, 2, 3};

        System.out.println("Brute: " + longestRectangleBrute(heights));
        System.out.println("Optimal: " + longestRectangleOptimal(heights));
    }
}

