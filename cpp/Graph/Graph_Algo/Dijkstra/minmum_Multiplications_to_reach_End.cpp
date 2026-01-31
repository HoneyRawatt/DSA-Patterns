#include <bits/stdc++.h>
using namespace std;

/*
------------------------------------------------------------
🧠 Problem: Minimum Multiplications to Reach End
------------------------------------------------------------
You are given:
- An array `arr` of integers (allowed multipliers)
- A start value and an end value

You can multiply the current number by any number in `arr`
and take modulo 100000.

Your task: Find the **minimum number of multiplications**
required to reach `end` from `start`.

------------------------------------------------------------
🧩 Approach: BFS (Unweighted graph shortest path)
------------------------------------------------------------
Each number (0 to 99999) represents a node in a graph.
An edge exists between two nodes (u → v) if:
    v = (u * x) % 100000  for some x in arr.

We use BFS since each multiplication counts as 1 step (equal cost).

------------------------------------------------------------
📊 Time Complexity:  O(100000 * arr.size())
💾 Space Complexity: O(100000)
------------------------------------------------------------
*/

// User function Template for C++

class Solution {
  public:
    /*
    ------------------------------------------------------------
    🧠 Approach: BFS (Shortest path in an unweighted graph)
    ------------------------------------------------------------
    - Treat each number from 0 to 99999 as a node.
    - From each node, we can move to (node * x) % 100000 for every x in arr.
    - Each move costs 1 step → use BFS for minimum steps.

    ------------------------------------------------------------
    📊 Time Complexity:  O(100000 * arr.size())
    💾 Space Complexity: O(100000)
    ------------------------------------------------------------
    */
    
    int minimumMultiplications(vector<int>& arr, int start, int end) {
        int mod = 100000;

        // Trivial case: already at target
        if (start == end) return 0;
        
        // Queue -> {current number, steps}
        queue<pair<int, int>> q;
        q.push({start, 0});

        // Distance array initialized to infinity (1e9)
        vector<int> dist(mod, 1e9);
        dist[start] = 0;

        // BFS traversal
        while (!q.empty()) {
            int node = q.front().first;
            int steps = q.front().second;
            q.pop();

            // Try all multipliers
            for (auto it : arr) {
                int num = (1LL * it * node) % mod; // use 1LL to be safe

                // If found a shorter path
                if (steps + 1 < dist[num]) {
                    dist[num] = steps + 1;

                    // If reached destination
                    if (num == end)
                        return steps + 1;

                    q.push({num, steps + 1});
                }
            }
        }

        // If end not reachable
        return -1;
    }
};


int main() {
    vector<int> arr = {2, 5, 7};
    int start = 3;
    int end = 30;

    int ans = minimumMultiplications(arr, start, end);
    cout << "Minimum multiplications = " << ans << endl;

    return 0;
}
