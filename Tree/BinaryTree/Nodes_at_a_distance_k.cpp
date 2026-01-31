#include <iostream>
#include <queue>
#include <unordered_map>
#include <vector>
using namespace std;

/*
====================================================
PROBLEM STATEMENT
====================================================
Given the root of a binary tree, a target node, and an
integer K, return all node values that are at distance
K from the target node.

Distance between two nodes is the number of edges
between them.

Important:
- Nodes can be above or below the target.
- Tree is not a graph, so parent traversal is not
  directly possible.
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
FUNCTION: markParents
====================================================
Purpose:
Creates a mapping from each node to its parent node.
This allows upward traversal from any node.

Approach:
- Perform BFS starting from root.
- For every child, store its parent in the map.

Why needed?
- Binary tree nodes don't have parent pointers.
- To move "upward" during BFS from target, we must
  know each node’s parent.
====================================================
*/
void markParents(TreeNode* root,
                 unordered_map<TreeNode*, TreeNode*>& parent_track) {

    queue<TreeNode*> q;
    q.push(root);

    while (!q.empty()) {
        TreeNode* curr = q.front();
        q.pop();

        if (curr->left) {
            parent_track[curr->left] = curr;
            q.push(curr->left);
        }

        if (curr->right) {
            parent_track[curr->right] = curr;
            q.push(curr->right);
        }
    }
}

/*
====================================================
FUNCTION: distanceK
====================================================
Purpose:
Returns all nodes that are exactly K distance away
from the target node.

High-Level Intuition:
- Convert the tree into an undirected graph:
  (left, right, parent)
- Perform BFS starting from target.
- Stop BFS when distance = K.
- Collect all nodes at that level.

Steps:
1. Mark parent of each node.
2. Start BFS from target node.
3. Track visited nodes to avoid infinite loops.
4. Move level-by-level until distance K.
====================================================
*/
vector<int> distanceK(TreeNode* root, TreeNode* target, int k) {

    // Step 1: Store parent pointers
    unordered_map<TreeNode*, TreeNode*> parent_track;
    markParents(root, parent_track);

    // Step 2: BFS from target node
    unordered_map<TreeNode*, bool> visited;
    queue<TreeNode*> q;

    q.push(target);
    visited[target] = true;

    int currLevel = 0;

    // Step 3: Traverse level by level
    while (!q.empty()) {
        int size = q.size();

        // Stop BFS once we reach distance K
        if (currLevel++ == k) break;

        for (int i = 0; i < size; i++) {
            TreeNode* curr = q.front();
            q.pop();

            // Visit left child
            if (curr->left && !visited[curr->left]) {
                q.push(curr->left);
                visited[curr->left] = true;
            }

            // Visit right child
            if (curr->right && !visited[curr->right]) {
                q.push(curr->right);
                visited[curr->right] = true;
            }

            // Visit parent
            if (parent_track.find(curr) != parent_track.end() &&
                !visited[parent_track[curr]]) {

                q.push(parent_track[curr]);
                visited[parent_track[curr]] = true;
            }
        }
    }

    // Step 4: Remaining nodes in queue are at distance K
    vector<int> res;
    while (!q.empty()) {
        res.push_back(q.front()->data);
        q.pop();
    }

    return res;
}

int main() {

    /*
              3
             / \
            5   1
           / \  / \
          6  2 0   8
            / \
           7   4
    */

    TreeNode* root = new TreeNode(3);
    root->left = new TreeNode(5);
    root->right = new TreeNode(1);
    root->left->left = new TreeNode(6);
    root->left->right = new TreeNode(2);
    root->right->left = new TreeNode(0);
    root->right->right = new TreeNode(8);
    root->left->right->left = new TreeNode(7);
    root->left->right->right = new TreeNode(4);

    TreeNode* target = root->left; // Node with value 5
    int k = 2;

    vector<int> result = distanceK(root, target, k);

    cout << "Nodes at distance " << k
         << " from target " << target->data << ": ";

    for (int val : result) {
        cout << val << " ";
    }
    cout << endl;

    return 0;
}

/*
====================================================
TIME & SPACE COMPLEXITY
====================================================

Time Complexity: O(N)
- Marking parents visits each node once → O(N)
- BFS traversal visits each node at most once → O(N)

Space Complexity: O(N)
- Parent map stores up to N entries
- Visited map stores up to N nodes
- BFS queue can hold up to N nodes in worst case
====================================================
*/
