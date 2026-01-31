#include <bits/stdc++.h>
using namespace std;

/*
--------------------------------------------
Function: is_Possible
Purpose : Determines if all courses can be completed
Approach: Kahn’s Algorithm (Topological Sort)
--------------------------------------------
Time Complexity: O(V + E)
Space Complexity: O(V + E)
--------------------------------------------
*/
bool is_Possible(int V, vector<pair<int, int>>& prerequisites) {
    // Step 1: Build adjacency list
    vector<int> adj[V];
    for (auto it : prerequisites) {
        adj[it.first].push_back(it.second);
    }

    // Step 2: Compute indegree of each node
    vector<int> indegree(V, 0);
    for (int i = 0; i < V; i++) {
        for (auto it : adj[i])
            indegree[it]++;
    }

    // Step 3: Push all nodes with indegree 0 into queue
    queue<int> q;
    for (int i = 0; i < V; i++) {
        if (indegree[i] == 0)
            q.push(i);
    }

    // Step 4: BFS traversal (Kahn's algorithm)
    int count = 0;
    while (!q.empty()) {
        int node = q.front();
        q.pop();
        count++;

        for (auto it : adj[node]) {
            indegree[it]--;
            if (indegree[it] == 0)
                q.push(it);
        }
    }

    // Step 5: If all nodes processed → no cycle → possible
    return (count == V);
}

/*
--------------------------------------------
Main function to test is_Possible
--------------------------------------------
*/
int main() {
    int V = 4;
    vector<pair<int, int>> prerequisites1 = {
        {1, 0}, {2, 1}, {3, 2}  // no cycle
    };

    vector<pair<int, int>> prerequisites2 = {
        {1, 0}, {0, 1}  // cycle exists
    };

    cout << "Case 1: " << (is_Possible(V, prerequisites1) ? "Possible" : "Not Possible") << endl;
    cout << "Case 2: " << (is_Possible(V, prerequisites2) ? "Possible" : "Not Possible") << endl;

    return 0;
}
