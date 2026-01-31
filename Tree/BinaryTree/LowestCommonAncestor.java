package Tree.BinaryTree;

/*
Class: TreeNode
Purpose: Represents a node in a binary tree.
*/
class TreeNode {
    int data;
    TreeNode left;
    TreeNode right;

    TreeNode(int data) {
        this.data = data;
        this.left = null;
        this.right = null;
    }
}

public class LowestCommonAncestor {

    /*
    Function: lowestCommonAncestor()
    Purpose:
        Finds the Lowest Common Ancestor (LCA) of two nodes (p, q) in a Binary Tree.

    Logic:
        - If the current node is null → return null
        - If the current node is equal to p or q → return current node
        - Recurse on both left and right subtrees
        - If both left and right are non-null → current node is LCA
        - If one side is null → propagate the non-null side

    Time Complexity:  O(N)
    Space Complexity: O(H)
    */
    public static TreeNode lowestCommonAncestor(TreeNode root, TreeNode p, TreeNode q) {

        if (root == null || root == p || root == q)
            return root;   // Base condition

        TreeNode left = lowestCommonAncestor(root.left, p, q);
        TreeNode right = lowestCommonAncestor(root.right, p, q);

        if (left == null)
            return right;
        else if (right == null)
            return left;
        else
            return root;   // Both sides found → LCA
    }

    /*
    Example Usage:
    Binary Tree:
             3
            / \
           5   1
          / \ / \
         6  2 0  8
           / \
          7   4
    */
    public static void main(String[] args) {

        TreeNode root = new TreeNode(3);
        root.left = new TreeNode(5);
        root.right = new TreeNode(1);
        root.left.left = new TreeNode(6);
        root.left.right = new TreeNode(2);
        root.right.left = new TreeNode(0);
        root.right.right = new TreeNode(8);
        root.left.right.left = new TreeNode(7);
        root.left.right.right = new TreeNode(4);

        TreeNode p = root.left;     // Node 5
        TreeNode q = root.right;    // Node 1

        TreeNode lca = lowestCommonAncestor(root, p, q);

        System.out.println(
            "LCA of " + p.data + " and " + q.data + " is: " + lca.data
        );
    }
}
