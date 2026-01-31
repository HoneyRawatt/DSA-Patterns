#include <iostream>
#include <vector>
using namespace std;
/*
Problem Statement

Given a binary array nums (containing only 0s and 1s) and an integer k, count the number of contiguous subarrays that contain exactly k ones.

Example
Input: nums = [1,0,1,0,1], k = 2
Output: 4
Explanation: Subarrays with exactly 2 ones:
[1,0,1], [1,0,1,0], [0,1,0,1], [1,0,1]

Key Idea

Count subarrays with at most k ones → atMost(k)

Count subarrays with at most k-1 ones → atMost(k-1)

Subarrays with exactly k ones = atMost(k) - atMost(k-1)

Intuition (Sliding Window)

Keep a window [l, r] with at most goal ones.

For each r, number of valid subarrays ending at r = r - l + 1.

Sliding window moves l forward when sum > goal. */

// --------------------------------------------
// Binary Subarrays With Sum
// Count subarrays with exactly k ones (1s)
// Formula: exactly_k = at_most(k) - at_most(k - 1)
int numberOfSubarrays(vector<int>& nums, int k) {
    return noofways(nums, k) - noofways(nums, k - 1);
}

// --------------------------------------------
// Count subarrays with at most 'goal' ones
// Time: O(n), Space: O(1)
// Remember:
// - Sliding window approach
// - Valid window: total number of 1s ≤ goal
// - For each valid window, (r - l + 1) subarrays end at r
int noofways(vector<int>& nums, int goal) {
    int l = 0, r = 0, sum = 0, cnt = 0;

    if (goal < 0) return 0;  // No valid subarray can have < 0 ones

    while (r < nums.size()) {
        sum += nums[r];  // Count 1s in current window

        while (sum > goal) {
            sum -= nums[l];  // Shrink from left if > goal
            l++;
        }

        cnt += (r - l + 1);  // All subarrays from l to r are valid
        r++;
    }

    return cnt;
}

// --------------------------------------------
// Main Function to test the logic
int main() {
    vector<int> nums = {1, 0, 1, 0, 1};
    int k = 2;

    int result = numberOfSubarrays(nums, k);
    cout << "Number of subarrays with exactly " << k << " ones: " << result << endl;

    return 0;
}
