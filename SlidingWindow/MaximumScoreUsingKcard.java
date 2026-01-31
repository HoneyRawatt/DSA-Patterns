package SlidingWindow;

import java.util.*;

/*
========================================================
PROBLEM STATEMENT:
--------------------------------------------------------
You are given an integer array `cardPoints` where each
element represents the points of a card.

You must pick exactly `k` cards.

Rules:
- You can pick cards only from the start OR the end
  of the array.
- Each picked card adds its value to your score.

Goal:
- Return the maximum possible score.

========================================================
BRUTE FORCE APPROACH:
--------------------------------------------------------
Try all possible ways of taking:
- `i` cards from the left
- `(k - i)` cards from the right

TIME COMPLEXITY:
- O(k²)

SPACE COMPLEXITY:
- O(1)
========================================================
*/
class MaximumScoreUsingKcard{

    public static int maxScoreBrute(int[] cardPoints, int k) {
        int n = cardPoints.length;
        int maxSum = 0;

        for (int left = 0; left <= k; left++) {
            int sum = 0;

            // take cards from the left
            for (int i = 0; i < left; i++) {
                sum += cardPoints[i];
            }

            // take cards from the right
            for (int i = 0; i < k - left; i++) {
                sum += cardPoints[n - 1 - i];
            }

            maxSum = Math.max(maxSum, sum);
        }

        return maxSum;
    }

    /*
    ========================================================
    OPTIMIZED APPROACH (SLIDING WINDOW / PREFIX-SUFFIX):
    --------------------------------------------------------

    INTUITION:
    --------------------------------------------------------
    If you pick `k` cards:
    - Some cards come from the LEFT
    - The remaining come from the RIGHT

    Try all such combinations efficiently.

    --------------------------------------------------------
    KEY IDEA:
    --------------------------------------------------------
    1. Take all `k` cards from the left.
    2. One by one:
       - Remove a card from the left
       - Add a card from the right
    3. Track the maximum sum.

    --------------------------------------------------------
    TIME COMPLEXITY:
    - O(k)

    SPACE COMPLEXITY:
    - O(1)
    ========================================================
    */
    public static int maxScore(int[] cardPoints, int k) {
        int n = cardPoints.length;
        int leftSum = 0, rightSum = 0, maxSum;

        // Step 1: Take all k cards from the left
        for (int i = 0; i < k; i++) {
            leftSum += cardPoints[i];
        }

        maxSum = leftSum;

        // Step 2: Replace left cards with right cards
        int rightIndex = n - 1;
        for (int i = k - 1; i >= 0; i--) {
            leftSum -= cardPoints[i];          // remove from left
            rightSum += cardPoints[rightIndex--]; // add from right
            maxSum = Math.max(maxSum, leftSum + rightSum);
        }

        return maxSum;
    }

    // ------------------- MAIN METHOD -------------------
    public static void main(String[] args) {
        int[] cardPoints = {1, 2, 3, 4, 5, 6, 1};
        int k = 3;

        int result = maxScore(cardPoints, k);
        System.out.println("Maximum score by picking " + k + " cards: " + result);
    }
}
