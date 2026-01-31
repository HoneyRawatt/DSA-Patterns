import java.util.*;

/*
====================================================
📌 Problem Statement
====================================================
Given the root of a Binary Search Tree (BST) and an
integer k, determine whether there exist two distinct
nodes in the BST such that their values sum up to k.

Constraints:
- Each node can be used at most once
- BST property should be leveraged for efficiency
====================================================
*/

/*
Class: TreeNode
Purpose: Represents a node in a Binary Search Tree (BST)
*/
class TreeNode {
    int val;
    TreeNode left;
    TreeNode right;

    TreeNode(int val) {
        this.val = val;
        left = right = null;
    }
}

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
- Using two iterators allows a two-pointer technique
  directly on the BST without storing all values.
====================================================
*/
class BSTIterator {
    private Stack<TreeNode> stack = new Stack<>();
    private boolean reverse; // false → normal inorder, true → reverse inorder

    // Constructor
    BSTIterator(TreeNode root, boolean isReverse) {
        reverse = isReverse;
        pushAll(root);
    }

    // Returns true if there is a next element
    boolean hasNext() {
        return !stack.isEmpty();
    }

    // Returns the next element based on traversal order
    int next() {
        TreeNode node = stack.pop();

        if (!reverse)
            pushAll(node.right); // normal inorder
        else
            pushAll(node.left);  // reverse inorder

        return node.val;
    }

    // Push nodes into stack based on traversal direction
    private void pushAll(TreeNode node) {
        while (node != null) {
            stack.push(node);
            if (reverse)
                node = node.right;
            else
                node = node.left;
        }
    }
}

/*
====================================================
🟩 OPTIMAL APPROACH (Two Iterators)
====================================================
💡 Idea:
- Use two BST iterators:
  - One from smallest value
  - One from largest value
- Apply two-pointer technique

Time Complexity:  O(N)
Space Complexity: O(H)
(where H = height of BST)
====================================================
*/
class Solution {

    public boolean findTarget(TreeNode root, int k) {
        if (root == null) return false;

        BSTIterator leftIter = new BSTIterator(root, false); // ascending
        BSTIterator rightIter = new BSTIterator(root, true); // descending

        int i = leftIter.next();
        int j = rightIter.next();

        while (i < j) {
            int sum = i + j;
            if (sum == k) return true;
            else if (sum < k) i = leftIter.next();
            else j = rightIter.next();
        }
        return false;
    }

    /*
    ====================================================
    🟥 BRUTE FORCE APPROACH
    ====================================================
    - Store inorder traversal in a list
    - Use two pointers on sorted list

    Time Complexity:  O(N)
    Space Complexity: O(N)
    ====================================================
    */
    void inorderTraversal(TreeNode root, List<Integer> nums) {
        if (root == null) return;
        inorderTraversal(root.left, nums);
        nums.add(root.val);
        inorderTraversal(root.right, nums);
    }

    public boolean findTargetBrute(TreeNode root, int k) {
        List<Integer> nums = new ArrayList<>();
        inorderTraversal(root, nums);

        int left = 0, right = nums.size() - 1;

        while (left < right) {
            int sum = nums.get(left) + nums.get(right);
            if (sum == k) return true;
            else if (sum < k) left++;
            else right--;
        }
        return false;
    }
}

/*
====================================================
🧪 Main Class for Testing
====================================================
*/
public class TwoSumIV{
    public static void main(String[] args) {

        /*
               5
              / \
             3   8
            / \   \
           2   4   9
        */
        TreeNode root = new TreeNode(5);
        root.left = new TreeNode(3);
        root.right = new TreeNode(8);
        root.left.left = new TreeNode(2);
        root.left.right = new TreeNode(4);
        root.right.right = new TreeNode(9);

        int k = 7;
        Solution sol = new Solution();

        if (sol.findTarget(root, k))
            System.out.println("Pair found for sum " + k);
        else
            System.out.println("No pair found for sum " + k);
    }
}

/*
====================================================
🧠 Complexity Summary
====================================================

Brute Force:
- Time:  O(N)
- Space: O(N)

Optimal (BST Iterators):
- Time:  O(N)
- Space: O(H)

====================================================
*/
