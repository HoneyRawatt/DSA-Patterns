package Tree.BinaryTree;

/*
Class: TreeNode
Purpose: Represents a single node in a binary tree.
Each node contains:
- data  → value stored in the node
- left  → reference to left child
- right → reference to right child
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

public class SymmetricTree {

    /*
    Function: isSymmetricHelper
    Purpose:
    - Checks whether two subtrees are mirror images of each other.

    Intuition:
    - Two trees are mirrors if:
      1️⃣ Their root values are equal
      2️⃣ Left subtree of one mirrors the right subtree of the other
      3️⃣ Right subtree of one mirrors the left subtree of the other

    Base Cases:
    - If both nodes are null → symmetric
    - If only one is null → not symmetric

    Recursive Case:
    - Compare values
    - Recursively compare mirrored children
    */
    public static boolean isSymmetricHelper(TreeNode left, TreeNode right) {

        // If either node is null, both must be null to be symmetric
        if (left == null || right == null)
            return left == right;

        // If values do not match, not symmetric
        if (left.data != right.data)
            return false;

        // Check outer and inner mirror pairs
        return isSymmetricHelper(left.left, right.right) &&
               isSymmetricHelper(left.right, right.left);
    }

    /*
    Function: isSymmetric
    Purpose:
    - Determines whether the binary tree is symmetric.

    Approach:
    - A tree is symmetric if its left and right subtrees are mirror images.
    - An empty tree is symmetric.
    */
    public static boolean isSymmetric(TreeNode root) {
        return root == null || isSymmetricHelper(root.left, root.right);
    }

    /*
    Time Complexity: O(N)
    - Every node is visited once.

    Space Complexity: O(H)
    - Recursion stack where H is the height of the tree.
    - Worst case: O(N) (skewed tree)
    - Best case: O(log N) (balanced tree)
    */

    public static void main(String[] args) {

        /*
        Example symmetric tree:

                1
               / \
              2   2
             / \ / \
            3  4 4  3
        */

        TreeNode root = new TreeNode(1);
        root.left = new TreeNode(2);
        root.right = new TreeNode(2);
        root.left.left = new TreeNode(3);
        root.left.right = new TreeNode(4);
        root.right.left = new TreeNode(4);
        root.right.right = new TreeNode(3);

        System.out.println(
            isSymmetric(root)
            ? "Tree is Symmetric"
            : "Tree is Not Symmetric"
        );
    }
}
