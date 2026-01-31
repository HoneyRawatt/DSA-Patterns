#include <iostream>
#include <vector>
#include <map>
using namespace std;

/*
Class: TreeNode
Purpose: Represents a node in a binary tree.
Each node contains:
- val   : value of the node
- left  : pointer to left child
- right : pointer to right child
*/
class TreeNode {
public:
    int val;
    TreeNode* left;
    TreeNode* right;

    // Constructor initializes node value and child pointers
    TreeNode(int val) {
        this->val = val;
        left = nullptr;
        right = nullptr;
    }
};

/*
Helper function: buildTreeHelper

Purpose:
Builds a binary tree recursively using preorder and inorder traversals.

Parameters:
- preorder : preorder traversal array
- prestart, preend : current index range in preorder
- inorder  : inorder traversal array
- instart, inend   : current index range in inorder
- mpp      : map storing value -> index mapping for inorder traversal

Returns:
- Pointer to the root of the constructed subtree

Time Complexity : O(N)
Space Complexity: O(N) (recursion stack + hashmap)
*/
TreeNode* buildTreeHelper(vector<int>& preorder, int prestart, int preend,
                          vector<int>& inorder, int instart, int inend,
                          map<int, int>& mpp) {

    // Base case: no elements left to construct subtree
    if (prestart > preend || instart > inend)
        return nullptr;

    // First element in preorder range is always the root
    TreeNode* root = new TreeNode(preorder[prestart]);

    // Find root index in inorder traversal using map
    int inroot = mpp[root->val];

    // Number of nodes in left subtree
    int numleft = inroot - instart;

    /*
    Recursively build left subtree:
    preorder range : prestart+1 to prestart+numleft
    inorder range  : instart to inroot-1
    */
    root->left = buildTreeHelper(preorder,
                                 prestart + 1,
                                 prestart + numleft,
                                 inorder,
                                 instart,
                                 inroot - 1,
                                 mpp);

    /*
    Recursively build right subtree:
    preorder range : prestart+numleft+1 to preend
    inorder range  : inroot+1 to inend
    */
    root->right = buildTreeHelper(preorder,
                                  prestart + numleft + 1,
                                  preend,
                                  inorder,
                                  inroot + 1,
                                  inend,
                                  mpp);

    // Return constructed subtree root
    return root;
}

/*
Function: buildTree

Purpose:
Builds a binary tree from preorder and inorder traversal arrays.

Steps:
1. Create a map for fast lookup of indices in inorder array.
2. Call recursive helper to build the tree.

Time Complexity : O(N)
Space Complexity: O(N)
*/
TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {

    // Map to store index of each value in inorder traversal
    map<int, int> mpp;
    for (int i = 0; i < inorder.size(); i++) {
        mpp[inorder[i]] = i;
    }

    // Build the tree using helper function
    return buildTreeHelper(preorder,
                           0, preorder.size() - 1,
                           inorder,
                           0, inorder.size() - 1,
                           mpp);
}

/*
Utility Function: printInorder

Purpose:
Prints inorder traversal of the tree.
Used to verify correctness of constructed tree.
*/
void printInorder(TreeNode* root) {
    if (!root) return;
    printInorder(root->left);
    cout << root->val << " ";
    printInorder(root->right);
}

/*
Main function to test buildTree()
*/
int main() {
    vector<int> preorder = {3, 9, 20, 15, 7};
    vector<int> inorder  = {9, 3, 15, 20, 7};

    // Build tree from traversals
    TreeNode* root = buildTree(preorder, inorder);

    // Print inorder traversal to verify correctness
    cout << "Inorder traversal of constructed tree: ";
    printInorder(root);   // Should match original inorder array
    cout << endl;

    return 0;
}
