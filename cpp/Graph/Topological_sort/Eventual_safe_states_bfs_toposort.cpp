#include <bits/stdc++.h>
using namespace std;

/*
Approach:
1. Reverse all the edges in the graph.
2. Perform Kahn’s Algorithm (BFS Topological Sort) on the reversed graph.
3. All nodes that can be reached in this reverse traversal are safe.
*/

vector<int> eventualSafeStates(int V, vector<int> adj[]) {
    vector<int> adjRev[V];       // reversed adjacency list
    vector<int> indegree(V, 0);  // indegree for reversed graph

    // Step 1: Build reverse graph
    for (int i = 0; i < V; i++) {
        for (auto it : adj[i]) {
            adjRev[it].push_back(i); // reverse the edge
            indegree[i]++;           // count indegree for reversed graph
        }
    }

    // Step 2: Push all nodes with indegree 0
    queue<int> q;
    for (int i = 0; i < V; i++) {
        if (indegree[i] == 0) q.push(i);
    }

    // Step 3: Perform Kahn’s Algorithm
    vector<int> safeNodes;
    while (!q.empty()) {
        int node = q.front();
        q.pop();
        safeNodes.push_back(node);

        for (auto it : adjRev[node]) {
            indegree[it]--;
            if (indegree[it] == 0) q.push(it);
        }
    }

    sort(safeNodes.begin(), safeNodes.end());
    return safeNodes;
}

// ---------------- MAIN FUNCTION ----------------
int main() {
    int V = 7;
    vector<int> adj[V];

    // Example: directed graph
    adj[0] = {1, 2};
    adj[1] = {2, 3};
    adj[2] = {5};
    adj[3] = {0};
    adj[4] = {5};
    adj[5] = {};
    adj[6] = {};

    vector<int> result = eventualSafeStates(V, adj);

    cout << "Safe nodes: ";
    for (auto x : result) cout << x << " ";
    cout << endl;

    return 0;
}

/*
Time Complexity:
O(V + E)
- Each node and edge is processed once during graph reversal and BFS.

Space Complexity:
O(V + E)
- Adjacency list + indegree array + queue + result vector.
*/
