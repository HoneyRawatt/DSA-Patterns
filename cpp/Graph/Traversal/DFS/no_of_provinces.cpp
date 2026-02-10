#include <bits/stdc++.h>
using namespace std;

/*
====================================================
PROBLEM STATEMENT:
====================================================
You are given an adjacency matrix representing connections
between cities. A group of directly or indirectly connected
cities forms a "province".

- adjMatrix[i][j] = 1 means city i is directly connected to city j
- adjMatrix[i][i] = 1 (a city is connected to itself)

Your task is to find the total number of provinces.

This is equivalent to finding the number of
CONNECTED COMPONENTS in an undirected graph.
====================================================
*/

/*
----------------------------------------------------
DFS Function
----------------------------------------------------
Parameters:
- node : current node to start DFS
- adj  : adjacency list of the graph
- vis  : visited array
- ls   : stores DFS traversal order (optional)

Purpose:
- Marks the current node as visited
- Recursively visits all unvisited neighbors
----------------------------------------------------
*/
void dfs(int node, vector<int> adj[], vector<int> &vis, vector<int> &ls) {
    vis[node] = 1;        // mark current node as visited
    ls.push_back(node);   // add node to DFS traversal

    for (auto it : adj[node]) {
        if (!vis[it]) {
            dfs(it, adj, vis, ls);
        }
    }
}

/*
----------------------------------------------------
numProvinces Function
----------------------------------------------------
Parameters:
- adjMatrix : adjacency matrix representation
- v         : number of cities (vertices)

Purpose:
- Converts adjacency matrix to adjacency list
- Uses DFS to count connected components (provinces)
- Returns total number of provinces
----------------------------------------------------
*/
int numProvinces(vector<vector<int>> &adjMatrix, int v) {

    // Step 1: Convert adjacency matrix to adjacency list
    vector<int> adj[v];
    for (int i = 0; i < v; i++) {
        for (int j = 0; j < v; j++) {
            if (adjMatrix[i][j] == 1 && i != j) {
                adj[i].push_back(j);
            }
        }
    }

    // Step 2: Visited array
    vector<int> vis(v, 0);
    int cnt = 0; // number of provinces

    // Step 3: Run DFS for each unvisited node
    for (int i = 0; i < v; i++) {
        if (!vis[i]) {
            vector<int> ls; // optional DFS traversal list
            cnt++;          // new province found
            dfs(i, adj, vis, ls);
        }
    }

    return cnt;
}

/*
----------------------------------------------------
Main Function
----------------------------------------------------
*/
int main() {
    vector<vector<int>> adj = {
        {1, 1, 0},
        {1, 1, 0},
        {0, 0, 1}
    };

    int v = adj.size();

    cout << "Number of provinces: " << numProvinces(adj, v) << endl;
    return 0;
}

/*
====================================================
INTUITION:
====================================================
- Each province is a connected component.
- Starting DFS from an unvisited city will visit
  all cities in the same province.
- Counting how many times DFS is initiated gives
  the total number of provinces.

====================================================
APPROACH:
====================================================
1. Convert adjacency matrix into adjacency list.
2. Maintain a visited array.
3. Traverse all nodes:
   - If a node is unvisited, start DFS.
   - Mark all reachable nodes as visited.
   - Increment province count.
4. Return the count.

====================================================
TIME COMPLEXITY:
====================================================
- Matrix → List conversion: O(V²)
- DFS traversal: O(V + E)
- Overall Time Complexity: O(V²)
  (since E can be at most V²)

====================================================
SPACE COMPLEXITY:
====================================================
- Adjacency list: O(V + E) → O(V²) worst case
- Visited array: O(V)
- DFS recursion stack: O(V)

Overall Space Complexity: O(V²)
====================================================
*/
