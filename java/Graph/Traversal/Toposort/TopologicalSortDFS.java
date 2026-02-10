import java.util.*;

// ---------------- TOPOLOGICAL SORT USING DFS ----------------
public class TopologicalSortDFS {

    /*
    Problem Statement:
    Given a Directed Acyclic Graph (DAG) with V vertices and adjacency list `adj`, 
    perform a Topological Sort of the vertices. In a topological ordering, for every 
    directed edge u -> v, vertex u comes before vertex v in the ordering.

    Intuition:
    - Use DFS for topological sorting.
    - When DFS finishes exploring all neighbors of a node, push it to a stack.
    - Popping elements from the stack gives the topological ordering.
    - Essentially, it's "post-order DFS" and reversing the finish order.
    */

    // DFS helper function
    private static void dfs(int node, boolean[] visited, Stack<Integer> stack, List<List<Integer>> adj) {
        visited[node] = true;

        // visit all unvisited neighbors
        for (int neighbor : adj.get(node)) {
            if (!visited[neighbor]) {
                dfs(neighbor, visited, stack, adj);
            }
        }

        stack.push(node); // push to stack after visiting all neighbors
    }

    // Function to perform topological sort
    public static List<Integer> topoSort(int V, List<List<Integer>> adj) {
        boolean[] visited = new boolean[V]; // visited array
        Stack<Integer> stack = new Stack<>(); // stack to store topological order

        // run DFS from all unvisited nodes
        for (int i = 0; i < V; i++) {
            if (!visited[i]) {
                dfs(i, visited, stack, adj);
            }
        }

        // pop from stack to get topological ordering
        List<Integer> result = new ArrayList<>();
        while (!stack.isEmpty()) {
            result.add(stack.pop());
        }

        return result;
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
    Time Complexity: 
    - O(V + E), where V is the number of vertices and E is the number of edges.
    - DFS visits every vertex and every edge exactly once.

    Space Complexity: 
    - O(V) for the visited array.
    - O(V) for the recursion stack in worst case.
    - O(V) for the stack storing topological order.
    - Overall O(V).
    */
}
