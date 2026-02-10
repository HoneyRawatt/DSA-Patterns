package Traversal.BFS;

import java.util.*;

/*
=====================================================
Problem Statement:
=====================================================
You are given an undirected graph with V vertices and
an adjacency list representation.

A graph is called **bipartite** if its vertices can be
divided into two disjoint sets such that:
- No two adjacent vertices belong to the same set
- Each edge connects vertices from different sets

The graph may be disconnected.
Your task is to determine whether the graph is bipartite.
*/

/*
=====================================================
Intuition:
=====================================================
- A graph is bipartite if it can be colored using only
  two colors such that no two adjacent nodes have
  the same color.
- BFS colors nodes level by level.
- Adjacent nodes must always receive opposite colors.

Key idea:
➡ If two adjacent nodes ever get the same color,
   the graph is NOT bipartite.
*/

/*
=====================================================
Approach (BFS):
=====================================================
1️⃣ Initialize a color array with -1 (uncolored).
2️⃣ Traverse all vertices to handle disconnected components.
3️⃣ For every uncolored vertex:
    - Start BFS
    - Assign an initial color (0)
4️⃣ For each visited node:
    - Assign opposite color to its neighbors
    - If a conflict occurs, return false
5️⃣ If BFS finishes without conflicts, the graph is bipartite.
*/

public class BipartiteGraphBFS {

    // Function to check if a graph is bipartite using BFS
    static boolean isBipartite(int V, List<List<Integer>> adj) {

        // Color array: -1 → uncolored, 0 and 1 → two colors
        int[] color = new int[V];
        Arrays.fill(color, -1);

        // Loop through all vertices to handle disconnected components
        for (int start = 0; start < V; start++) {

            // If the node is not colored, start BFS
            if (color[start] == -1) {

                Queue<Integer> q = new LinkedList<>();
                q.add(start);

                // Assign first color
                color[start] = 0;

                // Standard BFS traversal
                while (!q.isEmpty()) {
                    int node = q.poll();

                    // Visit all adjacent nodes
                    for (int it : adj.get(node)) {

                        // If adjacent node is uncolored
                        if (color[it] == -1) {
                            color[it] = 1 - color[node]; // assign opposite color
                            q.add(it);
                        }
                        // If adjacent node has same color → conflict
                        else if (color[it] == color[node]) {
                            return false;
                        }
                    }
                }
            }
        }
        return true;
    }

    /*
    =====================================================
    Time & Space Complexity:
    =====================================================

    ⏱ Time Complexity: O(V + E)
    - Each vertex is visited once
    - Each edge is checked at most twice

    📦 Space Complexity: O(V)
    - Color array
    - Queue used for BFS
    */

    public static void main(String[] args) {

        /*
            Example 1: Bipartite Graph
            Graph:
            0 -- 1
            |    |
            3 -- 2
        */
        int V1 = 4;
        List<List<Integer>> adj1 = new ArrayList<>();
        for (int i = 0; i < V1; i++) adj1.add(new ArrayList<>());

        adj1.get(0).add(1);
        adj1.get(0).add(3);
        adj1.get(1).add(0);
        adj1.get(1).add(2);
        adj1.get(2).add(1);
        adj1.get(2).add(3);
        adj1.get(3).add(0);
        adj1.get(3).add(2);

        System.out.println(
            "Graph 1: " + (isBipartite(V1, adj1) ? "Bipartite" : "Not Bipartite")
        );

        /*
            Example 2: Not Bipartite Graph (Odd Cycle)
            Graph:
            0
           / \
          1---2
        */
        int V2 = 3;
        List<List<Integer>> adj2 = new ArrayList<>();
        for (int i = 0; i < V2; i++) adj2.add(new ArrayList<>());

        adj2.get(0).add(1);
        adj2.get(0).add(2);
        adj2.get(1).add(0);
        adj2.get(1).add(2);
        adj2.get(2).add(0);
        adj2.get(2).add(1);

        System.out.println(
            "Graph 2: " + (isBipartite(V2, adj2) ? "Bipartite" : "Not Bipartite")
        );
    }
}
