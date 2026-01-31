package Linkedlist;

import java.util.*;

/*
PROBLEM STATEMENT:
You are given two sorted singly linked lists.
Your task is to merge both linked lists into a single sorted linked list
and return the head of the merged list.

Both input linked lists are already sorted in ascending order.
*/
// Definition of singly linked list node
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

public class MergeSortedLinkedLists {

    /*
     * Helper function:
     * Inserts a new node with value 'val' at the end of the linked list
     */
    static Node insertEnd(Node head, int val) {
        if (head == null) return new Node(val);

        Node temp = head;
        while (temp.next != null) {
            temp = temp.next;
        }
        temp.next = new Node(val);
        return head;
    }

    /*
     * Helper function:
     * Prints the linked list
     */
    static void printList(Node head) {
        while (head != null) {
            System.out.print(head.data + " ");
            head = head.next;
        }
        System.out.println();
    }

    /*
     * Helper function:
     * Converts an array/list into a linked list
     */
    static Node convertArrToList(List<Integer> arr) {
        if (arr.isEmpty()) return null;

        Node head = new Node(arr.get(0));
        Node temp = head;

        for (int i = 1; i < arr.size(); i++) {
            temp.next = new Node(arr.get(i));
            temp = temp.next;
        }
        return head;
    }

    // ---------------------------------------------------------
    // 🔴 BRUTE FORCE APPROACH
    // ---------------------------------------------------------
    /*
     * Approach:
     * 1. Traverse both linked lists and store elements in an array
     * 2. Sort the array
     * 3. Convert the sorted array back to a linked list
     *
     * Time Complexity: O((N + M) log(N + M))
     * Space Complexity: O(N + M)
     */
    static Node mergeTwoSortedLLBrute(Node head1, Node head2) {
        List<Integer> arr = new ArrayList<>();

        // Add elements of first list
        Node t1 = head1;
        while (t1 != null) {
            arr.add(t1.data);
            t1 = t1.next;
        }

        // Add elements of second list
        Node t2 = head2;
        while (t2 != null) {
            arr.add(t2.data);
            t2 = t2.next;
        }

        // Sort combined elements
        Collections.sort(arr);

        // Convert sorted array to linked list
        return convertArrToList(arr);
    }

    // ---------------------------------------------------------
    // 🟢 OPTIMAL APPROACH (Two Pointer Technique)
    // ---------------------------------------------------------
    /*
     * Intuition:
     * Since both lists are sorted, compare nodes one by one
     * and attach the smaller node to the merged list.
     *
     * Steps:
     * 1. Use two pointers for both lists
     * 2. Attach smaller node to result list
     * 3. Move pointer forward
     * 4. Attach remaining nodes if any
     *
     * Time Complexity: O(N + M)
     * Space Complexity: O(1)
     */
    static Node mergeTwoSortedLL(Node head1, Node head2) {

        Node t1 = head1;
        Node t2 = head2;

        // Dummy node to simplify edge cases
        Node dummy = new Node(-1);
        Node temp = dummy;

        // Merge while both lists have nodes
        while (t1 != null && t2 != null) {
            if (t1.data < t2.data) {
                temp.next = t1;
                t1 = t1.next;
            } else {
                temp.next = t2;
                t2 = t2.next;
            }
            temp = temp.next;
        }

        // Attach remaining nodes
        if (t1 != null) temp.next = t1;
        else temp.next = t2;

        // Return head of merged list
        return dummy.next;
    }

    // ---------------------------------------------------------
    // Driver Code
    // ---------------------------------------------------------
    public static void main(String[] args) {

        Node head1 = null;
        Node head2 = null;

        // List 1: 1 -> 3 -> 5
        head1 = insertEnd(head1, 1);
        head1 = insertEnd(head1, 3);
        head1 = insertEnd(head1, 5);

        // List 2: 2 -> 4 -> 6
        head2 = insertEnd(head2, 2);
        head2 = insertEnd(head2, 4);
        head2 = insertEnd(head2, 6);

        System.out.print("List 1: ");
        printList(head1);

        System.out.print("List 2: ");
        printList(head2);

        // Brute force merge
        Node mergedBrute = mergeTwoSortedLLBrute(head1, head2);
        System.out.print("Merged List (Brute Force): ");
        printList(mergedBrute);

        // Optimal merge
        Node mergedOptimal = mergeTwoSortedLL(head1, head2);
        System.out.print("Merged List (Optimal): ");
        printList(mergedOptimal);
    }
}

