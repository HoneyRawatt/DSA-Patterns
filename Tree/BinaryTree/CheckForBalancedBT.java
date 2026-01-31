package Tree.BinaryTree;

import java.util.*;

/*
Class: TreeNode
Purpose: Node of a binary tree
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

public class CheckForBalancedBT{

    static Scanner sc = new Scanner(System.in);

    /*
    Function: insertion
    Purpose: Recursively build a binary tree from user input
    Input: -1 means no node
    Time Complexity: O(N)
    Space Complexity: O(H)
    */
    static TreeNode insertion() {
        System.out.print("Enter data (-1 for no node): ");
        int val = sc.nextInt();

        if (val == -1)
            return null;

        TreeNode node = new TreeNode(val);

        System.out.println("Enter left child of " + val + ":");
        node.left = insertion();

        System.out.println("Enter right child of " + val + ":");
        node.right = insertion();

        return node;
    }

    /*
    Recursive Traversals
    Time Complexity: O(N)
    Space Complexity: O(H)
    */
    static void inorder(TreeNode root) {
        if (root == null) return;
        inorder(root.left);
        System.out.print(root.data + " ");
        inorder(root.right);
    }

    static void preorder(TreeNode root) {
        if (root == null) return;
        System.out.print(root.data + " ");
        preorder(root.left);
        preorder(root.right);
    }

    static void postorder(TreeNode root) {
        if (root == null) return;
        postorder(root.left);
        postorder(root.right);
        System.out.print(root.data + " ");
    }

    /*
    Level-order Traversal (BFS)
    Time Complexity: O(N)
    Space Complexity: O(N)
    */
    static List<List<Integer>> levelorder(TreeNode root) {
        List<List<Integer>> ans = new ArrayList<>();
        if (root == null) return ans;

        Queue<TreeNode> q = new LinkedList<>();
        q.add(root);

        while (!q.isEmpty()) {
            int size = q.size();
            List<Integer> level = new ArrayList<>();

            for (int i = 0; i < size; i++) {
                TreeNode node = q.poll();
                level.add(node.data);

                if (node.left != null) q.add(node.left);
                if (node.right != null) q.add(node.right);
            }
            ans.add(level);
        }
        return ans;
    }

    /*
    Iterative Traversals
    Time Complexity: O(N)
    Space Complexity: O(H)
    */
    static List<Integer> preorderitr(TreeNode root) {
        List<Integer> pre = new ArrayList<>();
        if (root == null) return pre;

        Stack<TreeNode> st = new Stack<>();
        st.push(root);

        while (!st.isEmpty()) {
            TreeNode node = st.pop();
            pre.add(node.data);

            if (node.right != null) st.push(node.right);
            if (node.left != null) st.push(node.left);
        }
        return pre;
    }

    static List<Integer> inorderitr(TreeNode root) {
        List<Integer> ino = new ArrayList<>();
        Stack<TreeNode> st = new Stack<>();
        TreeNode node = root;

        while (node != null || !st.isEmpty()) {
            if (node != null) {
                st.push(node);
                node = node.left;
            } else {
                node = st.pop();
                ino.add(node.data);
                node = node.right;
            }
        }
        return ino;
    }

    static List<Integer> postorderitr(TreeNode root) {
        List<Integer> post = new ArrayList<>();
        if (root == null) return post;

        Stack<TreeNode> st1 = new Stack<>();
        Stack<TreeNode> st2 = new Stack<>();

        st1.push(root);

        while (!st1.isEmpty()) {
            TreeNode node = st1.pop();
            st2.push(node);

            if (node.left != null) st1.push(node.left);
            if (node.right != null) st1.push(node.right);
        }

        while (!st2.isEmpty()) {
            post.add(st2.pop().data);
        }
        return post;
    }

    /*
    Function: maxDepth
    Purpose: Compute maximum depth of binary tree
    Time Complexity: O(N)
    Space Complexity: O(H)
    */
    static int maxDepth(TreeNode root) {
        if (root == null) return 0;
        return 1 + Math.max(maxDepth(root.left), maxDepth(root.right));
    }

    /*
    Function: isBalancedBrute
    Purpose: Brute-force balanced tree check
    Time Complexity: O(N^2)
    Space Complexity: O(H)
    */
    static boolean isBalancedBrute(TreeNode root) {
        if (root == null) return true;

        int lh = maxDepth(root.left);
        int rh = maxDepth(root.right);

        if (Math.abs(lh - rh) > 1) return false;

        return isBalancedBrute(root.left) && isBalancedBrute(root.right);
    }

    /*
    Optimized balanced tree check
    Time Complexity: O(N)
    Space Complexity: O(H)
    Returns -1 if unbalanced, else height
    */
    static int checkBalanced(TreeNode root) {
        if (root == null) return 0;

        int lh = checkBalanced(root.left);
        if (lh == -1) return -1;

        int rh = checkBalanced(root.right);
        if (rh == -1) return -1;

        if (Math.abs(lh - rh) > 1) return -1;

        return 1 + Math.max(lh, rh);
    }

    static boolean isBalanced(TreeNode root) {
        return checkBalanced(root) != -1;
    }

    /*
    Main Function
    */
    public static void main(String[] args) {

        TreeNode root = insertion();

        System.out.println("\nRecursive Traversals:");
        System.out.print("Inorder: "); inorder(root); System.out.println();
        System.out.print("Preorder: "); preorder(root); System.out.println();
        System.out.print("Postorder: "); postorder(root); System.out.println();

        System.out.println("\nIterative Traversals:");
        System.out.print("Preorder (iterative): ");
        for (int x : preorderitr(root)) System.out.print(x + " ");
        System.out.println();

        System.out.print("Inorder (iterative): ");
        for (int x : inorderitr(root)) System.out.print(x + " ");
        System.out.println();

        System.out.print("Postorder (iterative): ");
        for (int x : postorderitr(root)) System.out.print(x + " ");
        System.out.println();

        System.out.println("\nLevel Order Traversal:");
        for (List<Integer> lvl : levelorder(root)) {
            for (int x : lvl) System.out.print(x + " ");
            System.out.println();
        }

        System.out.println("\nMaximum Depth: " + maxDepth(root));
        System.out.println("Balanced (Brute): " + (isBalancedBrute(root) ? "Yes" : "No"));
        System.out.println("Balanced (Optimized): " + (isBalanced(root) ? "Yes" : "No"));
    }
}
