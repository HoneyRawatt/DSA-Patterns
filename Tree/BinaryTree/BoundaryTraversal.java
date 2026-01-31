package Tree.BinaryTree;

import java.util.*;

/*
====================================================
Problem Statement: Boundary Traversal of a Binary Tree
====================================================

Given the root of a binary tree, return its boundary
traversal in an anti-clockwise direction.

The boundary traversal consists of:
1. Root node (if it is not a leaf)
2. Left boundary (excluding leaf nodes)
3. All leaf nodes (from left to right)
4. Right boundary (excluding leaf nodes, in reverse order)

----------------------------------------------------
Time Complexity: O(N)
Space Complexity: O(H)
    N = number of nodes
    H = height of the tree
====================================================
*/

/*
Class: TreeNode
Purpose: Represents a node in a binary tree
*/
class TreeNode {
    int data;
    TreeNode left, right;

    TreeNode(int data) {
        this.data = data;
        this.left = null;
        this.right = null;
    }
}

public class BoundaryTraversal {

    /*
    Function: isLeaf
    Purpose: Checks if a node is a leaf node

    Time Complexity: O(1)
    Space Complexity: O(1)
    */
    static boolean isLeaf(TreeNode node) {
        return node.left == null && node.right == null;
    }

    /*
    Function: addLeftBoundary
    Purpose:
        Adds all left boundary nodes excluding leaf nodes

    Time Complexity: O(H)
    Space Complexity: O(1)
    */
    static void addLeftBoundary(TreeNode root, List<Integer> res) {
        TreeNode curr = root.left;

        while (curr != null) {
            if (!isLeaf(curr))
                res.add(curr.data);

            if (curr.left != null)
                curr = curr.left;
            else
                curr = curr.right;
        }
    }

    /*
    Function: addRightBoundary
    Purpose:
        Adds right boundary nodes excluding leaf nodes
        in reverse (bottom-up) order

    Time Complexity: O(H)
    Space Complexity: O(H)
    */
    static void addRightBoundary(TreeNode root, List<Integer> res) {
        TreeNode curr = root.right;
        List<Integer> temp = new ArrayList<>();

        while (curr != null) {
            if (!isLeaf(curr))
                temp.add(curr.data);

            if (curr.right != null)
                curr = curr.right;
            else
                curr = curr.left;
        }

        // Add right boundary in reverse order
        for (int i = temp.size() - 1; i >= 0; i--) {
            res.add(temp.get(i));
        }
    }

    /*
    Function: addLeaves
    Purpose:
        Adds all leaf nodes from left to right

    Time Complexity: O(N)
    Space Complexity: O(H)
    */
    static void addLeaves(TreeNode root, List<Integer> res) {
        if (root == null)
            return;

        if (isLeaf(root)) {
            res.add(root.data);
            return;
        }

        addLeaves(root.left, res);
        addLeaves(root.right, res);
    }

    /*
    Function: printBoundary
    Purpose:
        Returns boundary traversal of a binary tree

    Time Complexity: O(N)
    Space Complexity: O(H)
    */
    static List<Integer> printBoundary(TreeNode root) {
        List<Integer> res = new ArrayList<>();
        if (root == null)
            return res;

        // Add root if it's not a leaf
        if (!isLeaf(root))
            res.add(root.data);

        addLeftBoundary(root, res);   // Left boundary
        addLeaves(root, res);         // Leaf nodes
        addRightBoundary(root, res);  // Right boundary

        return res;
    }

    /*
    Driver Code
    */
    public static void main(String[] args) {

        /*
              1
            /   \
           2     3
          / \   / \
         4   5 6   7
            / \
           8   9
        */

        TreeNode root = new TreeNode(1);
        root.left = new TreeNode(2);
        root.right = new TreeNode(3);
        root.left.left = new TreeNode(4);
        root.left.right = new TreeNode(5);
        root.left.right.left = new TreeNode(8);
        root.left.right.right = new TreeNode(9);
        root.right.left = new TreeNode(6);
        root.right.right = new TreeNode(7);

        List<Integer> boundary = printBoundary(root);

        System.out.print("Boundary Traversal: ");
        for (int val : boundary)
            System.out.print(val + " ");
    }
}

