#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <set>
#include <algorithm>
using namespace std;

/*
====================================================
Problem Statement: Vertical Order Traversal of a Binary Tree
====================================================

Given the root of a binary tree, return its vertical
order traversal.

In vertical order traversal:
- Nodes are grouped by their vertical columns.
- Columns are ordered from leftmost to rightmost.
- For nodes in the same column:
    1. Nodes are ordered by their depth (top to bottom).
    2. If multiple nodes share the same column and depth,
       they are sorted by their values.

----------------------------------------------------
Coordinate System Used:
- Root node is at (x = 0, y = 0)
- Left child  → (x - 1, y + 1)
- Right child → (x + 1, y + 1)

----------------------------------------------------
Example Tree:

            3
           / \
          9   20
              / \
             15  7

Vertical Traversal Output:
[
  [9],
  [3, 15],
  [20],
  [7]
]

----------------------------------------------------
Time Complexity: O(N log N)
Space Complexity: O(N)
====================================================
*/

/*
Class: TreeNode
Purpose:
    Represents a node in a binary tree.
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
Function: verticalTraversal
Purpose:
    Performs vertical order traversal of a binary tree.

Approach:
1️⃣ Perform BFS (level-order traversal) to ensure
    nodes are visited top-to-bottom.

2️⃣ Track each node’s position using coordinates:
    - x → vertical column index
    - y → depth/level

3️⃣ Store nodes in a nested data structure:
    map<int, map<int, multiset<int>>> nodes

    Explanation:
    - First map key (x): vertical column
    - Second map key (y): depth
    - multiset: handles multiple nodes at same (x, y)
      and keeps them sorted automatically.

4️⃣ Finally, iterate over the map from leftmost column
    to rightmost and build the result.

Time Complexity:
    O(N log N)
    - Insertion into map/multiset costs log N
    - N nodes processed

Space Complexity:
    O(N)
    - Map storage + queue + result
*/
vector<vector<int>> verticalTraversal(TreeNode* root) {

    // Base case: empty tree
    if (!root) return {};

    // map<x, map<y, multiset<values>>>
    map<int, map<int, multiset<int>>> nodes;

    // Queue for BFS
    // Stores: {TreeNode*, {x, y}}
    queue<pair<TreeNode*, pair<int, int>>> todo;

    // Start with root at (0, 0)
    todo.push({root, {0, 0}});

    while (!todo.empty()) {
        auto p = todo.front();
        todo.pop();

        TreeNode* node = p.first;
        int x = p.second.first;   // horizontal distance
        int y = p.second.second;  // depth

        // Insert node value into its corresponding position
        nodes[x][y].insert(node->data);

        // Move to left child → x - 1, y + 1
        if (node->left)
            todo.push({node->left, {x - 1, y + 1}});

        // Move to right child → x + 1, y + 1
        if (node->right)
            todo.push({node->right, {x + 1, y + 1}});
    }

    // Build final answer from the map
    vector<vector<int>> ans;

    for (auto& xPair : nodes) {
        vector<int> col;

        // Traverse nodes column-wise and depth-wise
        for (auto& yPair : xPair.second) {
            col.insert(col.end(),
                       yPair.second.begin(),
                       yPair.second.end());
        }

        ans.push_back(col);
    }

    return ans;
}

/*
Driver Code
Purpose:
    Builds a sample tree and prints its
    vertical order traversal.
*/
int main() {

    /*
            3
           / \
          9   20
              / \
             15  7
    */

    TreeNode* root = new TreeNode(3);
    root->left = new TreeNode(9);
    root->right = new TreeNode(20);
    root->right->left = new TreeNode(15);
    root->right->right = new TreeNode(7);

    vector<vector<int>> result = verticalTraversal(root);

    cout << "Vertical Order Traversal:\n";
    for (auto& col : result) {
        for (int val : col)
            cout << val << " ";
        cout << endl;
    }

    return 0;
}
