package Tree.BinaryTree;

import java.util.*;

/*
====================================================
Problem Statement: Vertical Order Traversal of a Binary Tree
====================================================

Given the root of a binary tree, return its vertical
order traversal.

In vertical order traversal:
- Nodes are grouped by their vertical columns.
- Columns are ordered from leftmost to rightmost.
- For nodes in the same column:
    1. Nodes are ordered by their depth (top to bottom).
    2. If multiple nodes share the same column and depth,
       they are sorted by their values.

----------------------------------------------------
Time Complexity: O(N log N)
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
    TreeNode left, right;

    TreeNode(int data) {
        this.data = data;
        this.left = null;
        this.right = null;
    }
}

public class VerticalTraversal {

    /*
    Function: verticalTraversal
    Purpose:
        Performs vertical order traversal of a binary tree.

    Approach:
    1️⃣ BFS (level-order) while tracking coordinates (x, y)
    2️⃣ Use TreeMap<Integer, TreeMap<Integer, PriorityQueue<Integer>>>
       to store nodes in order: column → level → sorted nodes
    3️⃣ Flatten the map to return final result
    */
    public static List<List<Integer>> verticalTraversal(TreeNode root) {
        List<List<Integer>> ans = new ArrayList<>();
        if (root == null) return ans;

        // Map<x, Map<y, sorted nodes>>
        TreeMap<Integer, TreeMap<Integer, PriorityQueue<Integer>>> nodes = new TreeMap<>();

        // Queue for BFS: stores {node, x, y}
        Queue<Object[]> queue = new LinkedList<>();
        queue.offer(new Object[]{root, 0, 0});

        while (!queue.isEmpty()) {
            Object[] arr = queue.poll();
            TreeNode node = (TreeNode) arr[0];
            int x = (Integer) arr[1];
            int y = (Integer) arr[2];

            nodes.putIfAbsent(x, new TreeMap<>());
            nodes.get(x).putIfAbsent(y, new PriorityQueue<>());
            nodes.get(x).get(y).offer(node.data);

            if (node.left != null)
                queue.offer(new Object[]{node.left, x - 1, y + 1});
            if (node.right != null)
                queue.offer(new Object[]{node.right, x + 1, y + 1});
        }

        // Build final answer
        for (TreeMap<Integer, PriorityQueue<Integer>> ys : nodes.values()) {
            List<Integer> col = new ArrayList<>();
            for (PriorityQueue<Integer> pq : ys.values()) {
                while (!pq.isEmpty()) {
                    col.add(pq.poll());
                }
            }
            ans.add(col);
        }

        return ans;
    }

    /*
    Driver Code
    */
    public static void main(String[] args) {
        /*
                3
               / \
              9   20
                  / \
                 15  7
        */
        TreeNode root = new TreeNode(3);
        root.left = new TreeNode(9);
        root.right = new TreeNode(20);
        root.right.left = new TreeNode(15);
        root.right.right = new TreeNode(7);

        List<List<Integer>> result = verticalTraversal(root);

        System.out.println("Vertical Order Traversal:");
        for (List<Integer> col : result) {
            for (int val : col)
                System.out.print(val + " ");
            System.out.println();
        }
    }
}

