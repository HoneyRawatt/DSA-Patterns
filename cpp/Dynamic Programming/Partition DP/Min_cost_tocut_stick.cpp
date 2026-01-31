#include <bits/stdc++.h>
using namespace std;

/*
----------------------------------------------------
MEMOIZATION (TOP-DOWN DP)
----------------------------------------------------
Intuition:
- We add 0 and n to cuts array and sort it
- dp[i][j] = minimum cost to cut the stick between cuts[i-1] and cuts[j+1]
- Try making a cut at every possible position `ind` in [i..j]
----------------------------------------------------
*/

int min_cost_to_cut_stick_memo(int i, int j, vector<int>& cuts,
                              vector<vector<int>>& dp) {
    // No cuts left
    if (i > j) return 0;

    if (dp[i][j] != -1) return dp[i][j];

    int mini = 1e9;

    for (int ind = i; ind <= j; ind++) {
        int cost =
            cuts[j + 1] - cuts[i - 1] +      // cost of current cut
            min_cost_to_cut_stick_memo(i, ind - 1, cuts, dp) +
            min_cost_to_cut_stick_memo(ind + 1, j, cuts, dp);

        mini = min(mini, cost);
    }

    return dp[i][j] = mini;
}

/*
----------------------------------------------------
TABULATION (BOTTOM-UP DP)
----------------------------------------------------
Intuition: 
- Build solutions for smaller intervals first
- i goes from bottom to top
----------------------------------------------------
*/

int min_cost_to_cut_stick_tabu(vector<int>& cuts, int c) {
    vector<vector<int>> dp(c + 2, vector<int>(c + 2, 0));

    for (int i = c; i >= 1; i--) {
        for (int j = 1; j <= c; j++) {
            if(i>j) continue;   // also u remove this annd run the loop of j=i -- same thing 
            int mini = 1e9;

            for (int ind = i; ind <= j; ind++) {
                int cost =
                    cuts[j + 1] - cuts[i - 1] +
                    dp[i][ind - 1] +
                    dp[ind + 1][j];

                mini = min(mini, cost);
            }

            dp[i][j] = mini;
        }
    }

    return dp[1][c];
}

/*
----------------------------------------------------
MAIN FUNCTION
----------------------------------------------------
*/

int main() {
    int n = 7;                  // length of stick
    vector<int> cuts = {1, 3, 4, 5};
    int c = cuts.size();

    // Add boundaries
    cuts.push_back(n);
    cuts.insert(cuts.begin(), 0);
    sort(cuts.begin(), cuts.end());

    vector<vector<int>> dp(c + 2, vector<int>(c + 2, -1));

    cout << "Memoization Answer: "
         << min_cost_to_cut_stick_memo(1, c, cuts, dp) << endl;

    cout << "Tabulation Answer: "
         << min_cost_to_cut_stick_tabu(cuts, c) << endl;

    return 0;
}

// ⏱️ Time & Space Complexity
// ✅ Memoization

// Time: O(c³)

// Space: O(c²) + recursion stack

// ✅ Tabulation

// Time: O(c³)

// Space: O(c²)