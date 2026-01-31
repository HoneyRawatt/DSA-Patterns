package Recursion;

class MColoring {

    /*
    ============================
    INTUITION
    ============================
    - We try to color each node one by one.
    - For every node, we try all possible colors from 1 to m.
    - Before assigning a color, we check if any adjacent node
      already has the same color.
    - If a color causes a conflict, we backtrack and try another color.
    - If all nodes are successfully colored, return true.
    */

    // Check if it is safe to color 'node' with color 'col'
    static boolean isSafe(int node, int[] color, boolean[][] graph, int n, int col) {

        // Check all adjacent nodes
        for (int k = 0; k < n; k++) {

            // If there is an edge and adjacent node has same color
            if (k != node && graph[k][node] && color[k] == col) {
                return false;
            }
        }
        return true; // Safe to color
    }

    // Backtracking function to color nodes
    static boolean solve(int node, int[] color, int m, int n, boolean[][] graph) {

        // Base case: all nodes are colored
        if (node == n) return true;

        // Try all colors from 1 to m
        for (int c = 1; c <= m; c++) {

            // Check if current color can be assigned
            if (isSafe(node, color, graph, n, c)) {

                // Assign color
                color[node] = c;

                // Recur for next node
                if (solve(node + 1, color, m, n, graph))
                    return true;

                // Backtrack (remove color)
                color[node] = 0;
            }
        }

        // No valid color found for this node
        return false;
    }

    // Driver function
    public static boolean graphColoring(boolean[][] graph, int m, int n) {

        // color[i] = color assigned to node i (0 means uncolored)
        int[] color = new int[n];

        // Start coloring from node 0
        return solve(0, color, m, n, graph);
    }
}

/*
============================
TIME & SPACE COMPLEXITY
============================

Time Complexity:
- In the worst case, for each node we try all m colors.
- Total possibilities = m^n
- Hence: O(m^n)

Space Complexity:
- Color array: O(n)
- Recursion stack: O(n)
- Total Space: O(n)
*/
