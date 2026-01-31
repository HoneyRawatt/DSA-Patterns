#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;

/*
====================================================
Problem Statement: Zigzag (Spiral) Level Order Traversal
====================================================

Given the root of a binary tree, return the zigzag
level order traversal of its nodes' values.

Zigzag traversal means:
- Level 0 → Left to Right
- Level 1 → Right to Left
- Level 2 → Left to Right
- and so on...

----------------------------------------------------
Example:
Input Tree:
            1
           / \
          2   3
         / \   \
        4   5   6

Output:
[
  [1],
  [3, 2],
  [4, 5, 6]
]
----------------------------------------------------

Constraints:
- The number of nodes is in the range [0, N]
- Node values can be any integer

Expected Time Complexity: O(N)
Expected Space Complexity: O(N)
====================================================
*/

/*
Class: TreeNode
Purpose:
    Represents a single node in a binary tree.
Each node contains:
    - data  → value of the node
    - left  → pointer to left child
    - right → pointer to right child
*/
class TreeNode {
public:
    int data;
    TreeNode* left;
    TreeNode* right;

    // Constructor to initialize a node
    TreeNode(int data) {
        this->data = data;
        left = nullptr;
        right = nullptr;
    }
};

/*
Function: zigzagLevelOrder
Purpose:
    Performs zigzag (spiral) level order traversal
    of a binary tree.

Approach:
    1. Use a queue for standard BFS (level order traversal).
    2. Maintain a boolean flag `leftToRight`:
        - true  → traverse left to right
        - false → traverse right to left
    3. For each level:
        - Create a vector of size = number of nodes in that level
        - Insert elements using index trick:
            index = i               (left to right)
            index = size - 1 - i    (right to left)
    4. Toggle direction after each level.

Time Complexity: O(N)
    → Each node is visited exactly once.

Space Complexity: O(N)
    → Queue + result storage.
*/
vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
    vector<vector<int>> res;

    // If tree is empty, return empty result
    if (root == nullptr) return res;

    queue<TreeNode*> nodeQueue;
    nodeQueue.push(root);

    // Direction flag
    bool leftToRight = true;

    // Standard BFS loop
    while (!nodeQueue.empty()) {
        int size = nodeQueue.size();

        // Store current level elements
        vector<int> row(size);

        for (int i = 0; i < size; i++) {
            TreeNode* node = nodeQueue.front();
            nodeQueue.pop();

            // Calculate index based on direction
            int indx = leftToRight ? i : (size - 1 - i);
            row[indx] = node->data;

            // Add children to queue
            if (node->left) nodeQueue.push(node->left);
            if (node->right) nodeQueue.push(node->right);
        }

        // Change direction for next level
        leftToRight = !leftToRight;

        // Add current level to result
        res.push_back(row);
    }

    return res;
}

/*
Main Function
Purpose:
    Demonstrates zigzag level order traversal
*/
int main() {

    // Construct sample binary tree
    /*
            1
           / \
          2   3
         / \   \
        4   5   6
    */
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->left->left = new TreeNode(4);
    root->left->right = new TreeNode(5);
    root->right->right = new TreeNode(6);

    // Perform zigzag traversal
    vector<vector<int>> result = zigzagLevelOrder(root);

    // Print result
    cout << "Zigzag Level Order Traversal:" << endl;
    for (auto &level : result) {
        for (int val : level)
            cout << val << " ";
        cout << endl;
    }

    return 0;
}
