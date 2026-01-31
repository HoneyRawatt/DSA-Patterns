#include <bits/stdc++.h>
using namespace std;

/*
Function: dfs
Purpose: Perform Depth First Search (DFS) recursively from a given start node.
*/
void dfs(int node, vector<int> adj[], int vis[], vector<int> &ls) {
    vis[node] = 1;        // mark current node as visited
    ls.push_back(node);   // add it to DFS traversal list

    for (auto it : adj[node]) {
        if (!vis[it]) {
            dfs(it, adj, vis, ls);
        }
    }
}

/*
Main function to demonstrate DFS traversal
*/
int main() {
    int n, m;
    cin >> n >> m; // n = number of vertices, m = number of edges

    vector<int> adj[n + 1];

    // Building adjacency list
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u); // remove this line for directed graph
    }

    int vis[n + 1] = {0}; // visited array
    vector<int> dfsResult;

    // Start DFS from node 0
    dfs(0, adj, vis, dfsResult);

    cout << "DFS Traversal: ";
    for (auto node : dfsResult) {
        cout << node << " ";
    }
    cout << endl;

    return 0;
}

/*
---------------------------------------------
🧠 Explanation:
---------------------------------------------
- Start from a given source node (here 0)
- Mark it as visited and push to traversal list.
- Recursively visit all unvisited neighbors.
- The recursion explores as deep as possible before backtracking.

---------------------------------------------
⏱️ Time Complexity: O(V + 2E)
   - Each vertex and each edge is visited once.

💾 Space Complexity: O(V)
   - Visited array + recursion stack.
---------------------------------------------
*/
