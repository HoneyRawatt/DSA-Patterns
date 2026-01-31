#include<bits/stdc++.h>
using namespace std;
vector<int> longest_inc_subseq_optimal(vector<int>& arr, int n) {
    /*------------------------------------------------------
        Intuition:
        dp[i]   → length of LIS ending at index i
        hash[i] → previous index of LIS ending at i
                  (used to reconstruct the sequence)

        At each index i:
        - Try extending LIS from all previous indices j < i
        - If arr[i] > arr[j] and gives longer LIS → update
    ------------------------------------------------------*/

    vector<int> dp(n, 1), hash(n);
    int maxi = 1;
    int lastindx = 0;

    for (int ind = 0; ind < n; ind++) {
        hash[ind] = ind;   // initially points to itself

        for (int prev = 0; prev < ind; prev++) {
            if (arr[ind] > arr[prev] && 1 + dp[prev] > dp[ind]) {
                dp[ind] = 1 + dp[prev];
                hash[ind] = prev;
            }
        }

        if (dp[ind] > maxi) {
            maxi = dp[ind];
            lastindx = ind;
        }
    }

    /*------------------------------------------------------
        Reconstruct LIS using hash array
    ------------------------------------------------------*/

    vector<int> lis;
    while (hash[lastindx] != lastindx) {
        lis.push_back(arr[lastindx]);
        lastindx = hash[lastindx];
    }
    lis.push_back(arr[lastindx]);

    reverse(lis.begin(), lis.end());
    return lis;
}
