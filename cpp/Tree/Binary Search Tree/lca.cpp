#include <iostream>
using namespace std;

/*
Class: TreeNode
Purpose: Represents a node in a binary search tree (BST)
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
Function: lowestCommonAncestor
Purpose: Finds the Lowest Common Ancestor (LCA) of two given nodes (p and q)
         in a Binary Search Tree (BST).

Approach:
- If both p and q are smaller than the current node → LCA lies in the left subtree.
- If both p and q are greater than the current node → LCA lies in the right subtree.
- Otherwise → the current node is the split point (the LCA).

Time Complexity: O(h)   (where h = height of the tree)
Space Complexity: O(h)  (recursive stack space)
*/
TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
    if (root == nullptr) 
        return nullptr;  // Base case: empty tree

    int curr = root->val;

    // If both nodes are greater than current node, LCA lies in right subtree
    if (curr < p->val && curr < q->val)
        return lowestCommonAncestor(root->right, p, q);

    // If both nodes are smaller than current node, LCA lies in left subtree
    if (curr > p->val && curr > q->val)
        return lowestCommonAncestor(root->left, p, q);

    // Otherwise, current node is the Lowest Common Ancestor
    return root;
}

int main() {
    /*
         Constructing the following BST:
                 6
                / \
               2   8
              / \ / \
             0  4 7  9
               / \
              3   5
    */

    TreeNode* root = new TreeNode(6);
    root->left = new TreeNode(2);
    root->right = new TreeNode(8);
    root->left->left = new TreeNode(0);
    root->left->right = new TreeNode(4);
    root->left->right->left = new TreeNode(3);
    root->left->right->right = new TreeNode(5);
    root->right->left = new TreeNode(7);
    root->right->right = new TreeNode(9);

    TreeNode* p = root->left;        // Node with value 2
    TreeNode* q = root->right;       // Node with value 8

    TreeNode* ans = lowestCommonAncestor(root, p, q);
    if (ans)
        cout << "Lowest Common Ancestor of " << p->val << " and " << q->val << " is: " << ans->val << endl;
    else
        cout << "No common ancestor found." << endl;

    return 0;
}
