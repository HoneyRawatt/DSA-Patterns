import java.util.*;

public class GraphRepresentations {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        int n = sc.nextInt(); // number of nodes
        int m = sc.nextInt(); // number of edges

        // -------------------------------
        // 1️⃣ Adjacency Matrix (Unweighted)
        // -------------------------------
        int[][] adjMatrix = new int[n + 1][n + 1];

        for (int i = 0; i < m; i++) {
            int u = sc.nextInt();
            int v = sc.nextInt();

            // Undirected graph
            adjMatrix[u][v] = 1;
            adjMatrix[v][u] = 1;

            // For directed graph → remove the second line
        }

        // -------------------------------
        // 2️⃣ Adjacency List (Unweighted)
        // -------------------------------
        List<List<Integer>> adjList = new ArrayList<>();
        for (int i = 0; i <= n; i++) {
            adjList.add(new ArrayList<>());
        }

        for (int i = 0; i < m; i++) {
            int u = sc.nextInt();
            int v = sc.nextInt();

            // Undirected graph
            adjList.get(u).add(v);
            adjList.get(v).add(u);

            // For directed graph → remove the second add
        }

        // -------------------------------
        // 3️⃣ Adjacency Matrix (Weighted)
        // -------------------------------
        int[][] adjMatrixWt = new int[n + 1][n + 1];

        for (int i = 0; i < m; i++) {
            int u = sc.nextInt();
            int v = sc.nextInt();
            int wt = sc.nextInt();

            // Undirected graph
            adjMatrixWt[u][v] = wt;
            adjMatrixWt[v][u] = wt;

            // For directed graph → remove the second line
        }

        // -------------------------------
        // 4️⃣ Adjacency List (Weighted)
        // -------------------------------
        List<List<Pair>> adjListWt = new ArrayList<>();
        for (int i = 0; i <= n; i++) {
            adjListWt.add(new ArrayList<>());
        }

        for (int i = 0; i < m; i++) {
            int u = sc.nextInt();
            int v = sc.nextInt();
            int wt = sc.nextInt();

            // Undirected graph
            adjListWt.get(u).add(new Pair(v, wt));
            adjListWt.get(v).add(new Pair(u, wt));

            // For directed graph → remove the second add
        }

        sc.close();
    }

    // Helper class for weighted adjacency list
    static class Pair {
        int node;
        int weight;

        Pair(int node, int weight) {
            this.node = node;
            this.weight = weight;
        }
    }
}
// | Representation        | Data Structure                                      | Space Complexity | Suitable for                          |
// | --------------------- | --------------------------------------------------- | ---------------- | ------------------------------------- |
// | **Adjacency Matrix**  | `vector<vector<int>> adj(n+1, vector<int>(n+1, 0))` | O(V²)            | Dense graphs                          |
// | **Adjacency List**    | `vector<vector<int>> adj(n+1)`                      | O(V + 2E)        | Sparse graphs                         |
// | **Weighted (Matrix)** | Store weight at `adj[u][v] = wt`                    | O(V²)            | When quick edge lookups matter        |
// | **Weighted (List)**   | `vector<vector<pair<int,int>>> adj(n+1)`            | O(V + 2E)        | When edges are few and memory matters |
