#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
/*
========================================================
PROBLEM STATEMENT:
--------------------------------------------------------
You are given a binary array `nums` (containing only
0s and 1s) and an integer `k`.

You are allowed to flip at most `k` zeros to 1s.

Goal:
- Find the length of the longest subarray containing
  only 1s after performing at most `k` flips.

--------------------------------------------------------
EXAMPLE:
Input:  nums = [1,1,0,0,1,1,1,0,1], k = 2
Output: 7

========================================================
*/

    /*
    ========================================================
    BRUTE FORCE APPROACH:
    --------------------------------------------------------
    Idea:
    - Consider every subarray
    - Count number of zeros
    - If zeros ≤ k, update answer

    --------------------------------------------------------
    INTUITION:
    --------------------------------------------------------
    Check all possible windows and validate whether they
    satisfy the constraint (zeros ≤ k).

    --------------------------------------------------------
    TIME COMPLEXITY:
    - O(n²)

    SPACE COMPLEXITY:
    - O(1)
    ========================================================
    */
int longestOnes_brute(vector<int> &nums, int k) {
    int n = nums.size();
    int maxlen = 0;

    for (int i = 0; i < n; i++) {
        int zeros = 0;
        for (int j = i; j < n; j++) {
            if (nums[j] == 0) zeros++;

            if (zeros <= k) {
                int len = j - i + 1;
                maxlen = max(maxlen, len);
            } else break;
        }
    }
    return maxlen;
}

    /*
    ========================================================
    BETTER APPROACH (SLIDING WINDOW):
    --------------------------------------------------------
    Idea:
    - Use two pointers (left & right)
    - Expand window by moving right
    - Shrink window from left when zeros exceed k

    --------------------------------------------------------
    INTUITION:
    --------------------------------------------------------
    We maintain a window where zeros ≤ k.
    If constraint breaks, move left pointer.

    --------------------------------------------------------
    TIME COMPLEXITY:
    - O(2n) ≈ O(n)

    SPACE COMPLEXITY:
    - O(1)
    ========================================================
    */
int longestOnes_better(vector<int> &nums, int k) {
    int maxlen = 0, l = 0, r = 0, zeros = 0;

    while (r < nums.size()) {
        if (nums[r] == 0) zeros++;

        while (zeros > k) {
            if (nums[l] == 0) zeros--;
            l++;
        }

        // At this point, zeros in window <= k
        int len = r - l + 1;
        maxlen = max(maxlen, len);
        r++;
    }
    return maxlen;
}

    /*
    ========================================================
    OPTIMAL APPROACH (CLEAN SLIDING WINDOW):
    --------------------------------------------------------
    Same logic as above, written more concisely.

    --------------------------------------------------------
    INTUITION:
    --------------------------------------------------------
    - Always expand right
    - Shrink left only when zeros exceed k
    - Update answer whenever window is valid

    --------------------------------------------------------
    TIME COMPLEXITY:
    - O(n)

    SPACE COMPLEXITY:
    - O(1)
    ========================================================
    */
int longestOnes_optimal(vector<int> &nums, int k) {
    int n = nums.size();
    int l = 0, r = 0, maxlen = 0, zeros = 0;

    while (r < n) {
        if (nums[r] == 0) zeros++;

        if (zeros > k) {
            if (nums[l] == 0) zeros--;
            l++;
        }

        if(zeros<=k){
        int len = r - l + 1;
        maxlen = max(maxlen, len);
        }
        r++;
    }

    return maxlen;
}

// ---------------- MAIN FUNCTION ----------------
int main() {
    vector<int> nums = {1, 1, 0, 0, 1, 1, 1, 0, 1};
    int k = 2;

    cout << "Brute force: " << longestOnes_brute(nums, k) << endl;
    cout << "Better (sliding window): " << longestOnes_better(nums, k) << endl;
    cout << "Optimal (clean): " << longestOnes_optimal(nums, k) << endl;

    return 0;
}
