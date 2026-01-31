#include <bits/stdc++.h>
using namespace std;

/*
------------------------------------------------------------
🧠 Intuition:
------------------------------------------------------------
We are given an undirected weighted graph (roads with travel times).
We need to find:
1️⃣ The *shortest time* to reach from city 0 → city (n-1)
2️⃣ The *number of distinct ways* to reach city (n-1)
    with the **shortest time** only.

We use a modified version of **Dijkstra’s algorithm**:
- The priority queue ensures we always process the smallest current distance first.
- Along with distance, we track the number of ways to reach each node.

💡 When we relax edges:
  - If we find a *shorter path*, we update `dist[]` and set `ways[v] = ways[u]`
  - If we find *another path with the same distance*, we add ways:
        `ways[v] = (ways[v] + ways[u]) % MOD`

------------------------------------------------------------
📊 Time Complexity:  O((E + V) * log V)
   → because each edge relaxation in Dijkstra takes log V time in the priority queue.

💾 Space Complexity: O(V + E)
   → adjacency list + distance array + ways array + priority queue
------------------------------------------------------------
*/

class Solution {
public:
    int countPaths(int n, vector<vector<int>>& roads) {
        // Build adjacency list: (node -> {neighbor, edge_weight})
        vector<pair<int,int>> adj[n];
        for (auto it : roads) {
            adj[it[0]].push_back({it[1], it[2]});
            adj[it[1]].push_back({it[0], it[2]});
        }

        // Min-heap for Dijkstra: {distance, node}
        priority_queue<pair<long long,int>,
                       vector<pair<long long,int>>,
                       greater<pair<long long,int>>> pq;

        // Distance and ways arrays
        vector<long long> dist(n, LLONG_MAX);
        vector<int> ways(n, 0);

        int mod = 1e9 + 7;

        // Start from node 0
        dist[0] = 0;
        ways[0] = 1;
        pq.push({0, 0});

        while (!pq.empty()) {
            long long dis = pq.top().first;
            int node = pq.top().second;
            pq.pop();

            // Skip outdated entries
            if (dis > dist[node]) continue;

            for (auto it : adj[node]) {
                int adjNode = it.first;
                int edgeWt = it.second;

                // Case 1: Found a shorter path
                if (dis + edgeWt < dist[adjNode]) {
                    dist[adjNode] = dis + edgeWt;
                    pq.push({dist[adjNode], adjNode});
                    ways[adjNode] = ways[node];
                }

                // Case 2: Found another shortest path
                else if (dis + edgeWt == dist[adjNode]) {
                    ways[adjNode] = (ways[adjNode] + ways[node]) % mod;
                }
            }
        }

        return ways[n - 1] % mod;
    }
};

int main() {
    /*
    Example:
    n = 7
    roads = {
        {0,6,7},
        {0,1,2},
        {1,2,3},
        {1,3,3},
        {6,3,3},
        {3,5,1},
        {6,5,1},
        {2,5,1},
        {0,4,5},
    }

    Output → 4
    Explanation:
    There are 4 ways to reach node 6 with the minimum distance.
    */

    vector<vector<int>> roads = {
        {0,6,7},{0,1,2},{1,2,3},{1,3,3},
        {6,3,3},{3,5,1},{6,5,1},{2,5,1},{0,4,5}
    };
    int n = 7;

    Solution obj;
    cout << "Number of shortest paths: " << obj.countPaths(n, roads) << endl;
    return 0;
}
