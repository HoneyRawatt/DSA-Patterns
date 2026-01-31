package Tree.BinaryTree;

/*
====================================================
PROBLEM STATEMENT
====================================================
Count the number of nodes in a COMPLETE binary tree.

A complete binary tree:
- All levels are completely filled except possibly the last
- The last level is filled from left to right

We use an optimized approach instead of normal traversal.
====================================================
*/

/*
Class: TreeNode
Purpose:
Represents a node in a binary tree
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

public class CountCompleteTreeNodes {

    /*
    ------------------------------------------------
    Function: findHeightLeft
    Purpose :
    Find height by moving along the leftmost path
    of the tree.

    Input  : root node
    Output : height (int)

    Time Complexity: O(log N)
    ------------------------------------------------
    */
    public static int findHeightLeft(TreeNode root) {
        int height = 0;
        while (root != null) {
            height++;
            root = root.left;
        }
        return height;
    }

    /*
    ------------------------------------------------
    Function: findHeightRight
    Purpose :
    Find height by moving along the rightmost path
    of the tree.

    Input  : root node
    Output : height (int)

    Time Complexity: O(log N)
    ------------------------------------------------
    */
    public static int findHeightRight(TreeNode root) {
        int height = 0;
        while (root != null) {
            height++;
            root = root.right;
        }
        return height;
    }

    /*
    ====================================================
    Function: countNodes
    ====================================================
    Purpose:
    Count nodes in a complete binary tree using an
    optimized approach.

    Logic:
    1. Compute left height and right height.
    2. If left height == right height:
       → Tree is a perfect binary tree
       → Nodes = 2^height - 1
    3. Otherwise:
       → Recursively count nodes in left and right subtrees

    Time Complexity: O((log N)^2)
    - Height calculation: O(log N)
    - Performed at each recursive level

    Space Complexity: O(log N)
    - Recursion stack depth
    ====================================================
    */
    public static int countNodes(TreeNode root) {
        if (root == null) return 0;

        int lh = findHeightLeft(root);
        int rh = findHeightRight(root);

        // If heights are equal, it's a perfect binary tree
        if (lh == rh) {
            return (1 << lh) - 1;
        }

        // Otherwise, recurse on left and right subtrees
        return 1 + countNodes(root.left) + countNodes(root.right);
    }

    /*
    ------------------------------------------------
    Function: inorder
    Purpose:
    Count nodes using standard tree traversal
    (used here only for comparison)

    Time Complexity: O(N)
    Space Complexity: O(H) where H = height of tree
    ------------------------------------------------
    */
    public static void inorder(TreeNode root, int[] cnt) {
        if (root == null) return;

        cnt[0]++;
        inorder(root.left, cnt);
        inorder(root.right, cnt);
    }

    /*
    ------------------------------------------------
    Main function to test the solution
    ------------------------------------------------
    */
    public static void main(String[] args) {

        /*
               1
              / \
             2   3
            / \  /
           4   5 6

        Complete binary tree with 6 nodes
        */

        TreeNode root = new TreeNode(1);
        root.left = new TreeNode(2);
        root.right = new TreeNode(3);
        root.left.left = new TreeNode(4);
        root.left.right = new TreeNode(5);
        root.right.left = new TreeNode(6);

        // Optimized approach
        System.out.println(
            "Optimized countNodes output: " + countNodes(root)
        ); // Expected: 6

        // Traversal-based approach (for verification)
        int[] cnt = new int[1];
        inorder(root, cnt);
        System.out.println(
            "Traversal-based count (inorder) output: " + cnt[0]
        ); // Expected: 6
    }
}
