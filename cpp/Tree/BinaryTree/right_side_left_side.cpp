#include <iostream>
#include <vector>
using namespace std;

/*
Class: TreeNode
Purpose: Represents a node in a binary tree
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
Function: rightside
Purpose : Fills the right view of the binary tree into res
Approach: DFS, visit right child first
Time Complexity: O(N) - each node visited once
Space Complexity: O(H) - recursion stack (H = height)
*/
void rightside(TreeNode* root, int level, vector<int>& res) {
    if (!root) return;
    
    if (level == res.size())
        res.push_back(root->data);
    
    rightside(root->right, level + 1, res);
    rightside(root->left, level + 1, res);
}

/*
Function: leftside
Purpose : Fills the left view of the binary tree into res
Approach: DFS, visit left child first
Time Complexity: O(N)
Space Complexity: O(H)
*/
void leftside(TreeNode* root, int level, vector<int>& res) {
    if (!root) return;

    if (level == res.size())
        res.push_back(root->data);
    
    leftside(root->left, level + 1, res);
    leftside(root->right, level + 1, res);
}

/* Example usage */
int main() {
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->left->left = new TreeNode(4);
    root->left->right = new TreeNode(5);
    root->right->right = new TreeNode(6);
    root->right->left = new TreeNode(7);

    vector<int> right_view;
    rightside(root, 0, right_view);
    cout << "Right View: ";
    for (int val : right_view) cout << val << " ";
    cout << endl;

    vector<int> left_view;
    leftside(root, 0, left_view);
    cout << "Left View: ";
    for (int val : left_view) cout << val << " ";
    cout << endl;

    return 0;
}
