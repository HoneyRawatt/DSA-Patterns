package Tree.BinaryTree;

import java.util.*;

/*
===============================================================================
Problem Statement:
-------------------------------------------------------------------------------
Design a mechanism to serialize and deserialize a binary tree.

Serialization:
- Convert a binary tree into a string so it can be stored or transmitted.
- Null nodes must be included to preserve the exact tree structure.

Deserialization:
- Reconstruct the original binary tree from the serialized string.

Approach Used:
- Level Order Traversal (Breadth-First Search)
- Use "#" to represent NULL nodes
- Use commas (,) as separators
===============================================================================
*/

/*
Class: TreeNode
Purpose:
- Represents a node in a binary tree.
*/
class TreeNode {
    int val;
    TreeNode left;
    TreeNode right;

    TreeNode(int val) {
        this.val = val;
        left = null;
        right = null;
    }
}

public class SerializeDeserializeBinaryTree {

    /*
    ===========================================================================
    Function: serialize
    ---------------------------------------------------------------------------
    Purpose:
    - Converts a binary tree into a string using level-order traversal (BFS).

    Intuition:
    - Traverse the tree level by level.
    - Append node values to the string.
    - Use "#" for NULL children so structure is preserved.

    Time Complexity: O(N)
    Space Complexity: O(N)
    ===========================================================================
    */
    public static String serialize(TreeNode root) {
        if (root == null) return "#,";

        StringBuilder sb = new StringBuilder();
        Queue<TreeNode> queue = new LinkedList<>();
        queue.offer(root);

        while (!queue.isEmpty()) {
            TreeNode curr = queue.poll();

            if (curr == null) {
                sb.append("#,");
            } else {
                sb.append(curr.val).append(",");
                queue.offer(curr.left);
                queue.offer(curr.right);
            }
        }
        return sb.toString();
    }

    /*
    ===========================================================================
    Function: deserialize
    ---------------------------------------------------------------------------
    Purpose:
    - Reconstructs the binary tree from the serialized string.

    Intuition:
    - Read values one by one.
    - Use a queue to attach left and right children in level order.
    - Skip nodes marked with "#".

    Time Complexity: O(N)
    Space Complexity: O(N)
    ===========================================================================
    */
    public static TreeNode deserialize(String data) {
        if (data == null || data.length() == 0) return null;

        String[] values = data.split(",");
        if (values[0].equals("#")) return null;

        TreeNode root = new TreeNode(Integer.parseInt(values[0]));
        Queue<TreeNode> queue = new LinkedList<>();
        queue.offer(root);

        int i = 1;
        while (!queue.isEmpty() && i < values.length) {
            TreeNode node = queue.poll();

            // Left child
            if (!values[i].equals("#")) {
                node.left = new TreeNode(Integer.parseInt(values[i]));
                queue.offer(node.left);
            }
            i++;

            // Right child
            if (i < values.length && !values[i].equals("#")) {
                node.right = new TreeNode(Integer.parseInt(values[i]));
                queue.offer(node.right);
            }
            i++;
        }
        return root;
    }

    /*
    Helper Function: inorder
    Purpose:
    - Prints inorder traversal of the tree.
    - Used to verify correctness after deserialization.
    */
    public static void inorder(TreeNode root) {
        if (root == null) return;
        inorder(root.left);
        System.out.print(root.val + " ");
        inorder(root.right);
    }

    /*
    ===========================================================================
    Main Function:
    ---------------------------------------------------------------------------
    1. Creates a sample binary tree
    2. Serializes the tree
    3. Deserializes it back
    4. Prints inorder traversal for verification
    ===========================================================================
    */
    public static void main(String[] args) {

        /*
                  1
                 / \
                2   3
                   / \
                  4   5
        */
        TreeNode root = new TreeNode(1);
        root.left = new TreeNode(2);
        root.right = new TreeNode(3);
        root.right.left = new TreeNode(4);
        root.right.right = new TreeNode(5);

        // Serialize
        String data = serialize(root);
        System.out.println("Serialized Tree: " + data);

        // Deserialize
        TreeNode newRoot = deserialize(data);
        System.out.print("Inorder of Deserialized Tree: ");
        inorder(newRoot);
        System.out.println();
    }
}

/*
===============================================================================
Time & Space Complexity Summary:
-------------------------------------------------------------------------------
Time Complexity: O(N)
- Each node is visited once during serialization and deserialization.

Space Complexity: O(N)
- Queue may store up to N nodes.
- Serialized string also takes O(N) space.

Where N = number of nodes in the binary tree.
===============================================================================
*/
