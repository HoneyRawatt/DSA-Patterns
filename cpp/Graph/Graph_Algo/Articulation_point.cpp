
#include <bits/stdc++.h>
using namespace std;

class Solution {
    int timer = 0;

    // DFS helper for Tarjan’s algorithm
    void dfs(int node, int parent, vector<int> &vis, int tin[], int low[],
             vector<int> &mark, vector<int> adj[]) {

        vis[node] = 1;
        tin[node] = low[node] = timer++;  // discovery & low time
        int child = 0; // count of DFS children (important for root nodes)

        for (auto it : adj[node]) {
            if (it == parent) continue; // skip edge to parent

            if (!vis[it]) {
                dfs(it, node, vis, tin, low, mark, adj);
                low[node] = min(low[node], low[it]); // update low time
                child++;

                // ✅ Articulation condition for non-root nodes
                if (low[it] >= tin[node] && parent != -1) {
                    mark[node] = 1;
                }
            }
            else {
                // back edge case → update low
                low[node] = min(low[node], tin[it]);
            }
        }

        // ✅ Special condition for root node
        if (parent == -1 && child > 1) {
            mark[node] = 1;
        }
    }

  public:
    vector<int> articulationPoints(int n, vector<int> adj[]) {
        vector<int> vis(n, 0);
        int tin[n];
        int low[n];
        vector<int> mark(n, 0);

        // DFS for each component
        for (int i = 0; i < n; i++) {
            if (!vis[i]) {
                dfs(i, -1, vis, tin, low, mark, adj);
            }
        }

        // Collect all articulation points
        vector<int> ans;
        for (int i = 0; i < n; i++) {
            if (mark[i] == 1) ans.push_back(i);
        }

        if (ans.empty()) return {-1};
        return ans;
    }
};

// --------------------- MAIN FUNCTION ---------------------
int main() {
    int n = 5;
    vector<int> adj[n];
    adj[0].push_back(1);
    adj[1].push_back(0);
    adj[1].push_back(2);
    adj[2].push_back(1);
    adj[1].push_back(3);
    adj[3].push_back(1);
    adj[3].push_back(4);
    adj[4].push_back(3);

    Solution sol;
    vector<int> res = sol.articulationPoints(n, adj);

    cout << "Articulation Points: ";
    for (int x : res) cout << x << " ";
    cout << endl;

    return 0;
}

/*
🧠 Intuition:
-------------
Articulation points are vertices whose removal increases the number of connected components.

We use Tarjan’s Algorithm:
- `tin[node]`: time when the node is discovered
- `low[node]`: earliest discovered vertex reachable (including back edges)
- A node is an articulation point if:
  1️⃣ For non-root: there exists a child `v` such that `low[v] >= tin[u]`
  2️⃣ For root: it has more than one DFS child.

📈 Time Complexity:
-------------------
O(V + E) — each edge and vertex visited once during DFS.

🧮 Space Complexity:
--------------------
O(V + E) for adjacency list  
O(V) for `vis`, `tin`, `low`, and `mark`  
➡️ Total: **O(V + E)**
*/
