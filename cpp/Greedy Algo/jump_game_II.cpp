#include <bits/stdc++.h>
using namespace std;

/*
-------------------------------------------------------------
🔹 PROBLEM:
Given an array nums[] where each element represents the maximum jump
length from that position, find the minimum number of jumps required
to reach the end of the array (starting from index 0).

If it’s not possible to reach the end, return -1.
-------------------------------------------------------------
*/

/*-------------------------------------------------------------
🔹 Approach 1: Brute Force (Recursive)
---------------------------------------------------------------
Try all possible jumps from each index recursively and take
the minimum. Extremely slow (exponential).
---------------------------------------------------------------
Time Complexity: O(2^N)
Space Complexity: O(N) (recursion stack)
-------------------------------------------------------------*/
int maxJump_brute(int ind, int jumps, vector<int>& nums) {
    int n = nums.size();
    if (ind >= n - 1) return jumps;

    int mini = INT_MAX;
    for (int i = 1; i <= nums[ind]; i++)
        mini = min(mini, maxJump_brute(ind + i, jumps + 1, nums));

    return mini;
}

/*-------------------------------------------------------------
🔹 Approach 2: Dynamic Programming (Top-Down Memoization)
---------------------------------------------------------------
We store already computed results in dp[ind][jumps] to avoid
recomputing subproblems.
---------------------------------------------------------------
Time Complexity: O(N^2)
Space Complexity: O(N^2)
-------------------------------------------------------------*/
int maxJump_dp(int ind, int jumps, vector<int>& nums, vector<vector<int>>& dp) {
    int n = nums.size();
    if (ind >= n - 1) return jumps;
    if (dp[ind][jumps] != -1) return dp[ind][jumps];

    int mini = INT_MAX;
    for (int i = 1; i <= nums[ind]; i++)
        mini = min(mini, maxJump_dp(ind + i, jumps + 1, nums, dp));

    return dp[ind][jumps] = mini;
}

/*-------------------------------------------------------------
🔹 Approach 3: Greedy Optimal
---------------------------------------------------------------
We maintain a sliding window [l, r] representing the range of
indices we can reach with the current number of jumps.
We extend this window using the farthest reachable index
within that range, and increment jump count.

If at any point l > r, it means we’re stuck → return -1.
---------------------------------------------------------------
Time Complexity: O(N)
Space Complexity: O(1)
-------------------------------------------------------------*/
int maxJump_optimal(vector<int>& nums) {
    int n = nums.size();
    if (n <= 1) return 0;
    if (nums[0] == 0) return -1;

    int jumps = 0, l = 0, r = 0;
    while (r < n - 1) {
        int farthest = 0;
        for (int i = l; i <= r; i++)
            farthest = max(farthest, i + nums[i]);

        jumps++;
        l = r + 1;
        r = farthest;

        if (l > r) return -1; // unreachable
    }
    return jumps;
}

/*-------------------------------------------------------------
🔹 MAIN FUNCTION
-------------------------------------------------------------*/
int main() {
    vector<int> nums = {2, 3, 1, 1, 4};

    cout << "🔹 Input Array: ";
    for (int x : nums) cout << x << " ";
    cout << "\n";

    cout << "Brute Force (Exponential): " << maxJump_brute(0, 0, nums) << endl;

    vector<vector<int>> dp(nums.size() + 1, vector<int>(nums.size() + 1, -1));
    cout << "DP (Memoized): " << maxJump_dp(0, 0, nums, dp) << endl;

    cout << "Greedy Optimal: " << maxJump_optimal(nums) << endl;

    return 0;
}

/*
-------------------------------------------------------------
🔹 INTUITION SUMMARY
-------------------------------------------------------------
- The brute-force approach explores all possible jumps → exponential.
- The DP approach optimizes by storing overlapping subproblems.
- The greedy approach expands reachable ranges and counts jumps
  whenever the range ends — fastest and most memory-efficient.

🕒 Time Complexities:
    • Brute Force: O(2^N)
    • DP: O(N^2)
    • Greedy: O(N)

💾 Space Complexities:
    • Brute Force: O(N)
    • DP: O(N^2)
    • Greedy: O(1)
-------------------------------------------------------------
*/
