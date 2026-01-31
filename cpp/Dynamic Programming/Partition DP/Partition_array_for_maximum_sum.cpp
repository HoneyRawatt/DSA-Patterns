#include <bits/stdc++.h>
using namespace std;

/*
----------------------------------------------------
MEMOIZATION (TOP-DOWN DP)
----------------------------------------------------
Intuition:
- dp[ind] = maximum sum obtainable from index ind to end
- Try partitions of length 1 to k starting at ind
- For each partition, take max element * length + solve rest
----------------------------------------------------
Time Complexity: O(n * k)
Space Complexity: O(n) + recursion stack
----------------------------------------------------
*/

int partition_array_for_maximum_sum_memo(int ind,
                                         vector<int>& num,
                                         int k,
                                         int n,
                                         vector<int>& dp) {
    if (ind == n) return 0;

    if (dp[ind] != -1) return dp[ind];

    int len = 0;
    int maxi = INT_MIN;
    int maxans = INT_MIN;

    for (int j = ind; j < min(ind + k, n); j++) {
        len++;
        maxi = max(maxi, num[j]);
        int sum = len * maxi +
                  partition_array_for_maximum_sum_memo(j + 1, num, k, n, dp);
        maxans = max(maxans, sum);
    }

    return dp[ind] = maxans;
}

/*
----------------------------------------------------
TABULATION (BOTTOM-UP DP)
----------------------------------------------------
Intuition:
- Build dp[] from right to left
- dp[i] stores max sum from i to end
----------------------------------------------------
Time Complexity: O(n * k)
Space Complexity: O(n)
----------------------------------------------------
*/

int partition_array_for_maximum_sum_tabu(vector<int>& num, int k) {
    int n = num.size();
    vector<int> dp(n + 1, 0);

    for (int i = n - 1; i >= 0; i--) {
        int len = 0;
        int maxi = INT_MIN;
        int maxans = INT_MIN;

        for (int j = i; j < min(i + k, n); j++) {
            len++;
            maxi = max(maxi, num[j]);
            int sum = len * maxi + dp[j + 1];
            maxans = max(maxans, sum);
        }

        dp[i] = maxans;
    }

    return dp[0];
}

/*
----------------------------------------------------
MAIN FUNCTION
----------------------------------------------------
*/

int main() {
    vector<int> num = {1, 15, 7, 9, 2, 5, 10};
    int k = 3;
    int n = num.size();

    vector<int> dp(n, -1);

    cout << "Memoization Answer: "
         << partition_array_for_maximum_sum_memo(0, num, k, n, dp) << endl;

    cout << "Tabulation Answer: "
         << partition_array_for_maximum_sum_tabu(num, k) << endl;

    return 0;
}
