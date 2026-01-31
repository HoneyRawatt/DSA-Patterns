package Linkedlist;

/*
------------------------------------------------------------
Problem Statement:
------------------------------------------------------------
Given the head of a singly linked list, remove the N-th node
from the end of the list and return the head of the modified list.

The list contains at least one node and 1 ≤ N ≤ length of list.
------------------------------------------------------------
*/

public class RemoveNthNodeFromEnd {

    /*
    ------------------------------------------------------------
    Node structure for singly linked list
    ------------------------------------------------------------
    */
    static class Node {
        int data;      // Value stored in node
        Node next;     // Reference to next node

        Node(int val) {
            data = val;
            next = null;
        }

        Node(int val, Node next) {
            data = val;
            this.next = next;
        }
    }

    /*
    ------------------------------------------------------------
    Brute Force Approach
    ------------------------------------------------------------
    Intuition:
    Count the total number of nodes. The node to remove is
    (length - N)th node from the start.

    Steps:
    1. Traverse the list to count nodes.
    2. Traverse again to reach the node before target.
    3. Adjust pointers and delete the node.
    ------------------------------------------------------------
    */
    static Node removeNthNodeBrute(Node head, int n) {
        int cnt = 0;
        Node temp = head;

        // First pass: count total nodes
        while (temp != null) {
            cnt++;
            temp = temp.next;
        }

        // If head node needs to be removed
        if (cnt == n) {
            return head.next;
        }

        int res = cnt - n;
        temp = head;

        // Reach node before the target node
        while (temp.next != null) {
            res--;
            if (res == 0) break;
            temp = temp.next;
        }

        // Delete the target node
        temp.next = temp.next.next;

        return head;
    }

    /*
    ------------------------------------------------------------
    Optimal Approach (Two Pointer Technique)
    ------------------------------------------------------------
    Intuition:
    Maintain a gap of N nodes between fast and slow pointers.
    When fast reaches the end, slow is just before the node
    to be removed.

    Steps:
    1. Create a dummy node before head.
    2. Move fast pointer N steps ahead.
    3. Move both pointers until fast reaches the end.
    4. Delete slow.next.
    ------------------------------------------------------------
    */
    static Node removeNthNodeOptimal(Node head, int n) {
        Node dummy = new Node(-1, head);
        Node fast = dummy;
        Node slow = dummy;

        // Move fast pointer n steps ahead
        for (int i = 0; i < n; i++) {
            fast = fast.next;
        }

        // Move both pointers until fast reaches last node
        while (fast.next != null) {
            fast = fast.next;
            slow = slow.next;
        }

        // Delete the nth node from end
        slow.next = slow.next.next;

        return dummy.next;
    }

    /*
    ------------------------------------------------------------
    Utility Function: Print Linked List
    ------------------------------------------------------------
    */
    static void printList(Node head) {
        while (head != null) {
            System.out.print(head.data + " ");
            head = head.next;
        }
        System.out.println();
    }

    /*
    ------------------------------------------------------------
    Driver Code
    ------------------------------------------------------------
    */
    public static void main(String[] args) {

        Node head1 = new Node(1,
                        new Node(2,
                        new Node(3,
                        new Node(4,
                        new Node(5)))));

        Node head2 = new Node(1,
                        new Node(2,
                        new Node(3,
                        new Node(4,
                        new Node(5)))));

        System.out.print("Original list (Brute): ");
        printList(head1);
        head1 = removeNthNodeBrute(head1, 2);
        System.out.print("After brute removal: ");
        printList(head1);

        System.out.print("Original list (Optimal): ");
        printList(head2);
        head2 = removeNthNodeOptimal(head2, 2);
        System.out.print("After optimal removal: ");
        printList(head2);
    }

    /*
    ------------------------------------------------------------
    Time & Space Complexity:
    ------------------------------------------------------------

    Brute Force:
    - Time Complexity: O(N)
    - Space Complexity: O(1)

    Optimal Two Pointer:
    - Time Complexity: O(N)
    - Space Complexity: O(1)

    ------------------------------------------------------------
    */
}
