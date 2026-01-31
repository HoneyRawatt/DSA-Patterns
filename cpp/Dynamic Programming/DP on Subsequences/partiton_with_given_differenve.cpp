#include <bits/stdc++.h>
using namespace std;

const int MOD = 1e9 + 7;

/*
    TIME COMPLEXITY:  O(n * target)
    SPACE COMPLEXITY: O(target)

    This function counts subsets whose sum equals 'target'
    using space-optimized DP.
*/
    int noofsubset_so(vector<int>& arr, int target)
    {
        int n = arr.size();
        vector<int> prev(target + 1, 0), curr(target + 1, 0);

        // Base: sum = 0
        prev[0] = (arr[0] == 0 ? 2 : 1);

        if (arr[0] != 0 && arr[0] <= target)
            prev[arr[0]] = 1;

        for (int i = 1; i < n; i++)
        {
            curr[0] = (arr[i] == 0 ? (prev[0] * 2) % MOD : prev[0]);

            for (int s = 1; s <= target; s++)
            {
                int notTake = prev[s];
                int take = 0;
                if (arr[i] <= s)
                    take = prev[s - arr[i]];

                curr[s] = (take + notTake) % MOD;
            }
            prev = curr;
        }

        return prev[target];
    }


/*
    countPartitions:
    Count number of ways to split array into 2 subsets with diff = d.

    Using formula:
        S1 - S2 = d
        S1 + S2 = totalSum

    => S1 = (totalSum - d) / 2
*/
int countPartitions(int n, int d, vector<int>& arr)
{
    int totalSum = 0;
    for (int x : arr) totalSum += x;

    // Conditions for valid partition
    if (totalSum - d < 0 || (totalSum - d) % 2 != 0)
        return 0;

    int target = (totalSum - d) / 2;

    return noofsubset_so(arr, target);
}


/* ---------------- MAIN FUNCTION ---------------- */

int main()
{
    int n, d;
    cout << "Enter n and d: ";
    cin >> n >> d;

    vector<int> arr(n);
    cout << "Enter array elements: ";
    for (int i = 0; i < n; i++)
        cin >> arr[i];

    int result = countPartitions(n, d, arr);

    cout << "Number of partitions with difference " << d << " = " << result << endl;

    return 0;
}
