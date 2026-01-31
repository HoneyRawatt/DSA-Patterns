#include <bits/stdc++.h>
using namespace std;

/*
Approach:
---------
We are detecting a cycle in an undirected graph using BFS.

1️⃣ For each unvisited node, we perform BFS traversal.
2️⃣ We keep track of (node, parent) in the queue.
3️⃣ During traversal:
    - If we find a neighbor that is already visited and 
      it's not the parent of the current node → a cycle exists.
4️⃣ If we finish BFS for all components without finding such a case → no cycle.

Time Complexity:  O(V + E)
Space Complexity: O(V)
*/

bool detect(int src, vector<int> adj[], int vis[]) {
    vis[src] = 1;
    queue<pair<int, int>> q;
    q.push({src, -1});

    while (!q.empty()) {
        int node = q.front().first;
        int parent = q.front().second;
        q.pop();

        for (auto adjacentNode : adj[node]) {
            if (!vis[adjacentNode]) {
                vis[adjacentNode] = 1;
                q.push({adjacentNode, node});
            }
            // If the adjacent node is visited and not parent → cycle found
            else if (parent != adjacentNode) {
                return true;
            }
        }
    }
    return false;
}

bool isCycle(int V, vector<int> adj[]) {
    int vis[V] = {0};

    for (int i = 0; i < V; i++) {
        if (!vis[i]) {
            if (detect(i, adj, vis))
                return true;
        }
    }
    return false;
}

int main() {
    int V = 5;
    vector<int> adj[V];

    // Example: Graph with a cycle
    adj[0].push_back(1);
    adj[1].push_back(0);
    adj[1].push_back(2);
    adj[2].push_back(1);
    adj[2].push_back(3);
    adj[3].push_back(2);
    adj[3].push_back(1); // back edge creates a cycle

    if (isCycle(V, adj))
        cout << "Cycle Detected!" << endl;
    else
        cout << "No Cycle Found." << endl;

    return 0;
}
