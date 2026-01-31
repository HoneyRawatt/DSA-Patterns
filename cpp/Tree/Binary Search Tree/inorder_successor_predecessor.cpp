#include <iostream>
#include <vector>
#include <climits>
using namespace std;

/*
Class: TreeNode
Purpose: Represents a node in a binary search tree (BST)
*/
class TreeNode {
public:
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int val) {
        this->val = val;
        left = right = nullptr;
    }
};

/* ---------------------------------------------------------
   Helper: Insert node into BST
--------------------------------------------------------- */
TreeNode* insertBST(TreeNode* root, int val) {
    if (!root) return new TreeNode(val);
    if (val < root->val)
        root->left = insertBST(root->left, val);
    else
        root->right = insertBST(root->right, val);
    return root;
}

/* ---------------------------------------------------------
   🟥 BRUTE FORCE APPROACH
   Idea:
     1. Do an inorder traversal (sorted order for BST).
     2. Store all nodes in a vector.
     3. Find the index of 'p', then
        predecessor = inorder[i-1]
        successor   = inorder[i+1]
   Time Complexity:  O(n)
   Space Complexity: O(n)
--------------------------------------------------------- */
void inorderStore(TreeNode* root, vector<TreeNode*>& inorder) {
    if (!root) return;
    inorderStore(root->left, inorder);
    inorder.push_back(root);
    inorderStore(root->right, inorder);
}

pair<TreeNode*, TreeNode*> brutePreSuc(TreeNode* root, TreeNode* p) {
    vector<TreeNode*> inorder;
    inorderStore(root, inorder);
    TreeNode* pred = nullptr;
    TreeNode* succ = nullptr;

    for (int i = 0; i < inorder.size(); i++) {
        if (inorder[i]->val == p->val) {
            if (i > 0) pred = inorder[i - 1];
            if (i < inorder.size() - 1) succ = inorder[i + 1];
            break;
        }
    }
    return {pred, succ};
}

/* ---------------------------------------------------------
   🟧 BETTER APPROACH
   Idea:
     1. Traverse inorder recursively.
     2. Keep track of previous node.
     3. When previous == p → next node is successor.
        When current == p → previous node is predecessor.
   Time Complexity:  O(n)
   Space Complexity: O(h) (stack recursion)
--------------------------------------------------------- */
void inorderBetter(TreeNode* root, TreeNode* p,
                   TreeNode*& prev, TreeNode*& pred, TreeNode*& succ) {
    if (!root) return;

    inorderBetter(root->left, p, prev, pred, succ);

    if (prev == p) succ = root;
    if (root == p) pred = prev;
    prev = root;

    inorderBetter(root->right, p, prev, pred, succ);
}

pair<TreeNode*, TreeNode*> betterPreSuc(TreeNode* root, TreeNode* p) {
    TreeNode* prev = nullptr;
    TreeNode* pred = nullptr;
    TreeNode* succ = nullptr;
    inorderBetter(root, p, prev, pred, succ);
    return {pred, succ};
}

/* ---------------------------------------------------------
   🟩 OPTIMAL APPROACH
   Idea:
     1. Use BST property.
     2. To find successor:
          - If p->val >= root->val → go right.
          - Else → successor = root; go left.
     3. To find predecessor:
          - If p->val <= root->val → go left.
          - Else → predecessor = root; go right.
   Time Complexity:  O(h)
   Space Complexity: O(1)
--------------------------------------------------------- */
TreeNode* inorderSuccessor(TreeNode* root, TreeNode* p) {
    TreeNode* successor = nullptr;
    while (root != nullptr) {
        if (p->val >= root->val)
            root = root->right;
        else {
            successor = root;
            root = root->left;
        }
    }
    return successor;
}

TreeNode* inorderPredecessor(TreeNode* root, TreeNode* p) {
    TreeNode* predecessor = nullptr;
    while (root != nullptr) {
        if (p->val <= root->val)
            root = root->left;
        else {
            predecessor = root;
            root = root->right;
        }
    }
    return predecessor;
}

/* ---------------------------------------------------------
   MAIN FUNCTION: Test all approaches
--------------------------------------------------------- */
int main() {
    /*
        Construct BST:
                 20
               /    \
             10      30
            /  \    /  \
           5   15  25  35
    */
    TreeNode* root = nullptr;
    vector<int> vals = {20, 10, 30, 5, 15, 25, 35};
    for (int v : vals) root = insertBST(root, v);

    TreeNode* p = root->left; // Node with value 10

    // --- Brute Force ---
    auto bruteRes = brutePreSuc(root, p);
    cout << "Brute Force → Pred: "
         << (bruteRes.first ? to_string(bruteRes.first->val) : "None")
         << ", Succ: "
         << (bruteRes.second ? to_string(bruteRes.second->val) : "None") << endl;

    // --- Better Approach ---
    auto betterRes = betterPreSuc(root, p);
    cout << "Better Approach → Pred: "
         << (betterRes.first ? to_string(betterRes.first->val) : "None")
         << ", Succ: "
         << (betterRes.second ? to_string(betterRes.second->val) : "None") << endl;

    // --- Optimal Approach ---
    TreeNode* predOpt = inorderPredecessor(root, p);
    TreeNode* succOpt = inorderSuccessor(root, p);
    cout << "Optimal Approach → Pred: "
         << (predOpt ? to_string(predOpt->val) : "None")
         << ", Succ: "
         << (succOpt ? to_string(succOpt->val) : "None") << endl;

    return 0;
}
