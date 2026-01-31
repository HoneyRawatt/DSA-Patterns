#include <iostream>
#include <vector>
#include <map>
#include <queue>
using namespace std;

/*
----------------------------------------------------
Class: TreeNode
Purpose:
- Represents a node in a binary tree
- Each node stores:
    1) data value
    2) pointer to left child
    3) pointer to right child
----------------------------------------------------
*/
class TreeNode {
public:
    int data;
    TreeNode* left;
    TreeNode* right;

    TreeNode(int data) {
        this->data = data;
        left = nullptr;
        right = nullptr;
    }
};

/*
----------------------------------------------------
Problem Statement:
Given the root of a binary tree, return the **bottom view**
of the tree.

Bottom View Definition:
- When the tree is viewed from the bottom,
  the nodes visible are those that appear last
  in each vertical line (horizontal distance).

If multiple nodes share the same horizontal distance,
the node that is **lower (appears later in level order)**
is chosen.

----------------------------------------------------
Intuition:
- Each node lies on a vertical line identified by its
  horizontal distance (HD) from the root.
- Nodes deeper in the tree should overwrite upper nodes
  when they share the same HD.
- A level-order traversal (BFS) naturally processes nodes
  from top to bottom.
- By **overwriting values in a map**, the bottommost node
  for each HD remains.

----------------------------------------------------
Approach:
1) Use BFS (level-order traversal) with a queue.
2) Track horizontal distance (HD):
   - Root → HD = 0
   - Left child → HD - 1
   - Right child → HD + 1
3) Use a map<int, int>:
   - Key   → horizontal distance
   - Value → node value
4) For each node:
   - Overwrite map[HD] with current node value
5) Traverse the map from leftmost HD to rightmost HD
   to get the bottom view.

----------------------------------------------------
Time Complexity:
- O(N log N)
  - BFS visits each node once → O(N)
  - Map insertion takes log N per node

Space Complexity:
- O(N)
  - Queue for BFS
  - Map to store HD mappings
----------------------------------------------------
*/
vector<int> bottomv(TreeNode* root) {
    vector<int> ans;
    if (!root) return ans;

    // Map stores horizontal distance -> node value
    map<int, int> mp;

    // Queue stores (node, horizontal distance)
    queue<pair<TreeNode*, int>> q;
    q.push({root, 0});

    while (!q.empty()) {
        auto it = q.front();
        q.pop();

        TreeNode* node = it.first;
        int line = it.second;

        // Overwrite value so bottommost node remains
        mp[line] = node->data;

        // Move left → HD - 1
        if (node->left)
            q.push({node->left, line - 1});

        // Move right → HD + 1
        if (node->right)
            q.push({node->right, line + 1});
    }

    // Extract bottom view from leftmost to rightmost HD
    for (auto it : mp) {
        ans.push_back(it.second);
    }

    return ans;
}

/*
----------------------------------------------------
Example Usage
----------------------------------------------------
*/
int main() {
    /*
              20
            /    \
           8      22
         /   \   /  \
        5     3 4    25
             / \
            10 14

    Bottom View: 5 10 4 14 25
    */

    TreeNode* root = new TreeNode(20);
    root->left = new TreeNode(8);
    root->right = new TreeNode(22);
    root->left->left = new TreeNode(5);
    root->left->right = new TreeNode(3);
    root->right->left = new TreeNode(4);
    root->right->right = new TreeNode(25);
    root->left->right->left = new TreeNode(10);
    root->left->right->right = new TreeNode(14);

    vector<int> result = bottomv(root);
    for (int val : result)
        cout << val << " ";
    cout << endl;
