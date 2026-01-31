#include <bits/stdc++.h>
using namespace std;

/*
------------------------------------------------------------
🧠 Approach: BFS (Breadth First Search) on a Grid
------------------------------------------------------------
We use BFS because all edges have equal weight (1 step).
1️⃣ Start BFS from the source cell.
2️⃣ Move in 4 possible directions (up, right, down, left).
3️⃣ Maintain a distance matrix to record the shortest distance.
4️⃣ If we reach the destination, return the distance.
5️⃣ If BFS completes without reaching destination, return -1.

------------------------------------------------------------
📊 Time Complexity:  O(N * M)
💾 Space Complexity: O(N * M)
------------------------------------------------------------
*/

int shortestPath(vector<vector<int>>& grid, pair<int,int> source, pair<int,int> destination) {
    int n = grid.size();
    int m = grid[0].size();

    // If source is same as destination
    if (source.first == destination.first && source.second == destination.second)
        return 0;

    // If source or destination cell is blocked
    if (grid[source.first][source.second] == 0 || grid[destination.first][destination.second] == 0)
        return -1;

    // Distance matrix initialized to infinity (1e9)
    vector<vector<int>> dist(n, vector<int>(m, 1e9));

    // Min distance to source = 0
    dist[source.first][source.second] = 0;

    // BFS queue: {distance, {row, col}}
    queue<pair<int, pair<int, int>>> q;
    q.push({0, {source.first, source.second}});

    // 4-direction movement (up, right, down, left)
    int dr[] = {-1, 0, 1, 0};
    int dc[] = {0, 1, 0, -1};

    while (!q.empty()) {
        auto it = q.front();
        q.pop();

        int dis = it.first;
        int r = it.second.first;
        int c = it.second.second;

        // Explore 4 neighbors
        for (int i = 0; i < 4; i++) {
            int newr = r + dr[i];
            int newc = c + dc[i];

            // Check boundaries and valid move
            if (newr >= 0 && newr < n && newc >= 0 && newc < m && grid[newr][newc] == 1) {
                // If a shorter distance is found
                if (dis + 1 < dist[newr][newc]) {
                    dist[newr][newc] = dis + 1;

                    // If we reached the destination, return distance
                    if (newr == destination.first && newc == destination.second)
                        return dis + 1;

                    // Push to queue for BFS
                    q.push({dis + 1, {newr, newc}});
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
