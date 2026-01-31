#include <bits/stdc++.h>
using namespace std;

/*
    Function: dfs
    Purpose: Explore an island and store its shape (relative coordinates)
    Time Complexity (per DFS call): O(size_of_island)
    Space Complexity: O(size_of_island) for recursion stack
*/
void dfs(int row, int col, vector<vector<int>>& grid, vector<vector<int>>& vis,
         vector<pair<int, int>>& vec, int row0, int col0) {
    vis[row][col] = 1;
    vec.push_back({row - row0, col - col0}); // store relative position (shape)

    int delrow[] = {-1, 0, 1, 0};
    int delcol[] = {0, 1, 0, -1};
    int n = grid.size();
    int m = grid[0].size();

    for (int i = 0; i < 4; i++) {
        int nrow = row + delrow[i];
        int ncol = col + delcol[i];

        // explore valid, unvisited land cells
        if (nrow >= 0 && nrow < n && ncol >= 0 && ncol < m &&
            !vis[nrow][ncol] && grid[nrow][ncol] == 1) {
            dfs(nrow, ncol, grid, vis, vec, row0, col0);
        }
    }
}

/*
    Function: countDistinctIslands
    Purpose: Count unique island shapes using relative coordinates
    Time Complexity:
        - Outer loops: O(N*M)
        - Each cell is visited once in DFS: O(N*M)
        - Insertion into set: O(K * log(K)) where K = number of unique shapes
      => Overall: O(N*M * log(K)) ≈ O(N*M)
    Space Complexity:
        - vis matrix: O(N*M)
        - recursion stack: O(N*M) in worst case
        - set of shapes: O(K * L) (K = unique islands, L = average island size)
      => Overall: O(N*M)
*/
int countDistinctIslands(vector<vector<int>>& grid) {
    int n = grid.size();
    int m = grid[0].size();

    set<vector<pair<int, int>>> st; // stores unique island shapes
    vector<vector<int>> vis(n, vector<int>(m, 0));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            // perform DFS for each unvisited land cell
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
    Overall Time Complexity: O(N*M)
    Overall Space Complexity: O(N*M)
*/

int main() {
    vector<vector<int>> grid = {
        {1, 1, 0, 0, 0},
        {1, 0, 0, 0, 0},
        {0, 0, 0, 1, 1},
        {0, 0, 0, 1, 0}
    };

    cout << "Number of distinct islands: " << countDistinctIslands(grid) << endl;
    return 0;
}
