#include <bits/stdc++.h>
using namespace std;

/*
Intuition:
- A Bitonic Subsequence first increases, then decreases.
- For every index i:
    dp1[i] = Longest Increasing Subsequence ending at i
    dp2[i] = Longest Decreasing Subsequence starting from i
- Answer = max(dp1[i] + dp2[i] - 1)

Why -1?
Because arr[i] is counted twice in dp1 and dp2.
*/

int longest_Bitonic_Subsequence(vector<int>& arr, int n) {
    vector<int> dp1(n, 1), dp2(n, 1);
    int maxi=0;

    // LIS from left to right
    for (int ind = 0; ind < n; ind++) {
        for (int prev = 0; prev < ind; prev++) {
            if (arr[ind] > arr[prev]) {
                dp1[ind] = max(dp1[ind], 1 + dp1[prev]);
            }
        }
    }
    // LDS from right to left
    for (int ind = n - 1; ind >= 0; ind--) {
        for (int prev = n - 1; prev > ind; prev--) {
            if (arr[ind] > arr[prev]) {
                dp2[ind] = max(dp2[ind], 1 + dp2[prev]);
            }
        }
    }
     for (int i = 0; i < n; i++) {
            if (dp1[i] > 1 && dp2[i] > 1) {
                maxi = max(maxi, dp1[i] + dp2[i] - 1);
            }
    }
    return maxi;
}

int main() {
    vector<int> arr = {1, 11, 2, 10, 4, 5, 2, 1};
    int n = arr.size();

    cout << "Longest Bitonic Subsequence Length: "
         << longest_Bitonic_Subsequence(arr, n) << endl;

    return 0;
}

/*
Time Complexity:
- O(n^2)  (two nested loops for LIS and LDS)

Space Complexity:
- O(n) for dp1 and dp2
*/
