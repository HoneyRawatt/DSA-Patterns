package StackQ;

import java.util.*;

/*
=====================================================
PROBLEM STATEMENT:
-----------------------------------------------------
Given a CIRCULAR array arr of size n, find the
Next Greater Element (NGE) for each element.

The Next Greater Element of an element x is the first
element greater than x when traversing the array
circularly (wrapping around to the start).

If no such element exists, store -1.

Example:
Input:  [1, 2, 1]
Output: [2, -1, 2]
=====================================================
*/

class NextGreaterElementII{

    /*
    =====================================================
    BRUTE FORCE APPROACH (Circular Array)
    -----------------------------------------------------
    INTUITION:
    For each element arr[i], we check the next n elements
    in circular order using modulo (%) to find the first
    greater element.

    TIME COMPLEXITY:
    - O(n^2)

    SPACE COMPLEXITY:
    - O(n) for the result list
    =====================================================
    */
    public ArrayList<Integer> nextLargerElementBrute(int[] arr) {
        int n = arr.length;

        // Result list initialized with -1
        ArrayList<Integer> res = new ArrayList<>();
        for (int i = 0; i < n; i++) {
            res.add(-1);
        }

        // Check for each element
        for (int i = 0; i < n; i++) {
            // Traverse next n elements circularly
            for (int j = i + 1; j < i + n; j++) {
                int idx = j % n; // Circular index

                if (arr[idx] > arr[i]) {
                    res.set(i, arr[idx]);
                    break;
                }
            }
        }
        return res;
    }

    /*
    =====================================================
    OPTIMIZED APPROACH (Using Stack – Circular)
    -----------------------------------------------------
    INTUITION:
    - Traverse the array twice (2n) to simulate circularity
    - Use a MONOTONIC DECREASING STACK
    - Pop smaller or equal elements
    - Top of stack gives the next greater element

    WHY STORE ANSWER ONLY WHEN i < n?
    Because answers are required only for original indices.

    TIME COMPLEXITY:
    - O(n) → each element pushed and popped once

    SPACE COMPLEXITY:
    - O(n) → stack + result list
    =====================================================
    */
    public ArrayList<Integer> nextLargerElement(int[] arr) {
        int n = arr.length;

        ArrayList<Integer> res = new ArrayList<>();
        for (int i = 0; i < n; i++) {
            res.add(-1);
        }

        Stack<Integer> stack = new Stack<>();

        // Traverse array twice in reverse order
        for (int i = 2 * n - 1; i >= 0; i--) {
            int idx = i % n; // Circular index

            // Remove elements smaller or equal to current
            while (!stack.isEmpty() && stack.peek() <= arr[idx]) {
                stack.pop();
            }

            // Store result only for first n elements
            if (i < n && !stack.isEmpty()) {
                res.set(idx, stack.peek());
            }

            // Push current element
            stack.push(arr[idx]);
        }
        return res;
    }
}
