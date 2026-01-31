package Tree.BinaryTree;

import java.util.*;

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

public class MaximumWidthOfBinaryTree {

    /*
    Function: widthOfBinaryTree
    Purpose:
        Calculates the maximum width of a binary tree.

    Logic:
        - Perform level-order traversal (BFS)
        - Assign an index to each node as if the tree were a complete binary tree
        - Normalize indices at each level to prevent overflow
        - Width of each level = lastIndex - firstIndex + 1

    Time Complexity: O(N)
    Space Complexity: O(N)
    */
    public static int widthOfBinaryTree(TreeNode root) {
        if (root == null) return 0;

        long ans = 0; // use long to avoid overflow
        Queue<Pair> q = new LinkedList<>();
        q.offer(new Pair(root, 0L));

        while (!q.isEmpty()) {
            int size = q.size();
            long minIndex = q.peek().index; // minimum index at this level
            long first = 0, last = 0;

            for (int i = 0; i < size; i++) {
                Pair curr = q.poll();
                long currId = curr.index - minIndex; // normalize
                TreeNode node = curr.node;

                if (i == 0) first = currId;
                if (i == size - 1) last = currId;

                if (node.left != null)
                    q.offer(new Pair(node.left, currId * 2 + 1));

                if (node.right != null)
                    q.offer(new Pair(node.right, currId * 2 + 2));
            }

            ans = Math.max(ans, last - first + 1);
        }

        return (int) ans;
    }

    /*
    Helper class to store a TreeNode with its index
    */
    static class Pair {
        TreeNode node;
        long index;

        Pair(TreeNode node, long index) {
            this.node = node;
            this.index = index;
        }
    }
}
