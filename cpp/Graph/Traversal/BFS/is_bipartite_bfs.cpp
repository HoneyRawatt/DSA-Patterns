#include <bits/stdc++.h>
using namespace std;

/*
=====================================================
Problem Statement:
=====================================================
You are given an undirected graph with V vertices and
an adjacency list representation.

A graph is called **bipartite** if its vertices can be
divided into two disjoint sets such that:
- No two adjacent vertices belong to the same set
- Each edge connects vertices from different sets

The graph may be disconnected.
Your task is to determine whether the graph is bipartite.
*/

/*
=====================================================
Intuition:
=====================================================
- A graph is bipartite if it can be colored using only
  two colors such that no two adjacent nodes have
  the same color.
- BFS is used to color nodes level by level.
- Adjacent nodes must always receive opposite colors.

Key idea:
➡ If we ever find two adjacent nodes with the same color,
   the graph is NOT bipartite.
*/

/*
=====================================================
Approach (BFS):
=====================================================
1️⃣ Initialize a color array with -1 (uncolored).
2️⃣ Traverse all vertices to handle disconnected components.
3️⃣ For every uncolored vertex:
    - Start BFS
    - Assign an initial color (0)
4️⃣ For each visited node:
    - Assign opposite color to its neighbors
    - If a conflict occurs, return false
5️⃣ If BFS finishes without conflicts, the graph is bipartite.
*/

// Function to check if a graph is bipartite using BFS
bool isBipartite(int V, vector<int> adj[]) {

    // Color array: -1 → uncolored, 0 and 1 → two colors
    vector<int> color(V, -1);

    // Loop through all vertices to handle disconnected components
    for (int start = 0; start < V; start++) {

        // If the node is not colored, start BFS
        if (color[start] == -1) {

            queue<int> q;
            q.push(start);

            // Assign first color
            color[start] = 0;

            // Standard BFS traversal
            while (!q.empty()) {
                int node = q.front();
                q.pop();

                // Visit all adjacent nodes
                for (auto it : adj[node]) {

                    // If adjacent node is uncolored
                    if (color[it] == -1) {
                        color[it] = !color[node]; // assign opposite color
                        q.push(it);
                    }
                    // If adjacent node has same color → conflict
                    else if (color[it] == color[node]) {
                        return false;
                    }
                }
            }
        }
    }
    return true;
}

int main() {

    /*
        Example 1: Bipartite Graph
        Graph:
        0 -- 1
        |    |
        3 -- 2
    */
    int V1 = 4;
    vector<int> adj1[V1];
    adj1[0] = {1, 3};
    adj1[1] = {0, 2};
    adj1[2] = {1, 3};
    adj1[3] = {0, 2};

    cout << "Graph 1: "
         << (isBipartite(V1, adj1) ? "Bipartite" : "Not Bipartite")
         << endl;

    /*
        Example 2: Not Bipartite Graph (Odd Cycle)
        Graph:
        0
       / \
      1---2
    */
    int V2 = 3;
    vector<int> adj2[V2];
    adj2[0] = {1, 2};
    adj2[1] = {0, 2};
    adj2[2] = {0, 1};

    cout << "Graph 2: "
         << (isBipartite(V2, adj2) ? "Bipartite" : "Not Bipartite")
         << endl;

    return 0;
}

/*
=====================================================
Time & Space Complexity:
=====================================================

⏱ Time Complexity: O(V + E)
- Each vertex is visited once
- Each edge is checked at most twice

📦 Space Complexity: O(V)
- Color array
- Queue used for BFS
=====================================================
*/
