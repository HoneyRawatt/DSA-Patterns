#include <iostream>
#include <queue>
#include <algorithm>
using namespace std;

/*
====================================================
PROBLEM STATEMENT
====================================================
Given a binary tree, modify it so that it satisfies
the Children Sum Property (CSP).

Children Sum Property:
For every non-leaf node:
    node->data = (left child data) + (right child data)

Rules:
- You are allowed to only INCREASE node values.
- Tree structure must remain unchanged.
- Leaf nodes are always valid.

----------------------------------------------------
Example:
        50
       /  \
      7    2
     / \  / \
    3  5 1  30

After enforcing CSP:
        100
       /   \
     50     50
    /  \   /  \
   25  25 20  30
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
====================================================
INTUITION / APPROACH
====================================================

We solve this using a DFS (post-order style) traversal.

Key idea:
1. First, compare current node value with sum of children.
2. If children sum is GREATER → update current node.
3. If current node is GREATER → push its value down
   to its children.
4. Recursively fix left and right subtrees.
5. While returning back (post-order), recompute the
   current node using updated children values.

Why this works:
- We never decrease values (only increase).
- Fixing children first ensures correctness bottom-up.
====================================================
*/

/*
Function: changeTree()
Purpose:
Modifies the binary tree so that it satisfies the
Children Sum Property.
*/
void changeTree(TreeNode* root) {
    if (!root) return;

    // Step 1: Calculate sum of children
    int child = 0;
    if (root->left) child += root->left->data;
    if (root->right) child += root->right->data;

    /*
    Step 2:
    - If children sum >= node value:
        Update node to children sum
    - Else:
        Push node value down to children
    */
    if (child >= root->data)
        root->data = child;
    else {
        if (root->left) root->left->data = root->data;
        if (root->right) root->right->data = root->data;
    }

    // Step 3: Recurse for left and right subtrees
    changeTree(root->left);
    changeTree(root->right);

    /*
    Step 4 (Post-order fix):
    After children are fixed, update current node
    using final children values
    */
    int tot = 0;
    if (root->left) tot += root->left->data;
    if (root->right) tot += root->right->data;

    if (root->left || root->right)
        root->data = tot;
}

/*
Helper Function: printLevelOrder()
Purpose:
Prints the binary tree using Level Order Traversal
(Breadth-First Search).
*/
void printLevelOrder(TreeNode* root) {
    if (!root) return;

    queue<TreeNode*> q;
    q.push(root);

    while (!q.empty()) {
        int n = q.size();
        while (n--) {
            TreeNode* node = q.front();
            q.pop();
            cout << node->data << " ";
            if (node->left) q.push(node->left);
            if (node->right) q.push(node->right);
        }
        cout << endl;
    }
}

/*
====================================================
MAIN FUNCTION
====================================================
1. Builds a sample binary tree
2. Prints tree before applying CSP
3. Applies changeTree()
4. Prints tree after applying CSP
====================================================
*/
int main() {
    // Constructing the binary tree
    TreeNode* root = new TreeNode(50);
    root->left = new TreeNode(7);
    root->right = new TreeNode(2);
    root->left->left = new TreeNode(3);
    root->left->right = new TreeNode(5);
    root->right->left = new TreeNode(1);
    root->right->right = new TreeNode(30);

    cout << "Before changeTree() - Level Order Traversal:\n";
    printLevelOrder(root);

    // Apply Children Sum Property
    changeTree(root);

    cout << "\nAfter changeTree() - Level Order Traversal:\n";
    printLevelOrder(root);

    return 0;
}

/*
====================================================
TIME & SPACE COMPLEXITY
====================================================

Time Complexity: O(N)
- Each node is visited exactly once.

Space Complexity: O(H)
- Recursive call stack where H = height of tree
- Worst case (skewed tree): O(N)
- Best case (balanced tree): O(log N)
====================================================
*/
