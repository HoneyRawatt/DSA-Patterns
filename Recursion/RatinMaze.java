package Recursion;
import java.util.*;

class RatinMaze{

    /*
    ==================================================
    INTUITION
    ==================================================
    - The rat starts from (0,0) and wants to reach (n-1,n-1).
    - It can move in 4 directions: Down(D), Left(L), Right(R), Up(U).
    - The rat can only move to cells having value 1.
    - We use DFS + Backtracking:
        1. Mark current cell as visited.
        2. Explore all 4 possible directions.
        3. Backtrack (unmark visited) after recursion.
    - When destination is reached, store the path.
    */

    // DFS Backtracking function
    static void solve(int i, int j, int[][] maze, int n,
                      boolean[][] vis, String path,
                      ArrayList<String> ans) {

        // Base case: destination reached
        if (i == n - 1 && j == n - 1) {
            ans.add(path);
            return;
        }

        // Mark current cell visited
        vis[i][j] = true;

        // Down
        if (i + 1 < n && !vis[i + 1][j] && maze[i + 1][j] == 1) {
            solve(i + 1, j, maze, n, vis, path + "D", ans);
        }

        // Left
        if (j - 1 >= 0 && !vis[i][j - 1] && maze[i][j - 1] == 1) {
            solve(i, j - 1, maze, n, vis, path + "L", ans);
        }

        // Right
        if (j + 1 < n && !vis[i][j + 1] && maze[i][j + 1] == 1) {
            solve(i, j + 1, maze, n, vis, path + "R", ans);
        }

        // Up
        if (i - 1 >= 0 && !vis[i - 1][j] && maze[i - 1][j] == 1) {
            solve(i - 1, j, maze, n, vis, path + "U", ans);
        }

        // Backtrack
        vis[i][j] = false;
    }

    // Driver function (called by GFG)
    public static ArrayList<String> findPath(int[][] maze, int n) {

        ArrayList<String> ans = new ArrayList<>();
        boolean[][] vis = new boolean[n][n];

        // If starting cell is blocked, no path exists
        if (maze[0][0] == 0) return ans;

        solve(0, 0, maze, n, vis, "", ans);
        Collections.sort(ans); // GFG expects lexicographical order
        return ans;
    }
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