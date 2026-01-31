/*
====================================================
📌 Problem Statement
====================================================
Given a Binary Search Tree (BST):

1️⃣ Find the k-th smallest element
2️⃣ Find the k-th largest element

Constraints:
- Optimize space usage.
- Avoid recursion or stack if possible.

Observation:
- Inorder traversal of BST gives sorted order (ascending).
- Reverse inorder traversal gives sorted order (descending).
====================================================
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

public class KthElementBST {

    /*
    Helper Function: insertBST
    Purpose: Inserts a value into BST (used for testing)
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
    💡 Intuition (k-th Smallest)
    ====================================================
    - Inorder traversal of BST gives sorted order.
    - Morris Traversal allows inorder traversal
      without recursion or stack.
    - We temporarily create links (threads) to
      predecessor nodes.
    ====================================================
    */

    /*
    Function: kthSmallest
    Purpose: Find the k-th smallest element using
             Morris Inorder Traversal
    */
    static TreeNode kthSmallest(TreeNode root, int k) {
        int count = 0;
        TreeNode curr = root;

        while (curr != null) {

            // Case 1: No left child → visit node
            if (curr.left == null) {
                count++;
                if (count == k) return curr;
                curr = curr.right;
            }
            // Case 2: Left child exists
            else {
                // Find inorder predecessor
                TreeNode prev = curr.left;
                while (prev.right != null && prev.right != curr)
                    prev = prev.right;

                // Create thread
                if (prev.right == null) {
                    prev.right = curr;
                    curr = curr.left;
                }
                // Thread exists → remove it
                else {
                    prev.right = null;
                    count++;
                    if (count == k) return curr;
                    curr = curr.right;
                }
            }
        }
        return null; // k is larger than number of nodes
    }

    /*
    ====================================================
    💡 Intuition (k-th Largest)
    ====================================================
    - Reverse inorder traversal gives descending order.
    - Morris traversal can be applied in reverse:
      Right → Node → Left
    ====================================================
    */

    /*
    Function: kthLargest
    Purpose: Find the k-th largest element using
             Morris Reverse Inorder Traversal
    */
    static TreeNode kthLargest(TreeNode root, int k) {
        int count = 0;
        TreeNode curr = root;

        while (curr != null) {

            // Case 1: No right child → visit node
            if (curr.right == null) {
                count++;
                if (count == k) return curr;
                curr = curr.left;
            }
            // Case 2: Right child exists
            else {
                // Find reverse inorder successor
                TreeNode next = curr.right;
                while (next.left != null && next.left != curr)
                    next = next.left;

                // Create thread
                if (next.left == null) {
                    next.left = curr;
                    curr = curr.right;
                }
                // Thread exists → remove it
                else {
                    next.left = null;
                    count++;
                    if (count == k) return curr;
                    curr = curr.left;
                }
            }
        }
        return null; // k is larger than number of nodes
    }

    /*
    ====================================================
    🧪 Main Function (Testing)
    ====================================================
    BST Structure:
                5
               / \
              3   6
             / \
            2   4
           /
          1
    ====================================================
    */
    public static void main(String[] args) {

        TreeNode root = null;
        root = insertBST(root, 5);
        root = insertBST(root, 3);
        root = insertBST(root, 6);
        root = insertBST(root, 2);
        root = insertBST(root, 4);
        root = insertBST(root, 1);

        int kSmall = 3;
        TreeNode small = kthSmallest(root, kSmall);
        if (small != null)
            System.out.println(kSmall + "th smallest element is: " + small.val);

        int kLarge = 2;
        TreeNode large = kthLargest(root, kLarge);
        if (large != null)
            System.out.println(kLarge + "th largest element is: " + large.val);
    }
}

/*
====================================================
⏱ Time & Space Complexity
====================================================
Time Complexity:
- O(N): each node is visited at most twice

Space Complexity:
- O(1): no recursion, no stack

====================================================
🧠 Key Takeaways
====================================================
✔ Morris traversal enables inorder traversal in O(1) space
✔ BST properties give sorted traversal
✔ Very strong interview solution
====================================================
*/
