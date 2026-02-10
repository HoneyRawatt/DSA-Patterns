package Traversal.DFS;

import java.util.*;

/*
Approach:
---------
We detect a cycle in an undirected graph using DFS.

1️⃣ For every unvisited node, we start a DFS traversal.
2️⃣ During DFS, we pass the current node and its parent.
3️⃣ For each adjacent node:
    - If it is not visited → recursively call DFS.
    - If it is already visited AND not the parent → cycle detected.
4️⃣ If DFS completes without finding a cycle → graph is acyclic.

Time Complexity:  O(V + E)
Space Complexity: O(V + E)
*/

public class CycleDetectionDFS {

    // DFS function to detect cycle in an undirected graph
    static boolean dfs(int node, int parent, int[] vis,
                       ArrayList<ArrayList<Integer>> adj) {

        // Mark current node as visited
        vis[node] = 1;

        // Traverse all adjacent nodes
        for (int adjNode : adj.get(node)) {

            // If adjacent node is not visited, explore it
            if (vis[adjNode] == 0) {
                if (dfs(adjNode, node, vis, adj))
                    return true; // cycle found
            }
            // If visited and not parent → cycle detected
            else if (adjNode != parent) {
                return true;
            }
        }

        // No cycle found from this node
        return false;
    }

    // Function to check cycle in the entire graph
    static boolean isCycle(int V, ArrayList<ArrayList<Integer>> adj) {

        // Visited array
        int[] vis = new int[V];

        // Check all connected components
        for (int i = 0; i < V; i++) {
            if (vis[i] == 0) {
                if (dfs(i, -1, vis, adj))
                    return true;
            }
        }

        // No cycle in any component
        return false;
    }

    public static void main(String[] args) {

        int V = 5;

        // Initialize adjacency list
        ArrayList<ArrayList<Integer>> adj = new ArrayList<>();
        for (int i = 0; i < V; i++) {
            adj.add(new ArrayList<>());
        }

        /*
            Example Undirected Graph:
            0 - 1 - 2 - 3 - 4
                |__________|

            Cycle exists due to edge (4 → 1)
        */

        // Adding edges
        adj.get(0).add(1);
        adj.get(1).add(0);

        adj.get(1).add(2);
        adj.get(2).add(1);

        adj.get(2).add(3);
        adj.get(3).add(2);

        adj.get(3).add(4);
        adj.get(4).add(3);

        adj.get(4).add(1); // creates a cycle
        adj.get(1).add(4);

        // Output result
        System.out.println(isCycle(V, adj) ? "Cycle Found" : "No Cycle");
    }
}

/*
Complexity Analysis:
--------------------
| Type      | Complexity | Explanation                                          |
| --------- | ---------- | ---------------------------------------------------- |
| Time      | O(V + E)   | Each vertex and edge processed once                  |
| Space     | O(V + E)   | Adjacency list + visited array + recursion stack     |
*/

