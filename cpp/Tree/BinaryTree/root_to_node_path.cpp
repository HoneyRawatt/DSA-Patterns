#include <iostream>
#include <vector>
using namespace std;

/*
Class: TreeNode
Purpose: Represents a node in a binary tree.
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
Function: getpath()
Purpose:
    Recursively finds the path from the root node to the given target node `x`.
    - If the current node matches `x`, we stop and return true.
    - Otherwise, we recursively search in left and right subtrees.
    - If not found in either, we backtrack by removing the current node.

Parameters:
    root → current node being checked
    arr  → vector storing the current path
    x    → target node value

Returns:
    true if path to node `x` exists, otherwise false

Time Complexity:  O(N)
    → We may visit each node once in the worst case.

Space Complexity: O(H)
    → Due to recursion stack + path vector.
      H = height of the tree.
      Worst case (skewed tree): O(N)
      Best case (balanced tree): O(log N)
*/
bool getpath(TreeNode* root, vector<int>& arr, int x) {
    if (!root) return false;          // Base: empty subtree → no path

    arr.push_back(root->data);        // Include current node in path

    if (root->data == x)              // Found the target node
        return true;

    // Recur left or right — return true if found in either
    if (getpath(root->left, arr, x) || getpath(root->right, arr, x))
        return true;

    // If not found, backtrack — remove the node
    arr.pop_back();
    return false;
}

/*
Function: solve()
Purpose:
    Wrapper function that initializes the path vector
    and calls getpath() to find path from root (A) to target (B).
*/
vector<int> solve(TreeNode* A, int B) {
    vector<int> arr;
    if (!A) return arr;

    getpath(A, arr, B);
    return arr;
}

/*
Example Usage:
Input Tree:
        1
       / \
      2   3
     / \
    4   5
Target: 5
Expected Output: 1 → 2 → 5
*/
int main() {
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->left->left = new TreeNode(4);
    root->left->right = new TreeNode(5);

    int target = 5;
    vector<int> path = solve(root, target);

    cout << "Path from root to node " << target << ": ";
    for (int val : path)
        cout << val << " ";
    cout << endl;

    return 0;
}
