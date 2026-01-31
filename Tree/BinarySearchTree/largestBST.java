package Tree.BinarySearchTree;

import java.util.*;

/*
====================================================
📌 Problem Statement
====================================================
Given a Binary Tree (not necessarily a BST),
find the size of the largest subtree that is a
valid Binary Search Tree (BST).

BST rules:
- Left subtree values < root value
- Right subtree values > root value
- Both left and right subtrees must also be BSTs
====================================================
*/

/*
Class: TreeNode
Purpose: Represents a node in a binary tree
*/
class TreeNode {
    int val;
    TreeNode left;
    TreeNode right;

    TreeNode(int value) {
        val = value;
        left = right = null;
    }
}

/* ========================================================
   ✅ BRUTE FORCE APPROACH
   ========================================================
   For each node:
   - Check if the subtree rooted at that node is a valid BST
   - If yes, count the number of nodes
   - Else, recursively check left & right subtrees

   Time Complexity:  O(N^2)
   Space Complexity: O(H)   (recursion stack)
======================================================== */

class LargestBSTBrute {

    // Check whether a subtree is a valid BST
    private boolean isValidBST(TreeNode root, long minVal, long maxVal) {
        if (root == null) return true;

        if (root.val <= minVal || root.val >= maxVal)
            return false;

        return isValidBST(root.left, minVal, root.val) &&
               isValidBST(root.right, root.val, maxVal);
    }

    // Count total nodes in a subtree
    private int countNodes(TreeNode root) {
        if (root == null) return 0;
        return 1 + countNodes(root.left) + countNodes(root.right);
    }

    // Main brute force logic
    public int largestBST(TreeNode root) {
        if (root == null) return 0;

        // If current subtree is a BST, return its size
        if (isValidBST(root, Long.MIN_VALUE, Long.MAX_VALUE))
            return countNodes(root);

        // Otherwise, check left and right subtrees
        return Math.max(
                largestBST(root.left),
                largestBST(root.right)
        );
    }
}

/* ========================================================
   ✅ OPTIMAL APPROACH (Single Traversal)
   ========================================================
   Use postorder traversal and return information
   about each subtree:
   - Minimum value
   - Maximum value
   - Size of largest BST

   Time Complexity:  O(N)
   Space Complexity: O(H)
======================================================== */

/*
Helper class to store subtree information
*/
class NodeValue {
    int minNode;
    int maxNode;
    int maxSize;

    NodeValue(int minNode, int maxNode, int maxSize) {
        this.minNode = minNode;
        this.maxNode = maxNode;
        this.maxSize = maxSize;
    }
}

class LargestBSTOptimal {

    // Recursive postorder traversal
    private NodeValue largestBSTSubtree(TreeNode root) {

        // Base case: empty tree
        if (root == null) {
            return new NodeValue(Integer.MAX_VALUE, Integer.MIN_VALUE, 0);
        }

        // Get info from left and right subtrees
        NodeValue left = largestBSTSubtree(root.left);
        NodeValue right = largestBSTSubtree(root.right);

        // Check if current subtree is a valid BST
        if (left.maxNode < root.val && root.val < right.minNode) {

            // Valid BST → combine results
            return new NodeValue(
                    Math.min(root.val, left.minNode),
                    Math.max(root.val, right.maxNode),
                    left.maxSize + right.maxSize + 1
            );
        }

        // Not a BST → return invalid markers
        return new NodeValue(
                Integer.MIN_VALUE,
                Integer.MAX_VALUE,
                Math.max(left.maxSize, right.maxSize)
        );
    }

    // Wrapper function
    public int largestBST(TreeNode root) {
        return largestBSTSubtree(root).maxSize;
    }
}

/* ========================================================
   🧪 MAIN FUNCTION (Testing)
======================================================== */

public class largestBST{
    public static void main(String[] args) {

        /*
                 10
                /  \
               5    15
              / \     \
             1   8     7

        Largest BST Subtree:
               5
              / \
             1   8
        Size = 3
        */

        TreeNode root = new TreeNode(10);
        root.left = new TreeNode(5);
        root.right = new TreeNode(15);
        root.left.left = new TreeNode(1);
        root.left.right = new TreeNode(8);
        root.right.right = new TreeNode(7);

        LargestBSTBrute brute = new LargestBSTBrute();
        LargestBSTOptimal optimal = new LargestBSTOptimal();

        System.out.println("Brute Force Largest BST Size: " +
                brute.largestBST(root));

        System.out.println("Optimal Largest BST Size: " +
                optimal.largestBST(root));
    }
}

/*
============================================================
🧠 Summary
============================================================

Approach        Time        Space     Notes
------------------------------------------------
Brute Force     O(N^2)      O(H)      Easy but inefficient
Optimal        O(N)        O(H)      Best for interviews

============================================================
*/
