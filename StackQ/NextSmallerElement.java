package StackQ;

import java.util.*;

/*
=====================================================
PROBLEM STATEMENT:
-----------------------------------------------------
Given an array arr of size n, find the Nearest
Smaller Element to the LEFT for every element.

For each index i, find the closest element on the
left side of arr[i] that is strictly smaller than
arr[i]. If no such element exists, store -1.

Example:
Input:  [4, 5, 2, 8, 9, 3]
Output: [-1, 4, -1, 2, 8, 2]
=====================================================
*/

class NextSmallerElement{

    /*
    =====================================================
    BRUTE FORCE APPROACH
    -----------------------------------------------------
    INTUITION:
    For each element arr[i], scan all elements to its
    left (from i-1 down to 0) and find the first
    smaller element.

    TIME COMPLEXITY:
    - O(n^2)

    SPACE COMPLEXITY:
    - O(n) for result list
    =====================================================
    */
    public ArrayList<Integer> nearestSmallerElementBrute(int[] arr) {
        int n = arr.length;

        ArrayList<Integer> res = new ArrayList<>();
        for (int i = 0; i < n; i++) res.add(-1);

        for (int i = 0; i < n; i++) {
            // Check elements to the left
            for (int j = i - 1; j >= 0; j--) {
                if (arr[j] < arr[i]) {
                    res.set(i, arr[j]);
                    break;
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
    Use a MONOTONIC INCREASING STACK.

    - Traverse from left to right
    - Pop elements greater than or equal to current
    - Stack top (if exists) is the nearest smaller element

    TIME COMPLEXITY:
    - O(n) (each element pushed & popped once)

    SPACE COMPLEXITY:
    - O(n) for stack + result list
    =====================================================
    */
    public ArrayList<Integer> nearestSmallerElement(int[] arr) {
        int n = arr.length;

        ArrayList<Integer> res = new ArrayList<>();
        for (int i = 0; i < n; i++) res.add(-1);

        Stack<Integer> stack = new Stack<>();

        // Traverse from left to right
        for (int i = 0; i < n; i++) {

            // Remove elements >= current element
            while (!stack.isEmpty() && stack.peek() >= arr[i]) {
                stack.pop();
            }

            // Top of stack is nearest smaller
            if (!stack.isEmpty()) {
                res.set(i, stack.peek());
            }

            // Push current element
            stack.push(arr[i]);
        }
        return res;
    }
}
