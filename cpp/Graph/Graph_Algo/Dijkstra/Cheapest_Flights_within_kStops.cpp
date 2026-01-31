#include <bits/stdc++.h>
using namespace std;

/*
------------------------------------------------------------
🧠 Problem: Cheapest Flights Within K Stops
------------------------------------------------------------
We are given a list of flights where each flight[i] = [u, v, w]
represents a flight from city `u` to `v` with cost `w`.
We must find the cheapest price from `src` to `dst` with at most K stops.

------------------------------------------------------------
🧩 Approach: Modified BFS (Dijkstra-like with stop limit)
------------------------------------------------------------
We use a queue for BFS traversal — each state stores:
   (stops, node, current cost)
We only explore neighbors if stops <= K.
We update the minimum cost for each node.

Steps:
1️⃣ Build adjacency list.
2️⃣ Use a queue to traverse while tracking number of stops.
3️⃣ For each node, relax edges if a cheaper cost is found.
4️⃣ Return the cost to reach destination or -1 if unreachable.

------------------------------------------------------------
📊 Time Complexity:
- Building adjacency list: O(E)
- BFS traversal: O(E)
  → Overall: O(E)
------------------------------------------------------------
💾 Space Complexity:
- Adjacency list: O(V + E)
- Distance array: O(V)
→ Overall: O(V + E)
------------------------------------------------------------
*/

int CheapestFlight(int n, vector<vector<int>>& flights, int src, int dst, int K) {
    // Step 1: Build adjacency list
    vector<pair<int, int>> adj[n];
    for (auto& it : flights) {
        adj[it[0]].push_back({it[1], it[2]});
    }

    // Step 2: Queue => {stops, {node, cost}} 
    queue<pair<int, pair<int, int>>> q;
    q.push({0, {src, 0}});

    // Step 3: Distance array (min cost to reach each node)
    vector<int> dist(n, 1e9);
    dist[src] = 0;

    // Step 4: BFS traversal with stop constraint
    while (!q.empty()) {
        auto it = q.front();
        q.pop();

        int stops = it.first;
        int node = it.second.first;
        int cost = it.second.second;

        // If we've exceeded K stops, skip
        if (stops > K) continue;

        // Explore all neighbors
        for (auto& nbr : adj[node]) {
            int adjNode = nbr.first;
            int edgeWt = nbr.second;

            // If a cheaper cost found within K stops, update and push
            if (cost + edgeWt < dist[adjNode] && stops <= K) {
                dist[adjNode] = cost + edgeWt;
                q.push({stops + 1, {adjNode, dist[adjNode]}});
            }
        }
    }

    // Step 5: Return result
    return dist[dst] == 1e9 ? -1 : dist[dst];
}

int main() {
    int n = 4;
    vector<vector<int>> flights = {
        {0, 1, 100},
        {1, 2, 100},
        {2, 0, 100},
        {1, 3, 600},
        {2, 3, 200}
    };
    int src = 0, dst = 3, K = 1;

    cout << "Cheapest price: " << CheapestFlight(n, flights, src, dst, K) << endl;
    return 0;
}
