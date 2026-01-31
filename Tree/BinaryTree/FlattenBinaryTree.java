package Tree.BinaryTree;

import java.util.*;

/*
===============================================================================
Class: TreeNode
Purpose:
- Represents a node in a binary tree
===============================================================================
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

/*
===============================================================================
Flatten Binary Tree to Linked List
-------------------------------------------------------------------------------
Goal:
- Transform the binary tree into a linked list in-place.
- The linked list should follow preorder traversal:
  Root → Left → Right
- Left pointers must be null.
===============================================================================
*/

public class FlattenBinaryTree {

    /*
    ===========================================================================
    Approach 1: Recursive (Reverse Preorder)
    ---------------------------------------------------------------------------
    Idea:
    - Traverse in reverse preorder: Right → Left → Root
    - Maintain a `prev` pointer that tracks previously processed node.
    - Rewire pointers during backtracking.
    
    Time Complexity : O(N)
    Space Complexity: O(H)  (recursion stack)
    ===========================================================================
    */
    static TreeNode prev = null;

    public static void flattenDFS(TreeNode node) {
        if (node == null) return;

        flattenDFS(node.right);
        flattenDFS(node.left);

        node.right = prev;
        node.left = null;
        prev = node;
    }

    /*
    ===========================================================================
    Approach 2: Using Stack (Iterative Preorder)
    ---------------------------------------------------------------------------
    Idea:
    - Simulate preorder traversal using an explicit stack.
    - Always connect current node's right to next node in preorder.
    
    Time Complexity : O(N)
    Space Complexity: O(H)
    ===========================================================================
    */
    public static void flattenStack(TreeNode root) {
        if (root == null) return;

        Stack<TreeNode> stack = new Stack<>();
        stack.push(root);

        while (!stack.isEmpty()) {
            TreeNode curr = stack.pop();

            if (curr.right != null) stack.push(curr.right);
            if (curr.left != null) stack.push(curr.left);

            if (!stack.isEmpty()) {
                curr.right = stack.peek();
            }
            curr.left = null;
        }
    }

    /*
    ===========================================================================
    Approach 3: Morris Traversal (O(1) Space)
    ---------------------------------------------------------------------------
    Idea:
    - If a node has a left child:
        1. Find the rightmost node in left subtree.
        2. Connect it to the current node’s right subtree.
        3. Move left subtree to the right.
    - Move to the right child.
    
    Time Complexity : O(N)
    Space Complexity: O(1)
    ===========================================================================
    */
    public static void flattenMorris(TreeNode root) {
        TreeNode curr = root;

        while (curr != null) {
            if (curr.left != null) {
                TreeNode prev = curr.left;

                // Find rightmost node in left subtree
                while (prev.right != null) {
                    prev = prev.right;
                }

                // Rewire connections
                prev.right = curr.right;
                curr.right = curr.left;
                curr.left = null;
            }
            curr = curr.right;
        }
    }

    /*
    ===========================================================================
    Helper Function: Print Flattened Tree
    ---------------------------------------------------------------------------
    Prints the right-skewed linked list.
    ===========================================================================
    */
    public static void printFlattened(TreeNode root) {
        while (root != null) {
            System.out.print(root.val + " ");
            root = root.right;
        }
        System.out.println();
    }

    /*
    ===========================================================================
    Main Function (Testing)
    ===========================================================================
    */
    public static void main(String[] args) {

        /*
                  1
                 / \
                2   5
               / \   \
              3   4   6

        Expected Flattened Output:
        1 2 3 4 5 6
        */

        TreeNode root = new TreeNode(1);
        root.left = new TreeNode(2);
        root.right = new TreeNode(5);
        root.left.left = new TreeNode(3);
        root.left.right = new TreeNode(4);
        root.right.right = new TreeNode(6);

        System.out.print("Flatten (Morris method): ");
        flattenMorris(root);
        printFlattened(root);
    }
}

/*
===============================================================================
Time & Space Complexity Summary
-------------------------------------------------------------------------------
Time Complexity: O(N)
- Each node is processed once.

Space Complexity:
- Recursive DFS  → O(H)
- Stack method   → O(H)
- Morris method  → O(1)

Where:
- N = number of nodes
- H = height of the tree
===============================================================================
*/

