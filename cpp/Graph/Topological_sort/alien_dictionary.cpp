#include <bits/stdc++.h>
using namespace std;

// Kahn’s Algorithm for Topological Sorting
vector<int> topoSort(int V, vector<int> adj[]) {
    vector<int> indegree(V, 0);

    // Step 1: Compute indegree for each node
    for (int i = 0; i < V; i++) {
        for (auto it : adj[i]) {
            indegree[it]++;
        }
    }

    // Step 2: Push all nodes with indegree 0 into the queue
    queue<int> q;
    for (int i = 0; i < V; i++) {
        if (indegree[i] == 0) {
            q.push(i);
        }
    }

    // Step 3: BFS traversal
    vector<int> topo;
    while (!q.empty()) {
        int node = q.front();
        q.pop();
        topo.push_back(node);

        // Reduce indegree of all adjacent nodes
        for (auto it : adj[node]) {
            indegree[it]--;
            if (indegree[it] == 0)
                q.push(it);
        }
    }

    return topo;
}

// Function to find the order of characters in the alien dictionary
string findOrder(string dict[], int N, int K) {
    vector<int> adj[K]; // adjacency list of size K

    // Step 1: Build the graph
    for (int i = 0; i < N - 1; i++) {
        string s1 = dict[i];
        string s2 = dict[i + 1];
        int len = min(s1.size(), s2.size());

        for (int j = 0; j < len; j++) {
            if (s1[j] != s2[j]) {
                adj[s1[j] - 'a'].push_back(s2[j] - 'a');
                break; // only first mismatch matters
            }
        }
    }

    // Step 2: Perform Topological Sort
    vector<int> topo = topoSort(K, adj);

    // Step 3: Convert topo order to string
    string ans = "";
    for (auto it : topo)
        ans += (it + 'a');

    return ans;
}

// ---------- DRIVER CODE ----------
int main() {
    int N = 5, K = 4;
    string dict[] = {"baa", "abcd", "abca", "cab", "cad"};

    string order = findOrder(dict, N, K);
    cout << "Alien Dictionary Order: " << order << endl;
    return 0;
}


// Time Complexity
// Building the graph: O(N × min(|s1|, |s2|))
// Topological sort: O(V + E)
// Here, V = K (number of characters), and E ≤ K².
// Total: O(N × L + K + E)
// where L = average word length.

// 💾 Space Complexity
// Adjacency list: O(K + E)
// Indegree array & queue: O(K)
// Total: O(K + E)