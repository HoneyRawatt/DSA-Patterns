import java.util.*;

/*
=====================================================
Problem Statement:
=====================================================
You are given an undirected graph with V vertices and
an adjacency list representation.

A graph is called **bipartite** if its vertices can be
divided into two disjoint sets such that:
- Every edge connects a vertex from one set to the other
- No two adjacent vertices belong to the same set

The graph may be disconnected.
Your task is to check whether the graph is bipartite.
*/

/*
=====================================================
Intuition:
=====================================================
- A graph is bipartite if it can be colored using only
  two colors such that no two adjacent vertices have
  the same color.
- This is equivalent to checking whether the graph
  contains an odd-length cycle.
- We use DFS to try coloring adjacent nodes with
  alternate colors.

Key idea:
➡ If two adjacent nodes ever get the same color,
   the graph is NOT bipartite.
*/

public class BipartiteGraph {

    /*
    =====================================================
    DFS Function:
    =====================================================
    Purpose:
    - Try to color the graph using two colors (0 and 1)
    - Recursively color adjacent nodes with alternate colors
    - Detect conflicts in coloring

    Parameters:
    - node  : current node
    - col   : color to assign to current node
    - color : color array (-1 = unvisited)
    - adj   : adjacency list

    Time Complexity:
    - O(V + E)

    Space Complexity:
    - O(V) recursion stack + O(V) color array
    */
    static boolean dfs(int node, int col, int[] color, List<List<Integer>> adj) {

        // Assign color to current node
        color[node] = col;

        // Traverse all adjacent nodes
        for (int it : adj.get(node)) {

            // If adjacent node is uncolored
            if (color[it] == -1) {

                // Assign alternate color
                if (!dfs(it, 1 - col, color, adj))
                    return false;
            }
            // If adjacent node has same color → conflict
            else if (color[it] == col) {
                return false;
            }
        }
        return true;
    }

    /*
    =====================================================
    Function: isBipartite
    =====================================================
    Purpose:
    - Check whether the entire graph is bipartite
    - Works even if the graph is disconnected

    Approach:
    1️⃣ Initialize all vertices as uncolored (-1)
    2️⃣ For every vertex:
        - If unvisited, start DFS coloring
    3️⃣ If any conflict occurs → return false
    */
    static boolean isBipartite(int V, List<List<Integer>> adj) {

        // Color array initialized to -1 (unvisited)
        int[] color = new int[V];
        Arrays.fill(color, -1);

        // Check all components
        for (int i = 0; i < V; i++) {
            if (color[i] == -1) {
                if (!dfs(i, 0, color, adj))
                    return false;
            }
        }
        return true;
    }

    /*
    =====================================================
    Overall Time & Space Complexity:
    =====================================================

    ⏱ Time Complexity:
    - O(V + E)

    📦 Space Complexity:
    - O(V)
    */

    public static void main(String[] args) {

        /*
            Example 1: Bipartite Graph
            Graph:
            0 -- 1
            |    |
            3 -- 2
        */
        int V = 4;
        List<List<Integer>> adj = new ArrayList<>();

        for (int i = 0; i < V; i++)
            adj.add(new ArrayList<>());

        adj.get(0).add(1);
        adj.get(0).add(3);
        adj.get(1).add(0);
        adj.get(1).add(2);
        adj.get(2).add(1);
        adj.get(2).add(3);
        adj.get(3).add(0);
        adj.get(3).add(2);

        System.out.println(
            isBipartite(V, adj)
                ? "Graph is Bipartite"
                : "Graph is Not Bipartite"
        );

        /*
            Example 2: Not Bipartite (Odd Cycle)
            Graph:
            0
           / \
          1---2
        */
        int V2 = 3;
        List<List<Integer>> adj2 = new ArrayList<>();

        for (int i = 0; i < V2; i++)
            adj2.add(new ArrayList<>());

        adj2.get(0).add(1);
        adj2.get(0).add(2);
        adj2.get(1).add(0);
        adj2.get(1).add(2);
        adj2.get(2).add(0);
        adj2.get(2).add(1);

        System.out.println(
            isBipartite(V2, adj2)
                ? "Graph is Bipartite"
                : "Graph is Not Bipartite"
        );
    }
}
