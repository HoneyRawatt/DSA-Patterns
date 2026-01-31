#include <bits/stdc++.h>
using namespace std;

/*
==========================================
 HOUSE ROBBER (LINEAR VERSION)
 Used for solving House Robber II by
 taking two cases:
 1) Excluding first house
 2) Excluding last house
==========================================
*/

/* -------------------------------------
   1️⃣ MEMOIZATION (Top-Down DP)
   Time:  O(n)
   Space: O(n) + O(n) recursion stack
-------------------------------------- */
int robber_memo(int ind, vector<int>& nums, vector<int>& dp) {
    if (ind == 0) return nums[0];
    if (ind < 0) return 0;

    if (dp[ind] != -1) return dp[ind];

    int pick = nums[ind] + robber_memo(ind - 2, nums, dp);
    int notpick = robber_memo(ind - 1, nums, dp);

    return dp[ind] = max(pick, notpick);
}

/* -------------------------------------
   2️⃣ TABULATION (Bottom-Up DP)
   Time:  O(n)
   Space: O(n)
-------------------------------------- */
int robber_tabulation(vector<int>& nums) {
    int n = nums.size();
    vector<int> dp(n, 0);

    dp[0] = nums[0];

    for (int i = 1; i < n; i++) {
        int pick = nums[i];
        if (i > 1) pick += dp[i - 2];

        int notpick = dp[i - 1];

        dp[i] = max(pick, notpick);
    }

    return dp[n - 1];
}

/* -------------------------------------
   3️⃣ SPACE OPTIMIZED (Best Version)
   Time:  O(n)
   Space: O(1)
-------------------------------------- */
int robber_optimized(vector<int>& nums) {
    int n = nums.size();

    int prev = nums[0]; // dp[i-1]
    int prev2 = 0;      // dp[i-2]

    for (int i = 1; i < n; i++) {
        int pick = nums[i] + (i > 1 ? prev2 : 0);
        int notpick = prev;

        int curr = max(pick, notpick);

        prev2 = prev;
        prev = curr;
    }

    return prev;
}

/*
==========================================
      HOUSE ROBBER II (CIRCULAR)
==========================================
   Strategy:
   - If we include the 1st house, we cannot include last.
   - If we include the last house, we cannot include the 1st.

   So we compute two cases:
   Case 1: [1 ... n-1]
   Case 2: [0 ... n-2]

   Answer = max(case1, case2)
==========================================
*/
int rob(vector<int>& nums) {
    int n = nums.size();
    if (n == 1) return nums[0]; // special case

    vector<int> temp1, temp2;

    // Case 1: Exclude first house
    for (int i = 1; i < n; i++)
        temp1.push_back(nums[i]);

    // Case 2: Exclude last house
    for (int i = 0; i < n - 1; i++)
        temp2.push_back(nums[i]);

    // Use best version (space optimized)
    return max(robber_optimized(temp1), robber_optimized(temp2));
}

/* -------------------------------------
                MAIN
-------------------------------------- */
int main() {
    vector<int> nums = {2, 3, 2};

    cout << "House Robber II Answer = " << rob(nums) << endl;

    return 0;
}
