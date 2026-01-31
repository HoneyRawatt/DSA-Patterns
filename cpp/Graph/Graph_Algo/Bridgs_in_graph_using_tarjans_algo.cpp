#include <bits/stdc++.h>
using namespace std;

/*
===================================================================
🧩 Tarjan’s Algorithm — Find Bridges (Critical Connections)
===================================================================
🔹 Problem:
Given an undirected connected graph, find all the edges (u, v)
whose removal increases the number of connected components.

🔹 Idea:
We use DFS with discovery times (tin) and lowest reachable times (low):
- tin[node] = discovery time when DFS visits this node
- low[node] = lowest discovery time reachable from this node via DFS tree or back edges

🔹 Bridge condition:
If for any edge (u → v), we find:
      low[v] > tin[u]
Then, removing edge (u, v) disconnects the graph ⇒ it’s a bridge.
===================================================================
*/

class Solution {
public:
    int timer = 1; // ⏱️ Global timer to assign discovery times

    /*
    ---------------------------------------------------------
    🔸 dfs(node, parent, vis, adj, tin, low, bridges)
    ---------------------------------------------------------
    Performs DFS traversal, computes discovery and low times.

    Parameters:
    node   → current node being visited
    parent → parent of this node in DFS tree
    vis    → visited array
    adj    → adjacency list
    tin    → discovery time array
    low    → lowest reachable discovery time array
    bridges → stores result pairs (u, v)

    ⏱️ Time: O(V + E)
    💾 Space: O(V) recursion + O(V + E) adjacency list
    */
    void dfs(int node, int parent, vector<int> &vis, vector<int> adj[],
             vector<int> &tin, vector<int> &low, vector<vector<int>> &bridges) {

        vis[node] = 1;
        tin[node] = low[node] = timer++; // assign discovery & low time initially same

        // 🔁 Traverse all adjacent nodes
        for (auto it : adj[node]) {
            if (it == parent) continue; // skip the edge leading back to parent

            if (!vis[it]) {
                // 🧭 DFS on unvisited neighbor
                dfs(it, node, vis, adj, tin, low, bridges);

                // Update low[node] based on child’s reachable time
                low[node] = min(low[node], low[it]);

                // 🚨 Check bridge condition
                if (low[it] > tin[node]) {
                    bridges.push_back({node, it});
                }
            } else {
                // ⤴️ Back edge found → update low[node]
                low[node] = min(low[node], tin[it]);
            }
        }
    }

    /*
    ---------------------------------------------------------
    🔸 criticalConnections(n, connections)
    ---------------------------------------------------------
    Builds adjacency list and triggers DFS from node 0.

    ⏱️ Time: O(V + E)
    💾 Space: O(V + E)
    */
    vector<vector<int>> criticalConnections(int n, vector<vector<int>> &connections) {
        vector<int> adj[n];

        // 🧱 Build adjacency list (undirected graph)
        for (auto &it : connections) {
            adj[it[0]].push_back(it[1]);
            adj[it[1]].push_back(it[0]);
        }

        // Initialize helper arrays
        vector<int> vis(n, 0), tin(n, 0), low(n, 0);
        vector<vector<int>> bridges;

        // 🔥 Run DFS from every unvisited node (in case of disconnected graphs)
        for (int i = 0; i < n; i++) {
            if (!vis[i]) {
                dfs(i, -1, vis, adj, tin, low, bridges);
            }
        }

        return bridges;
    }
};

/*
===================================================================
🧪 Driver Code (Example)
===================================================================
*/
int main() {
    Solution obj;

    int n = 4;
    vector<vector<int>> connections = {{0, 1}, {1, 2}, {2, 0}, {1, 3}};

    vector<vector<int>> result = obj.criticalConnections(n, connections);

    cout << "🔹 Bridges (Critical Connections):\n";
    for (auto &edge : result) {
        cout << edge[0] << " - " << edge[1] << "\n";
    }

    return 0;
}

/*
===================================================================
🧭 Example Dry Run
===================================================================
Graph:
0 --- 1 --- 3
 \   /
   2

tin[] = [1, 2, 3, 4]
low[] = [1, 1, 1, 4]

Since low[3] (4) > tin[1] (2) ⇒ (1,3) is a bridge.

===================================================================
⏱️ TIME COMPLEXITY:
O(V + E)
- Each vertex and edge visited once.

💾 SPACE COMPLEXITY:
O(V + E)
- Adjacency list: O(V + E)
- Arrays tin[], low[], vis[]: O(V)
- Recursion stack: O(V)
===================================================================
*/
