#include <bits/stdc++.h>
using namespace std;

/*
Intuition:
------------
We use the Floyd–Warshall algorithm to find the shortest distances 
between all pairs of cities. Then for each city, we count how many 
other cities are reachable within the distance threshold.

Finally, we return the city with:
 - the smallest number of reachable cities
 - if there is a tie, the city with the larger index.

Time Complexity:  O(n^3)
Space Complexity: O(n^2)
*/

int findCity_floydWarshall(int n, int m, vector<vector<int>>& edges, int distanceThreshold) {
    vector<vector<int>> dist(n, vector<int>(n, 1e9));

    // Step 1: Build adjacency matrix
    for (auto& it : edges) {
        dist[it[0]][it[1]] = it[2];
        dist[it[1]][it[0]] = it[2]; // since graph is undirected
    }

    // Step 2: Distance to self = 0
    for (int i = 0; i < n; i++) dist[i][i] = 0;

    // Step 3: Floyd–Warshall algorithm
    for (int via = 0; via < n; via++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (dist[i][via] == 1e9 || dist[via][j] == 1e9) continue;
                dist[i][j] = min(dist[i][j], dist[i][via] + dist[via][j]);
            }
        }
    }

    // Step 4: Find the city with the smallest number of reachable neighbors
    int cntCity = INT_MAX;
    int cityNo = -1;

    for (int city = 0; city < n; city++) {
        int cnt = 0;
        for (int adjCity = 0; adjCity < n; adjCity++) {
            if (dist[city][adjCity] <= distanceThreshold)
                cnt++;
        }

        // Update answer: smallest count, break ties by larger city index
        if (cnt <= cntCity) {
            cntCity = cnt;
            cityNo = city;
        }
    }

    return cityNo;
}
/*
Intuition:
------------
We run Dijkstra's algorithm from each node to find the shortest distance 
to every other node.

Then, we count how many cities are reachable within the distance threshold 
for each source node.

Finally, we return the city that has:
  - the smallest number of reachable neighbors, and
  - in case of a tie, the city with the largest index.

Time Complexity:  O(V * (E log V))
Space Complexity: O(V + E)
*/

int findCity_dijkstra(int n, int m, vector<vector<int>>& edges, int distanceThreshold) {
    // Step 1: Build adjacency list
    vector<pair<int, int>> adj[n];
    for (auto& it : edges) {
        adj[it[0]].push_back({it[1], it[2]});
        adj[it[1]].push_back({it[0], it[2]});  // undirected
    }

    int cntCity = INT_MAX;
    int cityNo = -1;

    // Step 2: Run Dijkstra from each node
    for (int src = 0; src < n; src++) {
        vector<int> dist(n, 1e9);
        dist[src] = 0;

        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        pq.push({0, src});

        while (!pq.empty()) {
            auto [d, node] = pq.top();
            pq.pop();

            for (auto [nbr, wt] : adj[node]) {
                if (d + wt < dist[nbr]) {
                    dist[nbr] = d + wt;
                    pq.push({dist[nbr], nbr});
                }
            }
        }

        // Step 3: Count reachable cities within the threshold
        int cnt = 0;
        for (int j = 0; j < n; j++) {
            if (dist[j] <= distanceThreshold)
                cnt++;
        }

        // Step 4: Update result — prefer larger city index in tie
        if (cnt <= cntCity) {
            cntCity = cnt;
            cityNo = src;
        }
    }

    return cityNo;
}

// ---------------------------
// Example Driver Code
// ---------------------------
int main() {
    int n = 4, m = 4;
    vector<vector<int>> edges = {
        {0, 1, 3},
        {1, 2, 1},
        {2, 3, 4},
        {0, 3, 7}
    };
    int threshold = 4;

    cout << "City with smallest number of reachable cities: "
         << findCity_floydWarshall(n, m, edges, threshold) << endl;
}
