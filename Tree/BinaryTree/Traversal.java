package Tree.BinaryTree;

import java.util.*;

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

public class Traversal{

    static Scanner sc = new Scanner(System.in);

    /*
     * Function: insertion()
     * Purpose : Builds the binary tree recursively using user input (-1 = no node)
     *
     * Time Complexity:
     *     O(N) — Each node is created exactly once.
     * Space Complexity:
     *     O(H) — Recursive stack space (H = height of tree)
     */
    static TreeNode insertion() {
        System.out.print("Enter the data (-1 for no node): ");
        int val = sc.nextInt();

        if (val == -1)
            return null;

        TreeNode node = new TreeNode(val);

        System.out.println("Enter the left child of " + val + ": ");
        node.left = insertion();

        System.out.println("Enter the right child of " + val + ": ");
        node.right = insertion();

        return node;
    }

    /*
     * Function: inorder()
     * Purpose : Recursive Inorder Traversal (Left, Root, Right)
     *
     * Time Complexity: O(N)
     * Space Complexity: O(H)
     */
    static void inorder(TreeNode root) {
        if (root == null)
            return;
        inorder(root.left);
        System.out.print(root.data + " ");
        inorder(root.right);
    }

    /*
     * Function: preorder()
     * Purpose : Recursive Preorder Traversal (Root, Left, Right)
     *
     * Time Complexity: O(N)
     * Space Complexity: O(H)
     */
    static void preorder(TreeNode root) {
        if (root == null)
            return;
        System.out.print(root.data + " ");
        preorder(root.left);
        preorder(root.right);
    }

    /*
     * Function: postorder()
     * Purpose : Recursive Postorder Traversal (Left, Right, Root)
     *
     * Time Complexity: O(N)
     * Space Complexity: O(H)
     */
    static void postorder(TreeNode root) {
        if (root == null)
            return;
        postorder(root.left);
        postorder(root.right);
        System.out.print(root.data + " ");
    }

    /*
     * Function: levelorder()
     * Purpose : BFS traversal of all levels using a queue
     *
     * Time Complexity: O(N)
     * Space Complexity: O(N)
     */
    static List<List<Integer>> levelorder(TreeNode root) {
        List<List<Integer>> ans = new ArrayList<>();
        if (root == null)
            return ans;

        Queue<TreeNode> q = new LinkedList<>();
        q.add(root);

        while (!q.isEmpty()) {
            int size = q.size();
            List<Integer> level = new ArrayList<>();

            for (int i = 0; i < size; i++) {
                TreeNode node = q.poll();
                level.add(node.data);

                if (node.left != null)
                    q.add(node.left);
                if (node.right != null)
                    q.add(node.right);
            }
            ans.add(level);
        }
        return ans;
    }

    /*
     * Function: preorderitr()
     * Purpose : Iterative Preorder Traversal using a stack
     *
     * Time Complexity: O(N)
     * Space Complexity: O(H)
     */
    static List<Integer> preorderitr(TreeNode root) {
        List<Integer> preorder = new ArrayList<>();
        if (root == null)
            return preorder;

        Stack<TreeNode> st = new Stack<>();
        st.push(root);

        while (!st.isEmpty()) {
            TreeNode node = st.pop();
            preorder.add(node.data);

            // Push right first so left is processed first
            if (node.right != null)
                st.push(node.right);
            if (node.left != null)
                st.push(node.left);
        }
        return preorder;
    }

    /*
     * Function: inorderitr()
     * Purpose : Iterative Inorder Traversal using a stack
     *
     * Time Complexity: O(N)
     * Space Complexity: O(H)
     */
    static List<Integer> inorderitr(TreeNode root) {
        List<Integer> inorder = new ArrayList<>();
        Stack<TreeNode> st = new Stack<>();
        TreeNode node = root;

        while (true) {
            if (node != null) {
                st.push(node);
                node = node.left;
            } else {
                if (st.isEmpty())
                    break;
                node = st.pop();
                inorder.add(node.data);
                node = node.right;
            }
        }
        return inorder;
    }

    /*
     * Function: postorderitr()
     * Purpose : Iterative Postorder Traversal using two stacks
     *
     * Time Complexity: O(N)
     * Space Complexity: O(2H) ≈ O(H)
     */
    static List<Integer> postorderitr(TreeNode root) {
        List<Integer> postorder = new ArrayList<>();
        if (root == null)
            return postorder;

        Stack<TreeNode> st1 = new Stack<>();
        Stack<TreeNode> st2 = new Stack<>();

        st1.push(root);

        while (!st1.isEmpty()) {
            TreeNode node = st1.pop();
            st2.push(node);

            if (node.left != null)
                st1.push(node.left);
            if (node.right != null)
                st1.push(node.right);
        }

        while (!st2.isEmpty()) {
            postorder.add(st2.pop().data);
        }
        return postorder;
    }

    /*
     * Function: postorderitr_1stack()
     * Purpose : Iterative Postorder Traversal using only one stack
     *
     * Time Complexity: O(N)
     * Space Complexity: O(H)
     */
    static List<Integer> postorderitr_1stack(TreeNode root) {
        List<Integer> post = new ArrayList<>();
        if (root == null)
            return post;

        Stack<TreeNode> st = new Stack<>();
        TreeNode curr = root;
        TreeNode temp;

        while (curr != null || !st.isEmpty()) {
            if (curr != null) {
                st.push(curr);
                curr = curr.left;
            } else {
                temp = st.peek().right;
                if (temp == null) {
                    temp = st.pop();
                    post.add(temp.data);

                    while (!st.isEmpty() && temp == st.peek().right) {
                        temp = st.pop();
                        post.add(temp.data);
                    }
                } else {
                    curr = temp;
                }
            }
        }
        return post;
    }

    public static void main(String[] args) {

        TreeNode root = insertion();

        System.out.println("\nRecursive Traversals:");
        System.out.print("Inorder: ");
        inorder(root);

        System.out.print("\nPreorder: ");
        preorder(root);

        System.out.print("\nPostorder: ");
        postorder(root);

        System.out.println("\n\nIterative Traversals:");

        System.out.print("Preorder (Iterative): ");
        for (int val : preorderitr(root))
            System.out.print(val + " ");
        System.out.println();

        System.out.print("Inorder (Iterative): ");
        for (int val : inorderitr(root))
            System.out.print(val + " ");
        System.out.println();

        System.out.print("Postorder (Iterative): ");
        for (int val : postorderitr(root))
            System.out.print(val + " ");
        System.out.println();

        System.out.println("\nLevel Order Traversal:");
        for (List<Integer> level : levelorder(root)) {
            for (int val : level)
                System.out.print(val + " ");
            System.out.println();
        }
    }
}
