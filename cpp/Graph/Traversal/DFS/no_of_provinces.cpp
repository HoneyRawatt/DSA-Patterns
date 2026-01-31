#include <bits/stdc++.h>
using namespace std;

/*
DFS Function
Parameters:
- node: current node to start DFS
- adj: adjacency list representation of the graph
- vis: array to track visited nodes
- ls: vector to store DFS traversal order (optional)
Purpose:
- Marks the current node as visited
- Recursively visits all unvisited neighbors
*/
void dfs(int node, vector<int> adj[], int vis[], vector<int> &ls) {
    vis[node] = 1;
    ls.push_back(node);

    for (auto it : adj[node]) {
        if (!vis[it]) {
            dfs(it, adj, vis, ls);
        }
    }
}

/*
numprovinces Function
Parameters:
- adjMatrix: adjacency matrix representing the cities and connections
- v: number of cities (nodes)
Purpose:
- Converts adjacency matrix to adjacency list
- Uses DFS to count connected components (provinces)
- Returns the number of provinces
*/
int numprovinces(vector<vector<int>> adjMatrix, int v) {
    vector<int> graph[v];  // adjacency list

    // Convert adjacency matrix to adjacency list
    for (int i = 0; i < v; i++) {
        for (int j = 0; j < v; j++) {
            if (adjMatrix[i][j] == 1 && i != j) {
                graph[i].push_back(j);  // add edge from i to j
            }
        }
    }

    int vis[v] = {0};  // visited array initialized to 0
    int cnt = 0;       // count of provinces (connected components)

    // Traverse all nodes
    for (int i = 0; i < v; i++) {
        if (!vis[i]) {          // if not visited
            vector<int> ls;     // store DFS traversal (optional)
            cnt++;              // new province found
            dfs(i, graph, vis, ls);
        }
    }

    return cnt;
}

int main() {
    vector<vector<int>> adj = {
        {1, 1, 0},
        {1, 1, 0},
        {0, 0, 1}
    };
    int v = adj.size();
    cout << "Number of provinces: " << numprovinces(adj, v) << endl;
}

/*
Approach:
1. Convert the given adjacency matrix to an adjacency list for easier traversal.
2. Initialize a visited array to keep track of visited cities.
3. For each unvisited city, start a DFS traversal:
   - Mark all cities reachable from it as visited.
   - Increment the province count.
4. Return the total number of provinces (connected components).

Time Complexity:
- Converting adjacency matrix to adjacency list: O(V^2)
- DFS traversal: O(V + E), where V = number of nodes, E = number of edges
- Overall: O(V^2) (since E can be at most V^2 in a dense graph)

Space Complexity:
- Adjacency list: O(V + E) ~ O(V^2) in worst case
- Visited array: O(V)
- DFS recursion stack: O(V)
- Overall: O(V^2)
*/
