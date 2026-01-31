package Tree.BinarySearchTree;

/*
====================================================
📌 Problem Statement
====================================================
Given a Binary Search Tree (BST) and two nodes p and q,
find their Lowest Common Ancestor (LCA).

The Lowest Common Ancestor is the lowest node in the tree
that has both p and q as descendants (a node can be a
descendant of itself).
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
        this.left = null;
        this.right = null;
    }
}

public class LCAinBST {

    /*
    ====================================================
    Function: lowestCommonAncestor
    Purpose: Finds the Lowest Common Ancestor (LCA) of
             two given nodes (p and q) in a BST.

    Approach:
    - If both p and q are smaller than the current node
      → LCA lies in the left subtree.
    - If both p and q are greater than the current node
      → LCA lies in the right subtree.
    - Otherwise → current node is the split point
      (the LCA).

    Time Complexity: O(h)   (h = height of the tree)
    Space Complexity: O(h) (recursive call stack)
    ====================================================
    */
    static TreeNode lowestCommonAncestor(TreeNode root,
                                         TreeNode p,
                                         TreeNode q) {

        // Base case: empty tree
        if (root == null)
            return null;

        int curr = root.val;

        // Both nodes lie in right subtree
        if (curr < p.val && curr < q.val)
            return lowestCommonAncestor(root.right, p, q);

        // Both nodes lie in left subtree
        if (curr > p.val && curr > q.val)
            return lowestCommonAncestor(root.left, p, q);

        // Split point → this node is LCA
        return root;
    }

    /*
    ====================================================
    🧪 Example Usage
    ====================================================
    Constructing the following BST:

                 6
                / \
               2   8
              / \ / \
             0  4 7  9
               / \
              3   5
    ====================================================
    */
    public static void main(String[] args) {

        TreeNode root = new TreeNode(6);
        root.left = new TreeNode(2);
        root.right = new TreeNode(8);

        root.left.left = new TreeNode(0);
        root.left.right = new TreeNode(4);
        root.left.right.left = new TreeNode(3);
        root.left.right.right = new TreeNode(5);

        root.right.left = new TreeNode(7);
        root.right.right = new TreeNode(9);

        TreeNode p = root.left;   // Node with value 2
        TreeNode q = root.right;  // Node with value 8

        TreeNode ans = lowestCommonAncestor(root, p, q);

        if (ans != null)
            System.out.println(
                "Lowest Common Ancestor of " + p.val +
                " and " + q.val + " is: " + ans.val
            );
        else
            System.out.println("No common ancestor found.");
    }
}
