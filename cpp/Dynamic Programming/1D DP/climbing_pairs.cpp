#include <iostream>
#include <vector>
using namespace std;

/*
----------------------------------------------------------
🔹 1. Climbing Stairs using MEMOIZATION (Top-Down DP)
----------------------------------------------------------
Intuition:
The number of ways to reach step n = ways(n-1) + ways(n-2)
We store results (memoize) to avoid recomputation.
*/

int climbStairs_memoization(int n, vector<int> &dp) {
    if (n <= 2) return n;  // Base case
    if (dp[n] != -1) return dp[n]; // Already computed

    return dp[n] = climbStairs_memoization(n - 1, dp) + climbStairs_memoization(n - 2, dp);
}

/*
----------------------------------------------------------
🔹 2. Climbing Stairs using TABULATION (Bottom-Up DP)
----------------------------------------------------------
Intuition:
Build the dp table iteratively from step 1 to step n.
Each step i = dp[i-1] + dp[i-2]
*/

int climbStairs_tabulation(int n) {
    if (n <= 2) return n;

    vector<int> dp(n + 1, -1);
    dp[1] = 1;
    dp[2] = 2;

    for (int i = 3; i <= n; i++) {
        dp[i] = dp[i - 1] + dp[i - 2];
    }

    return dp[n];
}

/*
----------------------------------------------------------
🔹 3. Climbing Stairs using SPACE OPTIMIZATION
----------------------------------------------------------
Intuition:
We only need the last two computed values.
Instead of an array, just use two variables.
*/

int climbStairs_optimized(int n) {
    if (n <= 2) return n;

    int prev2 = 1;  // ways to reach (i-2)
    int prev = 2;   // ways to reach (i-1)

    for (int i = 3; i <= n; i++) {
        int curr = prev + prev2; // sum of previous two
        prev2 = prev;
        prev = curr;
    }

    return prev; // holds ways to reach step n
}

/*
----------------------------------------------------------
🔹 MAIN FUNCTION
----------------------------------------------------------
Demonstrates all three methods.
*/

int main() {
    int n;
    cout << "Enter number of stairs (n): ";
    cin >> n;

    vector<int> dp(n + 1, -1);

    cout << "\nClimbing Stairs using Memoization: " << climbStairs_memoization(n, dp);
    cout << "\nClimbing Stairs using Tabulation: " << climbStairs_tabulation(n);
    cout << "\nClimbing Stairs using Space Optimization: " << climbStairs_optimized(n) << endl;

    return 0;
}
