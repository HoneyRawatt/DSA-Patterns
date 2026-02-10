#include <bits/stdc++.h>
using namespace std;

/*
Problem Statement:
Given a Directed Acyclic Graph (DAG) with V vertices and adjacency list `adj[]`, 
perform a Topological Sort of the vertices. In a topological ordering, for every 
directed edge u -> v, vertex u comes before vertex v in the ordering.

Intuition:
- Topological sorting can be done using DFS.
- During DFS, once a node finishes exploring all its neighbors, it is safe to 
  push it onto a stack because all its dependencies are already visited.
- Finally, popping elements from the stack gives the topological ordering.
- Essentially, we are performing a "post-order DFS" and reversing the finish order.
*/

void dfs(int node, int vis[], stack<int>& st, vector<int> adj[]) {
    vis[node] = 1;  // mark current node as visited

    // visit all unvisited neighbors
    for (auto it : adj[node]) {
        if (!vis[it]) 
            dfs(it, vis, st, adj); 
    }

    st.push(node); // push to stack after visiting all neighbors
}

vector<int> topoSort(int V, vector<int> adj[]) {
    int vis[V] = {0}; // visited array
    stack<int> st;    // stack to store topological order

    // run DFS from all unvisited nodes
    for (int i = 0; i < V; i++) {
        if (!vis[i]) 
            dfs(i, vis, st, adj);
    }

    // pop from stack to get topological ordering
    vector<int> ans;
    while (!st.empty()) {
        ans.push_back(st.top());
        st.pop();
    }

    return ans;
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
Time Complexity: 
- O(V + E), where V is the number of vertices and E is the number of edges.
- DFS visits every vertex and every edge exactly once.

Space Complexity: 
- O(V) for the visited array.
- O(V) for the recursion stack in worst case.
- O(V) for the stack storing topological order.
- Overall O(V).
*/
