#include <bits/stdc++.h>
using namespace std;

/*
--------------------------------------------
Function: isCyclicKahn
Purpose : Detects if a Directed Graph contains a cycle
Approach: Kahn's Algorithm (BFS based Topological Sort)
--------------------------------------------
Time Complexity:
    - Building indegree array: O(V + E)
    - BFS traversal: O(V + E)
    => Overall: O(V + E)

Space Complexity:
    - indegree array: O(V)
    - queue: O(V)
    => Overall: O(V)
--------------------------------------------
*/
bool isCyclicKahn(int V, vector<int> adj[]) {
    vector<int> indegree(V, 0);

    // Step 1: Compute indegree of each node
    for (int i = 0; i < V; i++) {
        for (auto it : adj[i])
            indegree[it]++;
    }

    // Step 2: Push all nodes with indegree 0 into the queue
    queue<int> q;
    for (int i = 0; i < V; i++) {
        if (indegree[i] == 0)
            q.push(i);
    }

    // Step 3: Process nodes in BFS manner
    int count = 0;
    while (!q.empty()) {
        int node = q.front();
        q.pop();
        count++;  // count of processed nodes

        // Reduce indegree of neighbors
        for (auto it : adj[node]) {
            indegree[it]--;
            if (indegree[it] == 0)
                q.push(it);
        }
    }

    // Step 4: If count != V → cycle exists
    return (count != V);
}

/*
--------------------------------------------
Main Function
--------------------------------------------
*/
int main() {
    int V = 4;
    vector<int> adj[V];

    // Example 1: Graph with NO cycle
    adj[0].push_back(1);
    adj[1].push_back(2);
    adj[2].push_back(3);
    // No cycle here (0→1→2→3)

    cout << "Cycle present? " << (isCyclicKahn(V, adj) ? "Yes" : "No") << endl;

    // Example 2: Graph WITH cycle
    vector<int> adj2[V];
    adj2[0].push_back(1);
    adj2[1].push_back(2);
    adj2[2].push_back(0);  // cycle: 0→1→2→0

    cout << "Cycle present? " << (isCyclicKahn(V, adj2) ? "Yes" : "No") << endl;

    return 0;
}


// | Step                  | Operation                      | Time         | Space    |
// | --------------------- | ------------------------------ | ------------ | -------- |
// | Build indegree        | Traverse all edges             | O(E)         | O(V)     |
// | Push indegree=0 nodes | Traverse all vertices          | O(V)         | O(V)     |
// | BFS processing        | Traverse each node + edge once | O(V + E)     | O(V)     |
// | **Total**             |                                | **O(V + E)** | **O(V)** |
