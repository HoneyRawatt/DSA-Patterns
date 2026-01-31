#include <iostream>
#include <vector>
#include <stack>
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
Approach 1: Recursive (Reverse Preorder)
-----------------------------------------
We do a reverse preorder traversal (right → left → node)
and keep a `prev` pointer to connect the nodes.
*/

void flatten_dfs(TreeNode* node, TreeNode*& prev) {
    if (node == nullptr) return;
    flatten_dfs(node->right, prev);
    flatten_dfs(node->left, prev);
    node->right = prev;
    node->left = nullptr;
    prev = node;
}

/*
Approach 2: Using Stack (Iterative Preorder)
--------------------------------------------
We simulate preorder traversal using an explicit stack.
*/

void flatten_stack(TreeNode* root) {
    if (root == nullptr) return;
    stack<TreeNode*> st;
    st.push(root);

    while (!st.empty()) {
        TreeNode* curr = st.top();
        st.pop();

        if (curr->right) st.push(curr->right);
        if (curr->left) st.push(curr->left);

        if (!st.empty()) curr->right = st.top();
        curr->left = nullptr;
    }
}

/*
Approach 3: Morris Traversal (O(1) Space)
-----------------------------------------
For each node:
1. If left child exists:
   - Find the rightmost node (predecessor) in the left subtree.
   - Connect predecessor’s right to current’s right.
   - Move left subtree to the right.
2. Move to next right node.
*/

void flatten_morris(TreeNode* root) {
    TreeNode* curr = root;

    while (curr != nullptr) {
        if (curr->left) {
            TreeNode* prev = curr->left;
            // Find rightmost node in left subtree
            while (prev->right) {
                prev = prev->right;
            }
            // Connect predecessor’s right to current’s right
            prev->right = curr->right;
            // Move left subtree to right
            curr->right = curr->left;
            curr->left = nullptr;
        }
        // Move ahead
        curr = curr->right;
    }
}

/*
Helper function to print flattened linked list
----------------------------------------------
Prints the tree in its flattened (linked list) form.
*/

void printFlattened(TreeNode* root) {
    while (root) {
        cout << root->val << " ";
        root = root->right;
    }
    cout << endl;
}

/*
Main Function to Test
----------------------------------------------
Builds sample tree:
          1
         / \
        2   5
       / \   \
      3   4   6

Expected flattened form (preorder): 1 2 3 4 5 6
*/

int main() {
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(5);
    root->left->left = new TreeNode(3);
    root->left->right = new TreeNode(4);
    root->right->right = new TreeNode(6);

    cout << "Flatten (Morris method): ";
    flatten_morris(root);
    printFlattened(root);

    // Rebuild tree again if testing other versions (since it’s modified)
    return 0;
}

/*
----------------------------------------------
🕒 Time Complexity: O(N)
💾 Space Complexity:
- DFS → O(H) recursion stack
- Stack → O(H)
- Morris → O(1)
----------------------------------------------
💡 Approach Summary:
Flattening a tree means transforming it into a right-skewed linked list
following preorder traversal. Morris approach is most efficient (no stack).
----------------------------------------------
*/
