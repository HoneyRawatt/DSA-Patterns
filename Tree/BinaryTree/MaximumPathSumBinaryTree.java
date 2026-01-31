package Tree.BinaryTree;
/*
====================================================
Problem Statement: Maximum Path Sum in a Binary Tree
====================================================

Given the root of a binary tree, find the maximum path sum.

A path in the tree is defined as a sequence of nodes where:
- Each pair of adjacent nodes in the sequence has an edge connecting them.
- A node can appear at most once in the path.
- The path does NOT need to pass through the root.
- The path must contain at least one node.

The path sum is the sum of the values of all nodes present in the path.

----------------------------------------------------
Key Observations:
- The path may start and end at any node.
- Negative node values are allowed.
- Negative contributions should be ignored if they reduce the sum.

----------------------------------------------------
Expected Complexity:
- Time Complexity: O(N)
- Space Complexity: O(H) where H is the height of the tree
====================================================
*/

public class MaximumPathSumBinaryTree {

    // Definition of TreeNode
    static class TreeNode {
        int data;
        TreeNode left;
        TreeNode right;

        TreeNode(int data) {
            this.data = data;
            this.left = null;
            this.right = null;
        }
    }

    /*
    Function: maxPathSumHelper
    Purpose:
        Recursive helper to compute maximum path sum in a binary tree.

    Returns:
        Maximum path sum starting from the current node and going downward.

    Updates:
        maxi[0] — stores the maximum path sum found anywhere in the tree.

    Logic:
        - Compute left and right subtree sums recursively.
        - Ignore negative contributions using Math.max(0, ...).
        - Update global maximum considering path through current node.
        - Return best downward path for parent calls.

    Time Complexity: O(N)
    Space Complexity: O(H)
    */
    static int maxPathSumHelper(TreeNode root, int[] maxi) {
        if (root == null) return 0;

        int leftSum = Math.max(0, maxPathSumHelper(root.left, maxi));
        int rightSum = Math.max(0, maxPathSumHelper(root.right, maxi));

        // Path passing through current node
        maxi[0] = Math.max(maxi[0], leftSum + rightSum + root.data);

        // Return max path starting from current node
        return root.data + Math.max(leftSum, rightSum);
    }

    /*
    Function: maxPathSum
    Purpose:
        Returns the maximum path sum in the binary tree.
    */
    static int maxPathSum(TreeNode root) {
        int[] maxi = new int[]{Integer.MIN_VALUE};
        maxPathSumHelper(root, maxi);
        return maxi[0];
    }

    /* Example usage */
    public static void main(String[] args) {
        TreeNode root = new TreeNode(10);
        root.left = new TreeNode(2);
        root.right = new TreeNode(10);
        root.left.left = new TreeNode(20);
        root.left.right = new TreeNode(1);
        root.right.right = new TreeNode(-25);
        root.right.right.left = new TreeNode(3);
        root.right.right.right = new TreeNode(4);

        System.out.println("Maximum Path Sum: " + maxPathSum(root));
    }
}

