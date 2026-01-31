package Tree.BinarySearchTree;

import java.util.Stack;

/*
====================================================
📌 Problem Statement
====================================================
Design an iterator over a Binary Search Tree (BST)
that returns the elements in ascending (inorder) order.

The iterator should support:
1️⃣ next()    → returns the next smallest element
2️⃣ hasNext() → returns true if there exists a next element

Constraints:
- next() and hasNext() should run in average O(1) time
- Use O(h) space, where h is the height of the BST
====================================================
*/

/*
Class: TreeNode
Purpose: Represents a node in a Binary Search Tree (BST)
*/
class TreeNode {
    int val;
    TreeNode left;
    TreeNode right;

    TreeNode(int val) {
        this.val = val;
        left = null;
        right = null;
    }
}

/*
====================================================
Class: BSTIterator
====================================================
💡 Intuition:
- Inorder traversal of a BST gives elements in sorted order.
- Instead of storing the full inorder traversal,
  we simulate it using a stack.
- The stack always maintains the path to the next
  smallest unvisited node.

====================================================
⚙️ Approach:
- Push all left children starting from the root.
- The top of the stack is always the next smallest element.
- After visiting a node, push all left children
  of its right subtree.
====================================================
*/
class BSTIterator {

    private Stack<TreeNode> st = new Stack<>();

    /*
    Constructor:
    - Initializes the iterator.
    - Pushes all left children of the root into the stack.
    */
    public BSTIterator(TreeNode root) {
        pushAll(root);
    }

    /*
    Function: hasNext
    Purpose:
    - Checks whether there is a next smallest element.
    */
    public boolean hasNext() {
        return !st.isEmpty();
    }

    /*
    Function: next
    Purpose:
    - Returns the next smallest element in BST.
    - Pops the top node.
    - Processes its right subtree.
    */
    public int next() {
        TreeNode tempNode = st.pop();

        // Push all left children of the right subtree
        pushAll(tempNode.right);

        return tempNode.val;
    }

    /*
    Helper Function: pushAll
    Purpose:
    - Pushes all left children of a subtree into the stack.
    - Ensures the smallest available element is on top.
    */
    private void pushAll(TreeNode node) {
        while (node != null) {
            st.push(node);
            node = node.left;
        }
    }
}

/*
====================================================
🧠 Time & Space Complexity
====================================================

Time Complexity:
- next(): O(1) amortized
- hasNext(): O(1)

Each node is pushed and popped exactly once.

Space Complexity:
- O(h), where h is the height of the BST
  - Balanced BST → O(log N)
  - Skewed BST   → O(N)

====================================================
*/
