#include <bits/stdc++.h>
using namespace std;

// Function to check if a graph is bipartite using BFS
bool isBipartite(int V, vector<int> adj[]) {
    vector<int> color(V, -1); // -1: uncolored

    // Loop through all vertices to handle disconnected components
    for (int start = 0; start < V; start++) {
        if (color[start] == -1) {
            queue<int> q;
            q.push(start);
            color[start] = 0; // Assign first color

            while (!q.empty()) {
                int node = q.front();
                q.pop();

                for (auto it : adj[node]) {
                    if (color[it] == -1) {
                        color[it] = !color[node]; // Assign opposite color
                        q.push(it);
                    } 
                    else if (color[it] == color[node]) {
                        // Adjacent nodes have same color → not bipartite
                        return false;
                    }
                }
            }
        }
    }
    return true;
}

int main() {
    // Example 1: Bipartite graph
    int V1 = 4;
    vector<int> adj1[V1];
    adj1[0] = {1, 3};
    adj1[1] = {0, 2};
    adj1[2] = {1, 3};
    adj1[3] = {0, 2};

    cout << "Graph 1: " << (isBipartite(V1, adj1) ? "Bipartite" : "Not Bipartite") << endl;
    // Output: Bipartite

    // Example 2: Not bipartite graph
    int V2 = 3;
    vector<int> adj2[V2];
    adj2[0] = {1, 2};
    adj2[1] = {0, 2};
    adj2[2] = {0, 1};

    cout << "Graph 2: " << (isBipartite(V2, adj2) ? "Bipartite" : "Not Bipartite") << endl;
    // Output: Not Bipartite

    return 0;
}
/*
Time Complexity: O(V + E)
    - Each vertex is visited once
    - Each edge is checked at most twice
Space Complexity: O(V)
    - For color array
    - For queue storing vertices during BFS
*/
