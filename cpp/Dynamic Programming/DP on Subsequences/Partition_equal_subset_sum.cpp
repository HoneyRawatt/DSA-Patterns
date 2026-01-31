#include <bits/stdc++.h>
using namespace std;


// Time Complexity
// O(n * target)

// Space Complexity
// O(target)   // 1D DP array
// ---------------- TABULATION DP (Space Optimized) -----------------
bool subsetSumToK_tabu_OS(int n, int k, vector<int> &arr)
{
    // prev[t] = whether we can form sum t using elements up to previous index
    vector<bool> prev(k + 1, false);
    prev[0] = true;              // sum 0 is always possible

    if (arr[0] <= k)
        prev[arr[0]] = true;

    for (int ind = 1; ind < n; ind++)
    {
        vector<bool> curr(k + 1, false);
        curr[0] = true;

        for (int target = 1; target <= k; target++)
        {
            bool notTake = prev[target];
            bool take = false;

            if (arr[ind] <= target)
                take = prev[target - arr[ind]];

            curr[target] = (take || notTake);
        }
        prev = curr;
    }
    return prev[k];
}

// Time Complexity
// O(n * max_sum / 64)  // extremely fast in practice

// Space Complexity
// ~20000 bits → approx 2.5 KB
bool canPartition_DP(vector<int>& nums) {
    int sum = accumulate(nums.begin(), nums.end(), 0);

    // If total sum is odd → cannot split equally
    if (sum % 2) return false;

    int target = sum / 2;
    return subsetSumToK_tabu_OS(nums.size(), target, nums);
}

// --------------------- BITSET OPTIMIZED SOLUTION ---------------------
bool canPartition_Bitset(vector<int>& nums) {
    int sum = accumulate(nums.begin(), nums.end(), 0);
    if (sum & 1) return false;

    bitset<20200> bt;
    bt[0] = 1;       // sum 0 is possible

    // For each element, update possible sums
    for (auto &e : nums)
        bt |= (bt << e);

    return bt[sum / 2];
}

// ----------------------------- MAIN -----------------------------------
int main() {
    vector<int> nums = {1, 5, 11, 5};

    cout << "Input array: ";
    for (int x : nums) cout << x << " ";
    cout << "\n";

    // ---- Using DP Tabulation ----
    bool ansDP = canPartition_DP(nums);

    // ---- Using Bitset Optimization ----
    bool ansBitset = canPartition_Bitset(nums);

    cout << "DP Tabulation result       : " << (ansDP ? "YES" : "NO") << "\n";
    cout << "Bitset Optimized result    : " << (ansBitset ? "YES" : "NO") << "\n";

    return 0;
}
