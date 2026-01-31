#include <bits/stdc++.h>
using namespace std;

/*
----------------------------------------
🧠 Approach: Dijkstra’s Algorithm using Set
----------------------------------------
We find the shortest distance from a source vertex `S` to all other vertices
in a weighted graph (with non-negative edge weights).

We use:
- A set of pairs (distance, node) — works like a priority queue but allows easy deletion.
- A distance array to track the minimum distance to each node.

Whenever we find a shorter path to a neighbor, we:
1. Remove the previous pair (if it exists) from the set.
2. Update the distance.
3. Insert the new pair (distance, node) into the set.

----------------------------------------
📊 Time Complexity Analysis
----------------------------------------
Let:
- V = number of vertices
- E = number of edges

Each edge (u, v) is processed at most once.

Operations:
- Insertion/erasure in `set`: O(log V)
- Traversing all edges: O(E)

🔹 Total Time = O(E * log V)

----------------------------------------
💾 Space Complexity Analysis
----------------------------------------
- dist[]: O(V)
- set (stores at most V elements): O(V)
- adjacency list: O(V + E)

🔹 Total Space = O(V + E)
*/

// Dijkstra’s algorithm function
vector<int> dijkstra(int V, vector<vector<int>> adj[], int S) {
    // Set stores {distance, node}
    set<pair<int, int>> st;

    // Initialize all distances as infinity
    vector<int> dist(V, 1e9);
    dist[S] = 0;

    // Insert source node with distance 0
    st.insert({0, S});

    // Loop until all reachable nodes are processed
    while (!st.empty()) {
        // Fetch node with the smallest distance
        auto it = *(st.begin());
        int dis = it.first;
        int node = it.second;
        st.erase(it);

        // Traverse all adjacent nodes
        for (auto adjPair : adj[node]) {
            int adjNode = adjPair[0];
            int edgeWeight = adjPair[1];

            // Relaxation step
            if (dis + edgeWeight < dist[adjNode]) {
                // If an entry already exists, erase it
                if (dist[adjNode] != 1e9)
                    st.erase({dist[adjNode], adjNode});

                // Update distance
                dist[adjNode] = dis + edgeWeight;

                // Insert the updated pair
                st.insert({dist[adjNode], adjNode});
            }
        }
    }
    return dist;
}

/*
----------------------------------------
🧩 Function Complexity Summary
----------------------------------------
1️⃣ dijkstra() :
    ⏱️ Time: O(E * log V)
    💾 Space: O(V + E)

2️⃣ main() :
    Handles input/output and builds the adjacency list.
----------------------------------------
*/

// Driver Code
int main() {
    int V, E;
    cout << "Enter number of vertices (V): ";
    cin >> V;
    cout << "Enter number of edges (E): ";
    cin >> E;

    vector<vector<int>> adj[V];

    cout << "Enter edges (u v w):" << endl;
    for (int i = 0; i < E; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].push_back({v, w});
        adj[v].push_back({u, w}); // comment this line for directed graph
    }

    int S;
    cout << "Enter source vertex: ";
    cin >> S;

    // Compute shortest paths
    vector<int> res = dijkstra(V, adj, S);

    cout << "\nShortest distances from source " << S << ":\n";
    for (int i = 0; i < V; i++) {
        cout << "Node " << i << " -> Distance = ";
        if (res[i] == 1e9)
            cout << "INF";
        else
            cout << res[i];
        cout << endl;
    }

    return 0;
}

/*
----------------------------------------
✅ Total Overall Complexity:
----------------------------------------
⏱️ Time: O(E * log V)
💾 Space: O(V + E)
----------------------------------------
*/
