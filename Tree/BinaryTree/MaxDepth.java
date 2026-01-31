package Tree.BinaryTree;

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

public class MaxDepth{

    /*
     * Function: maxDepth()
     * Purpose : Returns the maximum depth (height) of the binary tree.
     *           Depth = number of nodes along the longest path
     *           from root to leaf.
     *
     * Approach:
     *  - Use recursion.
     *  - For each node:
     *      → compute left subtree height
     *      → compute right subtree height
     *      → result = 1 + max(left, right)
     *
     * Time Complexity:
     *  O(N) — each node is visited once.
     *
     * Space Complexity:
     *  O(H) — recursive call stack
     *      Worst case (skewed tree): O(N)
     *      Best case (balanced tree): O(log N)
     */
    static int maxDepth(TreeNode root) {
        if (root == null)
            return 0;

        int leftHeight = maxDepth(root.left);
        int rightHeight = maxDepth(root.right);

        return 1 + Math.max(leftHeight, rightHeight);
    }

    public static void main(String[] args) {

        // Example tree:
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

        System.out.println("Maximum Depth of Tree: " + maxDepth(root));
    }
}
