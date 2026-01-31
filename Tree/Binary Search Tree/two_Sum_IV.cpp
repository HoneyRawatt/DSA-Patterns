#include <iostream>
#include <vector>
#include <stack>
using namespace std;

/*
====================================================
📌 Problem Statement
====================================================
Given the root of a Binary Search Tree (BST) and an
integer k, determine whether there exist two distinct
nodes in the BST such that their values sum up to k.

Constraints:
- Each node can be used at most once
- BST property must be leveraged for efficiency
====================================================
*/

/*
Class: TreeNode
Purpose: Represents a node in a Binary Search Tree (BST)
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

/*
====================================================
Class: BSTIterator
====================================================
💡 Purpose:
- Supports inorder traversal of BST.
- Can work in:
  - Normal inorder (ascending order)
  - Reverse inorder (descending order)

💡 Intuition:
- Inorder traversal of BST gives sorted values.
- Reverse inorder gives values in decreasing order.
- Using two iterators allows a "two-pointer" technique
  directly on the BST without storing all values.
====================================================
*/
class BSTIterator {
    stack<TreeNode*> st;
    bool reverse; // false → normal inorder, true → reverse inorder

public:
    /*
    Constructor:
    - Initializes iterator direction.
    - Pushes all required nodes into stack.
    */
    BSTIterator(TreeNode* root, bool isReverse) {
        reverse = isReverse;
        pushAll(root);
    }

    /*
    Function: hasNext
    Purpose:
    - Checks if there is a next element available
    */
    bool hasNext() {
        return !st.empty();
    }

    /*
    Function: next
    Purpose:
    - Returns the next element based on traversal order
    */
    int next() {
        TreeNode* tmp = st.top();
        st.pop();

        // Move iterator forward based on traversal direction
        if (!reverse)
            pushAll(tmp->right); // normal inorder
        else
            pushAll(tmp->left);  // reverse inorder

        return tmp->val;
    }

private:
    /*
    Helper Function: pushAll
    Purpose:
    - Pushes nodes into stack following traversal direction
    */
    void pushAll(TreeNode* node) {
        while (node != nullptr) {
            st.push(node);
            if (reverse)
                node = node->right; // reverse inorder
            else
                node = node->left;  // normal inorder
        }
    }
};

/*
====================================================
🟩 OPTIMAL APPROACH (Two Iterators)
====================================================
💡 Idea:
- Use two BST iterators:
  - One from smallest value (left iterator)
  - One from largest value (right iterator)
- Apply two-pointer technique like a sorted array

Steps:
1️⃣ Get smallest value using inorder iterator
2️⃣ Get largest value using reverse inorder iterator
3️⃣ Compare sum with k
   - If sum == k → return true
   - If sum < k → move left iterator
   - If sum > k → move right iterator

Time Complexity:  O(n)
Space Complexity: O(h)
(where h = height of BST)
====================================================
*/
bool findTarget(TreeNode* root, int k) {
    if (!root) return false;

    BSTIterator leftIter(root, false);  // smallest → largest
    BSTIterator rightIter(root, true);  // largest → smallest

    int i = leftIter.next();
    int j = rightIter.next();

    while (i < j) {
        if (i + j == k) return true;
        else if (i + j < k) i = leftIter.next();
        else j = rightIter.next();
    }
    return false;
}

/*
====================================================
🟥 BRUTE FORCE APPROACH
====================================================
💡 Idea:
- Store inorder traversal in a vector (sorted list)
- Apply two-pointer technique on vector

Time Complexity:  O(n)
Space Complexity: O(n)
====================================================
*/
void inorderTraversal(TreeNode* root, vector<int>& nums) {
    if (!root) return;
    inorderTraversal(root->left, nums);
    nums.push_back(root->val);
    inorderTraversal(root->right, nums);
}

bool findTargetBrute(TreeNode* root, int k) {
    vector<int> nums;
    inorderTraversal(root, nums);

    int left = 0;
    int right = nums.size() - 1;

    while (left < right) {
        int sum = nums[left] + nums[right];
        if (sum == k) return true;
        else if (sum < k) left++;
        else right--;
    }
    return false;
}

/*
====================================================
🧪 Main Function (Testing)
====================================================
*/
int main() {
    /*
           5
          / \
         3   8
        / \   \
       2   4   9
    */
    TreeNode* root = new TreeNode(5);
    root->left = new TreeNode(3);
    root->right = new TreeNode(8);
    root->left->left = new TreeNode(2);
    root->left->right = new TreeNode(4);
    root->right->right = new TreeNode(9);

    int k = 7;
    if (findTarget(root, k))
        cout << "Pair found for sum " << k << endl;
    else
        cout << "No pair found for sum " << k << endl;

    return 0;
}

/*
====================================================
🧠 Final Complexity Comparison
====================================================

Brute Force:
- Time:  O(n)
- Space: O(n)

Optimal (BST Iterators):
- Time:  O(n)
- Space: O(h)  ← better

====================================================
*/
