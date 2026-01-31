#include <bits/stdc++.h>
using namespace std;

/*
-----------------------------------------------
 Function: toposort()
 Purpose:  Perform DFS-based Topological Sort
-----------------------------------------------
Time Complexity:  O(V + E)
    - Each node visited once
    - Each edge explored once
Space Complexity: O(V)
    - Visited array + recursion stack + stack<int> reference
-----------------------------------------------
*/
void toposort(int node, vector<pair<int, int>> adj[], int vis[], stack<int> &st) {
    vis[node] = 1;
    for (auto it : adj[node]) {
        int v = it.first;
        if (!vis[v]) {
            toposort(v, adj, vis, st);
        }
    }
    st.push(node);
}

/*
--------------------------------------------------------
 Function: shortestPath()
 Purpose:  Compute shortest path in a Directed Acyclic Graph (DAG)
--------------------------------------------------------
Steps:
1️⃣ Build adjacency list from edge list → O(M)
2️⃣ Topological sort of graph → O(V + E)
3️⃣ Relax edges in topological order → O(V + E)

--------------------------------------------------------
Time Complexity:
    Building adjacency list: O(M)
    Topo sort:               O(V + E)
    Relax edges:             O(V + E)
    --------------------------------
    ✅ Total = O(V + E)

Space Complexity:
    Adjacency list: O(V + E)
    Visited array:  O(V)
    Stack:          O(V)
    Distance array: O(V)
    --------------------------------
    ✅ Total = O(V + E)
--------------------------------------------------------
*/
vector<int> shortestPath(int N, int M, vector<vector<int>> &edges) {
    vector<pair<int, int>> adj[N];
    
    // Step 1: Build adjacency list
    for (int i = 0; i < M; i++) {
        int u = edges[i][0];
        int v = edges[i][1];
        int wt = edges[i][2];
        adj[u].push_back({v, wt});
    }

    int vis[N] = {0};
    stack<int> st;

    // Step 2: Perform Topological Sort
    for (int i = 0; i < N; i++) {
        if (!vis[i]) {
            toposort(i, adj, vis, st);
        }
    }

    // Step 3: Relax edges based on topological order
    vector<int> dist(N, 1e9);
    dist[0] = 0; // assuming source = 0

    while (!st.empty()) {
        int node = st.top();
        st.pop();

        if (dist[node] != 1e9) {
            for (auto it : adj[node]) {
                int v = it.first;
                int wt = it.second;
                if (dist[node] + wt < dist[v]) {
                    dist[v] = dist[node] + wt;
                }
            }
        }
    }

    return dist;
}

/*
-----------------------------------------------
 Function: main()
 Purpose:  Example usage and output display
-----------------------------------------------
Time Complexity:  O(V + E)
Space Complexity: O(V + E)
-----------------------------------------------
*/
int main() {
    int N = 6, M = 7;
    vector<vector<int>> edges = {
        {0, 1, 2}, {0, 4, 1}, {4, 5, 4},
        {4, 2, 2}, {1, 2, 3}, {2, 3, 6}, {5, 3, 1}
    };

    vector<int> ans = shortestPath(N, M, edges);

    cout << "Shortest distances from source (0):\n";
    for (int i = 0; i < N; i++) {
        if (ans[i] == 1e9)
            cout << "INF ";
        else
            cout << ans[i] << " ";
    }
    cout << endl;
}
