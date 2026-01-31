#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <algorithm>
using namespace std;

/*
====================================================
Problem Statement: Boundary Traversal of a Binary Tree
====================================================

Given the root of a binary tree, print the boundary
traversal of the tree in an anti-clockwise direction.

The boundary traversal consists of:
1. Root node (if it is not a leaf)
2. Left boundary (excluding leaf nodes)
3. All leaf nodes (from left to right)
4. Right boundary (excluding leaf nodes, printed bottom-up)

----------------------------------------------------
Example Tree:

              1
            /   \
           2     3
          / \   / \
         4   5 6   7
            / \
           8   9

Boundary Traversal Output:
1 2 4 8 9 6 7 3

----------------------------------------------------
Time Complexity: O(N)
Space Complexity: O(H)
    N = number of nodes
    H = height of the tree
====================================================
*/

/*
Class: TreeNode
Purpose:
    Represents a node in a binary tree.
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
Function: isLeaf
Purpose:
    Checks whether a given node is a leaf node
    (i.e., has no left or right child)

Time Complexity: O(1)
Space Complexity: O(1)
*/
bool isLeaf(TreeNode* temp) {
    return (temp->left == nullptr && temp->right == nullptr);
}

/*
Function: addLeftBoundary
Purpose:
    Adds all left boundary nodes of the tree
    (excluding leaf nodes).

Traversal Rule:
    - Prefer moving left
    - If left child doesn't exist, move right

Time Complexity: O(H)
Space Complexity: O(1)
*/
void addLeftBoundary(TreeNode* root, vector<int>& res) {
    TreeNode* curr = root->left;

    while (curr) {
        if (!isLeaf(curr))
            res.push_back(curr->data);

        if (curr->left)
            curr = curr->left;
        else
            curr = curr->right;
    }
}

/*
Function: addRightBoundary
Purpose:
    Adds all right boundary nodes of the tree
    (excluding leaf nodes) in reverse order.

Traversal Rule:
    - Prefer moving right
    - If right child doesn't exist, move left

Time Complexity: O(H)
Space Complexity: O(H) — temporary vector used
*/
void addRightBoundary(TreeNode* root, vector<int>& res) {
    TreeNode* curr = root->right;
    vector<int> temp;

    while (curr) {
        if (!isLeaf(curr))
            temp.push_back(curr->data);

        if (curr->right)
            curr = curr->right;
        else
            curr = curr->left;
    }

    // Add right boundary in reverse (bottom-up)
    for (int i = temp.size() - 1; i >= 0; i--) {
        res.push_back(temp[i]);
    }
}

/*
Function: addLeaves
Purpose:
    Adds all leaf nodes of the tree
    from left to right using DFS.

Time Complexity: O(N)
Space Complexity: O(H)
*/
void addLeaves(TreeNode* root, vector<int>& res) {
    if (isLeaf(root)) {
        res.push_back(root->data);
        return;
    }

    if (root->left)
        addLeaves(root->left, res);

    if (root->right)
        addLeaves(root->right, res);
}

/*
Function: printBoundary
Purpose:
    Performs boundary traversal of a binary tree.

Order:
    Root →
    Left Boundary →
    Leaf Nodes →
    Right Boundary (reversed)

Time Complexity: O(N)
Space Complexity: O(H)
*/
vector<int> printBoundary(TreeNode* root) {
    vector<int> res;
    if (!root) return res;

    // Add root if it's not a leaf
    if (!isLeaf(root))
        res.push_back(root->data);

    addLeftBoundary(root, res);   // Left boundary
    addLeaves(root, res);         // All leaf nodes
    addRightBoundary(root, res);  // Right boundary

    return res;
}

/*
Main Function
Purpose:
    Builds a sample binary tree and prints
    its boundary traversal.
*/
int main() {

    /*
              1
            /   \
           2     3
          / \   / \
         4   5 6   7
            / \
           8   9
    */

    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->left->left = new TreeNode(4);
    root->left->right = new TreeNode(5);
    root->left->right->left = new TreeNode(8);
    root->left->right->right = new TreeNode(9);
    root->right->left = new TreeNode(6);
    root->right->right = new TreeNode(7);

    vector<int> result = printBoundary(root);

    cout << "Boundary Traversal: ";
    for (int val : result)
        cout << val << " ";
    cout << endl;

    return 0;
}
