#include <bits/stdc++.h>
using namespace std;

// Function to perform Topological Sort using Kahn's Algorithm (BFS)
vector<int> topoSort(int V, vector<int> adj[]) {
    vector<int> indegree(V, 0);

    // Step 1: Compute indegree for each node
    for (int i = 0; i < V; i++) {
        for (auto it : adj[i]) {
            indegree[it]++;
        }
    }

    // Step 2: Push all nodes with indegree 0 into the queue
    queue<int> q;
    for (int i = 0; i < V; i++) {
        if (indegree[i] == 0) {
            q.push(i);
        }
    }

    // Step 3: BFS traversal
    vector<int> topo;
    while (!q.empty()) {
        int node = q.front();
        q.pop();
        topo.push_back(node);

        // Reduce indegree of all adjacent nodes
        for (auto it : adj[node]) {
            indegree[it]--;
            if (indegree[it] == 0) q.push(it);
        }
    }

    return topo;
}

// ---------------- MAIN FUNCTION ----------------
int main() {
    int V = 6;
    vector<int> adj[V];

    // Example DAG
    adj[5].push_back(0);
    adj[5].push_back(2);
    adj[4].push_back(0);
    adj[4].push_back(1);
    adj[2].push_back(3);
    adj[3].push_back(1);

    vector<int> result = topoSort(V, adj);

    cout << "Topological Sort: ";
    for (auto x : result) cout << x << " ";
    cout << endl;

    return 0;
}

/*
Time Complexity:  O(V + E)
    - Each vertex and edge is processed once.
Space Complexity: O(V)
    - For indegree array, queue, and topo vector.
*/
