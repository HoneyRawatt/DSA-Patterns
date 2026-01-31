// same like two parttiton with difference D
class Solution {
public:
    int findTargetSumWays(vector<int>& nums, int target) {
        int total = 0;
        for (int x : nums) total += x;
        
        // The equation derived: sum(S1) = (total + target) / 2
        if ((total + target) % 2 != 0 || total < abs(target))
            return 0;

        int sum = (total + target) / 2;

        vector<int> dp(sum + 1, 0); 
        dp[0] = 1; // one way to make sum 0 → take no elements

        for (int num : nums) {
            for (int s = sum; s >= num; s--) {
                dp[s] += dp[s - num];
            }
        }

        return dp[sum];
    }
};
