package Tree.BinarySearchTree;

import java.util.*;

/*
====================================================
📌 Problem Statement
====================================================
Given a Binary Search Tree (BST) and an integer key:

1️⃣ Ceil in BST:
   - Find the smallest value in the BST that is
     greater than or equal to the given key.

2️⃣ Floor in BST:
   - Find the largest value in the BST that is
     smaller than or equal to the given key.

If no such value exists, return -1.

BST Property:
- Left subtree values < root
- Right subtree values > root
====================================================
*/

/*
Class: TreeNode
Purpose: Represents a node in a Binary Search Tree
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

public class CeilFloorBST {

    /*
    ====================================================
    💡 Intuition (Ceil)
    ====================================================
    - If node.val == key → this is the ceil.
    - If node.val < key → ceil must be in right subtree.
    - If node.val > key → this node is a candidate ceil,
      but a smaller one may exist in the left subtree.
    ====================================================
    */

    /*
    Function: ceilBST
    Purpose: Finds the smallest value in BST that is >= key
    */
    static int ceilBST(TreeNode root, int key) {
        int ceil = -1;

        while (root != null) {
            if (root.val == key) {
                // Exact match → best possible ceil
                return root.val;
            }

            if (key > root.val) {
                // Ceil must be in right subtree
                root = root.right;
            } else {
                // Current node is a valid ceil candidate
                ceil = root.val;
                root = root.left;
            }
        }
        return ceil;
    }

    /*
    ====================================================
    💡 Intuition (Floor)
    ====================================================
    - If node.val == key → this is the floor.
    - If node.val > key → floor must be in left subtree.
    - If node.val < key → this node is a candidate floor,
      but a larger one may exist in the right subtree.
    ====================================================
    */

    /*
    Function: floorBST
    Purpose: Finds the largest value in BST that is <= key
    */
    static int floorBST(TreeNode root, int key) {
        int floor = -1;

        while (root != null) {
            if (root.val == key) {
                // Exact match → best possible floor
                return root.val;
            }

            if (key > root.val) {
                // Current node is a valid floor candidate
                floor = root.val;
                root = root.right;
            } else {
                // Floor must be in left subtree
                root = root.left;
            }
        }
        return floor;
    }

    /*
    Helper Function: Inserts a node into BST
    Used only to build test tree
    */
    static TreeNode insertBST(TreeNode root, int val) {
        if (root == null)
            return new TreeNode(val);

        if (val < root.val)
            root.left = insertBST(root.left, val);
        else
            root.right = insertBST(root.right, val);

        return root;
    }

    /*
    ====================================================
    🧪 Main Function (Testing)
    ====================================================
    BST Structure:
              8
             / \
            4   12
           / \  / \
          2  6 10 14
    ====================================================
    */
    public static void main(String[] args) {
        TreeNode root = null;
        int[] vals = {8, 4, 12, 2, 6, 10, 14};

        for (int v : vals)
            root = insertBST(root, v);

        int key = 5;

        System.out.println("Key: " + key);
        System.out.println("Ceil: " + ceilBST(root, key));
        System.out.println("Floor: " + floorBST(root, key));
    }
}

/*
====================================================
⏱ Time & Space Complexity
====================================================

Time Complexity:
- O(H) where H = height of BST
- Balanced BST → O(log N)
- Skewed BST → O(N)

Space Complexity:
- O(1) extra space (iterative approach)

====================================================
🧠 Summary
====================================================
✔ Uses BST property to skip unnecessary branches
✔ Iterative solution → constant space
✔ Optimal for interviews and competitive programming
====================================================
*/
