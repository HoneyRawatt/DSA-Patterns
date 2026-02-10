import java.util.*;

/*
=====================================================
Cycle Detection in a Directed Graph using DFS
=====================================================

We use **3-state coloring**:
0 → unvisited
1 → completely processed
2 → currently in DFS recursion path

If we ever encounter a node with state `2`,
it means a **back edge** exists → cycle detected.
*/
public class DirectedGraphCycle {

    // DFS helper function to detect cycle
    static boolean dfsCheck(int node, List<List<Integer>> adj, int[] vis) {

        // Mark node as part of current DFS path
        vis[node] = 2;

        // Traverse all adjacent nodes
        for (int it : adj.get(node)) {

            // If adjacent node is unvisited
            if (vis[it] == 0) {
                if (dfsCheck(it, adj, vis))
                    return true; // cycle found
            }
            // If adjacent node is already in current DFS path
            else if (vis[it] == 2) {
                // Back edge detected
                return true;
            }
        }

        // Mark node as fully processed
        vis[node] = 1;
        return false;
    }

    /*
    =====================================================
    Function to check cycle in the entire graph
    =====================================================
    Handles disconnected components
    */
    static boolean isCycle(int V, List<List<Integer>> adj) {

        // Visited array: 0 = unvisited, 1 = processed, 2 = in DFS path
        int[] vis = new int[V];

        // Check each vertex
        for (int i = 0; i < V; i++) {
            if (vis[i] == 0) {
                if (dfsCheck(i, adj, vis))
                    return true;
            }
        }
        return false;
    }

    // ---------------- MAIN FUNCTION ----------------
    public static void main(String[] args) {

        int V = 4;

        // Adjacency list initialization
        List<List<Integer>> adj = new ArrayList<>();
        for (int i = 0; i < V; i++) {
            adj.add(new ArrayList<>());
        }

        /*
            Example Directed Graph:
            0 → 1 → 2
            ↑         |
            └─────────┘

            Node 3 is isolated
        */
        adj.get(0).add(1);
        adj.get(1).add(2);
        adj.get(2).add(0); // creates a cycle
        // adj.get(3) remains empty (isolated)

        // Cycle check
        if (isCycle(V, adj))
            System.out.println("Graph contains a cycle");
        else
            System.out.println("Graph does not contain a cycle");
    }
}

/*
=====================================================
Time Complexity:
=====================================================
O(V + E)
- Each vertex visited once
- Each edge checked once

=====================================================
Space Complexity:
=====================================================
O(V)
- Visited array
- Recursion stack
*/

