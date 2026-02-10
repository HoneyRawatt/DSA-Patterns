#include <bits/stdc++.h>
using namespace std;

/*
Problem Statement:
Given a Directed Acyclic Graph (DAG) with V vertices and adjacency list `adj[]`,
perform a Topological Sort of the vertices. In a topological ordering, for every 
directed edge u -> v, vertex u comes before vertex v in the ordering.

Intuition (Kahn's Algorithm - BFS):
- Compute the indegree of each node (number of incoming edges).
- All nodes with indegree 0 can appear first in the ordering.
- Use a queue to perform BFS: repeatedly remove nodes with indegree 0, and 
  decrease the indegree of their neighbors.
- When a neighbor's indegree becomes 0, it is ready to be added to the ordering.
- Continue until all nodes are processed. This gives a valid topological sort.
*/

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

    // Step 3: BFS traversal to generate topological ordering
    vector<int> topo; // vector to store topological order
    while (!q.empty()) {
        int node = q.front();
        q.pop();
        topo.push_back(node);

        // Step 4: Reduce indegree of all adjacent nodes
        for (auto it : adj[node]) {
            indegree[it]--;
            if (indegree[it] == 0) {
                q.push(it); // ready to process next
            }
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
    - Each vertex is processed once when added to the queue.
    - Each edge is visited once when reducing indegrees.

Space Complexity: O(V)
    - For the indegree array, queue, and the vector storing the topological order.
*/
