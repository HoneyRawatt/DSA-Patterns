package Tree.BinaryTree;

import java.util.*;

/*
====================================================
PROBLEM STATEMENT
====================================================
Given a binary tree, modify it so that it satisfies
the Children Sum Property (CSP).

Children Sum Property:
For every non-leaf node:
    node.data = (left child data) + (right child data)

Rules:
- You are allowed to only INCREASE node values.
- Tree structure must remain unchanged.
- Leaf nodes are always valid.
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

    TreeNode(int data) {
        this.data = data;
        this.left = null;
        this.right = null;
    }
}

/*
====================================================
INTUITION / APPROACH
====================================================

We solve this problem using DFS with a post-order style
traversal.

Key Idea:
1. Compare current node value with sum of its children.
2. If children sum is greater → update current node.
3. If current node is greater → push its value down
   to its children.
4. Recursively fix left and right subtrees.
5. While returning back (post-order), recompute the
   node value using updated children.

Why this works:
- Values are never decreased.
- Fixing children first ensures correctness bottom-up.
====================================================
*/

public class ChildrenSumProperty {

    /*
    Function: changeTree()
    Purpose:
    Modifies the binary tree so that it satisfies
    the Children Sum Property.
    */
    public static void changeTree(TreeNode root) {
        if (root == null) return;

        // Step 1: Calculate sum of children
        int childSum = 0;
        if (root.left != null) childSum += root.left.data;
        if (root.right != null) childSum += root.right.data;

        /*
        Step 2:
        - If children sum >= node value → update node
        - Else → push node value to children
        */
        if (childSum >= root.data) {
            root.data = childSum;
        } else {
            if (root.left != null) root.left.data = root.data;
            if (root.right != null) root.right.data = root.data;
        }

        // Step 3: Recurse on left and right children
        changeTree(root.left);
        changeTree(root.right);

        /*
        Step 4 (Post-order fix):
        Update current node using final children values
        */
        int total = 0;
        if (root.left != null) total += root.left.data;
        if (root.right != null) total += root.right.data;

        if (root.left != null || root.right != null) {
            root.data = total;
        }
    }

    /*
    Helper Function: printLevelOrder()
    Purpose:
    Prints the binary tree in level order (BFS).
    */
    public static void printLevelOrder(TreeNode root) {
        if (root == null) return;

        Queue<TreeNode> queue = new LinkedList<>();
        queue.offer(root);

        while (!queue.isEmpty()) {
            int size = queue.size();
            while (size-- > 0) {
                TreeNode node = queue.poll();
                System.out.print(node.data + " ");

                if (node.left != null) queue.offer(node.left);
                if (node.right != null) queue.offer(node.right);
            }
            System.out.println();
        }
    }

    /*
    ====================================================
    MAIN FUNCTION
    ====================================================
    1. Builds a sample binary tree
    2. Prints tree before applying CSP
    3. Applies changeTree()
    4. Prints tree after applying CSP
    ====================================================
    */
    public static void main(String[] args) {

        // Constructing the binary tree
        TreeNode root = new TreeNode(50);
        root.left = new TreeNode(7);
        root.right = new TreeNode(2);
        root.left.left = new TreeNode(3);
        root.left.right = new TreeNode(5);
        root.right.left = new TreeNode(1);
        root.right.right = new TreeNode(30);

        System.out.println("Before changeTree() - Level Order Traversal:");
        printLevelOrder(root);

        // Apply Children Sum Property
        changeTree(root);

        System.out.println("\nAfter changeTree() - Level Order Traversal:");
        printLevelOrder(root);
    }
}

/*
====================================================
TIME & SPACE COMPLEXITY
====================================================

Time Complexity: O(N)
- Each node is visited exactly once.

Space Complexity: O(H)
- Recursive stack space where H = height of tree
- Worst case (skewed tree): O(N)
- Best case (balanced tree): O(log N)
====================================================
*/

