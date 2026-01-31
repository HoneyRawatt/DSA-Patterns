package Tree.BinaryTree;

import java.util.*;

/*
====================================================
PROBLEM STATEMENT
====================================================
Given the root of a binary tree, a target node, and an
integer K, return all node values that are at distance
K from the target node.

Distance between two nodes is defined as the number
of edges between them.

Important:
- Nodes can lie above or below the target node.
- Binary tree nodes do not have parent pointers.
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
MAIN CLASS
====================================================
*/
public class NodesAtDistanceK {

    /*
    ====================================================
    FUNCTION: markParents
    ====================================================
    Purpose:
    Stores parent information for each node to enable
    upward traversal during BFS.

    Approach:
    - Perform level-order traversal (BFS) from root.
    - For every child, store its parent in a map.
    ====================================================
    */
    private static void markParents(
            TreeNode root,
            Map<TreeNode, TreeNode> parentTrack) {

        Queue<TreeNode> queue = new LinkedList<>();
        queue.offer(root);

        while (!queue.isEmpty()) {
            TreeNode current = queue.poll();

            if (current.left != null) {
                parentTrack.put(current.left, current);
                queue.offer(current.left);
            }

            if (current.right != null) {
                parentTrack.put(current.right, current);
                queue.offer(current.right);
            }
        }
    }

    /*
    ====================================================
    FUNCTION: distanceK
    ====================================================
    Purpose:
    Returns all nodes that are exactly K distance away
    from the target node.

    Intuition:
    - Convert the tree into an undirected graph using
      left, right, and parent pointers.
    - Run BFS starting from the target node.
    - Stop BFS once distance K is reached.
    ====================================================
    */
    public static List<Integer> distanceK(
            TreeNode root,
            TreeNode target,
            int k) {

        // Step 1: Store parent pointers
        Map<TreeNode, TreeNode> parentTrack = new HashMap<>();
        markParents(root, parentTrack);

        // Step 2: BFS from target node
        Map<TreeNode, Boolean> visited = new HashMap<>();
        Queue<TreeNode> queue = new LinkedList<>();

        queue.offer(target);
        visited.put(target, true);

        int currentLevel = 0;

        // Step 3: Traverse level by level
        while (!queue.isEmpty()) {
            int size = queue.size();

            // Stop BFS when distance K is reached
            if (currentLevel++ == k) {
                break;
            }

            for (int i = 0; i < size; i++) {
                TreeNode current = queue.poll();

                // Visit left child
                if (current.left != null &&
                        !visited.containsKey(current.left)) {
                    queue.offer(current.left);
                    visited.put(current.left, true);
                }

                // Visit right child
                if (current.right != null &&
                        !visited.containsKey(current.right)) {
                    queue.offer(current.right);
                    visited.put(current.right, true);
                }

                // Visit parent
                if (parentTrack.containsKey(current)) {
                    TreeNode parent = parentTrack.get(current);
                    if (!visited.containsKey(parent)) {
                        queue.offer(parent);
                        visited.put(parent, true);
                    }
                }
            }
        }

        // Step 4: Nodes left in queue are at distance K
        List<Integer> result = new ArrayList<>();
        while (!queue.isEmpty()) {
            result.add(queue.poll().data);
        }

        return result;
    }

    /*
    ====================================================
    MAIN METHOD
    ====================================================
    Builds the tree, defines target and K, and prints
    nodes at distance K from the target.
    ====================================================
    */
    public static void main(String[] args) {

        /*
                  3
                 / \
                5   1
               / \  / \
              6  2 0   8
                / \
               7   4
        */

        TreeNode root = new TreeNode(3);
        root.left = new TreeNode(5);
        root.right = new TreeNode(1);
        root.left.left = new TreeNode(6);
        root.left.right = new TreeNode(2);
        root.right.left = new TreeNode(0);
        root.right.right = new TreeNode(8);
        root.left.right.left = new TreeNode(7);
        root.left.right.right = new TreeNode(4);

        TreeNode target = root.left; // Node with value 5
        int k = 2;

        List<Integer> result = distanceK(root, target, k);

        System.out.print("Nodes at distance " + k +
                " from target " + target.data + ": ");
        for (int val : result) {
            System.out.print(val + " ");
        }
    }
}

/*
====================================================
TIME & SPACE COMPLEXITY
====================================================

Time Complexity: O(N)
- Parent mapping visits each node once
- BFS traversal visits each node at most once

Space Complexity: O(N)
- Parent map: O(N)
- Visited map: O(N)
- BFS queue: O(N)
====================================================
*/

