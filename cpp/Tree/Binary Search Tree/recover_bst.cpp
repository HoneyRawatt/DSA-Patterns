#include <bits/stdc++.h>
using namespace std;

/*
====================================================
📌 Problem Statement
====================================================
You are given the root of a Binary Search Tree (BST)
in which exactly two nodes have been swapped by mistake.

Your task is to recover the BST without changing
its structure (i.e., only swap values back).

BST Property:
- Inorder traversal of BST produces a sorted sequence.

====================================================
*/

/*
Class: TreeNode
Purpose: Represents a node in a Binary Search Tree
*/
class TreeNode {
public:
    int val;
    TreeNode* left;
    TreeNode* right;

    TreeNode(int value) {
        val = value;
        left = right = nullptr;
    }
};

/*
====================================================
🟥 BRUTE FORCE APPROACH
====================================================

💡 Intuition:
- Inorder traversal of a correct BST should be sorted.
- If BST is corrupted, inorder sequence will not be sorted.
- Store inorder nodes, sort their values, and rewrite them.

Steps:
1️⃣ Perform inorder traversal and store node pointers.
2️⃣ Extract values and sort them.
3️⃣ Assign sorted values back to nodes.

⚠️ This fixes the BST but uses extra memory.

Time Complexity:
- O(N log N) → sorting inorder values

Space Complexity:
- O(N) → storing nodes and values

====================================================
*/
class BruteForceSolution {
private:
    // Inorder traversal to store node pointers
    void inorder(TreeNode* root, vector<TreeNode*>& nodes) {
        if (!root) return;
        inorder(root->left, nodes);
        nodes.push_back(root);
        inorder(root->right, nodes);
    }

public:
    void recoverTree(TreeNode* root) {
        vector<TreeNode*> nodes;
        inorder(root, nodes);

        // Extract values
        vector<int> values;
        for (auto node : nodes)
            values.push_back(node->val);

        // Sort inorder values
        sort(values.begin(), values.end());

        // Reassign sorted values to nodes
        for (int i = 0; i < nodes.size(); i++) {
            nodes[i]->val = values[i];
        }
    }
};

/*
====================================================
🟩 OPTIMAL APPROACH (Inorder Violation Detection)
====================================================

💡 Key Observation:
- Inorder traversal of BST should be strictly increasing.
- If two nodes are swapped:
  - Either one inversion occurs (adjacent swap)
  - Or two inversions occur (non-adjacent swap)

We track:
- prev   → previously visited node
- first  → first incorrect node
- middle → node next to first (adjacent case)
- last   → second incorrect node (non-adjacent case)

Cases:
1️⃣ Adjacent swap → swap(first, middle)
2️⃣ Non-adjacent swap → swap(first, last)

Time Complexity:
- O(N) → single inorder traversal

Space Complexity:
- O(H) → recursion stack (H = tree height)

====================================================
*/
class OptimalSolution {
private:
    TreeNode* first;
    TreeNode* middle;
    TreeNode* last;
    TreeNode* prev;

    // Inorder traversal to detect swapped nodes
    void inorder(TreeNode* root) {
        if (!root) return;

        inorder(root->left);

        // Detect violation of BST property
        if (prev && root->val < prev->val) {

            // First violation
            if (!first) {
                first = prev;
                middle = root;
            }
            // Second violation
            else {
                last = root;
            }
        }

        prev = root;

        inorder(root->right);
    }

public:
    void recoverTree(TreeNode* root) {
        first = middle = last = nullptr;
        prev = new TreeNode(INT_MIN); // Sentinel node

        inorder(root);

        // Fix swapped nodes
        if (first && last)
            swap(first->val, last->val);      // Non-adjacent swap
        else if (first && middle)
            swap(first->val, middle->val);    // Adjacent swap
    }
};

/*
====================================================
🧪 Utility Function
====================================================
Prints inorder traversal of BST
*/
void printInorder(TreeNode* root) {
    if (!root) return;
    printInorder(root->left);
    cout << root->val << " ";
    printInorder(root->right);
}

/*
====================================================
🧪 Main Function (Testing)
====================================================
*/
int main() {

    /*
        Example BST (corrupted):
               3
              / \
             1   4
                /
               2

        Correct BST should be:
               2
              / \
             1   4
                /
               3
    */

    TreeNode* root = new TreeNode(3);
    root->left = new TreeNode(1);
    root->right = new TreeNode(4);
    root->right->left = new TreeNode(2);

    cout << "Original inorder traversal: ";
    printInorder(root);
    cout << endl;

    // ---- Brute Force Fix ----
    BruteForceSolution brute;
    brute.recoverTree(root);

    cout << "After brute force recovery: ";
    printInorder(root);
    cout << endl;

    // Corrupt again for optimal test
    swap(root->val, root->right->left->val); // swap 3 and 2

    // ---- Optimal Fix ----
    OptimalSolution opt;
    opt.recoverTree(root);

    cout << "After optimal recovery: ";
    printInorder(root);
    cout << endl;

    return 0;
}

/*
====================================================
🧠 Final Comparison
====================================================

Approach        Time        Space       Notes
------------------------------------------------
Brute Force     O(N log N)  O(N)        Simple, extra memory
Optimal        O(N)        O(H)        Best solution

====================================================
*/
