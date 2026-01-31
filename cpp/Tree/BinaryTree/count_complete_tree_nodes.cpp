#include <iostream>
using namespace std;

/*
====================================================
PROBLEM STATEMENT
====================================================
Count the number of nodes in a COMPLETE binary tree.

A complete binary tree:
- All levels are completely filled except possibly the last
- The last level is filled from left to right

We use an optimized approach instead of normal traversal.
====================================================
*/
/*
Class: TreeNode
Purpose: Represents a node in a binary tree
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
Function: findHeightLeft
Purpose : Find height by going along the leftmost path
Input   : root node
Output  : height (int)
Time    : O(logN)
*/
int findHeightLeft(TreeNode* root) {
    int height = 0;
    while (root) {
        height++;
        root = root->left;
    }
    return height;
}

/*
Function: findHeightRight
Purpose : Find height by going along the rightmost path
Input   : root node
Output  : height (int)
Time    : O(logN)
*/
int findHeightRight(TreeNode* root) {
    int height = 0;
    while (root) {
        height++;
        root = root->right;
    }
    return height;
}

/*
Function: countNodes
Purpose : Count nodes in a complete binary tree using optimized approach
1. If left height == right height => perfect binary tree, nodes = 2^height - 1
2. Else, recursively count left and right subtrees
Time Complexity : O((logN)^2) — height computation O(logN) at each level
Space Complexity: O(logN) — recursion stack
*/
int countNodes(TreeNode* root) {
    if (!root) return 0;

    int lh = findHeightLeft(root);
    int rh = findHeightRight(root);

    if (lh == rh) {
        return (1 << lh) - 1; // Perfect binary tree
    }
    return 1 + countNodes(root->left) + countNodes(root->right);
}

/*
Function: inorder
Purpose : Count nodes using standard traversal (for comparison)
Time Complexity : O(N)
Space Complexity: O(H) — recursion stack
*/
void inorder(TreeNode* root, int &cnt) {
    if (!root) return;

    cnt++;
    inorder(root->left, cnt);
    inorder(root->right, cnt);
}

/* Main function to test */
int main() {
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->left->left = new TreeNode(4);
    root->left->right = new TreeNode(5);
    root->right->left = new TreeNode(6);
    // Complete binary tree with 6 nodes

    cout << "Optimized countNodes output: " << countNodes(root) << endl; // Output: 6

    int cnt = 0;
    inorder(root, cnt);
    cout << "Traversal-based count (inorder) output: " << cnt << endl; // Output: 6

    return 0;
}
