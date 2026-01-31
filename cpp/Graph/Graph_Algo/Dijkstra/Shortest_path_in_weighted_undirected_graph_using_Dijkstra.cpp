#include <bits/stdc++.h>
using namespace std;

/*
---------------------------------------------------------------
🧠 Approach: Dijkstra’s Algorithm (with Path Reconstruction)
---------------------------------------------------------------
We are given:
- n → number of vertices (1-indexed)
- m → number of edges
- edges → list of edges where edges[i] = {u, v, w}

Goal:
Find the shortest path from node 1 to node n.
If no path exists, return {-1}.

Steps:
1️⃣ Build adjacency list from edge list.
2️⃣ Use a min-heap (priority_queue) to get the node with the smallest distance.
3️⃣ Perform relaxation:
    if (dist[node] + weight < dist[adjNode]), update distance and parent.
4️⃣ Reconstruct path from `n` to `1` using the parent array.

---------------------------------------------------------------
📊 Time Complexity:
---------------------------------------------------------------
- Building adjacency list: O(m)
- Dijkstra relaxation: O(m * log n)
➡️ Total: O(m * log n)

---------------------------------------------------------------
💾 Space Complexity:
---------------------------------------------------------------
- dist[]: O(n)
- parent[]: O(n)
- adjacency list: O(n + m)
➡️ Total: O(n + m)
---------------------------------------------------------------
*/

vector<int> shortestPath(int n, int m, vector<vector<int>>& edges) {
    // Step 1: Build adjacency list
    vector<pair<int, int>> adj[n + 1]; // 1-indexed
    for (auto it : edges) {
        int u = it[0];
        int v = it[1];
        int w = it[2];
        adj[u].push_back({v, w});
        adj[v].push_back({u, w}); // undirected graph
    }

    // Step 2: Min-heap (distance, node)
    priority_queue<pair<int, int>,
                   vector<pair<int, int>>,
                   greater<pair<int, int>>> pq;

    // Step 3: Distance and parent initialization
    vector<int> dist(n + 1, 1e9), parent(n + 1);
    for (int i = 1; i <= n; i++)
        parent[i] = i;

    dist[1] = 0;
    pq.push({0, 1});

    // Step 4: Dijkstra’s relaxation
    while (!pq.empty()) {
        auto it = pq.top();
        pq.pop();
        int node = it.second;
        int dis = it.first;

        for (auto edge : adj[node]) {
            int adjNode = edge.first;
            int weight = edge.second;
            if (dis + weight < dist[adjNode]) {
                dist[adjNode] = dis + weight;
                pq.push({dist[adjNode], adjNode});
                parent[adjNode] = node;
            }
        }
    }

    // Step 5: Check if destination is reachable
    if (dist[n] == 1e9)
        return {-1};

    // Step 6: Reconstruct the path from n to 1
    vector<int> path;
    int node = n;
    while (parent[node] != node) {
        path.push_back(node);
        node = parent[node];
    }
    path.push_back(1);

    reverse(path.begin(), path.end());
    return path;
}

/*
---------------------------------------------------------------
🧩 main() function (Driver)
---------------------------------------------------------------
*/
int main() {
    int n, m;
    cout << "Enter number of vertices (n): ";
    cin >> n;
    cout << "Enter number of edges (m): ";
    cin >> m;

    vector<vector<int>> edges(m, vector<int>(3));
    cout << "Enter edges in format (u v w):\n";
    for (int i = 0; i < m; i++)
        cin >> edges[i][0] >> edges[i][1] >> edges[i][2];

    vector<int> path = shortestPath(n, m, edges);

    cout << "\nShortest path from 1 to " << n << ":\n";
    if (path.size() == 1 && path[0] == -1)
        cout << "No path exists.\n";
    else {
        for (auto node : path)
            cout << node << " ";
        cout << endl;
    }

    return 0;
}

/*
---------------------------------------------------------------
✅ Summary:
---------------------------------------------------------------
🔹 Approach: Dijkstra (Min-Heap + Parent tracking)
🔹 Time Complexity: O(m * log n)
🔹 Space Complexity: O(n + m)
---------------------------------------------------------------
*/
