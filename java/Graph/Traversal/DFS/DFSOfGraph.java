package Traversal.DFS;

import java.util.*;

public class DFSOfGraph {

    /*
     Function: dfs
     Purpose: Perform Depth First Search (DFS) recursively from a given start node.
    */
    public static void dfs(int node, List<List<Integer>> adj, int[] vis, List<Integer> dfsResult) {
        vis[node] = 1;              // mark current node as visited
        dfsResult.add(node);        // add node to DFS traversal list

        for (int it : adj.get(node)) {
            if (vis[it] == 0) {
                dfs(it, adj, vis, dfsResult);
            }
        }
    }

    /*
     Main function to demonstrate DFS traversal
    */
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        int n = sc.nextInt(); // number of vertices
        int m = sc.nextInt(); // number of edges

        // Adjacency list (1-based indexing supported)
        List<List<Integer>> adj = new ArrayList<>();
        for (int i = 0; i <= n; i++) {
            adj.add(new ArrayList<>());
        }

        // Building adjacency list
        for (int i = 0; i < m; i++) {
            int u = sc.nextInt();
            int v = sc.nextInt();

            adj.get(u).add(v);
            adj.get(v).add(u); // remove this line for directed graph
        }

        int[] vis = new int[n + 1]; // visited array
        List<Integer> dfsResult = new ArrayList<>();

        // Start DFS from node 0
        dfs(0, adj, vis, dfsResult);

        System.out.print("DFS Traversal: ");
        for (int node : dfsResult) {
            System.out.print(node + " ");
        }
        System.out.println();

        sc.close();
    }
}
