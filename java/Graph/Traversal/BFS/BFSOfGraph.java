package Traversal.BFS;

import java.util.*;

public class BFSOfGraph {

    /*
     Function: bfsOfGraph
     Purpose: Perform Breadth First Search (BFS) traversal on a graph

     Parameters:
      - n: number of vertices
      - adj: adjacency list of the graph

     Returns:
      - List<Integer>: list of nodes in BFS traversal order
    */
    public static List<Integer> bfsOfGraph(int n, List<List<Integer>> adj) {
        int[] vis = new int[n];          // visited array
        List<Integer> bfs = new ArrayList<>();
        Queue<Integer> q = new LinkedList<>();

        // Start BFS from node 0
        vis[0] = 1;
        q.add(0);

        while (!q.isEmpty()) {
            int node = q.poll();
            bfs.add(node);

            // Traverse all adjacent nodes
            for (int it : adj.get(node)) {
                if (vis[it] == 0) {
                    vis[it] = 1;
                    q.add(it);
                }
            }
        }

        return bfs;
    }

    /*
     Main function: Demonstrates BFS traversal
    */
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        int n = sc.nextInt(); // number of vertices
        int m = sc.nextInt(); // number of edges

        // Adjacency list
        List<List<Integer>> adj = new ArrayList<>();
        for (int i = 0; i < n; i++) {
            adj.add(new ArrayList<>());
        }

        // Building the graph
        for (int i = 0; i < m; i++) {
            int u = sc.nextInt();
            int v = sc.nextInt();

            adj.get(u).add(v);
            adj.get(v).add(u); // remove this line for directed graph
        }

        // BFS traversal
        List<Integer> bfs = bfsOfGraph(n, adj);

        System.out.print("BFS Traversal: ");
        for (int node : bfs) {
            System.out.print(node + " ");
        }
        System.out.println();

        sc.close();
    }
}
