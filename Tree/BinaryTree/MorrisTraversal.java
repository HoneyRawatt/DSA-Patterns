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
Approach: Morris Traversal
-------------------------------------------------------------------------------
Idea:
- Perform tree traversal without using recursion or an explicit stack.
- Temporarily modify the tree by creating "threads" from a node’s inorder
  predecessor to the current node.

Key Observations:
1. If left child is null → visit node and move to right.
2. If left child exists:
   - Find the rightmost node in left subtree (predecessor).
   - If predecessor.right is null → create a thread and move left.
   - If predecessor.right points to current → remove thread, visit node, move right.

This guarantees:
- O(N) time
- O(1) extra space
===============================================================================
*/

public class MorrisTraversal {

    /*
    ===========================================================================
    Morris Inorder Traversal
    ---------------------------------------------------------------------------
    Traversal Order: Left → Root → Right
    ===========================================================================
    */
    public static List<Integer> getInorder(TreeNode root) {
        List<Integer> inorder = new ArrayList<>();
        TreeNode curr = root;

        while (curr != null) {
            if (curr.left == null) {
                inorder.add(curr.val);
                curr = curr.right;
            } else {
                TreeNode prev = curr.left;

                // Find inorder predecessor
                while (prev.right != null && prev.right != curr) {
                    prev = prev.right;
                }

                if (prev.right == null) {
                    // Create thread
                    prev.right = curr;
                    curr = curr.left;
                } else {
                    // Remove thread
                    prev.right = null;
                    inorder.add(curr.val);
                    curr = curr.right;
                }
            }
        }
        return inorder;
    }

    /*
    ===========================================================================
    Morris Preorder Traversal
    ---------------------------------------------------------------------------
    Traversal Order: Root → Left → Right
    ===========================================================================
    */
    public static List<Integer> getPreorder(TreeNode root) {
        List<Integer> preorder = new ArrayList<>();
        TreeNode curr = root;

        while (curr != null) {
            if (curr.left == null) {
                preorder.add(curr.val);
                curr = curr.right;
            } else {
                TreeNode prev = curr.left;

                // Find inorder predecessor
                while (prev.right != null && prev.right != curr) {
                    prev = prev.right;
                }

                if (prev.right == null) {
                    preorder.add(curr.val); // visit before left
                    prev.right = curr;
                    curr = curr.left;
                } else {
                    prev.right = null;
                    curr = curr.right;
                }
            }
        }
        return preorder;
    }

    /* Helper function to print traversal result */
    public static void printList(List<Integer> list) {
        for (int x : list) {
            System.out.print(x + " ");
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

        List<Integer> inorder = getInorder(root);
        List<Integer> preorder = getPreorder(root);

        System.out.print("Morris Inorder Traversal: ");
        printList(inorder);

        System.out.print("Morris Preorder Traversal: ");
        printList(preorder);
    }
}

/*
===============================================================================
Time & Space Complexity Analysis
-------------------------------------------------------------------------------
Time Complexity: O(N)
- Each edge is visited at most twice:
  once when creating the thread and once when removing it.

Space Complexity: O(1)
- No recursion
- No stack
- Only constant extra pointers used

Key Insight:
Morris Traversal temporarily modifies the tree but restores it fully,
achieving traversal with constant space.
===============================================================================
*/

