#include <bits/stdc++.h>
using namespace std;

/*
====================================================
PROBLEM STATEMENT (Flood Fill):
====================================================
You are given a 2D image where each cell represents a
pixel value.

Given:
- image   : 2D grid of integers
- sr, sc  : starting row and column
- newColor: color to fill

You need to repaint the starting pixel and all
connected pixels (4-directionally) having the same
initial color with the new color.

This is a classic GRAPH / DFS problem.
====================================================
*/

/*
----------------------------------------------------
DFS Function
----------------------------------------------------
Purpose:
- Performs Depth First Search (DFS) to recolor
  all connected pixels having the same initial color.

Parameters:
- row, col  : current pixel position
- ans       : resulting image (acts as visited + output)
- image     : original image
- newColor  : color to be applied
- delrow    : row direction array (up, right, down, left)
- delcol    : column direction array
- inicolor  : original color at (sr, sc)

Logic:
- Change current pixel color to newColor
- Explore its 4-directionally connected neighbors
- Recursively recolor valid neighbors
----------------------------------------------------
*/
void dfs(int row, int col, vector<vector<int>>& ans,
         vector<vector<int>>& image, int newColor,
         int delrow[], int delcol[], int inicolor) {

    // Recolor current pixel
    ans[row][col] = newColor;

    int n = image.size();
    int m = image[0].size();

    // Traverse all 4 possible directions
    for (int i = 0; i < 4; i++) {
        int nrow = row + delrow[i];
        int ncol = col + delcol[i];

        // Check bounds and whether the pixel has same initial color
        // and is not already recolored
        if (nrow >= 0 && nrow < n &&
            ncol >= 0 && ncol < m &&
            image[nrow][ncol] == inicolor &&
            ans[nrow][ncol] != newColor) {

            dfs(nrow, ncol, ans, image, newColor, delrow, delcol, inicolor);
        }
    }
}

/*
----------------------------------------------------
floodFill Function
----------------------------------------------------
Purpose:
- Initializes DFS and returns the final recolored image.

Steps:
1. Store the initial color of starting pixel.
2. Copy original image into ans (result image).
3. Define direction arrays for 4-direction movement.
4. Call DFS from the starting pixel.
----------------------------------------------------
*/
vector<vector<int>> floodFill(vector<vector<int>>& image, int sr, int sc, int newColor) {

    int inicolor = image[sr][sc];        // original color
    vector<vector<int>> ans = image;     // result image

    // Direction arrays: up, right, down, left
    int delrow[] = {-1, 0, 1, 0};
    int delcol[] = {0, 1, 0, -1};

    // Start DFS from (sr, sc)
    dfs(sr, sc, ans, image, newColor, delrow, delcol, inicolor);

    return ans;
}

/*
----------------------------------------------------
Main Function
----------------------------------------------------
*/
int main() {
    vector<vector<int>> image = {
        {1, 1, 1},
        {1, 1, 0},
        {1, 0, 1}
    };

    int sr = 1, sc = 1, newColor = 2;

    vector<vector<int>> result = floodFill(image, sr, sc, newColor);

    // Print the updated image
    for (auto row : result) {
        for (auto val : row) cout << val << " ";
        cout << endl;
    }
}

/*
====================================================
INTUITION:
====================================================
- All pixels connected to the starting pixel (sr, sc)
  having the same color should be repainted.
- DFS helps explore all such connected pixels deeply.
- Using ans as both visited and result avoids extra space.

====================================================
TIME COMPLEXITY:
====================================================
Let N = number of rows, M = number of columns

- Each pixel is visited at most once.

Time Complexity: O(N * M)

====================================================
SPACE COMPLEXITY:
====================================================
- Recursion stack in worst case: O(N * M)
- Result image (ans): O(N * M)

Overall Space Complexity: O(N * M)
====================================================
*/
