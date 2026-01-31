#include <iostream>
#include <vector>
using namespace std;

/*
Class: TreeNode
Purpose: Represents a single node in a binary tree.
Each node contains:
- data  → value stored in the node
- left  → pointer to left child
- right → pointer to right child
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
Function: isSymmetricHelper
Purpose:
- Checks whether two subtrees are mirror images of each other.

Intuition:
- Two trees are mirrors if:
  1️⃣ Their root values are equal
  2️⃣ Left subtree of one tree mirrors the right subtree of the other
  3️⃣ Right subtree of one tree mirrors the left subtree of the other

Base Cases:
- If both nodes are NULL → symmetric at this level
- If only one is NULL → not symmetric

Recursive Case:
- Check value equality
- Recursively compare:
    left->left  with right->right
    left->right with right->left
*/
bool isSymmetricHelper(TreeNode* left, TreeNode* right) {
    // If either node is NULL, both must be NULL to be symmetric
    if (!left || !right)
        return left == right;

    // If values differ, tree cannot be symmetric
    if (left->data != right->data)
        return false;

    // Recursively check mirror structure:
    // outer pair (left->left, right->right)
    // inner pair (left->right, right->left)
    return isSymmetricHelper(left->left, right->right) &&
           isSymmetricHelper(left->right, right->left);
}

/*
Function: isSymmetric
Purpose:
- Determines whether the entire binary tree is symmetric.

Approach:
- A tree is symmetric if its left subtree is a mirror of its right subtree.
- An empty tree is always symmetric.
*/
bool isSymmetric(TreeNode* root) {
    return root == nullptr || isSymmetricHelper(root->left, root->right);
}

/*
Time Complexity: O(N)
- Each node is visited once during mirror comparison.

Space Complexity: O(H)
- Recursive call stack where H is the height of the tree.
- Worst case (skewed tree): O(N)
- Best case (balanced tree): O(log N)
*/

int main() {
    /*
    Example symmetric tree:

            1
           / \
          2   2
         / \ / \
        3  4 4  3
    */

    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(2);
    root->left->left = new TreeNode(3);
    root->left->right = new TreeNode(4);
    root->right->left = new TreeNode(4);
    root->right->right = new TreeNode(3);

    cout << (isSymmetric(root)
            ? "Tree is Symmetric"
            : "Tree is Not Symmetric") << endl;

    return 0;
}
