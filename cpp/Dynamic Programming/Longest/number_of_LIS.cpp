#include <bits/stdc++.h>
using namespace std;

/*
 Function to compute number of Longest Increasing Subsequences
*/
int number_of_longest_inc_subseq(vector<int>& arr, int n) {
    vector<int> dp(n, 1), cnt(n, 1);
    int maxi = 1;

    for (int ind = 0; ind < n; ind++) {
        for (int prev = 0; prev < ind; prev++) {
            if (arr[ind] > arr[prev] && dp[prev] + 1 > dp[ind]) {
                dp[ind] = dp[prev] + 1;
                cnt[ind] = cnt[prev];
            }
            else if (arr[ind] > arr[prev] && dp[prev] + 1 == dp[ind]) {
                cnt[ind] += cnt[prev];
            }
        }
        maxi = max(maxi, dp[ind]);
    }

    int ans = 0;
    for (int i = 0; i < n; i++) {
        if (dp[i] == maxi) ans += cnt[i];
    }
    return ans;
}

/*
 ---------------- MAIN FUNCTION ----------------

 Intuition:
 ----------
 1. Read input size n.
 2. Read n elements into array.
 3. Call the LIS counting function.
 4. Print the result.

 Time Complexity:
 ----------------
 O(n^2)
 - Dominated by the LIS DP function

 Space Complexity:
 -----------------
 O(n)
 - For dp[] and cnt[] arrays
*/

int main() {
    int n;
    cin >> n;                 // size of array

    vector<int> arr(n);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];        // input elements
    }

    int result = number_of_longest_inc_subseq(arr, n);

    cout << result << endl;   // output number of LIS

    return 0;
}
