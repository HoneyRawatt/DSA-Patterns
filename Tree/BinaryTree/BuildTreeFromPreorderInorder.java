package Tree.BinaryTree;

import java.util.*;

/*
Class: TreeNode
Purpose: Represents a node in a binary tree.
Each node contains:
- val   : value of the node
- left  : reference to left child
- right : reference to right child
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

public class BuildTreeFromPreorderInorder {

    /*
    Helper Function: buildTreeHelper

    Purpose:
    Recursively builds the binary tree using preorder and inorder traversals.

    Parameters:
    - preorder : preorder traversal array
    - preStart, preEnd : current range in preorder
    - inorder  : inorder traversal array
    - inStart, inEnd   : current range in inorder
    - map      : stores value -> index mapping of inorder traversal

    Returns:
    - Root node of the constructed subtree

    Time Complexity : O(N)
    Space Complexity: O(N) (recursion stack + hashmap)
    */
    private static TreeNode buildTreeHelper(
            int[] preorder, int preStart, int preEnd,
            int[] inorder, int inStart, int inEnd,
            Map<Integer, Integer> map) {

        // Base case: no elements left to process
        if (preStart > preEnd || inStart > inEnd) {
            return null;
        }

        // First element in preorder range is the root
        TreeNode root = new TreeNode(preorder[preStart]);

        // Find index of root in inorder traversal
        int inRoot = map.get(root.val);

        // Number of nodes in left subtree
        int numLeft = inRoot - inStart;

        /*
        Build left subtree:
        preorder range : preStart + 1 → preStart + numLeft
        inorder range  : inStart → inRoot - 1
        */
        root.left = buildTreeHelper(
                preorder,
                preStart + 1,
                preStart + numLeft,
                inorder,
                inStart,
                inRoot - 1,
                map
        );

        /*
        Build right subtree:
        preorder range : preStart + numLeft + 1 → preEnd
        inorder range  : inRoot + 1 → inEnd
        */
        root.right = buildTreeHelper(
                preorder,
                preStart + numLeft + 1,
                preEnd,
                inorder,
                inRoot + 1,
                inEnd,
                map
        );

        return root;
    }

    /*
    Function: buildTree

    Purpose:
    Builds a binary tree from preorder and inorder traversal arrays.

    Steps:
    1. Store inorder indices in a hashmap for O(1) lookup.
    2. Call recursive helper to construct the tree.

    Time Complexity : O(N)
    Space Complexity: O(N)
    */
    public static TreeNode buildTree(int[] preorder, int[] inorder) {

        // Map to store value -> index mapping of inorder traversal
        Map<Integer, Integer> map = new HashMap<>();
        for (int i = 0; i < inorder.length; i++) {
            map.put(inorder[i], i);
        }

        return buildTreeHelper(
                preorder,
                0, preorder.length - 1,
                inorder,
                0, inorder.length - 1,
                map
        );
    }

    /*
    Utility Function: printInorder

    Purpose:
    Prints inorder traversal of the tree.
    Used to verify correctness of the constructed tree.
    */
    private static void printInorder(TreeNode root) {
        if (root == null) return;
        printInorder(root.left);
        System.out.print(root.val + " ");
        printInorder(root.right);
    }

    /*
    Main function to test buildTree()
    */
    public static void main(String[] args) {
        int[] preorder = {3, 9, 20, 15, 7};
        int[] inorder  = {9, 3, 15, 20, 7};

        // Build tree
        TreeNode root = buildTree(preorder, inorder);

        // Verify using inorder traversal
        System.out.print("Inorder traversal of constructed tree: ");
        printInorder(root); // should match original inorder array
        System.out.println();
    }
}
