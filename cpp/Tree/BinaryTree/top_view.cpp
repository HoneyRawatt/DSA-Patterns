#include <iostream>
#include <vector>
#include <map>
#include <queue>
using namespace std;

/*
----------------------------------------------------
Class: TreeNode
Purpose:
- Represents a single node in a binary tree
- Each node stores:
    1) data value
    2) pointer to left child
    3) pointer to right child
----------------------------------------------------
*/
class TreeNode {
public:
    int data;           // Value stored in the node
    TreeNode* left;     // Pointer to left child
    TreeNode* right;    // Pointer to right child

    // Constructor to initialize a tree node
    TreeNode(int data) {
        this->data = data;
        left = nullptr;
        right = nullptr;
    }
};

/*
----------------------------------------------------
Function: topV
Purpose:
- Computes and returns the TOP VIEW of a binary tree

Top View:
- Nodes visible when the tree is viewed from the top
- For each vertical line (horizontal distance),
  only the first node encountered is included

Approach:
1) Use BFS (level-order traversal) to process nodes level by level
2) Track horizontal distance (HD) for each node
   - Root → HD = 0
   - Left child → HD - 1
   - Right child → HD + 1
3) Use map<int,int> to store:
   - key   → horizontal distance
   - value → node data
4) Insert into map only if that HD is not already present

Time Complexity:
- O(N log N)
  - N nodes processed
  - map insertion takes log N

Space Complexity:
- O(N)
  - queue for BFS
  - map for storing top view nodes
----------------------------------------------------
*/
vector<int> topV(TreeNode* root) {
    vector<int> ans;          // Stores final top view result

    // Edge case: empty tree
    if (!root) return ans;

    map<int,int> mp;          // Map to store HD -> node value
    queue<pair<TreeNode*, int>> q;  // Queue stores (node, HD)

    // Start BFS from root with horizontal distance 0
    q.push({root, 0});

    while (!q.empty()) {
        // Extract front element from queue
        auto it = q.front();
        q.pop();

        TreeNode* node = it.first; // Current node
        int line = it.second;      // Horizontal distance of node

        // Store node value only if this HD is encountered first time
        if (mp.find(line) == mp.end()) {
            mp[line] = node->data;
        }

        // Push left child with HD - 1
        if (node->left)
            q.push({node->left, line - 1});

        // Push right child with HD + 1
        if (node->right)
            q.push({node->right, line + 1});
    }

    // Extract values from map in sorted HD order
    // (map keeps keys sorted automatically)
    for (auto it : mp) {
        ans.push_back(it.second);
    }

    return ans;
}

/*
----------------------------------------------------
Example Usage (Driver Code)
----------------------------------------------------
*/
int main() {
    /*
            1
           / \
          2   3
           \
            4
             \
              5
               \
                6

    Top View: 2 1 3 6
    */

    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->left->right = new TreeNode(4);
    root->left->right->right = new TreeNode(5);
    root->left->right->right->right = new TreeNode(6);

    vector<int> result = topV(root);

    // Print top view
    for (int val : result)
        cout << val << " ";
    cout << endl;  // Expected output: 2 1 3 6

    return 0;
}
