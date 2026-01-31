#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

/*
========================================================
PROBLEM STATEMENT:
--------------------------------------------------------
You are given an array `cardPoints` where each element
represents the points of a card.

You must pick exactly `k` cards.

Rules:
- You can pick a card only from the start OR the end
  of the array.
- Each picked card adds its value to your score.

Goal:
- Return the maximum possible score obtainable by
  picking exactly `k` cards.

========================================================
BRUTE FORCE APPROACH:
--------------------------------------------------------
Try all possible subarrays of length k and compute
their sum.

TIME COMPLEXITY:
- O(k²)

SPACE COMPLEXITY:
- O(1)

========================================================
*/
int maxScore_brute(vector<int>& cardPoints, int k) {
    int n = cardPoints.size();
    int maxSum = 0;

    for (int left = 0; left <= k; left++) {
        int sum = 0;

        // take left cards
        for (int i = 0; i < left; i++)
            sum += cardPoints[i];

        // take right cards
        for (int i = 0; i < k - left; i++)
            sum += cardPoints[n - 1 - i];

        maxSum = max(maxSum, sum);
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
- You will take some cards from the LEFT
- And the remaining from the RIGHT

Let:
- i cards from the left
- (k - i) cards from the right

We try all such combinations and track the maximum sum.

--------------------------------------------------------
KEY IDEA:
--------------------------------------------------------
1. Start by taking all `k` cards from the left.
2. Then, step-by-step:
   - Remove one card from the left
   - Add one card from the right
3. Keep updating the maximum score.

--------------------------------------------------------
WHY THIS WORKS:
--------------------------------------------------------
There are only `k + 1` possible ways to pick cards
from both ends.

This avoids unnecessary recomputation.

--------------------------------------------------------
TIME COMPLEXITY:
- O(k)

SPACE COMPLEXITY:
- O(1)
========================================================
*/
int maxScore(vector<int>& cardPoints, int k) {
    int lsum = 0, rsum = 0, maxsum = 0;
    int n = cardPoints.size();

    // Step 1: Take all k cards from the left initially
    for (int i = 0; i < k; i++) {
        lsum += cardPoints[i];
    }

    maxsum = lsum;  // initial max

    // Step 2: Replace left cards with right cards one by one
    int rind = n - 1;
    for (int i = k - 1; i >= 0; i--) {
        lsum -= cardPoints[i];      // remove one from left
        rsum += cardPoints[rind];   // add one from right
        rind--;

        maxsum = max(maxsum, lsum + rsum);
    }

    return maxsum;
}

// ------------------- MAIN FUNCTION -------------------
int main() {
    vector<int> cardPoints = {1, 2, 3, 4, 5, 6, 1};
    int k = 3;

    int result = maxScore(cardPoints, k);
    cout << "Maximum score by picking " << k << " cards: " << result << endl;

    return 0;
}
