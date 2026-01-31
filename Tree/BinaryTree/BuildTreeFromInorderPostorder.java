package Tree.BinaryTree;

import java.util.*;

/*
Class: TreeNode
Purpose: Represents a node in a binary tree
*/
class TreeNode {
    int val;
    TreeNode left;
    TreeNode right;

    // Constructor to initialize node value
    TreeNode(int val) {
        this.val = val;
        this.left = null;
        this.right = null;
    }
}

public class BuildTreeFromInorderPostorder {

    /*
    Helper function to recursively build the binary tree
    from inorder and postorder traversals.

    inorder   : inorder traversal array
    is, ie    : start and end indices for inorder
    postorder : postorder traversal array
    ps, pe    : start and end indices for postorder
    map       : stores value -> index mapping for inorder
    */
    private static TreeNode buildTreeHelper(
            int[] inorder, int is, int ie,
            int[] postorder, int ps, int pe,
            Map<Integer, Integer> map) {

        // Base case: no elements to construct subtree
        if (ps > pe || is > ie) return null;

        // Last element of postorder is the root
        TreeNode root = new TreeNode(postorder[pe]);

        // Find root index in inorder traversal
        int inRoot = map.get(postorder[pe]);

        // Number of nodes in left subtree
        int numLeft = inRoot - is;

        // Recursively build left subtree
        root.left = buildTreeHelper(
                inorder, is, inRoot - 1,
                postorder, ps, ps + numLeft - 1,
                map
        );

        // Recursively build right subtree
        root.right = buildTreeHelper(
                inorder, inRoot + 1, ie,
                postorder, ps + numLeft, pe - 1,
                map
        );

        return root;
    }

    /*
    Function: buildTree
    Purpose : Initializes hashmap and calls helper function
    */
    public static TreeNode buildTree(int[] inorder, int[] postorder) {
        if (inorder.length != postorder.length) return null;

        // Map each value to its index in inorder traversal
        Map<Integer, Integer> map = new HashMap<>();
        for (int i = 0; i < inorder.length; i++) {
            map.put(inorder[i], i);
        }

        return buildTreeHelper(
                inorder, 0, inorder.length - 1,
                postorder, 0, postorder.length - 1,
                map
        );
    }

    /*
    Utility function to print preorder traversal
    to verify constructed tree
    */
    public static void printPreorder(TreeNode root) {
        if (root == null) return;
        System.out.print(root.val + " ");
        printPreorder(root.left);
        printPreorder(root.right);
    }

    /*
    Main function to test buildTree()
    */
    public static void main(String[] args) {
        int[] inorder = {9, 3, 15, 20, 7};
        int[] postorder = {9, 15, 7, 20, 3};

        TreeNode root = buildTree(inorder, postorder);

        System.out.print("Preorder traversal of constructed tree: ");
        printPreorder(root);
        System.out.println();
    }
}

/*
Expected Output:
Preorder traversal of constructed tree: 3 9 20 15 7

Time Complexity  : O(N)
Space Complexity : O(N)
*/
