import java.util.*;

/*
=====================================================
Problem Statement:
=====================================================
You are given a directed graph with V vertices
(numbered from 0 to V-1) represented using an
adjacency list.

A node is called an **eventual safe node** if:
- Every path starting from this node eventually
  leads to a terminal node (node with no outgoing edges).
- No path starting from this node leads to a cycle.

Return all the eventual safe nodes in increasing order.

This is the classic problem:
➡ LeetCode 802 – Eventual Safe States
=====================================================
*/

public class Main {

    /*
    =====================================================
    DFS helper function
    Purpose:
    - Detect cycles in the directed graph
    - Mark nodes as safe or unsafe

    vis states:
    0 → unvisited
    1 → fully processed
    2 → currently in DFS path (used to detect cycles)

    check array:
    1 → safe node
    0 → unsafe node
    =====================================================
    */
    static boolean dfsCheck(int node, List<List<Integer>> adj,
                            int[] vis, int[] check) {

        // Mark node as being in the current DFS path
        vis[node] = 2;

        // Assume node is unsafe initially
        check[node] = 0;

        // Explore all outgoing edges
        for (int it : adj.get(node)) {

            // If the adjacent node is unvisited
            if (vis[it] == 0) {
                if (dfsCheck(it, adj, vis, check)) {
                    // Cycle detected downstream
                    check[node] = 0;
                    return true;
                }
            }
            // If adjacent node is in current DFS path → cycle
            else if (vis[it] == 2) {
                check[node] = 0;
                return true;
            }
        }

        // No cycle detected from this node
        vis[node] = 1;   // mark as processed
        check[node] = 1; // mark as safe

        return false;
    }

    /*
    =====================================================
    Function: eventualSafeNodes
    Purpose:
    - Runs DFS for each node
    - Identifies all nodes that do not lead to cycles
    =====================================================
    */
    static List<Integer> eventualSafeNodes(int V, List<List<Integer>> adj) {

        int[] vis = new int[V];    // DFS state array
        int[] check = new int[V];  // Safe/unsafe marker
        List<Integer> safeNodes = new ArrayList<>();

        // Run DFS for all nodes (handles disconnected graph)
        for (int i = 0; i < V; i++) {
            if (vis[i] == 0) {
                dfsCheck(i, adj, vis, check);
            }
        }

        // Collect all safe nodes
        for (int i = 0; i < V; i++) {
            if (check[i] == 1)
                safeNodes.add(i);
        }

        return safeNodes;
    }

    // ---------------- MAIN FUNCTION ----------------
    public static void main(String[] args) {

        int V = 7;
        List<List<Integer>> adj = new ArrayList<>();

        for (int i = 0; i < V; i++) {
            adj.add(new ArrayList<>());
        }

        /*
            Example Graph:
            0 → 1 → 3 → 0   (cycle)
            ↓
            2 → 5          (safe)
            4 → 5          (safe)
            6              (safe)
        */

        adj.get(0).add(1);
        adj.get(0).add(2);
        adj.get(1).add(2);
        adj.get(1).add(3);
        adj.get(2).add(5);
        adj.get(3).add(0);
        adj.get(4).add(5);
        // 5 and 6 are terminal nodes

        List<Integer> result = eventualSafeNodes(V, adj);

        System.out.print("Safe Nodes: ");
        for (int node : result) {
            System.out.print(node + " ");
        }
    }
}

/*
=====================================================
Time Complexity:
=====================================================
O(V + E)
- Each vertex is visited once
- Each edge is explored once

=====================================================
Space Complexity:
=====================================================
O(V)
- vis[] and check[] arrays
- DFS recursion stack
=====================================================
*/
