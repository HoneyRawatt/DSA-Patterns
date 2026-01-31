#include <iostream>
#include <vector>
#include <map>
using namespace std;

/*
====================================================
PROBLEM STATEMENT
====================================================
Given two traversal arrays of a binary tree:
1. Inorder traversal
2. Postorder traversal

Construct the original binary tree.

Assumptions:
- All node values are unique.
- Tree contains at least one node.
====================================================
*/

/*
Class: TreeNode
Purpose:
Represents a node in a binary tree.
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
INTUITION / APPROACH
====================================================

Key Observations:
1. In postorder traversal:
   → Last element is always the ROOT of the tree.
2. In inorder traversal:
   → Elements left of root belong to left subtree.
   → Elements right of root belong to right subtree.

Steps:
1. Pick last element from postorder → root.
2. Find root index in inorder traversal.
3. Number of elements on left gives size of left subtree.
4. Recursively build left and right subtrees.
5. Use a map to find root index in O(1) time.

This avoids repeated scanning of inorder array.
====================================================
*/

/*
----------------------------------------------------
Helper Function: BuildTreeHelper
----------------------------------------------------
Purpose:
Recursively constructs the binary tree using ranges
of inorder and postorder arrays.

Parameters:
- inorder[is...ie]   → current inorder range
- postorder[ps...pe] → current postorder range
- mpp                → map storing inorder index of values
----------------------------------------------------
*/
TreeNode* BuildTreeHelper(vector<int>& inorder, int is, int ie,
                          vector<int>& postorder, int ps, int pe,
                          map<int, int>& mpp) {

    // Base case: invalid range means no subtree
    if (ps > pe || is > ie) return nullptr;

    // Step 1: Last element in postorder is root
    TreeNode* root = new TreeNode(postorder[pe]);

    // Step 2: Find root index in inorder traversal
    int inRoot = mpp[postorder[pe]];

    // Step 3: Number of nodes in left subtree
    int numLeft = inRoot - is;

    // Step 4: Recursively build left subtree
    root->left = BuildTreeHelper(
        inorder, is, inRoot - 1,
        postorder, ps, ps + numLeft - 1, mpp
    );

    // Step 5: Recursively build right subtree
    root->right = BuildTreeHelper(
        inorder, inRoot + 1, ie,
        postorder, ps + numLeft, pe - 1, mpp
    );

    return root;
}

/*
----------------------------------------------------
Function: BuildTree
----------------------------------------------------
Purpose:
Initializes the inorder index map and starts
the recursive tree construction.
----------------------------------------------------
*/
TreeNode* BuildTree(vector<int>& inorder, vector<int>& postorder) {

    // If traversals are invalid
    if (inorder.size() != postorder.size())
        return nullptr;

    // Map value → index for inorder traversal
    map<int, int> mpp;
    for (int i = 0; i < inorder.size(); i++) {
        mpp[inorder[i]] = i;
    }

    // Call recursive helper
    return BuildTreeHelper(
        inorder, 0, inorder.size() - 1,
        postorder, 0, postorder.size() - 1, mpp
    );
}

/*
----------------------------------------------------
Utility Function: printPreorder
----------------------------------------------------
Purpose:
Prints preorder traversal of the tree
to verify correctness of construction.
----------------------------------------------------
*/
void printPreorder(TreeNode* root) {
    if (!root) return;

    cout << root->val << " ";
    printPreorder(root->left);
    printPreorder(root->right);
}

/*
====================================================
MAIN FUNCTION
====================================================
Tests tree construction using inorder and postorder.
====================================================
*/
int main() {

    vector<int> inorder   = {9, 3, 15, 20, 7};
    vector<int> postorder = {9, 15, 7, 20, 3};

    TreeNode* root = BuildTree(inorder, postorder);

    cout << "Preorder traversal of constructed tree: ";
    printPreorder(root);
    cout << endl;

    return 0;
}

/*
====================================================
COMPLEXITY ANALYSIS
====================================================

Time Complexity: O(N)
- Each node is processed once.
- Map lookup is O(1) per node.

Space Complexity: O(N)
- Map storing inorder indices.
- Recursion stack in worst case (skewed tree).
====================================================

Expected Output:
Preorder traversal of constructed tree: 3 9 20 15 7
*/
