#include <bits/stdc++.h>
using namespace std;

/*
=====================================================
Problem Statement:
-----------------------------------------------------
You are given:
- An integer V representing the number of courses.
- A list of prerequisite pairs where
  (a, b) means course 'a' depends on course 'b'
  i.e., you must complete 'b' before 'a'.

Task:
Determine whether it is possible to finish all V courses.

Key Observation:
- This is equivalent to checking whether the directed graph
  formed by prerequisites contains a cycle.
- If a cycle exists → courses cannot be completed.
- If no cycle exists → all courses can be completed.

=====================================================
Intuition / Idea:
-----------------------------------------------------
- Model courses as nodes in a directed graph.
- A prerequisite (a, b) is an edge: b → a
- If the graph has a cycle, some courses depend on each
  other infinitely → impossible to complete.

To detect cycles in a directed graph efficiently:
➡ Use Kahn’s Algorithm (BFS-based Topological Sort)

Why Kahn’s Algorithm?
- In a DAG, at least one node has indegree = 0.
- Repeatedly remove such nodes and reduce indegrees.
- If all nodes are removed → no cycle.
- If some nodes remain → cycle exists.

=====================================================
Time Complexity:
-----------------------------------------------------
- Building adjacency list: O(E)
- Calculating indegrees: O(V + E)
- BFS traversal (Kahn’s Algorithm): O(V + E)

Overall Time Complexity: O(V + E)

=====================================================
Space Complexity:
-----------------------------------------------------
- Adjacency list: O(V + E)
- Indegree array: O(V)
- Queue: O(V)

Overall Space Complexity: O(V + E)
=====================================================
*/

bool is_Possible(int V, vector<pair<int, int>>& prerequisites) {

    // Step 1: Build adjacency list
    // Edge: prerequisite.second → prerequisite.first
    vector<int> adj[V];
    for (auto it : prerequisites) {
        adj[it.second].push_back(it.first);
    }

    // Step 2: Compute indegree of each node
    // indegree[i] = number of prerequisites for course i
    vector<int> indegree(V, 0);
    for (int i = 0; i < V; i++) {
        for (auto it : adj[i]) {
            indegree[it]++;
        }
    }

    // Step 3: Push all courses with indegree 0 into queue
    // These courses have no prerequisites and can be taken first
    queue<int> q;
    for (int i = 0; i < V; i++) {
        if (indegree[i] == 0)
            q.push(i);
    }

    // Step 4: BFS traversal (Kahn's Algorithm)
    int count = 0; // number of courses processed

    while (!q.empty()) {
        int node = q.front();
        q.pop();
        count++;

        // Reduce indegree of neighboring courses
        for (auto it : adj[node]) {
            indegree[it]--;
            if (indegree[it] == 0)
                q.push(it);
        }
    }

    // Step 5:
    // If all V courses are processed → no cycle → possible
    // Else → cycle exists → not possible
    return (count == V);
}

/*
--------------------------------------------
Main function to test is_Possible
--------------------------------------------
*/
int main() {
    int V = 4;

    // Case 1: No cycle (possible to complete all courses)
    vector<pair<int, int>> prerequisites1 = {
        {1, 0}, {2, 1}, {3, 2}
    };

    // Case 2: Cycle exists (not possible)
    vector<pair<int, int>> prerequisites2 = {
        {1, 0}, {0, 1}
    };

    cout << "Case 1: "
         << (is_Possible(V, prerequisites1) ? "Possible" : "Not Possible")
         << endl;

    cout << "Case 2: "
         << (is_Possible(V, prerequisites2) ? "Possible" : "Not Possible")
         << endl;

    return 0;
}
