package Linkedlist;

import java.util.ArrayList;

/*
====================================
Singly Linked List Node
====================================
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

public class OddEvenLinkedList {

    /*
    ====================================
    Brute Force Approach
    ====================================
    Intuition:
    - Store odd-position nodes first
    - Then store even-position nodes
    - Rewrite the linked list using stored values

    Time Complexity: O(n)
    Space Complexity: O(n)
    */
    static Node oddEvenLLBrute(Node head) {
        if (head == null || head.next == null) return head;

        ArrayList<Integer> arr = new ArrayList<>();
        Node temp = head;
        int pos = 1;

        // Collect odd position nodes
        while (temp != null) {
            if (pos % 2 != 0) arr.add(temp.data);
            temp = temp.next;
            pos++;
        }

        // Collect even position nodes
        temp = head;
        pos = 1;
        while (temp != null) {
            if (pos % 2 == 0) arr.add(temp.data);
            temp = temp.next;
            pos++;
        }

        // Rewrite linked list
        temp = head;
        int i = 0;
        while (temp != null) {
            temp.data = arr.get(i++);
            temp = temp.next;
        }

        return head;
    }

    /*
    ====================================
    Optimized Approach (Pointer Rearrangement)
    ====================================
    Intuition:
    - Separate odd and even nodes using pointers
    - Connect odd list with even list at the end

    Time Complexity: O(n)
    Space Complexity: O(1)
    */
    static Node oddEvenLLOptimized(Node head) {
        if (head == null || head.next == null) return head;

        Node odd = head;
        Node even = head.next;
        Node evenHead = even;

        while (even != null && even.next != null) {
            odd.next = even.next;
            odd = odd.next;

            even.next = odd.next;
            even = even.next;
        }

        odd.next = evenHead; // attach even list
        return head;
    }

    /*
    ====================================
    Insert at End (Helper)
    ====================================
    */
    static Node insert(Node head, int val) {
        if (head == null) {
            return new Node(val);
        }

        Node temp = head;
        while (temp.next != null) temp = temp.next;
        temp.next = new Node(val);
        return head;
    }

    /*
    ====================================
    Print Linked List (Helper)
    ====================================
    */
    static void printList(Node head) {
        while (head != null) {
            System.out.print(head.data);
            if (head.next != null) System.out.print(" -> ");
            head = head.next;
        }
        System.out.println();
    }

    /*
    ====================================
    Main Function
    ====================================
    */
    public static void main(String[] args) {

        Node head = null;
        head = insert(head, 1);
        head = insert(head, 2);
        head = insert(head, 3);
        head = insert(head, 4);
        head = insert(head, 5);

        System.out.print("Original: ");
        printList(head);

        Node res1 = oddEvenLLBrute(head);
        System.out.print("Brute Result: ");
        printList(res1);

        // rebuild list for optimized test
        Node head2 = null;
        head2 = insert(head2, 1);
        head2 = insert(head2, 2);
        head2 = insert(head2, 3);
        head2 = insert(head2, 4);
        head2 = insert(head2, 5);

        Node res2 = oddEvenLLOptimized(head2);
        System.out.print("Optimized Result: ");
        printList(res2);
    }
}

