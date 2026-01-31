package Linkedlist;
/*
====================================================
Problem Statement:
----------------------------------------------------
Given the head of a singly linked list, delete the
middle node of the linked list and return the head.

If the list has only one node, return null.

For even length lists, delete the second middle node.
====================================================
*/

class Node {
    int data;
    Node next;

    Node(int val) {
        data = val;
        next = null;
    }

    Node(int val, Node next) {
        data = val;
        this.next = next;
    }
}

public class DeleteMiddleOfLinkedList {

    /*
    ====================================================
    Brute Force Approach
    ----------------------------------------------------
    Intuition:
    1. Count total number of nodes.
    2. Middle index = count / 2.
    3. Traverse again to the node just before middle.
    4. Remove middle node by changing links.

    Time Complexity: O(n)
    Space Complexity: O(1)
    ====================================================
    */
    static Node deleteMiddleBrute(Node head) {
        if (head == null || head.next == null)
            return null;

        int count = 0;
        Node temp = head;

        // Count nodes
        while (temp != null) {
            count++;
            temp = temp.next;
        }

        int mid = count / 2;
        temp = head;

        // Traverse to node before middle
        while (temp != null) {
            mid--;
            if (mid == 0) {
                Node middle = temp.next;
                temp.next = temp.next.next;
                break;
            }
            temp = temp.next;
        }
        return head;
    }

    /*
    ====================================================
    Optimized Approach (Slow & Fast Pointer)
    ----------------------------------------------------
    Intuition:
    - Slow pointer moves one step.
    - Fast pointer moves two steps.
    - When fast reaches end, slow is just before middle.

    Time Complexity: O(n)
    Space Complexity: O(1)
    ====================================================
    */
    static Node deleteMiddle(Node head) {
        if (head == null || head.next == null)
            return null;

        Node slow = head;
        Node fast = head;

        // Move fast pointer ahead initially
        fast = fast.next.next;

        while (fast != null && fast.next != null) {
            slow = slow.next;
            fast = fast.next.next;
        }

        // Delete middle node
        slow.next = slow.next.next;
        return head;
    }

    // Utility function to print list
    static void printList(Node head) {
        while (head != null) {
            System.out.print(head.data + " ");
            head = head.next;
        }
        System.out.println();
    }

    // ---------------- Main ----------------
    public static void main(String[] args) {

        // 1 -> 2 -> 3 -> 4 -> 5
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

        System.out.print("Original List: ");
        printList(head1);

        head1 = deleteMiddleBrute(head1);
        System.out.print("After Brute Force: ");
        printList(head1);

        head2 = deleteMiddle(head2);
        System.out.print("After Optimized: ");
        printList(head2);
    }
}
