package Tree.BinarySearchTree;

import java.util.*;

/*
====================================================
📌 Problem Statement
====================================================
You are given the root of a Binary Search Tree (BST)
in which exactly two nodes have been swapped by mistake.

Your task is to recover the BST without changing
its structure (i.e., only swap values back).

BST Property:
- Inorder traversal of BST produces a sorted sequence.
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

    TreeNode(int value) {
        val = value;
        left = right = null;
    }
}

/*
====================================================
🟥 BRUTE FORCE APPROACH
====================================================

💡 Intuition:
- Inorder traversal of a valid BST is sorted.
- If BST is corrupted, inorder order will be wrong.
- Store inorder nodes, sort their values, and reassign.

Steps:
1️⃣ Perform inorder traversal and store nodes.
2️⃣ Extract values and sort them.
3️⃣ Replace node values with sorted values.

Time Complexity:  O(N log N)
Space Complexity: O(N)
====================================================
*/
class BruteForceSolution {

    private void inorder(TreeNode root, List<TreeNode> nodes) {
        if (root == null) return;
        inorder(root.left, nodes);
        nodes.add(root);
        inorder(root.right, nodes);
    }

    public void recoverTree(TreeNode root) {
        List<TreeNode> nodes = new ArrayList<>();
        inorder(root, nodes);

        List<Integer> values = new ArrayList<>();
        for (TreeNode node : nodes)
            values.add(node.val);

        Collections.sort(values);

        for (int i = 0; i < nodes.size(); i++) {
            nodes.get(i).val = values.get(i);
        }
    }
}

/*
====================================================
🟩 OPTIMAL APPROACH (Inorder Violation Detection)
====================================================

💡 Key Observation:
- Inorder traversal of BST should be strictly increasing.
- Swapping two nodes creates violations.

Cases:
1️⃣ Adjacent nodes swapped → one violation
2️⃣ Non-adjacent nodes swapped → two violations

We track:
- prev   → previously visited node
- first  → first wrong node
- middle → node next to first
- last   → second wrong node

Time Complexity:  O(N)
Space Complexity: O(H) (recursion stack)
====================================================
*/
class OptimalSolution {

    private TreeNode first;
    private TreeNode middle;
    private TreeNode last;
    private TreeNode prev;

    private void inorder(TreeNode root) {
        if (root == null) return;

        inorder(root.left);

        // Detect violation of BST property
        if (prev != null && root.val < prev.val) {

            // First violation
            if (first == null) {
                first = prev;
                middle = root;
            }
            // Second violation
            else {
                last = root;
            }
        }

        prev = root;

        inorder(root.right);
    }

    public void recoverTree(TreeNode root) {
        first = middle = last = null;
        prev = new TreeNode(Integer.MIN_VALUE); // sentinel

        inorder(root);

        // Fix swapped nodes
        if (first != null && last != null) {
            int temp = first.val;
            first.val = last.val;
            last.val = temp;
        } else if (first != null && middle != null) {
            int temp = first.val;
            first.val = middle.val;
            middle.val = temp;
        }
    }
}

/*
====================================================
🧪 Utility Function
====================================================
Print inorder traversal of BST
*/
class Utils {
    static void printInorder(TreeNode root) {
        if (root == null) return;
        printInorder(root.left);
        System.out.print(root.val + " ");
        printInorder(root.right);
    }
}

/*
====================================================
🧪 Main Class (Testing)
====================================================
*/
public class Main {
    public static void main(String[] args) {

        /*
            Corrupted BST:
                   3
                  / \
                 1   4
                    /
                   2
        */

        TreeNode root = new TreeNode(3);
        root.left = new TreeNode(1);
        root.right = new TreeNode(4);
        root.right.left = new TreeNode(2);

        System.out.print("Original inorder traversal: ");
        Utils.printInorder(root);
        System.out.println();

        // ---- Brute Force Recovery ----
        BruteForceSolution brute = new BruteForceSolution();
        brute.recoverTree(root);

        System.out.print("After brute force recovery: ");
        Utils.printInorder(root);
        System.out.println();

        // Corrupt again for optimal test
        int temp = root.val;
        root.val = root.right.left.val;
        root.right.left.val = temp;

        // ---- Optimal Recovery ----
        OptimalSolution optimal = new OptimalSolution();
        optimal.recoverTree(root);

        System.out.print("After optimal recovery: ");
        Utils.printInorder(root);
        System.out.println();
    }
}

/*
====================================================
🧠 Final Comparison
====================================================

Approach        Time        Space       Notes
------------------------------------------------
Brute Force     O(N log N)  O(N)        Simple but extra memory
Optimal        O(N)        O(H)        Best solution

====================================================
*/
