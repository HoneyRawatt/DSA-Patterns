#include <bits/stdc++.h>
using namespace std;

/*
Function: bfsofgraph
Purpose: Perform Breadth First Search (BFS) traversal on a graph

Parameters:
 - n: number of vertices
 - adj: adjacency list of the graph

Returns:
 - vector<int>: list of nodes in BFS traversal order
*/
vector<int> bfsofgraph(int n, vector<int> adj[]) {
    vector<int> vis(n, 0); // visited array initialized to 0
    vector<int> bfs;       // stores BFS traversal
    queue<int> q;

    // Start BFS from node 0 (you can modify for disconnected graphs)
    vis[0] = 1;
    q.push(0);

    while (!q.empty()) {
        int node = q.front();
        q.pop();
        bfs.push_back(node);

        // Traverse all adjacent nodes
        for (auto it : adj[node]) {
            if (!vis[it]) {
                vis[it] = 1;
                q.push(it);
            }
        }
    }

    return bfs;
}

/*
Main function: Demonstrates BFS traversal
*/
int main() {
    int n, m;
    cin >> n >> m; // number of vertices and edges

    vector<int> adj[n];

    // Building the adjacency list
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u); // remove this for directed graph
    }

    // Get BFS traversal
    vector<int> bfs = bfsofgraph(n, adj);

    cout << "BFS Traversal: ";
    for (auto node : bfs) {
        cout << node << " ";
    }
    cout << endl;

    return 0;
}

/*
-------------------------
Time & Space Complexity:
-------------------------
🕒 Time Complexity:  O(V + 2E)
    - Each vertex and each edge is visited once.
    - For adjacency list representation.

💾 Space Complexity: O(V)
    - Visited array: O(V)
    - Queue: O(V) in the worst case
    - BFS output list: O(V)
-------------------------
*/
