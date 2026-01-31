#include <bits/stdc++.h>
using namespace std;

/*
====================================================================
🧠 Approach: Dijkstra's Algorithm on a Grid
====================================================================
We want to find a path from (0,0) to (n-1,m-1) that minimizes the
maximum absolute difference in heights between consecutive cells.

We treat each cell as a graph node, and the "cost" of an edge is
the absolute height difference between adjacent cells.

At each step, we pick the cell with the minimum current "effort"
and relax its neighbors (like Dijkstra).

====================================================================
📊 Time Complexity:
--------------------------------------------------------------------
For each of N*M cells, we may push/pop from a priority queue (log(N*M)).
✅ O(N * M * log(N*M))

💾 Space Complexity:
--------------------------------------------------------------------
- dist matrix: O(N*M)
- priority queue: O(N*M)
✅ Total: O(N*M)
====================================================================
*/

int minimumEffort(vector<vector<int>>& heights) {
    int n = heights.size();
    int m = heights[0].size();

    // Min-heap: {effort, {row, col}}
    priority_queue<pair<int, pair<int, int>>,
                   vector<pair<int, pair<int, int>>>,
                   greater<pair<int, pair<int, int>>>> pq;

    // Distance (minimum effort to reach each cell)
    vector<vector<int>> dist(n, vector<int>(m, 1e9));
    dist[0][0] = 0;

    // 4 directions: up, right, down, left
    int dr[] = {-1, 0, 1, 0};
    int dc[] = {0, 1, 0, -1};

    pq.push({0, {0, 0}}); // starting from top-left

    while (!pq.empty()) {
        auto it = pq.top();
        pq.pop();

        int diff = it.first;
        int row = it.second.first;
        int col = it.second.second;

        // If we reached the destination, return the effort
        if (row == n - 1 && col == m - 1)
            return diff;

        // Explore 4 neighboring cells
        for (int i = 0; i < 4; i++) {
            int newr = row + dr[i];
            int newc = col + dc[i];

            // Boundary check
            if (newr >= 0 && newr < n && newc >= 0 && newc < m) {
                // Compute new effort as the max of current effort and height difference
                int newEffort = max(abs(heights[row][col] - heights[newr][newc]), diff);

                // Relaxation step
                if (newEffort < dist[newr][newc]) {
                    dist[newr][newc] = newEffort;
                    pq.push({newEffort, {newr, newc}});
                }
            }
        }
    }

    return 0; // control never actually reaches here
}

int main() {
    vector<vector<int>> heights = {
        {1, 2, 2},
        {3, 8, 2},
        {5, 3, 5}
    };

    cout << "Minimum Effort Path = " << minimumEffort(heights) << endl;
    return 0;
}
