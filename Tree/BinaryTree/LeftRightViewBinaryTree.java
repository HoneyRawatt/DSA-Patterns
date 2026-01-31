package Tree.BinaryTree;
import java.util.*;

/*
Class: TreeNode
Purpose: Represents a node in a binary tree
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

public class LeftRightViewBinaryTree {

    /*
    Function: rightSide
    Purpose : Fills the right view of the binary tree
    Approach:
    - DFS traversal
    - Visit right child first so the first node at each level is visible
    Time Complexity: O(N)  — each node visited once
    Space Complexity: O(H) — recursion stack (H = height of tree)
    */
    public static void rightSide(TreeNode root, int level, List<Integer> res) {
        if (root == null) return;

        // First node visited at this level is part of right view
        if (level == res.size()) {
            res.add(root.data);
        }

        rightSide(root.right, level + 1, res);
        rightSide(root.left, level + 1, res);
    }

    /*
    Function: leftSide
    Purpose : Fills the left view of the binary tree
    Approach:
    - DFS traversal
    - Visit left child first so the first node at each level is visible
    Time Complexity: O(N)
    Space Complexity: O(H)
    */
    public static void leftSide(TreeNode root, int level, List<Integer> res) {
        if (root == null) return;

        // First node visited at this level is part of left view
        if (level == res.size()) {
            res.add(root.data);
        }

        leftSide(root.left, level + 1, res);
        leftSide(root.right, level + 1, res);
    }

    /*
    Example usage
    */
    public static void main(String[] args) {
        /*
                1
               / \
              2   3
             / \ / \
            4  5 7  6
        */

        TreeNode root = new TreeNode(1);
        root.left = new TreeNode(2);
        root.right = new TreeNode(3);
        root.left.left = new TreeNode(4);
        root.left.right = new TreeNode(5);
        root.right.left = new TreeNode(7);
        root.right.right = new TreeNode(6);

        List<Integer> rightView = new ArrayList<>();
        rightSide(root, 0, rightView);
        System.out.print("Right View: ");
        for (int val : rightView) System.out.print(val + " ");
        System.out.println();

        List<Integer> leftView = new ArrayList<>();
        leftSide(root, 0, leftView);
        System.out.print("Left View: ");
        for (int val : leftView) System.out.print(val + " ");
        System.out.println();
    }
}
