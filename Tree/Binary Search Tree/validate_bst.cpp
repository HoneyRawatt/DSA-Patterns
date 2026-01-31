#include <iostream>
#include <climits> // for LONG_MIN, LONG_MAX
using namespace std;

/*
====================================================
📌 Problem Statement
====================================================
Given the root of a binary tree, determine whether
it is a valid Binary Search Tree (BST).

A valid BST must satisfy:
1️⃣ All values in the left subtree are strictly less
    than the current node.
2️⃣ All values in the right subtree are strictly greater
    than the current node.
3️⃣ Both left and right subtrees must also be BSTs.
====================================================
*/

/*
Class: TreeNode
Purpose: Represents a node in a Binary Search Tree
*/
class TreeNode {
public:
    int val;
    TreeNode* left;
    TreeNode* right;

    TreeNode(int val) {
        this->val = val;
        left = nullptr;
        right = nullptr;
    }
};

/*
====================================================
💡 Intuition
====================================================
- A node is not just constrained by its parent,
  but by ALL its ancestors.
- So we maintain a valid range (minval, maxval)
  for each node.
- Every node must satisfy:
      minval < node->val < maxval
====================================================
*/

/*
Helper Function: isValidBST
Purpose:
- Checks whether the subtree rooted at `root`
  is a valid BST within the range (minval, maxval)
*/
bool isValidBST(TreeNode* root, long minval, long maxval) {

    // Base case: empty tree is a valid BST
    if (!root) return true;

    // Current node must lie within valid range
    if (root->val <= minval || root->val >= maxval)
        return false;

    // Recursively validate left and right subtrees
    return isValidBST(root->left, minval, root->val) &&
           isValidBST(root->right, root->val, maxval);
}

/*
Main Function: isValidBST
Purpose:
- Starts validation with the full possible range
  of values
*/
bool isValidBST(TreeNode* root) {
    return isValidBST(root, LONG_MIN, LONG_MAX);
}

/*
====================================================
🧪 Example Usage
====================================================
Tree:
        2
       / \
      1   3
====================================================
*/
int main() {
    TreeNode* root = new TreeNode(2);
    root->left = new TreeNode(1);
    root->right = new TreeNode(3);

    // FIXED TYPO: isvalidbst → isValidBST
    if (isValidBST(root))
        cout << "Valid BST\n";
    else
        cout << "Not a valid BST\n";

    return 0;
}

/*
====================================================
🧠 Explanation Summary
====================================================

Each node must satisfy:
    minval < node->val < maxval

Left Subtree:
- maxval becomes the current node’s value

Right Subtree:
- minval becomes the current node’s value

This ensures:
✔ Global BST property
✔ Not just parent-based checking

====================================================
⚙️ Complexity Analysis
====================================================

Time Complexity:
- O(N): each node is visited once

Space Complexity:
- O(H): recursion stack
  - Balanced BST → O(log N)
  - Skewed BST → O(N)

====================================================
*/
