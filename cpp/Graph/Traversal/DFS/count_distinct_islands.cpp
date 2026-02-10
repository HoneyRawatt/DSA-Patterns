#include <bits/stdc++.h>
using namespace std;

/*
=====================================================
Problem Statement:
=====================================================
You are given a binary grid of size N × M where:
- 1 represents land
- 0 represents water

An island is formed by connecting adjacent land cells
(connected 4-directionally).

Two islands are considered DISTINCT if their shapes are different.
Translation is allowed (i.e., shifting an island does not change its shape),
but rotation and reflection are NOT allowed.

Your task is to count the number of distinct island shapes.
*/

/*
=====================================================
Intuition:
=====================================================
- To compare island shapes independent of their positions,
  we store each island using RELATIVE coordinates.
- For every island, we pick its first cell as a reference (row0, col0).
- All other cells in that island are stored as (row - row0, col - col0).
- This normalizes the shape, making comparison easy.

Key idea:
➡ Same-shaped islands will produce identical relative-coordinate vectors.
➡ Different shapes will produce different vectors.
*/

/*
=====================================================
DFS Function:
=====================================================
Purpose:
- Traverse a complete island using DFS.
- Store the island's shape using relative coordinates.

How shape is stored:
- Instead of absolute positions, we store (row - row0, col - col0)
- This makes the shape independent of its position in the grid.

Time Complexity (per DFS call):
- O(size_of_island)

Space Complexity (per DFS call):
- O(size_of_island) for recursion stack
*/
void dfs(int row, int col,
         vector<vector<int>>& grid,
         vector<vector<int>>& vis,
         vector<pair<int, int>>& vec,
         int row0, int col0) {

    // Mark current cell as visited
    vis[row][col] = 1;

    // Store relative position to capture island shape
    vec.push_back({row - row0, col - col0});

    // Direction vectors: Up, Right, Down, Left
    int delrow[] = {-1, 0, 1, 0};
    int delcol[] = {0, 1, 0, -1};

    int n = grid.size();
    int m = grid[0].size();

    // Explore all 4 adjacent directions
    for (int i = 0; i < 4; i++) {
        int nrow = row + delrow[i];
        int ncol = col + delcol[i];

        // Check valid, unvisited land cell
        if (nrow >= 0 && nrow < n &&
            ncol >= 0 && ncol < m &&
            !vis[nrow][ncol] &&
            grid[nrow][ncol] == 1) {

            dfs(nrow, ncol, grid, vis, vec, row0, col0);
        }
    }
}

/*
=====================================================
Function: countDistinctIslands
=====================================================
Purpose:
- Traverse the grid and find all islands.
- Store each island's shape using relative coordinates.
- Use a set to keep only unique island shapes.

Approach:
1️⃣ Traverse the entire grid.
2️⃣ For each unvisited land cell, start DFS.
3️⃣ Capture the island shape in a vector.
4️⃣ Insert the vector into a set to ensure uniqueness.
5️⃣ Return the size of the set.
*/
int countDistinctIslands(vector<vector<int>>& grid) {
    int n = grid.size();
    int m = grid[0].size();

    // Set to store unique island shapes
    set<vector<pair<int, int>>> st;

    // Visited array
    vector<vector<int>> vis(n, vector<int>(m, 0));

    // Traverse all cells
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {

            // Start DFS for unvisited land cell
            if (!vis[i][j] && grid[i][j] == 1) {
                vector<pair<int, int>> vec;
                dfs(i, j, grid, vis, vec, i, j);
                st.insert(vec); // store unique shape
            }
        }
    }

    return st.size();
}

/*
=====================================================
Overall Time & Space Complexity:
=====================================================

⏱ Time Complexity:
- Grid traversal: O(N × M)
- DFS visits each cell once
- Set insertion for each island shape

➡ Overall: O(N × M)

📦 Space Complexity:
- Visited matrix: O(N × M)
- DFS recursion stack: O(N × M) (worst case)
- Set storing island shapes

➡ Overall: O(N × M)
*/

int main() {
    vector<vector<int>> grid = {
        {1, 1, 0, 0, 0},
        {1, 0, 0, 0, 0},
        {0, 0, 0, 1, 1},
        {0, 0, 0, 1, 0}
    };

    cout << "Number of distinct islands: "
         << countDistinctIslands(grid) << endl;

    return 0;
}
