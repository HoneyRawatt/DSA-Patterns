package Tree.BinarySearchTree;

import java.util.*;

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
        this.left = this.right = null;
    }
}

public class BSTFromPreorder {

    // -------------------------------------------------
    // Helper: Insert a node into BST
    // -------------------------------------------------
    static TreeNode insertBST(TreeNode root, int val) {
        if (root == null) return new TreeNode(val);

        if (val < root.val)
            root.left = insertBST(root.left, val);
        else
            root.right = insertBST(root.right, val);

        return root;
    }

    // -------------------------------------------------
    // Brute Force Approach
    // Build BST by inserting preorder elements one by one
    // Time: O(N^2)
    // Space: O(N)
    // -------------------------------------------------
    static TreeNode bstFromPreorder_Brute(int[] preorder) {
        TreeNode root = null;
        for (int val : preorder) {
            root = insertBST(root, val);
        }
        return root;
    }

    // -------------------------------------------------
    // Helper for Better Approach (Preorder + Inorder)
    // -------------------------------------------------
    static TreeNode buildTree(
            int[] preorder, int preStart, int preEnd,
            int[] inorder, int inStart, int inEnd,
            Map<Integer, Integer> inMap) {

        if (preStart > preEnd || inStart > inEnd)
            return null;

        TreeNode root = new TreeNode(preorder[preStart]);
        int inRoot = inMap.get(root.val);
        int numsLeft = inRoot - inStart;

        root.left = buildTree(
                preorder, preStart + 1, preStart + numsLeft,
                inorder, inStart, inRoot - 1, inMap
        );

        root.right = buildTree(
                preorder, preStart + numsLeft + 1, preEnd,
                inorder, inRoot + 1, inEnd, inMap
        );

        return root;
    }

    // -------------------------------------------------
    // Better Approach
    // Sort preorder → get inorder → build BST
    // Time: O(N log N)
    // Space: O(N)
    // -------------------------------------------------
    static TreeNode bstFromPreorder_Better(int[] preorder) {
        int[] inorder = preorder.clone();
        Arrays.sort(inorder);

        Map<Integer, Integer> inMap = new HashMap<>();
        for (int i = 0; i < inorder.length; i++)
            inMap.put(inorder[i], i);

        return buildTree(
                preorder, 0, preorder.length - 1,
                inorder, 0, inorder.length - 1,
                inMap
        );
    }

    // -------------------------------------------------
    // Optimal Approach Helper (Using bounds)
    // -------------------------------------------------
    static TreeNode buildBST(int[] preorder, int[] index, int bound) {
        if (index[0] == preorder.length || preorder[index[0]] > bound)
            return null;

        TreeNode root = new TreeNode(preorder[index[0]++]);
        root.left = buildBST(preorder, index, root.val);
        root.right = buildBST(preorder, index, bound);

        return root;
    }

    // -------------------------------------------------
    // Optimal Approach
    // Use preorder directly with upper bounds
    // Time: O(N)
    // Space: O(N)
    // -------------------------------------------------
    static TreeNode bstFromPreorder_Optimal(int[] preorder) {
        int[] index = {0};
        return buildBST(preorder, index, Integer.MAX_VALUE);
    }

    // -------------------------------------------------
    // Inorder traversal (to verify BST)
    // -------------------------------------------------
    static void printInorder(TreeNode root) {
        if (root == null) return;
        printInorder(root.left);
        System.out.print(root.val + " ");
        printInorder(root.right);
    }

    // -------------------------------------------------
    // MAIN
    // -------------------------------------------------
    public static void main(String[] args) {

        int[] preorder = {8, 5, 1, 7, 10, 12};

        System.out.print("Brute Force BST Inorder: ");
        TreeNode root1 = bstFromPreorder_Brute(preorder);
        printInorder(root1);
        System.out.println();

        System.out.print("Better Approach BST Inorder: ");
        TreeNode root2 = bstFromPreorder_Better(preorder);
        printInorder(root2);
        System.out.println();

        System.out.print("Optimal Approach BST Inorder: ");
        TreeNode root3 = bstFromPreorder_Optimal(preorder);
        printInorder(root3);
        System.out.println();
    }
}

