package Linkedlist;

/*
====================================================
Problem Statement:
----------------------------------------------------
Given the head of a singly linked list, find and
return the middle node of the linked list.

Rules:
- If the number of nodes is odd → return the exact middle.
- If the number of nodes is even → return the second middle.
====================================================
*/

public class MiddleOfLinkedList {

    // Definition of Linked List Node
    static class Node {
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

    /*
    ====================================================
    Approach 1: Brute Force (Length Counting)
    ----------------------------------------------------
    Intuition:
    - First count total number of nodes.
    - Middle index = length / 2.
    - Traverse again to reach the middle node.

    Time Complexity:  O(n)
    Space Complexity: O(1)
    ====================================================
    */
    static Node middleBrute(Node head) {
        if (head == null) return null;

        int cnt = 0;
        Node temp = head;

        // Count nodes
        while (temp != null) {
            cnt++;
            temp = temp.next;
        }

        // Move to middle
        int mid = cnt / 2;
        temp = head;
        while (mid-- > 0) {
            temp = temp.next;
        }

        return temp;
    }

    /*
    ====================================================
    Approach 2: Optimal (Slow–Fast Pointer)
    ----------------------------------------------------
    Intuition:
    - Slow pointer moves one step.
    - Fast pointer moves two steps.
    - When fast reaches end, slow is at middle.

    Why it works:
    - Fast pointer covers list twice as fast.

    Time Complexity:  O(n)
    Space Complexity: O(1)
    ====================================================
    */
    static Node middle(Node head) {
        if (head == null) return null;

        Node slow = head;
        Node fast = head;

        while (fast != null && fast.next != null) {
            slow = slow.next;
            fast = fast.next.next;
        }

        return slow;
    }

    /*
    ====================================================
    Main Function (Testing)
    ====================================================
    */
    public static void main(String[] args) {
        Node head = new Node(1,
                        new Node(2,
                        new Node(3,
                        new Node(4,
                        new Node(5)))));

        Node mid1 = middleBrute(head);
        System.out.println("Middle (brute): " + mid1.data);

        Node mid2 = middle(head);
        System.out.println("Middle (optimal): " + mid2.data);
    }
}

