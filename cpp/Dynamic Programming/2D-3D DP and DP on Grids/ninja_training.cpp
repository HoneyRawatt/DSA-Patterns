#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

/*
    -----------------------------------------------------------
    NINJA TRAINING PROBLEM
    Each day ninja must choose 1 of 3 tasks: 0, 1, 2
    Cannot choose the same task on consecutive days.
    -----------------------------------------------------------
*/


/* -----------------------------------------------------------
     1️⃣ MEMOIZATION  (Top-Down DP)
     dp[day][last] = max points till 'day' when last task is 'last'
     TIME: O(N * 4 * 3)
     SPACE: O(N * 4) + recursion stack O(N)
----------------------------------------------------------- */
int ninja_training_memo(int day, int last, vector<vector<int>>& points,
                        vector<vector<int>>& dp)
{
    if (day == 0) {
        int maxi = 0;
        for (int task = 0; task < 3; task++) {
            if (task != last)
                maxi = max(maxi, points[0][task]);
        }
        return dp[0][last] = maxi;
    }

    if (dp[day][last] != -1) return dp[day][last];

    int maxi = 0;
    for (int task = 0; task < 3; task++) {
        if (task != last) {
            int point = points[day][task] +
                        ninja_training_memo(day - 1, task, points, dp);
            maxi = max(maxi, point);
        }
    }
    return dp[day][last] = maxi;
}


/* -----------------------------------------------------------
     2️⃣ TABULATION (Bottom-Up DP)
     dp[day][last]
     TIME: O(N * 4 * 3)
     SPACE: O(N * 4)
----------------------------------------------------------- */
int ninja_training_tabulation(int n, vector<vector<int>>& points)
{
    vector<vector<int>> dp(n, vector<int>(4, 0));

    // Base case for day 0
    dp[0][0] = max(points[0][1], points[0][2]);              // last=0 → cannot pick task 0
    dp[0][1] = max(points[0][0], points[0][2]);              // last=1
    dp[0][2] = max(points[0][0], points[0][1]);              // last=2
    dp[0][3] = max({points[0][0], points[0][1], points[0][2]}); // last=3 → can pick any

    for (int day = 1; day < n; day++) {
        for (int last = 0; last < 4; last++) {
            dp[day][last] = 0;
            for (int task = 0; task < 3; task++) {
                if (task != last)
                    dp[day][last] = max(dp[day][last],
                        points[day][task] + dp[day - 1][task]);
            }
        }
    }
    return dp[n - 1][3];   // last = 3 → no restriction
}


/* -----------------------------------------------------------
     3️⃣ SPACE OPTIMIZED DP
     TIME: O(N * 4 * 3)
     SPACE: O(4)
----------------------------------------------------------- */
int ninja_training_opti(int n, vector<vector<int>>& points)
{
    vector<int> prev(4, 0);

    // Base case for day 0
    prev[0] = max(points[0][1], points[0][2]);
    prev[1] = max(points[0][0], points[0][2]);
    prev[2] = max(points[0][0], points[0][1]);
    prev[3] = max({points[0][0], points[0][1], points[0][2]});

    for (int day = 1; day < n; day++) {
        vector<int> temp(4, 0);

        for (int last = 0; last < 4; last++) {
            temp[last] = 0;
            for (int task = 0; task < 3; task++) {
                if (task != last) {
                    temp[last] = max(temp[last],
                        points[day][task] + prev[task]);
                }
            }
        }
        prev = temp;
    }
    return prev[3];
}


/* -----------------------------------------------------------
     MAIN FUNCTION (Test)
----------------------------------------------------------- */
int main()
{
    vector<vector<int>> points =
    {
        {10, 40, 70},
        {20, 50, 80},
        {30, 60, 90}
    };

    int n = points.size();

    vector<vector<int>> dp(n, vector<int>(4, -1));

    cout << "Memoization: "
         << ninja_training_memo(n - 1, 3, points, dp) << endl;

    cout << "Tabulation: "
         << ninja_training_tabulation(n, points) << endl;

    cout << "Optimized: "
         << ninja_training_opti(n, points) << endl;

    return 0;
}
