#include <bits/stdc++.h>
using namespace std;

/*
====================================================================
🧠 Approach: A* Search (Heuristic-based pathfinding on a Grid)
====================================================================
We use A* instead of BFS to reduce unnecessary exploration.
A* uses both:
   - g: cost (distance) so far from source
   - h: heuristic (estimated distance to destination)
and always expands nodes with the smallest f = g + h.

Since all edges have equal weight (1 step), A* behaves like BFS
but is often much faster in practice for larger grids.

====================================================================
📊 Time Complexity per Module:
--------------------------------------------------------------------
1️⃣ Heuristic Calculation (per cell): O(1)
2️⃣ Insertion/Pop from Priority Queue: O(log(N*M))
3️⃣ Processing Each Cell (once): O(N*M)
=> ⏱ Total Time Complexity: O(N * M * log(N*M))

====================================================================
💾 Space Complexity:
--------------------------------------------------------------------
1️⃣ Distance Matrix (dist): O(N*M)
2️⃣ Priority Queue: O(N*M)
=> 🧮 Total Space Complexity: O(N*M)
====================================================================
*/

int heuristic(pair<int,int> a, pair<int,int> b) {
    // Manhattan distance since movement is 4-directional
    return abs(a.first - b.first) + abs(a.second - b.second);
}

int shortestPath(vector<vector<int>>& grid, pair<int,int> source, pair<int,int> destination) {
    int n = grid.size();
    int m = grid[0].size();

    // If source == destination
    if (source == destination)
        return 0;

    // If source or destination cell is blocked
    if (grid[source.first][source.second] == 0 || grid[destination.first][destination.second] == 0)
        return -1;

    // Distance (g-cost)
    vector<vector<int>> dist(n, vector<int>(m, 1e9));
    dist[source.first][source.second] = 0;

    // Priority Queue: {f = g + h, {g, {r, c}}}
    using Node = pair<int, pair<int, pair<int, int>>>;
    priority_queue<Node, vector<Node>, greater<Node>> pq;

    // Push starting node
    int start_h = heuristic(source, destination);
    pq.push({start_h, {0, {source.first, source.second}}});

    // 4-direction movement (up, right, down, left)
    int dr[] = {-1, 0, 1, 0};
    int dc[] = {0, 1, 0, -1};

    while (!pq.empty()) {
        auto it = pq.top();
        pq.pop();

        int f = it.first;
        int g = it.second.first;
        int r = it.second.second.first;
        int c = it.second.second.second;

        // Destination reached
        if (r == destination.first && c == destination.second)
            return g;

        // Explore 4 neighbors
        for (int i = 0; i < 4; i++) {
            int newr = r + dr[i];
            int newc = c + dc[i];

            // Check boundaries and valid move
            if (newr >= 0 && newr < n && newc >= 0 && newc < m && grid[newr][newc] == 1) {
                int new_g = g + 1;
                if (new_g < dist[newr][newc]) {
                    dist[newr][newc] = new_g;
                    int h = heuristic({newr, newc}, destination);
                    pq.push({new_g + h, {new_g, {newr, newc}}});
                }
            }
        }
    }

    // Destination not reachable
    return -1;
}

int main() {
    vector<vector<int>> grid = {
        {1, 1, 1, 1},
        {0, 1, 0, 1},
        {1, 1, 1, 1},
        {1, 0, 1, 1}
    };

    pair<int, int> source = {0, 0};
    pair<int, int> destination = {3, 3};

    int ans = shortestPath(grid, source, destination);
    cout << "Shortest path length = " << ans << endl;

    return 0;
}
