#include <bits/stdc++.h>
using namespace std;

/*
    ------------------- INTUITION -------------------
    We want to divide the array into 2 subsets S1 and S2 such that:
            |sum(S1) - sum(S2)| is minimum.

    Let total = sum(arr)
    Let S1 be any subset-sum possible.
    Then S2 = total - S1

    Difference = |(total - S1) - S1|
                = |total - 2*S1|

    To minimize difference, we only need to check S1 from 0 to total/2.
    This becomes a classic subset-sum DP (0/1 knapsack style DP).

    DP state meaning:
        prev[t] = true  -> sum t is possible using some elements.

    -------------------------------------------------
    TIME COMPLEXITY:
        O(N * TotalSum)
    SPACE COMPLEXITY:
        O(TotalSum)     (using 1D DP)
    -------------------------------------------------
*/

int miSubsetSumDifference(vector<int> &arr, int n)
{
    int totalsum = 0;
    for (int i = 0; i < n; i++)
        totalsum += arr[i];

    int k = totalsum;

    // prev[t] = can we make sum t ?
    vector<bool> prev(k + 1, false);
    prev[0] = true;

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

    int mini = 1e9;

    // Only check till total/2
    for (int s1 = 0; s1 <= totalsum / 2; s1++)
    {
        if (prev[s1])
        {
            int diff = abs((totalsum - s1) - s1);
            mini = min(mini, diff);
        }
    }
    return mini;
}

int main()
{
    /*
        Example:
        arr = [1, 2, 3]
        Total = 6
        Possible S1 values: 0,1,2,3,4,5,6

        Best split:
            S1 = 3, S2 = 3 → difference = 0
    */

    vector<int> arr = {1, 2, 3, 9};
    int n = arr.size();

    int ans = miSubsetSumDifference(arr, n);

    cout << "Minimum Subset Sum Difference = " << ans << endl;

    return 0;
}
