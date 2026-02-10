#include <bits/stdc++.h>
using namespace std;

/*
====================================================
PROBLEM STATEMENT:
====================================================
Given a 2D grid of characters where:
- '1' represents land
- '0' represents water

An island is formed by connecting adjacent lands.
Connections are allowed in ALL 8 directions:
- Horizontal
- Vertical
- Diagonal

Your task is to count the total number of islands.

This is a classic GRAPH + BFS/DFS problem.
====================================================
*/

/*
----------------------------------------------------
BFS Function
----------------------------------------------------
Purpose:
- Performs Breadth First Search (BFS) to traverse
  an entire island starting from a given cell.

Parameters:
- row, col : starting cell of the island
- vis      : visited matrix to track visited cells
- grid     : input grid containing land ('1') and water ('0')

Logic:
- Mark the starting cell as visited
- Push it into the queue
- Explore all 8 neighboring cells
- Visit and enqueue unvisited land cells
----------------------------------------------------
*/
void bfs(int row, int col, vector<vector<int>>& vis, vector<vector<char>>& grid) {
    vis[row][col] = 1;            // mark starting cell as visited
    queue<pair<int, int>> q;
    q.push({row, col});           // push starting cell into queue

    int n = grid.size();          // number of rows
    int m = grid[0].size();       // number of columns

    while (!q.empty()) {
        int r = q.front().first;
        int c = q.front().second;
        q.pop();

        // Traverse all 8 possible directions
        for (int delrow = -1; delrow <= 1; delrow++) {
            for (int delcol = -1; delcol <= 1; delcol++) {
                int nrow = r + delrow;
                int ncol = c + delcol;

                // Check boundaries and unvisited land
                if (nrow >= 0 && nrow < n &&
                    ncol >= 0 && ncol < m &&
                    grid[nrow][ncol] == '1' &&
                    !vis[nrow][ncol]) {

                    vis[nrow][ncol] = 1;     // mark visited
                    q.push({nrow, ncol});    // add to queue
                }
            }
        }
    }
}

/*
----------------------------------------------------
numsislands Function
----------------------------------------------------
Purpose:
- Counts the number of islands in the grid.

Approach:
- Traverse each cell of the grid
- If an unvisited land cell ('1') is found:
    - It represents a new island
    - Perform BFS to mark all connected land cells
    - Increment island count

Returns:
- Total number of islands
----------------------------------------------------
*/
int numsislands(vector<vector<char>>& grid) {
    int n = grid.size();
    int m = grid[0].size();

    int cnt = 0;  // number of islands
    vector<vector<int>> vis(n, vector<int>(m, 0)); // visited matrix

    for (int row = 0; row < n; row++) {
        for (int col = 0; col < m; col++) {
            // If land is found and not visited, it's a new island
            if (!vis[row][col] && grid[row][col] == '1') {
                cnt++;                 // new island found
                bfs(row, col, vis, grid);
            }
        }
    }

    return cnt;
}

/*
----------------------------------------------------
Main Function
----------------------------------------------------
*/
int main() {
    vector<vector<char>> grid = {
        {'1','1','0','0'},
        {'1','1','0','0'},
        {'0','0','1','0'},
        {'0','0','0','1'}
    };

    cout << "Number of islands: " << numsislands(grid) << endl;
}

/*
====================================================
INTUITION:
====================================================
- Each island is a connected component of '1's.
- BFS helps traverse all connected land cells
  starting from one land cell.
- Every time BFS starts from an unvisited land cell,
  we discover a new island.

====================================================
TIME COMPLEXITY:
====================================================
Let n = number of rows, m = number of columns

- Each cell is visited at most once.
- BFS processes each cell once.

Time Complexity: O(n * m)

====================================================
SPACE COMPLEXITY:
====================================================
- Visited matrix: O(n * m)
- Queue in BFS (worst case): O(n * m)

Total Space Complexity: O(n * m)
====================================================
*/
