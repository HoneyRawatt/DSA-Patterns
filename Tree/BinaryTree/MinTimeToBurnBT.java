package Tree.BinaryTree;

import java.util.*;

/*
====================================================
PROBLEM STATEMENT
====================================================
Given a binary tree and a starting node (target),
a fire starts from the target node.

In one unit of time, fire spreads to:
- left child
- right child
- parent

Return the minimum time required to burn the entire tree.
====================================================
*/

/*
Class: TreeNode
Purpose:
Represents a node in a binary tree.
*/
class TreeNode {
    int val;
    TreeNode left;
    TreeNode right;

    TreeNode(int val) {
        this.val = val;
        this.left = null;
        this.right = null;
    }
}

/*
====================================================
APPROACH 1: BFS + PARENT MAPPING
====================================================

Idea:
- Convert the tree into an undirected graph.
- Since nodes do not store parent pointers, first
  map each node to its parent.
- Perform BFS starting from the target node.
- Each BFS level represents 1 unit of time.

Time Complexity: O(N)
Space Complexity: O(N)
====================================================
*/
class BurningTreeBFS {

    /*
    ------------------------------------------------
    Step 1: BFS to map each node to its parent
            and locate the target node
    ------------------------------------------------
    */
    private static TreeNode bfsToMapParents(
            TreeNode root,
            Map<TreeNode, TreeNode> parentMap,
            int start) {

        Queue<TreeNode> queue = new LinkedList<>();
        queue.offer(root);

        TreeNode targetNode = null;

        while (!queue.isEmpty()) {
            TreeNode node = queue.poll();

            // Identify target node
            if (node.val == start) {
                targetNode = node;
            }

            // Map left child to parent
            if (node.left != null) {
                parentMap.put(node.left, node);
                queue.offer(node.left);
            }

            // Map right child to parent
            if (node.right != null) {
                parentMap.put(node.right, node);
                queue.offer(node.right);
            }
        }

        return targetNode;
    }

    /*
    ------------------------------------------------
    Step 2: BFS from target to calculate
            minimum time to burn the tree
    ------------------------------------------------
    */
    private static int findMinDistance(
            Map<TreeNode, TreeNode> parentMap,
            TreeNode target) {

        Queue<TreeNode> queue = new LinkedList<>();
        Map<TreeNode, Boolean> visited = new HashMap<>();

        queue.offer(target);
        visited.put(target, true);

        int time = 0;

        while (!queue.isEmpty()) {
            int size = queue.size();
            boolean flag = false; // indicates fire spread

            for (int i = 0; i < size; i++) {
                TreeNode node = queue.poll();

                // Burn left child
                if (node.left != null && !visited.containsKey(node.left)) {
                    flag = true;
                    visited.put(node.left, true);
                    queue.offer(node.left);
                }

                // Burn right child
                if (node.right != null && !visited.containsKey(node.right)) {
                    flag = true;
                    visited.put(node.right, true);
                    queue.offer(node.right);
                }

                // Burn parent
                TreeNode parent = parentMap.get(node);
                if (parent != null && !visited.containsKey(parent)) {
                    flag = true;
                    visited.put(parent, true);
                    queue.offer(parent);
                }
            }

            // Increase time only if fire spreads further
            if (flag) time++;
        }

        return time;
    }

    /*
    ------------------------------------------------
    Main BFS-based function
    ------------------------------------------------
    */
    public static int timeToBurnTree(TreeNode root, int start) {
        Map<TreeNode, TreeNode> parentMap = new HashMap<>();
        TreeNode target = bfsToMapParents(root, parentMap, start);
        return findMinDistance(parentMap, target);
    }
}

/*
====================================================
APPROACH 2: DFS (RECURSIVE)
====================================================

Idea:
- Perform post-order traversal.
- Return subtree height if target not found.
- If target found, return negative distance.
- Use opposite subtree height to update answer.

Time Complexity: O(N)
Space Complexity: O(H) where H is tree height
====================================================
*/
class MinTimeToBurnBT{

    int ans = 0;

    /*
    Returns:
    - Height of subtree if target not found
    - Negative distance from target if found
    */
    private int solve(TreeNode node, int start) {
        if (node == null) return 0;

        int left = solve(node.left, start);
        int right = solve(node.right, start);

        // Case 1: Current node is target
        if (node.val == start) {
            ans = Math.max(ans, Math.max(left, right));
            return -1; // mark target found
        }
        // Case 2: Target in left subtree
        else if (left < 0) {
            ans = Math.max(ans, Math.abs(left) + right);
            return left - 1; // propagate distance
        }
        // Case 3: Target in right subtree
        else if (right < 0) {
            ans = Math.max(ans, Math.abs(right) + left);
            return right - 1; // propagate distance
        }

        // Case 4: Target not in subtree
        return 1 + Math.max(left, right);
    }

    public int amountOfTime(TreeNode root, int start) {
        solve(root, start);
        return ans;
    }
}
