#include <bits/stdc++.h>
using namespace std;

// ⏱ Complexity
// Time: O(32 * (n + m)) ≈ O(n + m)
// Space: O(32 * n)

struct Node {
    Node* links[2];

    // Constructor to initialize pointers
    Node() {
        links[0] = nullptr;
        links[1] = nullptr;
    }
    bool containsKey(int bit) {
        return links[bit] != nullptr;
    }

    Node* get(int bit) {
        return links[bit];
    }

    void put(int bit, Node* node) {
        links[bit] = node;
    }
};

class Trie {
private:
    Node* root;

public:
    Trie() {
        root = new Node();
    }

    // Insert a number into trie
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

    // Get maximum XOR for a number
    int getMax(int num) {
        Node* node = root;
        int maxNum = 0;

        for (int i = 31; i >= 0; i--) {
            int bit = (num >> i) & 1;

            // Prefer opposite bit
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

// Function to calculate maximum XOR between two arrays
int maxXor(int n, int m, vector<int>& arr1, vector<int>& arr2) {
    Trie trie;

    // Insert all elements of arr1
    for (auto &it : arr1) {
        trie.insert(it);
    }

    int maxi = 0;

    // Query for each element of arr2
    for (auto &it : arr2) {
        maxi = max(maxi, trie.getMax(it));
    }

    return maxi;
}

// ------------------ DRIVER CODE ------------------
int main() {
    int n, m;
    cin >> n >> m;

    vector<int> arr1(n), arr2(m);

    for (int i = 0; i < n; i++) cin >> arr1[i];
    for (int i = 0; i < m; i++) cin >> arr2[i];

    cout << maxXor(n, m, arr1, arr2) << endl;

    return 0;
}
