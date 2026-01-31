package Tree.BinaryTree;

import java.util.*;

/*
====================================================
Problem Statement: Zigzag (Spiral) Level Order Traversal
====================================================

Given the root of a binary tree, return the zigzag
level order traversal of its nodes' values.

Zigzag traversal means:
- Level 0 → Left to Right
- Level 1 → Right to Left
- Level 2 → Left to Right
- and so on...

----------------------------------------------------
Example:
Input Tree:
            1
           / \
          2   3
         / \   \
        4   5   6

Output:
[
  [1],
  [3, 2],
  [4, 5, 6]
]
----------------------------------------------------

Time Complexity: O(N)
Space Complexity: O(N)
====================================================
*/

/*
Class: TreeNode
Purpose:
    Represents a node in a binary tree.
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

/*
Class: ZigzagTraversal
Purpose:
    Contains method to perform zigzag level order traversal.
*/
public class ZigzagTraversal {

    /*
    Function: zigzagLevelOrder
    Purpose:
        Perform zigzag (spiral) level order traversal
        using BFS.

    Approach:
        - Use a queue for level order traversal.
        - Use a boolean flag to alternate direction.
        - Use index mapping to avoid reversing lists.

    Time Complexity: O(N)
    Space Complexity: O(N)
    */
    public static List<List<Integer>> zigzagLevelOrder(TreeNode root) {
        List<List<Integer>> result = new ArrayList<>();

        // Empty tree case
        if (root == null) return result;

        Queue<TreeNode> queue = new LinkedList<>();
        queue.offer(root);

        boolean leftToRight = true;

        // BFS traversal
        while (!queue.isEmpty()) {
            int size = queue.size();
            List<Integer> level = new ArrayList<>(Collections.nCopies(size, 0));

            for (int i = 0; i < size; i++) {
                TreeNode node = queue.poll();

                // Decide index based on traversal direction
                int index = leftToRight ? i : (size - 1 - i);
                level.set(index, node.data);

                // Add children
                if (node.left != null) queue.offer(node.left);
                if (node.right != null) queue.offer(node.right);
            }

            // Flip direction
            leftToRight = !leftToRight;

            result.add(level);
        }

        return result;
    }

    /*
    Main Function
    Demonstrates zigzag level order traversal
    */
    public static void main(String[] args) {

        // Construct sample tree
        /*
                1
               / \
              2   3
             / \   \
            4   5   6
        */
        TreeNode root = new TreeNode(1);
        root.left = new TreeNode(2);
        root.right = new TreeNode(3);
        root.left.left = new TreeNode(4);
        root.left.right = new TreeNode(5);
        root.right.right = new TreeNode(6);

        List<List<Integer>> result = zigzagLevelOrder(root);

        System.out.println("Zigzag Level Order Traversal:");
        for (List<Integer> level : result) {
            for (int val : level) {
                System.out.print(val + " ");
            }
            System.out.println();
        }
    }
}
