#include <iostream>
#include <algorithm>
using namespace std;

/*
====================================================
Problem Statement: Check if Two Binary Trees are Identical
====================================================

Given the roots of two binary trees p and q, determine
whether they are identical.

Two binary trees are considered identical if:
1. They have the same structure.
2. Corresponding nodes have the same values.

----------------------------------------------------
Example:
Tree p:        1          Tree q:        1
              / \                       / \
             2   3                     2   3
Result: Identical

If any node value or structure differs → NOT identical
----------------------------------------------------

Expected Complexity:
- Time Complexity: O(N)
- Space Complexity: O(H)
====================================================
*/

/*
Class: TreeNode
Purpose:
    Represents a node in a binary tree.

Members:
    - data  : value stored in the node
    - left  : pointer to left child
    - right : pointer to right child
*/
class TreeNode {
public:
    int data;
    TreeNode* left;
    TreeNode* right;

    // Constructor to initialize node value and children
    TreeNode(int data) {
        this->data = data;
        left = nullptr;
        right = nullptr;
    }
};

/*
Function: check
Purpose:
    Checks whether two binary trees (p and q) are identical.

Definition of identical trees:
    - Same structure
    - Same values at corresponding nodes

Approach (Recursive DFS):
    1. If both nodes are NULL:
        → Trees are identical up to this branch.
    2. If one node is NULL and the other is not:
        → Trees are NOT identical.
    3. If both nodes exist:
        → Check current node values
        → Recursively check left subtrees
        → Recursively check right subtrees

Returns:
    true  → Trees are identical
    false → Trees differ

Time Complexity: O(N)
    - Each node is visited once.

Space Complexity: O(H)
    - Recursive call stack
    - H = height of the tree
*/
bool check(TreeNode* p, TreeNode* q) {

    // Case 1: If either node is NULL
    // - Both NULL → identical
    // - One NULL  → not identical
    if (p == nullptr || q == nullptr)
        return p == q;

    // Case 2: Both nodes are non-null
    // Check:
    // 1. Current node values
    // 2. Left subtrees
    // 3. Right subtrees
    return (p->data == q->data) &&
           check(p->left, q->left) &&
           check(p->right, q->right);
}

/*
Example usage
*/
int main() {

    // --------- Construct Tree 1 ---------
    //        1
    //       / \
    //      2   3
    TreeNode* p = new TreeNode(1);
    p->left = new TreeNode(2);
    p->right = new TreeNode(3);

    // --------- Construct Tree 2 ---------
    //        1
    //       / \
    //      2   3
    TreeNode* q = new TreeNode(1);
    q->left = new TreeNode(2);
    q->right = new TreeNode(3);

    // Check if both trees are identical
    cout << (check(p, q) ? 
            "Both trees are identical" : 
            "Trees are not identical") 
         << endl;

    // Modify Tree 2 to make it different
    q->right->data = 4;

    // Check again after modification
    cout << (check(p, q) ? 
            "Both trees are identical" : 
            "Trees are not identical") 
         << endl;

    return 0;
}
