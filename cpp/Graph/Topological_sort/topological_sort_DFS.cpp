#include <bits/stdc++.h>
using namespace std;

void dfs(int node, int vis[], stack<int>& st, vector<int> adj[]) {
    vis[node] = 1;
    for (auto it : adj[node]) {
        if (!vis[it]) dfs(it, vis, st, adj); 
    }
    st.push(node); 
}

vector<int> topoSort(int V, vector<int> adj[]) {
    int vis[V] = {0};
    stack<int> st;

    for (int i = 0; i < V; i++) {
        if (!vis[i]) dfs(i, vis, st, adj);
    }

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
Time Complexity: O(V + E)
Space Complexity: O(V) (for visited + recursion stack)
*/
