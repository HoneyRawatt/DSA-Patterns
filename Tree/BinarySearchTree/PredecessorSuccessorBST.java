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

public class PredecessorSuccessorBST {

    /* ---------------------------------------------------------
       Helper: Insert node into BST
    --------------------------------------------------------- */
    static TreeNode insertBST(TreeNode root, int val) {
        if (root == null) return new TreeNode(val);

        if (val < root.val)
            root.left = insertBST(root.left, val);
        else
            root.right = insertBST(root.right, val);

        return root;
    }

    /* ---------------------------------------------------------
       🟥 BRUTE FORCE APPROACH
       Time:  O(n)
       Space: O(n)
    --------------------------------------------------------- */
    static void inorderStore(TreeNode root, List<TreeNode> inorder) {
        if (root == null) return;
        inorderStore(root.left, inorder);
        inorder.add(root);
        inorderStore(root.right, inorder);
    }

    static TreeNode[] brutePreSuc(TreeNode root, TreeNode p) {
        List<TreeNode> inorder = new ArrayList<>();
        inorderStore(root, inorder);

        TreeNode pred = null, succ = null;

        for (int i = 0; i < inorder.size(); i++) {
            if (inorder.get(i).val == p.val) {
                if (i > 0) pred = inorder.get(i - 1);
                if (i < inorder.size() - 1) succ = inorder.get(i + 1);
                break;
            }
        }
        return new TreeNode[]{pred, succ};
    }

    /* ---------------------------------------------------------
       🟧 BETTER APPROACH (Recursive inorder)
       Time:  O(n)
       Space: O(h)
    --------------------------------------------------------- */
    static void inorderBetter(
            TreeNode root, TreeNode p,
            TreeNode[] prev, TreeNode[] pred, TreeNode[] succ) {

        if (root == null) return;

        inorderBetter(root.left, p, prev, pred, succ);

        if (prev[0] == p) succ[0] = root;
        if (root == p) pred[0] = prev[0];
        prev[0] = root;

        inorderBetter(root.right, p, prev, pred, succ);
    }

    static TreeNode[] betterPreSuc(TreeNode root, TreeNode p) {
        TreeNode[] prev = new TreeNode[1];
        TreeNode[] pred = new TreeNode[1];
        TreeNode[] succ = new TreeNode[1];

        inorderBetter(root, p, prev, pred, succ);
        return new TreeNode[]{pred[0], succ[0]};
    }

    /* ---------------------------------------------------------
       🟩 OPTIMAL APPROACH (Using BST property)
       Time:  O(h)
       Space: O(1)
    --------------------------------------------------------- */
    static TreeNode inorderSuccessor(TreeNode root, TreeNode p) {
        TreeNode successor = null;

        while (root != null) {
            if (p.val >= root.val) {
                root = root.right;
            } else {
                successor = root;
                root = root.left;
            }
        }
        return successor;
    }

    static TreeNode inorderPredecessor(TreeNode root, TreeNode p) {
        TreeNode predecessor = null;

        while (root != null) {
            if (p.val <= root.val) {
                root = root.left;
            } else {
                predecessor = root;
                root = root.right;
            }
        }
        return predecessor;
    }

    /* ---------------------------------------------------------
       MAIN FUNCTION
    --------------------------------------------------------- */
    public static void main(String[] args) {

        /*
            Construct BST:
                     20
                   /    \
                 10      30
                /  \    /  \
               5   15  25  35
        */
        TreeNode root = null;
        int[] values = {20, 10, 30, 5, 15, 25, 35};
        for (int v : values)
            root = insertBST(root, v);

        TreeNode p = root.left; // Node with value 10

        // --- Brute Force ---
        TreeNode[] brute = brutePreSuc(root, p);
        System.out.println("Brute Force → Pred: "
                + (brute[0] != null ? brute[0].val : "None")
                + ", Succ: "
                + (brute[1] != null ? brute[1].val : "None"));

        // --- Better Approach ---
        TreeNode[] better = betterPreSuc(root, p);
        System.out.println("Better Approach → Pred: "
                + (better[0] != null ? better[0].val : "None")
                + ", Succ: "
                + (better[1] != null ? better[1].val : "None"));

        // --- Optimal Approach ---
        TreeNode predOpt = inorderPredecessor(root, p);
        TreeNode succOpt = inorderSuccessor(root, p);
        System.out.println("Optimal Approach → Pred: "
                + (predOpt != null ? predOpt.val : "None")
                + ", Succ: "
                + (succOpt != null ? succOpt.val : "None"));
    }
}
