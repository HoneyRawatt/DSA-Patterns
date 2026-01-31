#include <bits/stdc++.h>
using namespace std;

/*
    Function: dfs
    Purpose: Try to color each node using two colors (0 and 1)
             If we find two adjacent nodes with the same color → not bipartite
    Time Complexity: O(V + E)
    Space Complexity: O(V) recursion + O(V) color array
*/
bool dfs(int node, int col, vector<int>& color, vector<int> adj[]) {
    color[node] = col; // assign color

    // explore all adjacent nodes
    for (auto it : adj[node]) {
        if (color[it] == -1) {
            // color alternate (1 - col)
            if (dfs(it, !col, color, adj) == false)
                return false;
        }
        // if adjacent node has the same color → not bipartite
        else if (color[it] == col) {
            return false;
        }
    }
    return true;
}

/*
    Function: isBipartite
    Purpose: Check if entire graph is bipartite (even if disconnected)
    Time Complexity: O(V + E)
    Space Complexity: O(V)
*/
bool isBipartite(int V, vector<int> adj[]) {
    vector<int> color(V, -1); // initialize all colors as -1

    for (int i = 0; i < V; i++) {
        if (color[i] == -1) {
            if (dfs(i, 0, color, adj) == false)
                return false;
        }
    }
    return true;
}

/*
    Overall:
    Time Complexity: O(V + E)
    Space Complexity: O(V)
*/

int main() {
    int V = 4;
    vector<int> adj[V];

    // Example 1: Bipartite graph
    adj[0] = {1, 3};
    adj[1] = {0, 2};
    adj[2] = {1, 3};
    adj[3] = {0, 2};

    cout << (isBipartite(V, adj) ? "Graph is Bipartite" : "Graph is Not Bipartite") << endl;

    // Example 2: Not Bipartite (odd cycle)
    vector<int> adj2[3];
    adj2[0] = {1, 2};
    adj2[1] = {0, 2};
    adj2[2] = {0, 1};

    cout << (isBipartite(3, adj2) ? "Graph is Bipartite" : "Graph is Not Bipartite") << endl;

    return 0;
}
