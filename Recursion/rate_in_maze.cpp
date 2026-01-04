#include <bits/stdc++.h>
using namespace std;

/*
==================================================
INTUITION
==================================================
- Use DFS + Backtracking
- From each cell, try all 4 directions: D, L, R, U
- Mark cell as visited before moving
- Unmark after recursion (backtracking)
- Store path when destination is reached
*/

// Recursive function
void solve(int i, int j, vector<vector<int>>& a, int n,
           vector<string>& ans, string move,
           vector<vector<int>>& vis) {

    // Base case: destination reached
    if (i == n - 1 && j == n - 1) {
        ans.push_back(move);
        return;
    }

    // Mark current cell as visited
    vis[i][j] = 1;

    // Down
    if (i + 1 < n && !vis[i + 1][j] && a[i + 1][j] == 1)
        solve(i + 1, j, a, n, ans, move + 'D', vis);

    // Left
    if (j - 1 >= 0 && !vis[i][j - 1] && a[i][j - 1] == 1)
        solve(i, j - 1, a, n, ans, move + 'L', vis);

    // Right
    if (j + 1 < n && !vis[i][j + 1] && a[i][j + 1] == 1)
        solve(i, j + 1, a, n, ans, move + 'R', vis);

    // Up
    if (i - 1 >= 0 && !vis[i - 1][j] && a[i - 1][j] == 1)
        solve(i - 1, j, a, n, ans, move + 'U', vis);

    // Backtrack
    vis[i][j] = 0;
}

// Driver function
vector<string> findpath(vector<vector<int>>& m, int n) {
    vector<string> ans;
    vector<vector<int>> vis(n, vector<int>(n, 0));

    if (m[0][0] == 1)
        solve(0, 0, m, n, ans, "", vis);

    return ans;
}


// ⏱️ TIME COMPLEXITY
// In the worst case, rat explores all possible paths
// Each cell has 4 choices
// ⏱️ Time:
// O(4^(n*n))   (worst case)

// 💾 SPACE COMPLEXITY
// Component	Space
// Visited matrix	O(n²)
// Recursion stack	O(n²)
// Path storage	Depends on number of paths