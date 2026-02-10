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
- Every edge connects a vertex from one set to the other
- No two adjacent vertices belong to the same set

Your task is to check whether the given graph is bipartite.

Note:
- The graph may be disconnected.
*/

/*
=====================================================
Intuition:
=====================================================
- A graph is bipartite if it can be colored using only
  two colors such that no two adjacent nodes have
  the same color.
- This is equivalent to checking whether the graph
  contains an **odd-length cycle**.
- We use DFS to try coloring adjacent nodes with
  alternate colors.

Key idea:
➡ If at any point two adjacent nodes have the same color,
   the graph is NOT bipartite.
*/

/*
=====================================================
DFS Function:
=====================================================
Purpose:
- Try to color the graph using two colors (0 and 1)
- Recursively color adjacent nodes with alternate colors
- Detect conflicts in coloring

Parameters:
- node  : current node
- col   : color to assign to current node
- color : color array (-1 = unvisited)
- adj   : adjacency list

Time Complexity:
- O(V + E)

Space Complexity:
- O(V) for recursion stack
- O(V) for color array
*/
bool dfs(int node, int col, vector<int>& color, vector<int> adj[]) {

    // Assign color to current node
    color[node] = col;

    // Traverse all adjacent nodes
    for (auto it : adj[node]) {

        // If adjacent node is uncolored
        if (color[it] == -1) {

            // Assign alternate color
            if (dfs(it, !col, color, adj) == false)
                return false;
        }
        // If adjacent node has same color → conflict
        else if (color[it] == col) {
            return false;
        }
    }
    return true;
}

/*
=====================================================
Function: isBipartite
=====================================================
Purpose:
- Check if the entire graph is bipartite
- Handles disconnected graphs by checking
  every unvisited component

Approach:
1️⃣ Initialize all nodes as uncolored (-1)
2️⃣ For each node:
    - If unvisited, start DFS coloring from it
3️⃣ If any DFS call detects a conflict → return false
4️⃣ Otherwise, graph is bipartite
*/
bool isBipartite(int V, vector<int> adj[]) {

    // Color array initialized to -1 (unvisited)
    vector<int> color(V, -1);

    // Check all components of the graph
    for (int i = 0; i < V; i++) {

        // If node is unvisited, start DFS
        if (color[i] == -1) {
            if (dfs(i, 0, color, adj) == false)
                return false;
        }
    }
    return true;
}

/*
=====================================================
Overall Time & Space Complexity:
=====================================================

⏱ Time Complexity:
- O(V + E)
  Each vertex and edge is processed once.

📦 Space Complexity:
- O(V)
  Color array + recursion stack.
*/

int main() {

    int V = 4;
    vector<int> adj[V];

    /*
        Example 1: Bipartite Graph
        Graph:
        0 -- 1
        |    |
        3 -- 2
    */
    adj[0] = {1, 3};
    adj[1] = {0, 2};
    adj[2] = {1, 3};
    adj[3] = {0, 2};

    cout << (isBipartite(V, adj)
            ? "Graph is Bipartite"
            : "Graph is Not Bipartite")
         << endl;

    /*
        Example 2: Not Bipartite (Odd Cycle)
        Graph:
        0
       / \
      1---2
    */
    vector<int> adj2[3];
    adj2[0] = {1, 2};
    adj2[1] = {0, 2};
    adj2[2] = {0, 1};

    cout << (isBipartite(3, adj2)
            ? "Graph is Bipartite"
            : "Graph is Not Bipartite")
         << endl;

    return 0;
}
