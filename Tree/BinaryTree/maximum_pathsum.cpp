#include <iostream>
#include <algorithm>
using namespace std;

/*
====================================================
Problem Statement: Maximum Path Sum in a Binary Tree
====================================================

Given the root of a binary tree, find the maximum path sum.

A path in the tree is defined as a sequence of nodes where:
- Each pair of adjacent nodes in the sequence has an edge connecting them.
- A node can appear at most once in the path.
- The path does NOT need to pass through the root.
- The path must contain at least one node.

The path sum is the sum of the values of all nodes present in the path.

Your task is to compute and return the maximum possible path sum
that can be obtained from any path in the tree.

----------------------------------------------------
Key Observations:
- The path may start and end at any node.
- Negative node values are allowed.
- While computing a path, negative contributions should be ignored
  if they reduce the total sum.

----------------------------------------------------
Expected Complexity:
- Time Complexity: O(N), where N is the number of nodes.
- Space Complexity: O(H), where H is the height of the tree
  (due to recursion stack).
====================================================
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
Function: maxPathSumHelper
Purpose:
    Recursive helper to compute maximum path sum in a binary tree.

Returns:
    Maximum path sum **starting from the current node and going downward**
    (either left or right, but not both).

Updates:
    maxi — stores the maximum path sum found anywhere in the tree.

Logic:
    - Recursively compute left and right subtree sums.
    - Ignore negative contributions using max(0, ...).
    - Update global maximum considering the path passing through
      the current node (left + root + right).
    - Return the best downward path sum for parent computation.

Time Complexity: O(N)
Space Complexity: O(H)
*/
int maxPathSumHelper(TreeNode* root, int &maxi) {
    if (!root) return 0;

    int leftsum = max(0, maxPathSumHelper(root->left, maxi));
    int rightsum = max(0, maxPathSumHelper(root->right, maxi));

    // Path passing through current node
    maxi = max(maxi, leftsum + rightsum + root->data);

    // Return max path starting from current node
    return root->data + max(leftsum, rightsum);
}

/*
Function: maxPathSum
Purpose:
    Returns the maximum path sum in the entire binary tree.

Approach:
    - Uses a helper function with a reference variable to track
      the global maximum path sum.

Time Complexity: O(N)
Space Complexity: O(H)
*/
int maxPathSum(TreeNode* root) {
    int maxi = INT_MIN;
    maxPathSumHelper(root, maxi);
    return maxi;
}

/* Example usage */
int main() {
    TreeNode* root = new TreeNode(10);
    root->left = new TreeNode(2);
    root->right = new TreeNode(10);
    root->left->left = new TreeNode(20);
    root->left->right = new TreeNode(1);
    root->right->right = new TreeNode(-25);
    root->right->right->left = new TreeNode(3);
    root->right->right->right = new TreeNode(4);

    cout << "Maximum Path Sum: " << maxPathSum(root) << endl;
    return 0;
}
