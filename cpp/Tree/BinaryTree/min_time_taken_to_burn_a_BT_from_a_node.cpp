#include <iostream>
#include <queue>
#include <map>
using namespace std;

/*
====================================================
PROBLEM STATEMENT
====================================================
Given a binary tree and a starting node (target),
a fire starts at the target node and spreads to:
- left child
- right child
- parent

In one unit of time, fire spreads to all adjacent nodes.

Task:
Return the minimum time required to burn the entire tree.
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
APPROACH 1: BFS + PARENT MAPPING
====================================================

Idea:
- Treat the tree as an undirected graph.
- Since nodes don’t have parent pointers, we first
  map each node to its parent.
- Then perform BFS starting from the target node.
- Each BFS level represents 1 unit of time.

Time Complexity: O(N)
Space Complexity: O(N)
====================================================
*/

/*
----------------------------------------------------
Step 1: Map each node to its parent and
        find the target node
----------------------------------------------------
*/
TreeNode* bfsToMapParents(
        TreeNode* root,
        map<TreeNode*, TreeNode*>& parentMap,
        int start) {

    queue<TreeNode*> q;
    q.push(root);

    TreeNode* targetNode = nullptr;

    while (!q.empty()) {
        TreeNode* node = q.front();
        q.pop();

        // Identify the target node
        if (node->val == start)
            targetNode = node;

        // Map left child to parent
        if (node->left) {
            parentMap[node->left] = node;
            q.push(node->left);
        }

        // Map right child to parent
        if (node->right) {
            parentMap[node->right] = node;
            q.push(node->right);
        }
    }

    return targetNode;
}

/*
----------------------------------------------------
Step 2: BFS from target node to calculate
        minimum time to burn the tree
----------------------------------------------------
*/
int findMinDistance(
        map<TreeNode*, TreeNode*>& parentMap,
        TreeNode* target) {

    queue<TreeNode*> q;
    map<TreeNode*, bool> visited;

    q.push(target);
    visited[target] = true;

    int time = 0;

    while (!q.empty()) {
        int size = q.size();
        bool flag = false; // checks if fire spreads further

        for (int i = 0; i < size; i++) {
            TreeNode* node = q.front();
            q.pop();

            // Burn left child
            if (node->left && !visited[node->left]) {
                flag = true;
                visited[node->left] = true;
                q.push(node->left);
            }

            // Burn right child
            if (node->right && !visited[node->right]) {
                flag = true;
                visited[node->right] = true;
                q.push(node->right);
            }

            // Burn parent
            if (parentMap[node] && !visited[parentMap[node]]) {
                flag = true;
                visited[parentMap[node]] = true;
                q.push(parentMap[node]);
            }
        }

        // Increase time only if fire spreads
        if (flag) time++;
    }

    return time;
}

/*
----------------------------------------------------
Main BFS-based function
----------------------------------------------------
*/
int timeToBurnTree(TreeNode* root, int start) {
    map<TreeNode*, TreeNode*> parentMap;

    // Map parents and locate target
    TreeNode* target = bfsToMapParents(root, parentMap, start);

    // BFS from target to compute time
    return findMinDistance(parentMap, target);
}

/*
====================================================
APPROACH 2: DFS (RECURSIVE)
====================================================

Idea:
- Perform a post-order DFS.
- Return height of subtrees.
- When target is found, mark it using -1.
- Propagate distance upwards and update answer
  using opposite subtree height.

Time Complexity: O(N)
Space Complexity: O(H)  (H = height of tree)
====================================================
*/
class Solution {
public:
    int ans = 0;

    /*
    Returns:
    - Height of subtree if target not found
    - Negative value representing distance from target
    */
    int solve(TreeNode* node, int start) {
        if (!node) return 0;

        int l = solve(node->left, start);
        int r = solve(node->right, start);

        // Case 1: Current node is target
        if (node->val == start) {
            ans = max(ans, max(l, r));
            return -1; // mark target found
        }
        // Case 2: Target found in left subtree
        else if (l < 0) {
            ans = max(ans, abs(l) + r);
            return l - 1; // increase distance
        }
        // Case 3: Target found in right subtree
        else if (r < 0) {
            ans = max(ans, abs(r) + l);
            return r - 1; // increase distance
        }

        // Case 4: Target not found in subtree
        return 1 + max(l, r);
    }

    int amountOfTime(TreeNode* root, int start) {
        solve(root, start);
        return ans;
    }
};
