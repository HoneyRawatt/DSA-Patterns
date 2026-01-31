package Linkedlist;

import java.util.Stack;

/*
------------------------------------------------------------
Problem Statement:
------------------------------------------------------------
Given the head of a singly linked list, reverse the linked
list and return the new head of the reversed list.

We will demonstrate three methods:
1. Using a Stack (brute force)
2. Iterative in‑place reversal
3. Recursive reversal
------------------------------------------------------------
*/

public class ReverseLinkedList {

    // Node class for linked list
    static class Node {
        int data;
        Node next;

        Node(int data) {
            this.data = data;
            this.next = null;
        }

        Node(int data, Node next) {
            this.data = data;
            this.next = next;
        }
    }

    /*
    ------------------------------------------------------------
    Brute Force Approach (using a Stack)
    ------------------------------------------------------------
    Intuition:
    - Push all values to a stack
    - Pop and overwrite the list nodes
    - Reverses data not links
    ------------------------------------------------------------
    */
    static Node reverseBrute(Node head) {
        if (head == null) return head;

        Stack<Integer> st = new Stack<>();
        Node temp = head;

        // Push all node values into the stack
        while (temp != null) {
            st.push(temp.data);
            temp = temp.next;
        }

        // Rewrite the list with reversed values
        temp = head;
        while (temp != null) {
            temp.data = st.pop();
            temp = temp.next;
        }
        return head;
    }

    /*
    ------------------------------------------------------------
    Iterative In‑Place Reversal
    ------------------------------------------------------------
    Intuition:
    - Adjust the next pointers one by one
    - Uses three pointers: prev, curr, next
    ------------------------------------------------------------
    */
    static Node reverseIterative(Node head) {
        Node prev = null;
        Node curr = head;

        while (curr != null) {
            Node next = curr.next; // temporarily store next
            curr.next = prev;      // reverse link
            prev = curr;           // advance prev
            curr = next;           // advance curr
        }
        return prev; // new head
    }

    /*
    ------------------------------------------------------------
    Recursive Reversal
    ------------------------------------------------------------
    Intuition:
    - Recursively reverse the list from head.next
    - Then make head.next.next point to head
    - Finally make head.next = null
    ------------------------------------------------------------
    */
    static Node reverseRecursive(Node head) {
        if (head == null || head.next == null) return head;

        Node newHead = reverseRecursive(head.next);
        head.next.next = head;
        head.next = null;
        return newHead;
    }

    // Utility to print list
    static void printList(Node head) {
        while (head != null) {
            System.out.print(head.data + " ");
            head = head.next;
        }
        System.out.println();
    }

    // Main — testing all three approaches
    public static void main(String[] args) {
        // Create sample list: 1 -> 2 -> 3 -> 4 -> 5
        Node head = new Node(1, new Node(2, new Node(3, new Node(4, new Node(5)))));

        System.out.print("Original list: ");
        printList(head);

        // Reverse by stack
        head = reverseBrute(head);
        System.out.print("Reversed (Stack):   ");
        printList(head);

        // Reverse again (iterative)
        head = reverseIterative(head);
        System.out.print("Reversed (Iterative): ");
        printList(head);

        // Reverse again (recursive)
        head = reverseRecursive(head);
        System.out.print("Reversed (Recursive): ");
        printList(head);
    }
}

/*
------------------------------------------------------------
Time & Space Complexity:
------------------------------------------------------------

1. Brute Force (Stack):
   - Time Complexity: O(N)
   - Space Complexity: O(N)  // stack stores N values

2. Iterative In‑Place:
   - Time Complexity: O(N)
   - Space Complexity: O(1)

3. Recursive:
   - Time Complexity: O(N)
   - Space Complexity: O(N) due to recursion stack
------------------------------------------------------------
*/

