package Linkedlist;
/*
====================================================
PROBLEM STATEMENT:
----------------------------------------------------
Given the head of a singly linked list and an integer k,
rotate the linked list to the right by k positions.

Example:
Input : 1 -> 2 -> 3 -> 4 -> 5 , k = 2
Output: 4 -> 5 -> 1 -> 2 -> 3
====================================================
*/

/*
Definition for singly linked list node (GFG style)
class Node {
    int data;
    Node next;

    Node(int x) {
        data = x;
        next = null;
    }
}
*/

class rotateALL{

    /*
    ====================================================
    HELPER FUNCTION:
    ----------------------------------------------------
    Finds and returns the k-th node (1-based indexing)
    from the given node.
    ====================================================
    */
    private static Node findNthNode(Node temp, int k) {
        int count = 1;
        while (temp != null) {
            if (count == k) return temp;
            count++;
            temp = temp.next;
        }
        return null;
    }

    /*
    ====================================================
    MAIN FUNCTION:
    ----------------------------------------------------
    INTUITION:
    1. Find the length of the linked list.
    2. Reduce k using k = k % length.
    3. Make the list circular by connecting tail to head.
    4. Find the new last node at (length - k).
    5. Break the circular link to get rotated list.
    ====================================================
    */
    public static Node rotate(Node head, int k) {

        // Edge cases
        if (head == null || head.next == null || k == 0)
            return head;

        // Step 1: Find length and tail
        int length = 1;
        Node tail = head;
        while (tail.next != null) {
            length++;
            tail = tail.next;
        }

        // Step 2: Normalize k
        k = k % length;
        if (k == 0) return head;

        // Step 3: Make list circular
        tail.next = head;

        // Step 4: Find new last node
        Node newLastNode = findNthNode(head, length - k);

        // Step 5: Break the circle
        head = newLastNode.next;
        newLastNode.next = null;

        return head;
    }

    /*
    ====================================================
    TIME COMPLEXITY:
    ----------------------------------------------------
    O(N)

    SPACE COMPLEXITY:
    ----------------------------------------------------
    O(1)
    ====================================================
    */
}
