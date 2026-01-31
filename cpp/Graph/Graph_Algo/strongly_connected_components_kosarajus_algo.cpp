#include <bits/stdc++.h>
using namespace std;

// Step 1: DFS to get finishing order
void dfs1(int node, vector<int>& vis, vector<int> adj[], stack<int>& st) {
    vis[node] = 1;
    for (auto it : adj[node]) {
        if (!vis[it]) {
            dfs1(it, vis, adj, st);
        }
    }
    st.push(node);
}

// Step 2: DFS on the transposed graph
void dfs2(int node, vector<int>& vis, vector<int> adjT[]) {
    vis[node] = 1;
    for (auto it : adjT[node]) {
        if (!vis[it]) {
            dfs2(it, vis, adjT);
        }
    }
}

// Step 3: Kosaraju’s algorithm
int kosaraju(int V, vector<int> adj[]) {
    vector<int> vis(V, 0);
    stack<int> st;

    // 1️⃣ Fill stack with vertices in finishing order
    for (int i = 0; i < V; i++) {
        if (!vis[i]) {
            dfs1(i, vis, adj, st);
        }
    }

    // 2️⃣ Transpose the graph
    vector<int> adjT[V];
    for (int i = 0; i < V; i++) {
        for (auto it : adj[i]) {
            adjT[it].push_back(i);
        }
    }

    // 3️⃣ DFS on transposed graph in stack order
    for (int i = 0; i < V; i++) vis[i] = 0;
    int scc = 0;

    while (!st.empty()) {
        int node = st.top();
        st.pop();
        if (!vis[node]) {
            scc++;
            dfs2(node, vis, adjT);
        }
    }

    return scc;
}

// Driver
int main() {
    int V = 5;
    vector<int> adj[V];

    // Example graph
    adj[0] = {1};
    adj[1] = {2};
    adj[2] = {0, 3};
    adj[3] = {4};
    adj[4] = {};

    cout << "Number of Strongly Connected Components: "
         << kosaraju(V, adj) << endl;

    return 0;
}

// | Type      | Complexity                                               |
// | --------- | -------------------------------------------------------- |
// | **Time**  | O(V + E) → DFS + Transpose + DFS                         |
// | **Space** | O(V + E) → For adjacency lists, stack, and visited array |
