#include <iostream>
#include <vector>
using namespace std;

/*
----------------------------------------------------------
🔹 1. Fibonacci using MEMOIZATION (Top-Down DP)
----------------------------------------------------------
Intuition:
We recursively compute fib(n) but store results (memoize)
so that we don’t recompute the same subproblems.

Time Complexity: O(n)
  → Each number from 0 to n is computed once.
Space Complexity: O(n) 
  → Recursion stack + dp array.
*/

int fibonacci_memoization(int n, vector<int> &dp) {
    if (n <= 1) return n;
    
    if (dp[n] != -1) return dp[n]; // If already computed
    
    // Store and return the result
    return dp[n] = fibonacci_memoization(n - 1, dp) + fibonacci_memoization(n - 2, dp);
}

/*
----------------------------------------------------------
🔹 2. Fibonacci using TABULATION (Bottom-Up DP)
----------------------------------------------------------
Intuition:
Instead of recursion, build up the dp table iteratively
from base cases to n.

Time Complexity: O(n)
Space Complexity: O(n)
*/

int fibonacci_tabulation(int n) {
    vector<int> dp(n + 1, -1);
    dp[0] = 0;
    dp[1] = 1;

    for (int i = 2; i <= n; i++) {
        dp[i] = dp[i - 1] + dp[i - 2];
    }

    return dp[n];
}

/*
----------------------------------------------------------
🔹 3. Fibonacci using SPACE OPTIMIZATION
----------------------------------------------------------
Intuition:
We only need the last two Fibonacci values to compute the next one.
So, instead of storing all values, we just keep track of two.

Time Complexity: O(n)
Space Complexity: O(1)
*/

int fibonacci_tabulation_optimization(int n) {
    if (n <= 1) return n;

    int prev2 = 0;
    int prev = 1;

    for (int i = 2; i <= n; i++) {
        int curr = prev + prev2;
        prev2 = prev;
        prev = curr;
    }

    return prev;
}

/*
----------------------------------------------------------
🔹 MAIN FUNCTION
----------------------------------------------------------
We demonstrate all three methods for a given n.
*/

int main() {
    int n;
    cout << "Enter n: ";
    cin >> n;

    // MEMOIZATION
    vector<int> dp(n + 1, -1);
    cout << "\nFibonacci using Memoization: " << fibonacci_memoization(n, dp);

    // TABULATION
    cout << "\nFibonacci using Tabulation: " << fibonacci_tabulation(n);

    // SPACE OPTIMIZATION
    cout << "\nFibonacci using Space Optimization: " << fibonacci_tabulation_optimization(n) << endl;

    return 0;
}
