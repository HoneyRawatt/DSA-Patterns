import java.util.*;

/*
--------------------------------------------
Function: isCyclicKahn
Purpose : Detects if a Directed Graph contains a cycle
Approach: Kahn's Algorithm (BFS based Topological Sort)
--------------------------------------------
Time Complexity:
    - Building indegree array: O(V + E)
    - BFS traversal: O(V + E)
    => Overall: O(V + E)

Space Complexity:
    - indegree array: O(V)
    - queue: O(V)
    => Overall: O(V)
--------------------------------------------
*/
public class CycleDetectionKahn {

    static boolean isCyclicKahn(int V, ArrayList<ArrayList<Integer>> adj) {
        int[] indegree = new int[V];

        // Step 1: Compute indegree of each node
        for (int i = 0; i < V; i++) {
            for (int it : adj.get(i)) {
                indegree[it]++;
            }
        }

        // Step 2: Push all nodes with indegree 0 into the queue
        Queue<Integer> q = new LinkedList<>();
        for (int i = 0; i < V; i++) {
            if (indegree[i] == 0) {
                q.add(i);
            }
        }

        // Step 3: Process nodes in BFS manner
        int count = 0;
        while (!q.isEmpty()) {
            int node = q.poll();
            count++; // count of processed nodes

            // Reduce indegree of neighbors
            for (int it : adj.get(node)) {
                indegree[it]--;
                if (indegree[it] == 0) {
                    q.add(it);
                }
            }
        }

        // Step 4: If count != V → cycle exists
        return count != V;
    }

    /*
    --------------------------------------------
    Main Function
    --------------------------------------------
    */
    public static void main(String[] args) {
        int V = 4;

        // Example 1: Graph with NO cycle
        ArrayList<ArrayList<Integer>> adj = new ArrayList<>();
        for (int i = 0; i < V; i++) adj.add(new ArrayList<>());

        adj.get(0).add(1);
        adj.get(1).add(2);
        adj.get(2).add(3);
        // No cycle here (0 → 1 → 2 → 3)

        System.out.println("Cycle present? " + (isCyclicKahn(V, adj) ? "Yes" : "No"));

        // Example 2: Graph WITH cycle
        ArrayList<ArrayList<Integer>> adj2 = new ArrayList<>();
        for (int i = 0; i < V; i++) adj2.add(new ArrayList<>());

        adj2.get(0).add(1);
        adj2.get(1).add(2);
        adj2.get(2).add(0); // cycle: 0 → 1 → 2 → 0

        System.out.println("Cycle present? " + (isCyclicKahn(V, adj2) ? "Yes" : "No"));
    }
}
