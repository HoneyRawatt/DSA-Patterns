package Tree.BinaryTree;

import java.util.*;

/*
----------------------------------------------------
Class: TreeNode
Purpose:
- Represents a node in a binary tree
- Each node contains:
    1) data value
    2) reference to left child
    3) reference to right child
----------------------------------------------------
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

public class BottomViewBinaryTree {

    /*
    ----------------------------------------------------
    Problem Statement:
    Given the root of a binary tree, return the **bottom view**
    of the tree.

    Bottom View Definition:
    - Nodes visible when the tree is viewed from the bottom.
    - For each vertical line (horizontal distance),
      the bottom-most node is selected.

    ----------------------------------------------------
    Intuition:
    - Each node lies on a vertical line identified by its
      horizontal distance (HD).
    - If multiple nodes have the same HD, the one that appears
      lower in the tree should be chosen.
    - Level-order traversal (BFS) ensures top-to-bottom processing.
    - By overwriting values for each HD, the bottom-most node remains.

    ----------------------------------------------------
    Approach:
    1) Perform BFS (level-order traversal).
    2) Track horizontal distance (HD):
       - Root → HD = 0
       - Left child → HD - 1
       - Right child → HD + 1
    3) Use TreeMap<Integer, Integer>:
       - Key   → horizontal distance
       - Value → node value
    4) Overwrite the value at each HD during traversal.
    5) Extract values from TreeMap in sorted order of HD.

    ----------------------------------------------------
    Time Complexity:
    - O(N log N)
      BFS traversal → O(N)
      TreeMap insertion → O(log N) per node

    Space Complexity:
    - O(N)
      Queue for BFS + TreeMap for storage
    ----------------------------------------------------
    */
    public static List<Integer> bottomView(TreeNode root) {
        List<Integer> ans = new ArrayList<>();
        if (root == null) return ans;

        // TreeMap keeps keys (HD) sorted automatically
        Map<Integer, Integer> map = new TreeMap<>();

        // Queue stores pair of (node, horizontal distance)
        Queue<Pair> queue = new LinkedList<>();
        queue.add(new Pair(root, 0));

        while (!queue.isEmpty()) {
            Pair current = queue.poll();
            TreeNode node = current.node;
            int hd = current.hd;

            // Overwrite value so bottom-most node stays
            map.put(hd, node.data);

            if (node.left != null)
                queue.add(new Pair(node.left, hd - 1));

            if (node.right != null)
                queue.add(new Pair(node.right, hd + 1));
        }

        // Extract bottom view from leftmost to rightmost HD
        for (int val : map.values()) {
            ans.add(val);
        }

        return ans;
    }

    /*
    Helper class to store node with its horizontal distance
    */
    static class Pair {
        TreeNode node;
        int hd;

        Pair(TreeNode node, int hd) {
            this.node = node;
            this.hd = hd;
        }
    }

    /*
    ----------------------------------------------------
    Example Usage
    ----------------------------------------------------
    */
    public static void main(String[] args) {
        /*
                  20
                /    \
               8      22
             /   \   /  \
            5     3 4    25
                 / \
                10 14

        Bottom View: 5 10 4 14 25
        */

        TreeNode root = new TreeNode(20);
        root.left = new TreeNode(8);
        root.right = new TreeNode(22);
        root.left.left = new TreeNode(5);
        root.left.right = new TreeNode(3);
        root.right.left = new TreeNode(4);
        root.right.right = new TreeNode(25);
        root.left.right.left = new TreeNode(10);
        root.left.right.right = new TreeNode(14);

        List<Integer> result = bottomView(root);
        System.out.println(result); // [5, 10, 4, 14, 25]
    }
}
