package Tree.BinaryTree;

import java.util.*;

/*
----------------------------------------------------
Class: TreeNode
Purpose:
- Represents a single node in a binary tree
- Each node contains:
    1) data value
    2) reference to left child
    3) reference to right child
----------------------------------------------------
*/
class TreeNode {
    int data;          // Value stored in the node
    TreeNode left;     // Reference to left child
    TreeNode right;    // Reference to right child

    // Constructor to initialize the node
    TreeNode(int data) {
        this.data = data;
        this.left = null;
        this.right = null;
    }
}

public class TopViewBinaryTree {

    /*
    ----------------------------------------------------
    Function: topV
    Purpose:
    - Returns the TOP VIEW of a binary tree

    Top View Definition:
    - Nodes visible when the tree is viewed from the top
    - For each vertical line (horizontal distance),
      only the first node encountered is included

    Approach:
    1) Perform BFS (level-order traversal)
    2) Track horizontal distance (HD) for each node
        - Root → HD = 0
        - Left child → HD - 1
        - Right child → HD + 1
    3) Use TreeMap to store:
        HD → node value
       (TreeMap keeps keys sorted automatically)
    4) Insert into map only if HD is encountered for the first time

    Time Complexity:
    - O(N log N)
      N nodes processed, TreeMap insertion takes log N

    Space Complexity:
    - O(N)
      Queue + map storage
    ----------------------------------------------------
    */
    public static List<Integer> topV(TreeNode root) {
        List<Integer> ans = new ArrayList<>();

        // Edge case: empty tree
        if (root == null) return ans;

        // TreeMap maintains sorted order of horizontal distances
        Map<Integer, Integer> map = new TreeMap<>();

        // Queue stores Pair of (node, horizontal distance)
        Queue<Pair> queue = new LinkedList<>();
        queue.offer(new Pair(root, 0));

        while (!queue.isEmpty()) {
            Pair current = queue.poll();
            TreeNode node = current.node;
            int hd = current.hd;

            // Store only the first node for each horizontal distance
            if (!map.containsKey(hd)) {
                map.put(hd, node.data);
            }

            // Add left child with HD - 1
            if (node.left != null) {
                queue.offer(new Pair(node.left, hd - 1));
            }

            // Add right child with HD + 1
            if (node.right != null) {
                queue.offer(new Pair(node.right, hd + 1));
            }
        }

        // Extract top view values from leftmost HD to rightmost HD
        for (int value : map.values()) {
            ans.add(value);
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
    Driver Code
    ----------------------------------------------------
    */
    public static void main(String[] args) {

        /*
                1
               / \
              2   3
               \
                4
                 \
                  5
                   \
                    6

        Top View: 2 1 3 6
        */

        TreeNode root = new TreeNode(1);
        root.left = new TreeNode(2);
        root.right = new TreeNode(3);
        root.left.right = new TreeNode(4);
        root.left.right.right = new TreeNode(5);
        root.left.right.right.right = new TreeNode(6);

        List<Integer> result = topV(root);

        // Print top view
        for (int val : result) {
            System.out.print(val + " ");
        }
    }
}

