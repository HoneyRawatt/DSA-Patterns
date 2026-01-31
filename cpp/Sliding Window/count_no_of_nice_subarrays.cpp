#include <iostream>
#include <vector>
using namespace std;

// --------------------------------------------
// Count subarrays with exactly k odd numbers
// Formula: exactly_k = at_most(k) - at_most(k - 1)
int numberOfSubarrays(vector<int>& nums, int k) {
    return noofways(nums, k) - noofways(nums, k - 1);
}

// --------------------------------------------
// Count subarrays with at most 'goal' odd numbers
// Time: O(n), Space: O(1)
// Remember:
// - Sliding window approach
// - Count subarrays where the number of odd numbers ≤ goal
// - Add (r - l + 1) to count because every subarray ending at r and starting from l..r is valid
int noofways(vector<int>& nums, int goal) {
    int l = 0, r = 0, sum = 0, cnt = 0;

    if (goal < 0) return 0;

    while (r < nums.size()) {
        sum += (nums[r] % 2);  // Count odd numbers

        while (sum > goal) {
            sum -= (nums[l] % 2);
            l++;
        }

        cnt += (r - l + 1);  // All subarrays ending at r and starting from l to r
        r++;
    }

    return cnt;
}

// --------------------------------------------
// Main Function to test the logic
int main() {
    vector<int> nums = {1, 1, 2, 1, 1};
    int k = 3;

    int result = numberOfSubarrays(nums, k);
    cout << "Number of subarrays with exactly " << k << " odd numbers: " << result << endl;

    return 0;
}
