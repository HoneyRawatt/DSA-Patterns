#include <iostream>
#include <queue>
#include <algorithm>
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

// Function to calculate the maximum width of a binary tree
int widthofbinarytree(TreeNode* root) {
    if (!root) return 0;

    long long ans = 0;  // use long long to avoid overflow
    queue<pair<TreeNode*, long long>> q;
    q.push({root, 0});

    while (!q.empty()) {
        int size = q.size();
        long long minIndex = q.front().second; // Minimum index at current level
        long long first, last;

        for (int i = 0; i < size; i++) {
            long long currId = q.front().second - minIndex; // Normalize index
            TreeNode* node = q.front().first;
            q.pop();

            if (i == 0) first = currId;
            if (i == size - 1) last = currId;

            if (node->left) q.push({node->left, currId * 2 + 1});
            if (node->right) q.push({node->right, currId * 2 + 2});
        }

        ans = max(ans, last - first + 1);
    }

    return (int)ans;
}
