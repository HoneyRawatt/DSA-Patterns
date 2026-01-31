#include <bits/stdc++.h>
using namespace std;

/*
-----------------------------------------------
Shortest Path in an Unweighted Graph using BFS
-----------------------------------------------
Time Complexity:  O(V + E)
Space Complexity: O(V + E)
-----------------------------------------------
*/
vector<int> shortestPath(vector<vector<int>> &edges, int N, int M, int src) {
    // Step 1: Build adjacency list
    vector<int> adj[N];
    for (auto it : edges) {
        int u = it[0];
        int v = it[1];
        adj[u].push_back(v);
        adj[v].push_back(u); // since graph is undirected
    }

    // Step 2: Initialize distance array
    vector<int> dist(N, 1e9);
    dist[src] = 0;

    // Step 3: BFS traversal
    queue<int> q;
    q.push(src);

    while (!q.empty()) {
        int node = q.front();
        q.pop();

        for (auto it : adj[node]) {
            if (dist[node] + 1 < dist[it]) {
                dist[it] = dist[node] + 1;
                q.push(it);
            }
        }
    }

    // Step 4: Replace unreachable nodes with -1
    vector<int> ans(N, -1);
    for (int i = 0; i < N; i++) {
        if (dist[i] != 1e9)
            ans[i] = dist[i];
    }

    return ans;
}

// Example usage
int main() {
    int N = 6, M = 7, src = 0;
    vector<vector<int>> edges = {
        {0, 1}, {0, 2}, {1, 3},
        {2, 4}, {4, 5}, {3, 5}, {1, 2}
    };

    vector<int> res = shortestPath(edges, N, M, src);

    cout << "Shortest distances from source " << src << ":\n";
    for (auto d : res)
        cout << d << " ";
    cout << endl;

    return 0;
}
