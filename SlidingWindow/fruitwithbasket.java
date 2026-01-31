package SlidingWindow;

import java.util.*;

/*
========================================================
PROBLEM STATEMENT:
--------------------------------------------------------
You are given an integer array `fruits` where each
element represents a type of fruit.

You have two baskets, and each basket can hold only
one type of fruit, but unlimited quantity.

Rules:
- You must pick fruits from a contiguous subarray.
- You can store at most 2 different fruit types.

Goal:
- Return the maximum number of fruits you can collect.

--------------------------------------------------------
EXAMPLE:
Input:  fruits = [1, 2, 1, 2, 3, 2, 2, 1]
Output: 4
Explanation: The longest subarray is [1,2,1,2]

========================================================
*/

class fruitwithbasket{

    /*
    ========================================================
    BRUTE FORCE APPROACH:
    --------------------------------------------------------
    Idea:
    - Try every possible subarray
    - Use a set to track distinct fruit types
    - If types ≤ 2, update answer

    --------------------------------------------------------
    INTUITION:
    --------------------------------------------------------
    Generate all subarrays and stop expanding when more
    than 2 fruit types appear.

    --------------------------------------------------------
    TIME COMPLEXITY:
    - O(n²)

    SPACE COMPLEXITY:
    - O(1) (at most 3 elements in set)
    ========================================================
    */
    public static int totalFruitsBrute(int[] fruits) {
        int maxLen = 0;

        for (int i = 0; i < fruits.length; i++) {
            Set<Integer> set = new HashSet<>();

            for (int j = i; j < fruits.length; j++) {
                set.add(fruits[j]);

                if (set.size() <= 2) {
                    maxLen = Math.max(maxLen, j - i + 1);
                } else {
                    break;
                }
            }
        }
        return maxLen;
    }

    /*
    ========================================================
    BETTER APPROACH (SLIDING WINDOW + HASHMAP):
    --------------------------------------------------------
    Idea:
    - Use two pointers (left & right)
    - Store fruit counts in a hashmap
    - Shrink window when distinct fruits exceed 2

    --------------------------------------------------------
    INTUITION:
    --------------------------------------------------------
    Maintain a window with at most 2 fruit types.
    Expand right, shrink left only when constraint breaks.

    --------------------------------------------------------
    TIME COMPLEXITY:
    - O(2n) ≈ O(n)

    SPACE COMPLEXITY:
    - O(n)
    ========================================================
    */
    public static int totalFruitBetter(int[] fruits) {
        int left = 0, maxLen = 0;
        Map<Integer, Integer> map = new HashMap<>();

        for (int right = 0; right < fruits.length; right++) {
            map.put(fruits[right], map.getOrDefault(fruits[right], 0) + 1);

            // shrink window if more than 2 fruit types
            while (map.size() > 2) {
                map.put(fruits[left], map.get(fruits[left]) - 1);
                if (map.get(fruits[left]) == 0)
                    map.remove(fruits[left]);
                left++;
            }

            maxLen = Math.max(maxLen, right - left + 1);
        }
        return maxLen;
    }

    /*
    ========================================================
    OPTIMAL APPROACH (CLEAN SLIDING WINDOW):
    --------------------------------------------------------
    Same logic as above but with a cleaner shrinking step.

    --------------------------------------------------------
    INTUITION:
    --------------------------------------------------------
    - Expand window using right pointer
    - Shrink only once per iteration when needed
    - Window always remains valid

    --------------------------------------------------------
    TIME COMPLEXITY:
    - O(n)

    SPACE COMPLEXITY:
    - O(n)
    ========================================================
    */
    public static int totalFruitOptimal(int[] fruits) {
        int left = 0, maxLen = 0;
        Map<Integer, Integer> map = new HashMap<>();

        for (int right = 0; right < fruits.length; right++) {
            map.put(fruits[right], map.getOrDefault(fruits[right], 0) + 1);

            if (map.size() > 2) {
                map.put(fruits[left], map.get(fruits[left]) - 1);
                if (map.get(fruits[left]) == 0)
                    map.remove(fruits[left]);
                left++;
            }

            if (map.size() <= 2) {
                maxLen = Math.max(maxLen, right - left + 1);
            }
        }
        return maxLen;
    }

    // ------------------- MAIN METHOD -------------------
    public static void main(String[] args) {
        int[] fruits = {1, 2, 1, 2, 3, 2, 2, 1};

        System.out.println("Brute Force: " + totalFruitsBrute(fruits));
        System.out.println("Better (Sliding Window): " + totalFruitBetter(fruits));
        System.out.println("Optimal (Clean Sliding Window): " + totalFruitOptimal(fruits));
    }
}
