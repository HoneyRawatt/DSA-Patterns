#include <bits/stdc++.h>
using namespace std;

/*
Intuition:
------------
The Floyd-Warshall algorithm finds shortest paths between all pairs of vertices 
in a weighted graph (can handle negative weights but no negative cycles).

It uses dynamic programming and tries to improve the shortest path between i and j 
by checking if an intermediate vertex k gives a shorter path.

Steps:
1. Replace -1 with ∞ (1e9 here), since -1 means "no edge".
2. Set diagonal elements (i == j) to 0.
3. For every vertex k:
       For every vertex i:
           For every vertex j:
               matrix[i][j] = min(matrix[i][j], matrix[i][k] + matrix[k][j]);
4. If matrix[i][i] < 0 → negative cycle exists.
5. Convert ∞ (1e9) back to -1.

Time Complexity:  O(V³)
Space Complexity: O(1) → in-place
*/

void shortest_distance(vector<vector<int>>& matrix) {
    int n = matrix.size();

    // Step 1: Initialize -1 to 1e9 and i==j to 0
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (matrix[i][j] == -1)
                matrix[i][j] = 1e9;
            if (i == j)
                matrix[i][j] = 0;
        }
    }

    // Step 2: Floyd-Warshall relaxation
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (i == j) matrix[i][j] = 0;
                if (matrix[i][k] < 1e9 && matrix[k][j] < 1e9)
                    matrix[i][j] = min(matrix[i][j], matrix[i][k] + matrix[k][j]);
            }
        }
    }

    // Step 3: Check for negative weight cycles
    for (int i = 0; i < n; i++) {
        if (matrix[i][i] < 0) {
            cout << "Negative cycle detected\n";
            return;
        }
    }

    // Step 4: Convert 1e9 back to -1 for unreachable nodes
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (matrix[i][j] == 1e9)
                matrix[i][j] = -1;
        }
    }
}

// -----------------------
// Example Driver Code
// -----------------------
int main() {
    vector<vector<int>> matrix = {
        {0, 3, -1, 7},
        {-1, 0, 2, -1},
        {-1, -1, 0, 1},
        {-1, -1, -1, 0}
    };

    shortest_distance(matrix);

    cout << "Shortest distance matrix:\n";
    for (auto& row : matrix) {
        for (auto val : row) cout << val << " ";
        cout << "\n";
    }

    return 0;
}
