package Tree.BinaryTree;

import java.util.ArrayList;
import java.util.List;

/*
Class: TreeNode
Purpose: Represents a node in a binary tree.
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

public class RootToNodePath {

    /*
    Function: getPath()
    Purpose:
        Recursively finds the path from the root node to the given target node `x`.
        - If the current node matches `x`, we stop and return true.
        - Otherwise, we recursively search in left and right subtrees.
        - If not found in either, we backtrack by removing the current node.

    Parameters:
        root → current node being checked
        path → list storing the current path
        x    → target node value

    Returns:
        true if path to node `x` exists, otherwise false

    Time Complexity:  O(N)
        → We may visit each node once in the worst case.

    Space Complexity: O(H)
        → Due to recursion stack + path list.
          H = height of the tree.
          Worst case (skewed tree): O(N)
          Best case (balanced tree): O(log N)
    */
    public static boolean getPath(TreeNode root, List<Integer> path, int x) {

        if (root == null) return false;        // Base: empty subtree → no path

        path.add(root.data);                  // Include current node in path

        if (root.data == x)                   // Found the target node
            return true;

        // Recur left or right — return true if found in either
        if (getPath(root.left, path, x) || getPath(root.right, path, x))
            return true;

        // If not found, backtrack — remove the node
        path.remove(path.size() - 1);
        return false;
    }

    /*
    Function: solve()
    Purpose:
        Wrapper function that initializes the path list
        and calls getPath() to find path from root (A) to target (B).
    */
    public static List<Integer> solve(TreeNode A, int B) {
        List<Integer> path = new ArrayList<>();
        if (A == null) return path;

        getPath(A, path, B);
        return path;
    }

    /*
    Example Usage:
    Input Tree:
            1
           / \
          2   3
         / \
        4   5
    Target: 5
    Expected Output: 1 → 2 → 5
    */
    public static void main(String[] args) {

        TreeNode root = new TreeNode(1);
        root.left = new TreeNode(2);
        root.right = new TreeNode(3);
        root.left.left = new TreeNode(4);
        root.left.right = new TreeNode(5);

        int target = 5;
        List<Integer> path = solve(root, target);

        System.out.print("Path from root to node " + target + ": ");
        for (int val : path) {
            System.out.print(val + " ");
        }
        System.out.println();
    }
}

