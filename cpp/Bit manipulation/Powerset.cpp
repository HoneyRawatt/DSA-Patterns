#include <iostream>
#include <vector>
using namespace std;

/*
Intuition:
- Any array of size n has exactly 2^n subsets.
- We use bit masking to generate all subsets.
- Each number from 0 to (2^n - 1) represents a subset.
- If the i-th bit of the number is set, we include arr[i] in the subset.

Example:
arr = {1, 2, 3}
mask = 5 -> binary 101
=> include arr[0] and arr[2] -> {1, 3}
*/

vector<vector<int>> subsets(vector<int> arr) {
    int n = arr.size();
    vector<vector<int>> ans;

    // Loop through all possible masks from 0 to (2^n - 1)
    for (int mask = 0; mask < (1 << n); mask++) {
        vector<int> lis;

        // Check each bit position
        for (int i = 0; i < n; i++) {
            // If i-th bit is set, include arr[i]
            if (mask & (1 << i)) {
                lis.push_back(arr[i]);
            }
        }
        ans.push_back(lis);
    }
    return ans;
}

/*
Time Complexity:
- Outer loop runs 2^n times (all subsets)
- Inner loop runs n times (checking each bit)
- Total Time Complexity: O(n * 2^n)

Space Complexity:
- Output space: O(n * 2^n) to store all subsets
- Auxiliary space (excluding output): O(n) for temporary list
*/
