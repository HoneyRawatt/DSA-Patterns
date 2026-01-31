package Tree.BinaryTree;
// 🧩 Problem Statement: Diameter of a Binary Tree

// Given the root of a binary tree, find the diameter of the tree.

// The diameter of a binary tree is defined as the length of the longest path between any two nodes in the tree.
// This path may or may not pass through the root.

// The length of the path is measured as the number of edges between the two nodes.

// A path is a sequence of nodes where each consecutive pair is connected by an edge.

// ✍️ Example

// For the binary tree:

//         1
//        / \
//       2   3
//      / \
//     4   5


// The longest path is:
// 4 → 2 → 5 (or 4 → 2 → 1 → 3)

// So, the diameter = 3 edges.
/**
 * Tree Node Definition
 */
class TreeNode {
    int data;
    TreeNode left;
    TreeNode right;

    TreeNode(int data) {
        this.data = data;
        left = null;
        right = null;
    }
}

public class DiameterOfBT{

    /*
    Function: maxDepth
    Purpose: Compute the maximum depth of a tree
    Time: O(N)
    Space: O(H)
    */
    static int maxDepth(TreeNode root) {
        if (root == null) return 0;
        return 1 + Math.max(maxDepth(root.left), maxDepth(root.right));
    }

    /*
    Brute-force diameter (O(N^2))
    Time: O(N^2) - maxDepth called for each node
    Space: O(H)
    */
    static int diameterBrute(TreeNode root) {
        if (root == null) return 0;

        int lh = maxDepth(root.left);
        int rh = maxDepth(root.right);

        int d1 = lh + rh;                    // diameter through root
        int d2 = diameterBrute(root.left);  // left subtree
        int d3 = diameterBrute(root.right); // right subtree

        return Math.max(d1, Math.max(d2, d3));
    }

    /*
    Optimized diameter (O(N))
    Time: O(N) - each node visited once
    Space: O(H)
    */
    static int diameterOptimized(TreeNode root, int[] maxi) {
        if (root == null) return 0;

        int lh = diameterOptimized(root.left, maxi);
        int rh = diameterOptimized(root.right, maxi);

        // Update maximum diameter
        maxi[0] = Math.max(maxi[0], lh + rh);

        // Return height
        return 1 + Math.max(lh, rh);
    }

    static int diameter(TreeNode root) {
        int[] maxi = new int[1]; // acts like pass-by-reference
        diameterOptimized(root, maxi);
        return maxi[0];
    }

    /* Example usage */
    public static void main(String[] args) {

        // Build simple tree:
        //        1
        //       / \
        //      2   3
        //     / \
        //    4   5
        TreeNode root = new TreeNode(1);
        root.left = new TreeNode(2);
        root.right = new TreeNode(3);
        root.left.left = new TreeNode(4);
        root.left.right = new TreeNode(5);

        System.out.println("Diameter (Brute-force): " + diameterBrute(root));
        System.out.println("Diameter (Optimized): " + diameter(root));
    }
}
