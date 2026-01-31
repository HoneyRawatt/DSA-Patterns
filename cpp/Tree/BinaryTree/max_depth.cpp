#include <iostream>
#include <algorithm> // for max()
using namespace std;

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
Function: maxDepth()
Purpose : Returns the maximum depth (or height) of the binary tree.
          Depth = number of nodes along the longest path from root to leaf.

Approach:
    - Use recursion.
    - For each node:
        → compute the depth of left subtree (lh)
        → compute the depth of right subtree (rh)
        → answer = 1 + max(lh, rh)

Time Complexity:
    O(N) — every node is visited once.

Space Complexity:
    O(H) — recursive call stack, where H is height of tree.
           Worst case (skewed tree): O(N)
           Best case (balanced tree): O(log N)
*/
int maxDepth(TreeNode* root) {
    if (root == nullptr) return 0;

    int lh = maxDepth(root->left);
    int rh = maxDepth(root->right);

    return 1 + max(lh, rh);
}

int main() {
    // Example tree:
    //        1
    //       / \
    //      2   3
    //     / \
    //    4   5

    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->left->left = new TreeNode(4);
    root->left->right = new TreeNode(5);

    cout << "Maximum Depth of Tree: " << maxDepth(root) << endl;
    return 0;
}
