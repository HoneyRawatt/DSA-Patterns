#include <iostream>
#include <vector>
using namespace std;

/*
====================================================
📌 Problem Statement
====================================================
Given a Binary Search Tree (BST) and an integer key:

1️⃣ Ceil in BST:
   - Find the smallest value in the BST that is
     greater than or equal to the given key.

2️⃣ Floor in BST:
   - Find the largest value in the BST that is
     smaller than or equal to the given key.

If no such value exists, return -1.

BST Property:
- Left subtree values < root
- Right subtree values > root
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
💡 Intuition (Ceil)
====================================================
- If node->val == key → this is the ceil.
- If node->val < key → ceil must be in right subtree.
- If node->val > key → this node is a potential ceil,
  but a smaller one might exist in the left subtree.

So:
✔ Move right when value is smaller
✔ Move left when value is greater and store candidate
====================================================
*/

/*
Function: ceil_bst
Purpose: Finds the smallest value in BST that is >= key
*/
int ceil_bst(TreeNode* root, int key) {
    int ceil = -1;  // stores current best answer

    while (root) {
        if (root->val == key) {
            // Exact match → best possible ceil
            ceil = root->val;
            return ceil;
        }

        if (key > root->val) {
            // Ceil must be in right subtree
            root = root->right;
        } else {
            // Current node is a valid ceil candidate
            ceil = root->val;
            root = root->left;
        }
    }
    return ceil;
}

/*
====================================================
💡 Intuition (Floor)
====================================================
- If node->val == key → this is the floor.
- If node->val > key → floor must be in left subtree.
- If node->val < key → this node is a potential floor,
  but a larger one might exist in the right subtree.

So:
✔ Move left when value is greater
✔ Move right when value is smaller and store candidate
====================================================
*/

/*
Function: floor_bst
Purpose: Finds the largest value in BST that is <= key
*/
int floor_bst(TreeNode* root, int key) {
    int floor = -1;  // stores current best answer

    while (root) {
        if (root->val == key) {
            // Exact match → best possible floor
            floor = root->val;
            return floor;
        }

        if (key > root->val) {
            // Current node is a valid floor candidate
            floor = root->val;
            root = root->right;
        } else {
            // Floor must be in left subtree
            root = root->left;
        }
    }
    return floor;
}

/*
Helper Function: Insert node into BST
Used only for building test tree
*/
TreeNode* insertBST(TreeNode* root, int val) {
    if (!root) return new TreeNode(val);

    if (val < root->val)
        root->left = insertBST(root->left, val);
    else
        root->right = insertBST(root->right, val);

    return root;
}

/*
====================================================
🧪 Main Function (Testing)
====================================================
BST Structure:
          8
         / \
        4   12
       / \  / \
      2  6 10 14
====================================================
*/
int main() {
    TreeNode* root = nullptr;
    vector<int> vals = {8, 4, 12, 2, 6, 10, 14};
    for (int v : vals)
        root = insertBST(root, v);

    int key = 5;

    cout << "Key: " << key << endl;
    cout << "Ceil: " << ceil_bst(root, key) << endl;
    cout << "Floor: " << floor_bst(root, key) << endl;

    return 0;
}

/*
====================================================
⏱ Time & Space Complexity
====================================================

Time Complexity:
- O(H) where H = height of BST
- Balanced BST → O(log N)
- Skewed BST → O(N)

Space Complexity:
- O(1) extra space (iterative approach)

====================================================
🧠 Summary
====================================================
✔ We leverage BST ordering to skip half the tree
✔ No recursion → constant space
✔ Efficient and interview-optimal solution
====================================================
*/
