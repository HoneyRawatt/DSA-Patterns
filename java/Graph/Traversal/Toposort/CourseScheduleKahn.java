import java.util.*;

/*
=====================================================
Problem Statement:
-----------------------------------------------------
You are given:
- An integer V representing the total number of courses.
- A list of prerequisite pairs where
  (a, b) means course 'a' depends on course 'b',
  i.e., you must complete course 'b' before course 'a'.

Task:
Determine whether it is possible to finish all courses.

Key Insight:
- Courses and prerequisites form a directed graph.
- If the graph contains a cycle, it is impossible
  to complete all courses.
- If no cycle exists, all courses can be completed.

=====================================================
Intuition / Idea:
-----------------------------------------------------
- Model each course as a node in a directed graph.
- For a prerequisite (a, b), create an edge: b → a
- The problem reduces to detecting a cycle in a
  directed graph.

We use Kahn’s Algorithm (BFS-based Topological Sort):
- Nodes with indegree 0 have no prerequisites.
- Repeatedly process such nodes and reduce indegrees.
- If all nodes are processed → no cycle.
- Otherwise → cycle exists.

=====================================================
Time Complexity:
-----------------------------------------------------
- Building adjacency list: O(E)
- Calculating indegrees: O(V + E)
- BFS traversal: O(V + E)

Overall Time Complexity: O(V + E)

=====================================================
Space Complexity:
-----------------------------------------------------
- Adjacency list: O(V + E)
- Indegree array: O(V)
- Queue: O(V)

Overall Space Complexity: O(V + E)
=====================================================
*/

public class CourseScheduleKahn {

    static boolean isPossible(int V, List<int[]> prerequisites) {

        // Step 1: Build adjacency list
        List<List<Integer>> adj = new ArrayList<>();
        for (int i = 0; i < V; i++) {
            adj.add(new ArrayList<>());
        }

        // Edge: prerequisite[1] → prerequisite[0]
        for (int[] pre : prerequisites) {
            adj.get(pre[1]).add(pre[0]);
        }

        // Step 2: Compute indegree of each course
        int[] indegree = new int[V];
        for (int i = 0; i < V; i++) {
            for (int neighbor : adj.get(i)) {
                indegree[neighbor]++;
            }
        }

        // Step 3: Add all courses with indegree 0 to queue
        Queue<Integer> queue = new LinkedList<>();
        for (int i = 0; i < V; i++) {
            if (indegree[i] == 0) {
                queue.add(i);
            }
        }

        // Step 4: BFS traversal (Kahn’s Algorithm)
        int count = 0; // number of courses processed

        while (!queue.isEmpty()) {
            int node = queue.poll();
            count++;

            // Reduce indegree of dependent courses
            for (int neighbor : adj.get(node)) {
                indegree[neighbor]--;
                if (indegree[neighbor] == 0) {
                    queue.add(neighbor);
                }
            }
        }

        // Step 5:
        // If all courses are processed → no cycle → possible
        return count == V;
    }

    /*
    --------------------------------------------
    Main function to test isPossible
    --------------------------------------------
    */
    public static void main(String[] args) {
        int V = 4;

        // Case 1: No cycle (possible to finish all courses)
        List<int[]> prerequisites1 = new ArrayList<>();
        prerequisites1.add(new int[]{1, 0});
        prerequisites1.add(new int[]{2, 1});
        prerequisites1.add(new int[]{3, 2});

        // Case 2: Cycle exists (not possible)
        List<int[]> prerequisites2 = new ArrayList<>();
        prerequisites2.add(new int[]{1, 0});
        prerequisites2.add(new int[]{0, 1});

        System.out.println("Case 1: " +
                (isPossible(V, prerequisites1) ? "Possible" : "Not Possible"));

        System.out.println("Case 2: " +
                (isPossible(V, prerequisites2) ? "Possible" : "Not Possible"));
    }
}
