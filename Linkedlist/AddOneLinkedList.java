package Linkedlist;

/*
------------------------------------------------------------
Problem Statement:
------------------------------------------------------------
Given a non-empty singly linked list representing a non-negative
integer, add 1 to the number and return the updated linked list.

Example:
Input: 1 -> 2 -> 9 -> 9 -> 9
Output: 1 -> 3 -> 0 -> 0 -> 0
------------------------------------------------------------
*/

public class AddOneLinkedList {

    // Node class for singly linked list
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
    ------------------------------------------------------------
    Helper: Reverse linked list
    ------------------------------------------------------------
    Iterative method to reverse a singly linked list
    */
    static Node reverse(Node head) {
        Node prev = null;
        Node curr = head;

        while (curr != null) {
            Node next = curr.next;
            curr.next = prev;
            prev = curr;
            curr = next;
        }

        return prev;
    }

    /*
    ------------------------------------------------------------
    Iterative Approach to Add 1
    ------------------------------------------------------------
    Steps:
    1. Reverse the list to start addition from least significant digit.
    2. Add 1 and propagate carry.
    3. Reverse list back.
    4. If carry remains after last node, add a new node at the front.
    ------------------------------------------------------------
    */
    static Node addOneIterative(Node head) {
        head = reverse(head);
        Node temp = head;
        int carry = 1;

        while (temp != null) {
            temp.data += carry;
            if (temp.data < 10) {
                carry = 0;
                break;
            } else {
                temp.data = 0;
                carry = 1;
            }

            if (temp.next == null) break;
            temp = temp.next;
        }

        if (carry == 1) {
            Node newNode = new Node(1);
            head = reverse(head);
            newNode.next = head;
            return newNode;
        }

        head = reverse(head);
        return head;
    }

    /*
    ------------------------------------------------------------
    Recursive Helper
    ------------------------------------------------------------
    Recursively propagate addition from least significant digit.
    Returns carry to previous node.
    */
    static int helperAdd(Node node) {
        if (node == null) return 1; // base case: add 1 at the end

        int carry = helperAdd(node.next);
        node.data += carry;

        if (node.data < 10) return 0;
        node.data = 0;
        return 1;
    }

    /*
    ------------------------------------------------------------
    Recursive Approach to Add 1
    ------------------------------------------------------------
    Steps:
    1. Call helperAdd to recursively propagate addition.
    2. If carry remains at head, create new node at front.
    */
    static Node addOneRecursive(Node head) {
        int carry = helperAdd(head);
        if (carry == 1) {
            Node newNode = new Node(1, head);
            return newNode;
        }
        return head;
    }

    // Utility: print linked list
    static void printList(Node head) {
        while (head != null) {
            System.out.print(head.data + " ");
            head = head.next;
        }
        System.out.println();
    }

    // Driver code
    public static void main(String[] args) {
        Node head1 = new Node(1, new Node(2, new Node(9, new Node(9, new Node(9)))));
        System.out.print("Original number: ");
        printList(head1);

        Node addedIter = addOneIterative(head1);
        System.out.print("After adding 1 (iterative): ");
        printList(addedIter);

        Node head2 = new Node(1, new Node(2, new Node(9, new Node(9, new Node(9)))));
        Node addedRec = addOneRecursive(head2);
        System.out.print("After adding 1 (recursive): ");
        printList(addedRec);
    }

    /*
    ------------------------------------------------------------
    Time & Space Complexity
    ------------------------------------------------------------

    Iterative Approach:
    - Time Complexity: O(N) // reverse + addition + reverse
    - Space Complexity: O(1)

    Recursive Approach:
    - Time Complexity: O(N)
    - Space Complexity: O(N) // recursion stack
    ------------------------------------------------------------
    */
}
