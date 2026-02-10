package Traversal.DFS;

import java.util.*;

/*
====================================================
PROBLEM STATEMENT:
====================================================
You are given an adjacency matrix representing connections
between cities. A group of directly or indirectly connected
cities forms a "province".

Your task is to find the total number of provinces.

- adjMatrix[i][j] = 1 means city i is directly connected to city j
- adjMatrix[i][i] = 1 (a city is connected to itself)

This is essentially the problem of counting
CONNECTED COMPONENTS in an undirected graph.
====================================================
*/

public class NumberOfProvinces {

    /*
    ----------------------------------------------------
    DFS Function
    ----------------------------------------------------
    Parameters:
    - node : current node to start DFS
    - adj  : adjacency list of the graph
    - vis  : visited array to mark nodes
    - list : stores DFS traversal order (optional)

    Purpose:
    - Marks the current node as visited
    - Recursively visits all unvisited neighbors
    ----------------------------------------------------
    */
    static void dfs(int node, List<List<Integer>> adj, int[] vis, List<Integer> list) {
        vis[node] = 1;          // mark node as visited
        list.add(node);         // add node to traversal list

        for (int it : adj.get(node)) {
            if (vis[it] == 0) {
                dfs(it, adj, vis, list);
            }
        }
    }

    /*
    ----------------------------------------------------
    numProvinces Function
    ----------------------------------------------------
    Parameters:
    - adjMatrix : adjacency matrix representation
    - v         : number of cities (vertices)

    Purpose:
    - Converts adjacency matrix to adjacency list
    - Uses DFS to count connected components (provinces)
    - Returns total number of provinces
    ----------------------------------------------------
    */
    static int numProvinces(int[][] adjMatrix, int v) {

        // Step 1: Convert adjacency matrix to adjacency list
        List<List<Integer>> graph = new ArrayList<>();
        for (int i = 0; i < v; i++) {
            graph.add(new ArrayList<>());
        }

        for (int i = 0; i < v; i++) {
            for (int j = 0; j < v; j++) {
                if (adjMatrix[i][j] == 1 && i != j) {
                    graph.get(i).add(j);
                }
            }
        }

        // Step 2: Visited array
        int[] vis = new int[v];
        int count = 0; // number of provinces

        // Step 3: DFS on each unvisited node
        for (int i = 0; i < v; i++) {
            if (vis[i] == 0) {
                List<Integer> list = new ArrayList<>(); // optional DFS traversal
                count++; // new province found
                dfs(i, graph, vis, list);
            }
        }

        return count;
    }

    /*
    ----------------------------------------------------
    Main Method
    ----------------------------------------------------
    */
    public static void main(String[] args) {
        int[][] adj = {
            {1, 1, 0},
            {1, 1, 0},
            {0, 0, 1}
        };

        int v = adj.length;

        System.out.println("Number of provinces: " + numProvinces(adj, v));
    }
}

/*
====================================================
INTUITION:
====================================================
- Each province is a connected component.
- If we start DFS from an unvisited city, all cities
  reachable from it belong to the same province.
- Counting how many times we start DFS gives
  the number of provinces.

====================================================
APPROACH:
====================================================
1. Convert the adjacency matrix into an adjacency list
   (easier to traverse using DFS).
2. Maintain a visited array to track visited cities.
3. Loop through each city:
   - If not visited, start DFS.
   - Mark all connected cities as visited.
   - Increase province count.
4. Return the total count.

====================================================
TIME COMPLEXITY:
====================================================
- Converting adjacency matrix to adjacency list: O(V²)
- DFS traversal: O(V + E)
- Overall Time Complexity: O(V²)
  (since E can be up to V² in a dense graph)

====================================================
SPACE COMPLEXITY:
====================================================
- Adjacency list: O(V + E) → O(V²) in worst case
- Visited array: O(V)
- DFS recursion stack: O(V)

Overall Space Complexity: O(V²)
====================================================
*/

