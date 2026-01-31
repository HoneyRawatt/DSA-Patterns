package Linkedlist;
/*
====================================================
PROBLEM STATEMENT:
----------------------------------------------------
Given the head of a singly linked list and an integer k,
reverse the nodes of the list k at a time and return
the modified list.

If the number of nodes left is less than k,
they should remain unchanged.
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
public class ReverseNodes_kgroup {

    /*
    ====================================================
    HELPER FUNCTION 1:
    ----------------------------------------------------
    Returns the k-th node starting from the given node.
    If fewer than k nodes are present, returns null.
    ====================================================
    */
    private static Node getKthNode(Node temp, int k) {
        while (temp != null && k > 1) {
            temp = temp.next;
            k--;
        }
        return temp;
    }

    /*
    ====================================================
    HELPER FUNCTION 2:
    ----------------------------------------------------
    Reverses a linked list segment starting at `head`.
    Standard iterative linked list reversal.
    ====================================================
    */
    private static void reverseList(Node head) {
        Node prev = null;
        Node curr = head;

        while (curr != null) {
            Node nextNode = curr.next;
            curr.next = prev;
            prev = curr;
            curr = nextNode;
        }
    }

    /*
    ====================================================
    MAIN FUNCTION:
    ----------------------------------------------------
    INTUITION:
    1. Traverse the list in groups of size k.
    2. For each group:
       - Find the k-th node.
       - Detach the group.
       - Reverse it.
       - Reconnect it to the main list.
    3. Leave remaining nodes unchanged if < k.
    ====================================================
    */

    public static Node kReverse(Node head, int k) {

        Node temp = head;        // Current group head
        Node prevNode = null;    // Tail of previous group

        while (temp != null) {

            // Find k-th node of current group
            Node kthNode = getKthNode(temp, k);

            // If fewer than k nodes remain
            if (kthNode == null) {
                if (prevNode != null) {
                    prevNode.next = temp;
                }
                break;
            }

            // Store next group's head
            Node nextNode = kthNode.next;

            // Detach current k-group
            kthNode.next = null;

            // Reverse current group
            reverseList(temp);

            // Update head for the first group
            if (temp == head) {
                head = kthNode;
            } else {
                prevNode.next = kthNode;
            }

            // Prepare for next iteration
            prevNode = temp;   // temp becomes tail after reversal
            temp = nextNode;   // Move to next group
        }

        return head;
    }

    /*
    ====================================================
    TIME COMPLEXITY:
    ----------------------------------------------------
    O(N) — each node is visited once

    SPACE COMPLEXITY:
    ----------------------------------------------------
    O(1) — in-place reversal
    ====================================================
    */
}
