#include <iostream>
#include <vector>
using namespace std;

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
Approach: Morris Traversal
---------------------------------
Idea:
Instead of using recursion or a stack, we temporarily modify
the tree by creating "threads" to connect nodes to their inorder predecessors.

We repeatedly:
1. If left child is null → visit node & move to right.
2. Else, find the rightmost node in left subtree (predecessor).
   - If predecessor’s right is null → make thread to current node and move left.
   - If predecessor’s right points to current → remove thread, visit node, move right.

This allows us to traverse the tree without extra space.
*/

/* Morris Inorder Traversal */
vector<int> getInorder(TreeNode* root) {
    vector<int> inorder;
    TreeNode* curr = root;

    while (curr != nullptr) {
        if (curr->left == nullptr) {
            inorder.push_back(curr->val);
            curr = curr->right;
        } else {
            TreeNode* prev = curr->left;
            // Find rightmost node in left subtree
            while (prev->right && prev->right != curr) {
                prev = prev->right;
            }

            if (prev->right == nullptr) {
                // Create thread
                prev->right = curr;
                curr = curr->left;
            } else {
                // Thread already exists — remove it
                prev->right = nullptr;
                inorder.push_back(curr->val);
                curr = curr->right;
            }
        }
    }
    return inorder;
}

/* Morris Preorder Traversal */
vector<int> getPreorder(TreeNode* root) {
    vector<int> preorder;
    TreeNode* curr = root;

    while (curr != nullptr) {
        if (curr->left == nullptr) {
            preorder.push_back(curr->val);
            curr = curr->right;
        } else {
            TreeNode* prev = curr->left;
            // Find rightmost node in left subtree
            while (prev->right && prev->right != curr) {
                prev = prev->right;
            }

            if (prev->right == nullptr) {
                preorder.push_back(curr->val); // Visit before left (preorder)
                prev->right = curr;
                curr = curr->left;
            } else {
                prev->right = nullptr;
                curr = curr->right;
            }
        }
    }
    return preorder;
}

/* Helper to print a vector */
void printVector(const vector<int>& v) {
    for (int x : v) cout << x << " ";
    cout << endl;
}

/* Main function to test */
int main() {
    /*
            1
           / \
          2   3
         / \   \
        4   5   6
    */

    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->left->left = new TreeNode(4);
    root->left->right = new TreeNode(5);
    root->right->right = new TreeNode(6);

    vector<int> inorder = getInorder(root);
    vector<int> preorder = getPreorder(root);

    cout << "Morris Inorder Traversal: ";
    printVector(inorder);

    cout << "Morris Preorder Traversal: ";
    printVector(preorder);

    return 0;
}

/*
------------------------------------------------------
🕒 Time Complexity:
O(N) — Each edge is visited at most twice (once for creating
and once for removing a thread).

💾 Space Complexity:
O(1) — No recursion or stack used, only constant variables.

💡 View of Approach:
Morris traversal is a clever way to do tree traversal
without extra memory, by temporarily modifying the tree structure.
After traversal, the tree is restored to its original form.
Hence, it achieves O(1) space with O(N) time.
------------------------------------------------------
*/
