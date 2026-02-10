package Traversal.BFS;
import java.util.*;

/*
Approach:
---------
We detect a cycle in an undirected graph using BFS.

1️⃣ For every unvisited node, we start a BFS traversal.
2️⃣ Each queue element stores {currentNode, parentNode}.
3️⃣ While traversing:
    - If an adjacent node is already visited
    - AND it is NOT the parent of the current node
      → a cycle exists.
4️⃣ If BFS finishes for all components without finding such a case,
   then the graph has no cycle.

Time Complexity:  O(V + E)
Space Complexity: O(V)
*/

public class CycleDetectionBFS {

    // BFS function to detect cycle starting from a source node
    static boolean detect(int src, ArrayList<ArrayList<Integer>> adj, int[] vis) {

        // Mark source node as visited
        vis[src] = 1;

        // Queue stores {node, parent}
        Queue<int[]> q = new LinkedList<>();

        // Add source node with parent = -1
        q.offer(new int[]{src, -1});

        // BFS traversal
        while (!q.isEmpty()) {

            int[] curr = q.poll();
            int node = curr[0];
            int parent = curr[1];

            // Traverse all adjacent nodes
            for (int adjacentNode : adj.get(node)) {

                // If adjacent node is not visited
                if (vis[adjacentNode] == 0) {
                    vis[adjacentNode] = 1;
                    q.offer(new int[]{adjacentNode, node});
                }
                // If visited and not parent → cycle detected
                else if (adjacentNode != parent) {
                    return true;
                }
            }
        }

        // No cycle found in this component
        return false;
    }

    // Function to check cycle in the entire graph
    static boolean isCycle(int V, ArrayList<ArrayList<Integer>> adj) {

        // Visited array
        int[] vis = new int[V];

        // Check each connected component
        for (int i = 0; i < V; i++) {
            if (vis[i] == 0) {
                if (detect(i, adj, vis))
                    return true;
            }
        }

        // No cycle found
        return false;
    }

    public static void main(String[] args) {

        int V = 5;

        // Adjacency list initialization
        ArrayList<ArrayList<Integer>> adj = new ArrayList<>();
        for (int i = 0; i < V; i++) {
            adj.add(new ArrayList<>());
        }

        /*
            Example Graph:
            0 - 1 - 2
                |   |
                ----3

            Cycle exists: 1 → 2 → 3 → 1
        */

        // Adding edges (undirected graph)
        adj.get(0).add(1);
        adj.get(1).add(0);

        adj.get(1).add(2);
        adj.get(2).add(1);

        adj.get(2).add(3);
        adj.get(3).add(2);

        adj.get(3).add(1); // Back edge
        adj.get(1).add(3);

        // Cycle check
        if (isCycle(V, adj))
            System.out.println("Cycle Detected!");
        else
            System.out.println("No Cycle Found.");
    }
}
