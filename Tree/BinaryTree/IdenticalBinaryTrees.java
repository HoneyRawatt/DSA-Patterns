package Tree.BinaryTree;

/*
====================================================
Problem Statement: Check if Two Binary Trees are Identical
====================================================

Given the roots of two binary trees p and q, determine
whether they are identical.

Two binary trees are considered identical if:
1. They have the same structure.
2. Corresponding nodes have the same values.

----------------------------------------------------
Example:
Tree p:        1          Tree q:        1
              / \                       / \
             2   3                     2   3
Result: Identical

If any node value or structure differs → NOT identical
----------------------------------------------------

Time Complexity: O(N)
Space Complexity: O(H)
====================================================
*/

class TreeNode {
    int data;
    TreeNode left;
    TreeNode right;

    // Constructor
    TreeNode(int data) {
        this.data = data;
        this.left = null;
        this.right = null;
    }
}

public class IdenticalBinaryTrees {

    /*
    Function: check
    Purpose:
        Checks whether two binary trees are identical.

    Approach:
        - If both nodes are null → identical
        - If only one is null → not identical
        - Compare node values
        - Recursively compare left and right subtrees

    Time Complexity: O(N)
    Space Complexity: O(H)
    */
    static boolean check(TreeNode p, TreeNode q) {

        // Base case: if either node is null
        if (p == null || q == null)
            return p == q;

        // Check current node value and both subtrees
        return (p.data == q.data)
                && check(p.left, q.left)
                && check(p.right, q.right);
    }

    /*
    Example usage
    */
    public static void main(String[] args) {

        // -------- Tree 1 --------
        //        1
        //       / \
        //      2   3
        TreeNode p = new TreeNode(1);
        p.left = new TreeNode(2);
        p.right = new TreeNode(3);

        // -------- Tree 2 --------
        //        1
        //       / \
        //      2   3
        TreeNode q = new TreeNode(1);
        q.left = new TreeNode(2);
        q.right = new TreeNode(3);

        // Check identical trees
        System.out.println(
            check(p, q) ? 
            "Both trees are identical" : 
            "Trees are not identical"
        );

        // Modify Tree 2
        q.right.data = 4;

        // Check again
        System.out.println(
            check(p, q) ? 
            "Both trees are identical" : 
            "Trees are not identical"
        );
    }
}

