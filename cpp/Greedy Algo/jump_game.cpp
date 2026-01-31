#include <bits/stdc++.h>
using namespace std;

/*
---------------------------------------------------------
🏃‍♂️ PROBLEM: Jump Game
---------------------------------------------------------
Given an array `nums` where each element represents the
maximum jump length at that position, determine if you
can reach the last index starting from index 0.

Example:
nums = [2, 3, 1, 1, 4] → true  (0→1→4)
nums = [3, 2, 1, 0, 4] → false (stuck at index 3)
---------------------------------------------------------
*/

class Solution {
public:
    bool canJump(vector<int>& nums) {
        int maxind = 0; // farthest reachable index so far
        
        for (int i = 0; i < nums.size(); i++) {
            if (i > maxind) return false;          // if current index is unreachable
            maxind = max(maxind, i + nums[i]);     // update farthest reachable index
            if (maxind >= nums.size() - 1) return true; // can already reach or exceed last index
        }
        return true;
    }
};

int main() {
    Solution sol;

    // Example 1
    vector<int> nums1 = {2, 3, 1, 1, 4};
    cout << "Can jump (example 1): "
         << (sol.canJump(nums1) ? "true" : "false") << endl;

    // Example 2
    vector<int> nums2 = {3, 2, 1, 0, 4};
    cout << "Can jump (example 2): "
         << (sol.canJump(nums2) ? "true" : "false") << endl;

    return 0;
}

/*
---------------------------------------------------------
🧠 Intuition:
---------------------------------------------------------
- Each position tells you how far you can jump.
- As you iterate through the array, maintain the
  farthest index (`maxind`) you can currently reach.
- If at any point `i > maxind`, it means you are
  stuck before reaching index i → return false.
- If `maxind` reaches or exceeds the last index,
  return true early.

Example walkthrough:
nums = [2, 3, 1, 1, 4]
i=0 → maxind=2
i=1 → maxind=max(2,1+3)=4 → can reach end → return true
---------------------------------------------------------
⏱️ Time Complexity:
---------------------------------------------------------
- Single pass through the array → **O(n)**

---------------------------------------------------------
💾 Space Complexity:
---------------------------------------------------------
- Only uses a few integer variables → **O(1)**

---------------------------------------------------------
✅ Example Output:
Can jump (example 1): true
Can jump (example 2): false
---------------------------------------------------------
*/
