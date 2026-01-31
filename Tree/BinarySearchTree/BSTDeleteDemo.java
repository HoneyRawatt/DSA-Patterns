package Tree.BinarySearchTree;

/*
Class: TreeNode
Purpose: Represents a node in a binary search tree (BST)
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

public class BSTDeleteDemo {

    /*
    Function: insert
    Purpose: Inserts a new value into the BST and returns the root.
    */
    static TreeNode insert(TreeNode root, int val) {
        if (root == null)
            return new TreeNode(val);

        TreeNode curr = root;
        while (true) {
            if (val > curr.val) {
                if (curr.right != null)
                    curr = curr.right;
                else {
                    curr.right = new TreeNode(val);
                    break;
                }
            } else {
                if (curr.left != null)
                    curr = curr.left;
                else {
                    curr.left = new TreeNode(val);
                    break;
                }
            }
        }
        return root;
    }

    /*
    Helper: Finds the rightmost node in a subtree.
    */
    static TreeNode findLastRight(TreeNode root) {
        if (root.right == null)
            return root;
        return findLastRight(root.right);
    }

    /*
    Helper: Deletes a node (used in iterative version)
    */
    static TreeNode helper(TreeNode root) {
        if (root.left == null)
            return root.right;
        else if (root.right == null)
            return root.left;

        // Both children exist
        TreeNode rightChild = root.right;
        TreeNode lastRight = findLastRight(root.left);
        lastRight.right = rightChild;
        return root.left;
    }

    /*
    Helper: Finds smallest node in a subtree (used in recursive version)
    */
    static TreeNode findMin(TreeNode node) {
        while (node.left != null)
            node = node.left;
        return node;
    }

    /*
    Version 1: Iterative deleteNode (O(1) extra space)
    */
    static TreeNode deleteNodeIterative(TreeNode root, int key) {
        if (root == null)
            return null;

        if (root.val == key)
            return helper(root);

        TreeNode curr = root;
        while (curr != null) {
            if (key < curr.val) {
                if (curr.left != null && curr.left.val == key) {
                    curr.left = helper(curr.left);
                    break;
                } else
                    curr = curr.left;
            } else {
                if (curr.right != null && curr.right.val == key) {
                    curr.right = helper(curr.right);
                    break;
                } else
                    curr = curr.right;
            }
        }
        return root;
    }

    /*
    Version 2: Recursive deleteNode (simpler, but uses O(h) space)
    */
    static TreeNode deleteNodeRecursive(TreeNode root, int key) {
        if (root == null)
            return null;

        if (key < root.val) {
            root.left = deleteNodeRecursive(root.left, key);
        } else if (key > root.val) {
            root.right = deleteNodeRecursive(root.right, key);
        } else {
            // Node found
            if (root.left == null)
                return root.right;
            else if (root.right == null)
                return root.left;

            // Node has two children
            TreeNode successor = findMin(root.right);
            root.val = successor.val;
            root.right = deleteNodeRecursive(root.right, successor.val);
        }

        return root;
    }

    /*
    Helper: inorder traversal to verify BST structure
    */
    static void inorder(TreeNode root) {
        if (root == null)
            return;
        inorder(root.left);
        System.out.print(root.val + " ");
        inorder(root.right);
    }

    /*
    Main function for testing
    */
    public static void main(String[] args) {
        TreeNode root = null;

        // Insert nodes
        root = insert(root, 8);
        root = insert(root, 3);
        root = insert(root, 10);
        root = insert(root, 1);
        root = insert(root, 6);
        root = insert(root, 14);
        root = insert(root, 4);
        root = insert(root, 7);
        root = insert(root, 13);

        System.out.print("Inorder before deletion: ");
        inorder(root);
        System.out.println();

        int key = 6;

        // Choose which version to test:
        // root = deleteNodeIterative(root, key);
        root = deleteNodeRecursive(root, key);

        System.out.print("Inorder after deleting " + key + ": ");
        inorder(root);
        System.out.println();
    }
}

/*
Complexity:
Operation       Time        Space
Insert          O(h)        O(1)
Search          O(h)        O(1)
Delete          O(h)        O(h) (recursive) or O(1) (iterative)

For balanced BST: h = log n
For skewed BST:   h = n
*/
