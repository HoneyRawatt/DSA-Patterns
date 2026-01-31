#include <bits/stdc++.h>
using namespace std;

/*
=====================================================
BRUTE FORCE APPROACH
=====================================================
For each query (xi, ai):
- Check all elements of array
- If arr[j] <= ai
    compute arr[j] ^ xi
    update maximum XOR

=====================================================
Time Complexity:
- Outer loop  : O(q)
- Inner loop  : O(n)
- Total       : O(q * n)

Space Complexity:
- O(1) extra space (excluding output array)
=====================================================
*/

vector<int> maxXorQueriesBrute(vector<int>& arr, vector<vector<int>>& queries) {

    int n = arr.size();
    int q = queries.size();

    vector<int> ans;

    // Loop over each query
    for (int i = 0; i < q; i++) {

        int xi = queries[i][0];
        int ai = queries[i][1];

        int maxxor = -1;

        // Check all elements of array
        for (int j = 0; j < n; j++) {
            if (arr[j] <= ai) {
                maxxor = max(maxxor, arr[j] ^ xi);
            }
        }

        // Store result of current query
        ans.push_back(maxxor);
    }

    return ans;
}


/*
=====================================================
PROBLEM INTUITION (Offline XOR Queries)
=====================================================
For each query (xi, ai):
- We want maximum XOR of xi with any number <= ai from array.

Brute force would be O(n*q) → TLE.

OPTIMIZATION:
1. Sort array.
2. Sort queries by ai (offline processing).
3. Insert only those array elements into Trie which are <= ai.
4. For each query, compute max XOR using binary Trie.

Why Trie?
- XOR depends on binary representation.
- Greedily choosing opposite bits gives maximum XOR.
=====================================================
*/

// ⏱ OVERALL COMPLEXITY
// Time  : O((n + q) * 32)
// Space : O(n * 32)

/* ===================== TRIE NODE ===================== */
struct Node {
    Node* links[2];

    // Constructor
    Node() {
        links[0] = nullptr;
        links[1] = nullptr;
    }

    // Check if bit exists
    bool containsKey(int bit) {
        return links[bit] != nullptr;
    }

    // Get next node
    Node* get(int bit) {
        return links[bit];
    }

    // Insert new node
    void put(int bit, Node* node) {
        links[bit] = node;
    }
};

/* ===================== TRIE CLASS ===================== */
class Trie {
private:
    Node* root;

public:
    Trie() {
        root = new Node();
    }

    /*
    -----------------------------------------------------
    insert(num)
    Intuition:
    - Insert binary representation of num (32 bits)
    - Create path if it doesn't exist

    Time  : O(32)
    Space : O(32) per number
    -----------------------------------------------------
    */
    void insert(int num) {
        Node* node = root;
        for (int i = 31; i >= 0; i--) {
            int bit = (num >> i) & 1;
            if (!node->containsKey(bit)) {
                node->put(bit, new Node());
            }
            node = node->get(bit);
        }
    }

    /*
    -----------------------------------------------------
    getMax(num)
    Intuition:
    - To maximize XOR:
      prefer opposite bit at every level
    - If opposite bit exists → take it
    - Else → take same bit

    Time  : O(32)
    Space : O(1)
    -----------------------------------------------------
    */
    int getMax(int num) {
        Node* node = root;
        int maxNum = 0;

        for (int i = 31; i >= 0; i--) {
            int bit = (num >> i) & 1;

            if (node->containsKey(1 - bit)) {
                maxNum |= (1 << i);
                node = node->get(1 - bit);
            } else {
                node = node->get(bit);
            }
        }
        return maxNum;
    }
};

/* ===================== MAIN FUNCTION ===================== */
vector<int> maxXorQueries(vector<int>& arr, vector<vector<int>>& queries) {

    /*
    -----------------------------------------------------
    Intuition:
    - Sort array
    - Convert queries to offline format:
        (ai, (xi, index))
    - Process queries in increasing order of ai
    - Insert elements into Trie only once
    -----------------------------------------------------
    */

    int n = arr.size();
    int q = queries.size();

    sort(arr.begin(), arr.end()); // O(n log n)

    // Offline queries
    vector<pair<int, pair<int, int>>> OQ;
    for (int i = 0; i < q; i++) {
        OQ.push_back({queries[i][1], {queries[i][0], i}});
    }

    sort(OQ.begin(), OQ.end()); // O(q log q)

    Trie trie;
    vector<int> ans(q, 0);

    int ind = 0;

    /*
    -----------------------------------------------------
    Processing queries
    - Insert arr[ind] while arr[ind] <= ai
    - Then compute max XOR for xi
    -----------------------------------------------------
    */

    for (int i = 0; i < q; i++) {
        int ai = OQ[i].first;
        int xi = OQ[i].second.first;
        int qind = OQ[i].second.second;

        while (ind < n && arr[ind] <= ai) {
            trie.insert(arr[ind]);
            ind++;
        }

        if (ind == 0)
            ans[qind] = -1;
        else
            ans[qind] = trie.getMax(xi);
    }

    return ans;
}
