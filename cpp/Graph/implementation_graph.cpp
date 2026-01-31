#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m; // n = number of nodes, m = number of edges

    // -------------------------------
    // 1️⃣ Adjacency Matrix (Unweighted)
    // -------------------------------
    vector<vector<int>> adjMatrix(n + 1, vector<int>(n + 1, 0));

    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;

        // Undirected graph
        adjMatrix[u][v] = 1;
        adjMatrix[v][u] = 1;

        // For directed graph → remove the second line
    }

    // -------------------------------
    // 2️⃣ Adjacency List (Unweighted)
    // -------------------------------
    vector<vector<int>> adjList(n + 1);

    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;

        // Undirected graph
        adjList[u].push_back(v);
        adjList[v].push_back(u);

        // For directed graph → remove the second push_back
    }

    // -------------------------------
    // 3️⃣ Adjacency Matrix (Weighted)
    // -------------------------------
    vector<vector<int>> adjMatrixWt(n + 1, vector<int>(n + 1, 0));

    for (int i = 0; i < m; i++) {
        int u, v, wt;
        cin >> u >> v >> wt;

        // Undirected graph
        adjMatrixWt[u][v] = wt;
        adjMatrixWt[v][u] = wt;

        // For directed graph → remove the second line
    }

    // -------------------------------
    // 4️⃣ Adjacency List (Weighted)
    // -------------------------------
    vector<vector<pair<int, int>>> adjListWt(n + 1);

    for (int i = 0; i < m; i++) {
        int u, v, wt;
        cin >> u >> v >> wt;

        // Undirected graph
        adjListWt[u].push_back({v, wt});
        adjListWt[v].push_back({u, wt});

        // For directed graph → remove the second push_back
    }

    return 0;
}

// | Representation        | Data Structure                                      | Space Complexity | Suitable for                          |
// | --------------------- | --------------------------------------------------- | ---------------- | ------------------------------------- |
// | **Adjacency Matrix**  | `vector<vector<int>> adj(n+1, vector<int>(n+1, 0))` | O(V²)            | Dense graphs                          |
// | **Adjacency List**    | `vector<vector<int>> adj(n+1)`                      | O(V + 2E)        | Sparse graphs                         |
// | **Weighted (Matrix)** | Store weight at `adj[u][v] = wt`                    | O(V²)            | When quick edge lookups matter        |
// | **Weighted (List)**   | `vector<vector<pair<int,int>>> adj(n+1)`            | O(V + 2E)        | When edges are few and memory matters |
