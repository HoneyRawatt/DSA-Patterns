#include <bits/stdc++.h>
using namespace std;

/*------------------------------------------------------
    Largest Divisible Subset (Optimal DP)

    Intuition:
    - This problem is a variation of LIS.
    - After sorting the array:
        If arr[i] is divisible by arr[j] (j < i),
        then arr[i] can extend the divisible subset ending at j.

    State:
    dp[i]   → size of largest divisible subset ending at index i
    hash[i] → previous index used to reconstruct the subset

    Approach:
    1. Sort the array
    2. Use LIS-style DP
    3. Reconstruct the subset using hash array
------------------------------------------------------*/

vector<int> largest_div_subset_optimal(vector<int>& arr, int n) {
    sort(arr.begin(), arr.end());  // REQUIRED step

    vector<int> dp(n, 1), hash(n);
    int maxi = 1;
    int lastindx = 0;

    for (int ind = 0; ind < n; ind++) {
        hash[ind] = ind;

        for (int prev = 0; prev < ind; prev++) {
            if (arr[ind] % arr[prev] == 0 && dp[prev] + 1 > dp[ind]) {
                dp[ind] = dp[prev] + 1;
                hash[ind] = prev;
            }
        }

        if (dp[ind] > maxi) {
            maxi = dp[ind];
            lastindx = ind;
        }
    }

    /*------------------------------------------------------
        Reconstruct Largest Divisible Subset
    ------------------------------------------------------*/

    vector<int> lds;
    while (hash[lastindx] != lastindx) {
        lds.push_back(arr[lastindx]);
        lastindx = hash[lastindx];
    }
    lds.push_back(arr[lastindx]);

    reverse(lds.begin(), lds.end());
    return lds;
}

/*------------------------------------------------------
    MAIN FUNCTION
------------------------------------------------------*/

int main() {
    vector<int> arr = {1, 2, 4, 8, 9, 72};
    int n = arr.size();

    vector<int> result = largest_div_subset_optimal(arr, n);

    cout << "Largest Divisible Subset: ";
    for (int x : result) {
        cout << x << " ";
    }
    cout << endl;

    return 0;
}
