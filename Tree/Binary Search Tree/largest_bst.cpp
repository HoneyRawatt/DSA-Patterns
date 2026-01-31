#include <bits/stdc++.h>
using namespace std;

/*
====================================================
📌 Problem Statement
====================================================
Given a Binary Tree (not necessarily a BST),
find the size of the largest subtree that is a
valid Binary Search Tree (BST).

BST rules:
- Left subtree values < root value
- Right subtree values > root value
- Both left and right subtrees must also be BSTs
====================================================
*/

/*
Class: TreeNode
Purpose: Represents a node in a binary tree
*/
class TreeNode {
public:
    int val;            // Value stored in node
    TreeNode* left;     // Pointer to left child
    TreeNode* right;    // Pointer to right child

    // Constructor
    TreeNode(int value) {
        val = value;
        left = right = nullptr;
    }
};

/* ========================================================
   ✅ BRUTE FORCE APPROACH
   ========================================================
   Idea:
   - For every node, check if the subtree rooted at it
     forms a valid BST.
   - If yes, count the number of nodes in that subtree.
   - Otherwise, recursively check left and right subtrees.

   Why brute force?
   - Each node may re-validate all its descendants.

   Time Complexity:  O(N^2)
   Space Complexity: O(H)  (recursion stack)
======================================================== */

/*
Helper Function: isValidBST
---------------------------------
Checks whether a subtree is a valid BST
using range constraints (minval, maxval).
*/
bool isValidBST(TreeNode* root, long minval, long maxval) {
    // Empty tree is always a valid BST
    if (!root) return true;

    // If current node violates BST property
    if (root->val <= minval || root->val >= maxval)
        return false;

    // Recursively validate left and right subtrees
    return isValidBST(root->left, minval, root->val) &&
           isValidBST(root->right, root->val, maxval);
}

/*
Helper Function: countNodes
---------------------------------
Counts total number of nodes in a subtree.
*/
int countNodes(TreeNode* root) {
    if (!root) return 0;
    return 1 + countNodes(root->left) + countNodes(root->right);
}

/*
Main Brute Force Function
---------------------------------
Returns size of the largest BST subtree.
*/
int largestBSTBrute(TreeNode* root) {
    if (!root) return 0;

    // If current subtree is a valid BST
    if (isValidBST(root, LONG_MIN, LONG_MAX))
        return countNodes(root);

    // Otherwise, check left and right subtrees
    return max(
        largestBSTBrute(root->left),
        largestBSTBrute(root->right)
    );
}

/* ========================================================
   ✅ OPTIMAL APPROACH (Single Traversal)
   ========================================================
   Idea:
   - Use postorder traversal (left → right → root).
   - For each subtree, return:
       1. Minimum value in subtree
       2. Maximum value in subtree
       3. Size of largest BST in subtree
   - If subtree is valid BST, merge results.

   Time Complexity:  O(N)
   Space Complexity: O(H)
======================================================== */

/*
Class: NodeValue
---------------------------------
Stores information about a subtree:
- minnode: minimum value in subtree
- maxnode: maximum value in subtree
- maxsize: size of largest BST found so far
*/
class NodeValue {
public:
    int minnode;
    int maxnode;
    int maxsize;

    NodeValue(int minnode, int maxnode, int maxsize) {
        this->minnode = minnode;
        this->maxnode = maxnode;
        this->maxsize = maxsize;
    }
};

/*
Recursive Function: largestBSTSubtree
---------------------------------
Returns NodeValue object for each subtree.
*/
NodeValue largestBSTSubtree(TreeNode* root) {

    // Base case:
    // Empty subtree is a valid BST of size 0
    if (!root)
        return NodeValue(INT_MAX, INT_MIN, 0);

    // Postorder traversal
    NodeValue left = largestBSTSubtree(root->left);
    NodeValue right = largestBSTSubtree(root->right);

    // Check BST validity condition
    if (left.maxnode < root->val && root->val < right.minnode) {

        // Current subtree is a valid BST
        return NodeValue(
            min(root->val, left.minnode),     // New minimum
            max(root->val, right.maxnode),    // New maximum
            left.maxsize + right.maxsize + 1  // Total size
        );
    }

    // If not a BST:
    // Return invalid range and carry forward max size found
    return NodeValue(
        INT_MIN,
        INT_MAX,
        max(left.maxsize, right.maxsize)
    );
}

/*
Wrapper Function
---------------------------------
Returns only the size of the largest BST.
*/
int largestBST(TreeNode* root) {
    return largestBSTSubtree(root).maxsize;
}

/* ========================================================
   🧪 MAIN FUNCTION (Testing)
======================================================== */
int main() {

    /*
             10
            /  \
           5    15
          / \     \
         1   8     7

    Largest BST Subtree:
           5
          / \
         1   8
    Size = 3
    */

    TreeNode* root = new TreeNode(10);
    root->left = new TreeNode(5);
    root->right = new TreeNode(15);
    root->left->left = new TreeNode(1);
    root->left->right = new TreeNode(8);
    root->right->right = new TreeNode(7);

    cout << "Brute Force Largest BST Size: "
         << largestBSTBrute(root) << endl;

    cout << "Optimal Largest BST Size: "
         << largestBST(root) << endl;

    return 0;
}

/*
============================================================
🧠 Final Comparison
============================================================

Approach        Time        Space     Notes
------------------------------------------------
Brute Force     O(N^2)      O(H)      Simple but inefficient
Optimal        O(N)        O(H)      Best & interview-ready

============================================================
*/
