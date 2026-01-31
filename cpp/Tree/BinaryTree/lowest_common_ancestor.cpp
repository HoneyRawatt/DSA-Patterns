#include <iostream>
using namespace std;

/*
Class: TreeNode
Purpose: Represents a node in a binary tree.
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
Function: lowestCommonAncestor()
Purpose:
    Finds the Lowest Common Ancestor (LCA) of two nodes (p, q) in a Binary Tree.

Logic:
    - If the current node is NULL → return NULL (no LCA found in this branch)
    - If the current node is equal to p or q → return current node (found one target)
    - Recurse on both left and right subtrees
    - If both left and right return non-null → current node is LCA
    - If one side returns null → propagate the non-null side (LCA is there)

Time Complexity:  O(N)
    → Each node is visited once.

Space Complexity: O(H)
    → Recursive call stack where H = height of the tree.
      Worst case (skewed): O(N)
      Best case (balanced): O(log N)
*/
TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
    if (root == nullptr || root == p || root == q)
        return root; // Base condition: null or one of the targets found

    TreeNode* left = lowestCommonAncestor(root->left, p, q);
    TreeNode* right = lowestCommonAncestor(root->right, p, q);

    if (!left) return right;   // LCA found on right side
    else if (!right) return left; // LCA found on left side
    else return root;          // Both sides found → current node is LCA
}

/*
Example Usage:
Binary Tree:
         3
        / \
       5   1
      / \ / \
     6  2 0  8
       / \
      7   4
LCA(5, 1) = 3
LCA(6, 4) = 5
*/
int main() {
    TreeNode* root = new TreeNode(3);
    root->left = new TreeNode(5);
    root->right = new TreeNode(1);
    root->left->left = new TreeNode(6);
    root->left->right = new TreeNode(2);
    root->right->left = new TreeNode(0);
    root->right->right = new TreeNode(8);
    root->left->right->left = new TreeNode(7);
    root->left->right->right = new TreeNode(4);

    TreeNode* p = root->left;           // Node 5
    TreeNode* q = root->right;          // Node 1
    TreeNode* lca = lowestCommonAncestor(root, p, q);

    cout << "LCA of " << p->data << " and " << q->data << " is: " << lca->data << endl;

    return 0;
}
