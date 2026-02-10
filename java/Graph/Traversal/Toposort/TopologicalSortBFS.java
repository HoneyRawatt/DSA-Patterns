import java.util.*;

public class TopologicalSortBFS {

    /*
    Problem Statement:
    Given a Directed Acyclic Graph (DAG) with V vertices and adjacency list `adj`,
    perform a Topological Sort of the vertices. In a topological ordering, for every
    directed edge u -> v, vertex u comes before vertex v in the ordering.

    Intuition (Kahn's Algorithm - BFS):
    - Compute the indegree of each node (number of incoming edges).
    - All nodes with indegree 0 can appear first in the ordering.
    - Use a queue to perform BFS: repeatedly remove nodes with indegree 0, and 
      decrease the indegree of their neighbors.
    - When a neighbor's indegree becomes 0, it is ready to be added to the ordering.
    - Continue until all nodes are processed. This gives a valid topological sort.
    */

    // Function to perform Topological Sort using Kahn's Algorithm (BFS)
    public static List<Integer> topoSort(int V, List<List<Integer>> adj) {
        int[] indegree = new int[V]; // store indegree of each node

        // Step 1: Compute indegree for each node
        for (int i = 0; i < V; i++) {
            for (int neighbor : adj.get(i)) {
                indegree[neighbor]++;
            }
        }

        // Step 2: Push all nodes with indegree 0 into the queue
        Queue<Integer> q = new LinkedList<>();
        for (int i = 0; i < V; i++) {
            if (indegree[i] == 0) {
                q.add(i);
            }
        }

        // Step 3: BFS traversal to generate topological ordering
        List<Integer> topo = new ArrayList<>(); // store topological order
        while (!q.isEmpty()) {
            int node = q.poll();
            topo.add(node);

            // Step 4: Reduce indegree of all adjacent nodes
            for (int neighbor : adj.get(node)) {
                indegree[neighbor]--;
                if (indegree[neighbor] == 0) {
                    q.add(neighbor); // ready to process next
                }
            }
        }

        return topo;
    }

    // ---------------- MAIN FUNCTION ----------------
    public static void main(String[] args) {
        int V = 6;
        List<List<Integer>> adj = new ArrayList<>();

        // Initialize adjacency list
        for (int i = 0; i < V; i++) {
            adj.add(new ArrayList<>());
        }

        // Example DAG
        adj.get(5).add(0);
        adj.get(5).add(2);
        adj.get(4).add(0);
        adj.get(4).add(1);
        adj.get(2).add(3);
        adj.get(3).add(1);

        List<Integer> result = topoSort(V, adj);

        System.out.print("Topological Sort: ");
        for (int x : result) System.out.print(x + " ");
        System.out.println();
    }

    /*
    Time Complexity: O(V + E)
        - Each vertex is processed once when added to the queue.
        - Each edge is visited once when reducing indegrees.

    Space Complexity: O(V)
        - For the indegree array, queue, and the list storing the topological order.
    */
}

