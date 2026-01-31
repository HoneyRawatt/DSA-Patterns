package Tree.BinarySearchTree;

#include <iostream>
using namespace std;

/*
====================================================
📌 Problem Statement
====================================================
Given a Binary Search Tree (BST):

1️⃣ Find the k-th smallest element
2️⃣ Find the k-th largest element

Constraints:
- Must do it efficiently.
- Extra space should be minimized.

Observation:
- Inorder traversal of BST gives sorted order (ascending).
- Reverse inorder traversal gives sorted order (descending).
====================================================
*/

/*
Class: TreeNode
Purpose: Represents a node in a Binary Search Tree (BST)
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
Helper Function: insertBST
Purpose: Inserts a value into BST (used only for testing)
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
💡 Intuition (k-th Smallest)
====================================================
- Inorder traversal of BST → sorted order.
- Normally done using recursion or stack (O(H) space).
- Morris Traversal allows inorder traversal in O(1) space
  by temporarily modifying tree links (threads).

Key Idea:
✔ Count nodes as we visit them in inorder
✔ When count == k → answer found
====================================================
*/

/*
Function: kthsmallest
Purpose: Find the k-th smallest element using Morris Inorder Traversal
*/
TreeNode* kthsmallest(TreeNode* root, int k) {
    int cnt = 0;                  // counts visited nodes
    TreeNode* curr = root;

    while (curr != nullptr) {

        // Case 1: No left child → visit node
        if (curr->left == nullptr) {
            cnt++;
            if (cnt == k) return curr;
            curr = curr->right;
        }
        // Case 2: Left child exists
        else {
            // Find inorder predecessor
            TreeNode* prev = curr->left;
            while (prev->right && prev->right != curr)
                prev = prev->right;

            // Create temporary thread
            if (prev->right == nullptr) {
                prev->right = curr;
                curr = curr->left;
            }
            // Thread exists → remove and visit node
            else {
                prev->right = nullptr;
                cnt++;
                if (cnt == k) return curr;
                curr = curr->right;
            }
        }
    }
    return nullptr;  // k exceeds number of nodes
}

/*
====================================================
💡 Intuition (k-th Largest)
====================================================
- Reverse inorder traversal → descending order.
- Same Morris idea, but traversal is:
  Right → Node → Left
====================================================
*/

/*
Function: kthLargest
Purpose: Find the k-th largest element using Morris Reverse Inorder
*/
TreeNode* kthLargest(TreeNode* root, int k) {
    int cnt = 0;
    TreeNode* curr = root;

    while (curr != nullptr) {

        // Case 1: No right child → visit node
        if (curr->right == nullptr) {
            cnt++;
            if (cnt == k) return curr;
            curr = curr->left;
        }
        // Case 2: Right child exists
        else {
            // Find reverse inorder successor
            TreeNode* next = curr->right;
            while (next->left && next->left != curr)
                next = next->left;

            // Create temporary thread
            if (next->left == nullptr) {
                next->left = curr;
                curr = curr->right;
            }
            // Thread exists → remove and visit node
            else {
                next->left = nullptr;
                cnt++;
                if (cnt == k) return curr;
                curr = curr->left;
            }
        }
    }
    return nullptr;  // k exceeds number of nodes
}

/*
====================================================
🧪 Main Function (Testing)
====================================================
BST Structure:
            5
           / \
          3   6
         / \
        2   4
       /
      1
====================================================
*/
int main() {
    TreeNode* root = nullptr;
    root = insertBST(root, 5);
    root = insertBST(root, 3);
    root = insertBST(root, 6);
    root = insertBST(root, 2);
    root = insertBST(root, 4);
    root = insertBST(root, 1);

    int k_small = 3;
    TreeNode* kthSmallestNode = kthsmallest(root, k_small);
    if (kthSmallestNode)
        cout << k_small << "th smallest element is: "
             << kthSmallestNode->val << endl;

    int k_large = 2;
    TreeNode* kthLargestNode = kthLargest(root, k_large);
    if (kthLargestNode)
        cout << k_large << "th largest element is: "
             << kthLargestNode->val << endl;

    return 0;
}

/*
====================================================
⏱ Time & Space Complexity
====================================================
Time Complexity:
- O(N) → each node visited at most twice

Space Complexity:
- O(1) → no recursion, no stack

====================================================
🧠 Key Takeaways
====================================================
✔ Morris Traversal avoids extra memory
✔ BST inorder = sorted order
✔ Excellent follow-up question in interviews
====================================================
*/
