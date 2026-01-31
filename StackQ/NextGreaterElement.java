package StackQ;

import java.util.*;

/*
=====================================================
PROBLEM STATEMENT:
-----------------------------------------------------
Given an integer array arr of size n, for each element,
find the Next Greater Element (NGE).

The Next Greater Element for an element x is the
first element to the right of x that is greater than x.
If no such element exists, return -1 for that position.

Example:
Input:  [4, 5, 2, 25]
Output: [5, 25, 25, -1]
=====================================================
*/

public class NextGreaterElement {

    /*
    =====================================================
    BRUTE FORCE APPROACH
    -----------------------------------------------------
    INTUITION:
    For every element arr[i], scan all elements to its
    right and find the first element greater than arr[i].

    If found, store it and stop searching.
    If not found, store -1.

    TIME COMPLEXITY:
    - Two nested loops → O(n^2)

    SPACE COMPLEXITY:
    - O(n) for the result array
    =====================================================
    */
    public static int[] nextGreaterElementBrute(int[] arr) {
        int n = arr.length;
        int[] res = new int[n];

        // Initialize result array with -1
        Arrays.fill(res, -1);

        // Check for each element
        for (int i = 0; i < n; i++) {
            // Look to the right of i
            for (int j = i + 1; j < n; j++) {
                if (arr[j] > arr[i]) {
                    res[i] = arr[j]; // Next greater found
                    break;           // Stop at first greater
                }
            }
        }
        return res;
    }

    /*
    =====================================================
    OPTIMIZED APPROACH (Using Stack)
    -----------------------------------------------------
    INTUITION:
    We traverse the array from RIGHT to LEFT and maintain
    a monotonic decreasing stack.

    - Stack stores potential next greater elements
    - Pop elements smaller than or equal to current
    - Top of the stack (if any) is the next greater element

    WHY RIGHT TO LEFT?
    Because the next greater element must be on the right.

    TIME COMPLEXITY:
    - Each element is pushed and popped once → O(n)

    SPACE COMPLEXITY:
    - O(n) for stack and result array
    =====================================================
    */
    public static int[] nextGreaterElement(int[] arr) {
        int n = arr.length;
        int[] res = new int[n];
        Arrays.fill(res, -1);

        Stack<Integer> stack = new Stack<>();

        // Traverse from right to left
        for (int i = n - 1; i >= 0; i--) {

            // Remove smaller or equal elements
            while (!stack.isEmpty() && stack.peek() <= arr[i]) {
                stack.pop();
            }

            // If stack is not empty, top is next greater
            if (!stack.isEmpty()) {
                res[i] = stack.peek();
            }

            // Push current element
            stack.push(arr[i]);
        }
        return res;
    }

    public static void main(String[] args) {
        int[] arr = {4, 5, 2, 25};

        int[] res1 = nextGreaterElementBrute(arr);
        int[] res2 = nextGreaterElement(arr);

        System.out.print("Brute force result: ");
        for (int x : res1) {
            System.out.print(x + " ");
        }
        System.out.println();

        System.out.print("Optimized result: ");
        for (int x : res2) {
            System.out.print(x + " ");
        }
        System.out.println();
    }
}

