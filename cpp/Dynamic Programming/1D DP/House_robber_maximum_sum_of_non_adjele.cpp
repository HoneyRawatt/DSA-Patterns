#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

/*
-----------------------------------------------------
💰 HOUSE ROBBER (Dynamic Programming)
-----------------------------------------------------
You are given an array `nums` where each element
represents the amount of money in a house.
You cannot rob two adjacent houses.

Return the maximum amount of money you can rob.
-----------------------------------------------------
Example:
nums = [2, 7, 9, 3, 1]
Output = 12  (Rob house 1 and 3 → 2 + 9 + 1 = 12)
-----------------------------------------------------
*/

// 🔹 MEMOIZATION (Top-Down DP)
int house_robber_memoization(int ind, vector<int>& nums, vector<int>& dp) {
    if (ind == 0) return nums[0];
    if (ind < 0) return 0;
    if (dp[ind] != -1) return dp[ind];

    int pick = nums[ind] + house_robber_memoization(ind - 2, nums, dp);
    int notpick = 0 + house_robber_memoization(ind - 1, nums, dp);

    return dp[ind] = max(pick, notpick);
}

// 🔹 TABULATION (Bottom-Up DP)
int house_robber_tabulation(vector<int>& nums) {
    int n = nums.size();
    vector<int> dp(n, 0);
    dp[0] = nums[0];

    for (int i = 1; i < n; i++) {
        int pick = nums[i];
        if (i > 1) pick += dp[i - 2];
        int notpick = 0 + dp[i - 1];
        dp[i] = max(pick, notpick);
    }
    return dp[n - 1];
}

// 🔹 SPACE OPTIMIZED
int house_robber_optimized(vector<int>& nums) {
    int n = nums.size();
    int prev = nums[0];
    int prev2 = 0;

    for (int i = 1; i < n; i++) {
        int pick = nums[i];
        if (i > 1) pick += prev2;
        int notpick = 0 + prev;

        int curr = max(pick, notpick);
        prev2 = prev;
        prev = curr;
    }
    return prev;
}

// 🔹 MAIN FUNCTION
int main() {
    vector<int> nums = {2, 7, 9, 3, 1};
    int n = nums.size();
    vector<int> dp(n, -1);

    cout << "Memoization: " << house_robber_memoization(n - 1, nums, dp) << endl;
    cout << "Tabulation: " << house_robber_tabulation(nums) << endl;
    cout << "Optimized: " << house_robber_optimized(nums) << endl;

    return 0;
}
