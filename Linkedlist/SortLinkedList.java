package Linkedlist;

import java.util.*;

/*
=========================================================
PROBLEM STATEMENT
=========================================================
You are given the head of a singly linked list.
Your task is to sort the linked list in ascending order
and return the head of the sorted list.

This problem is commonly asked in interviews and appears as:
- LeetCode: Sort List
- GeeksforGeeks: Sort a linked list
=========================================================
*/

// Definition of linked list node
class Node {
    int val;
    Node next;
    Node child; // not used here, kept for consistency

    Node(int val) {
        this.val = val;
        this.next = null;
        this.child = null;
    }

    Node(int val, Node next, Node child) {
        this.val = val;
        this.next = next;
        this.child = child;
    }
}

public class SortLinkedList {

    /*
    =========================================================
    APPROACH 1: BRUTE FORCE (USING ARRAY)
    =========================================================
    INTUITION:
    - Traverse the linked list and store all values in an array
    - Sort the array
    - Traverse the linked list again and overwrite values
      with sorted values

    TIME COMPLEXITY:
    - O(N log N)

    SPACE COMPLEXITY:
    - O(N)
    =========================================================
    */
    static Node sortLLBrute(Node head) {
        List<Integer> arr = new ArrayList<>();
        Node temp = head;

        // Store values in array
        while (temp != null) {
            arr.add(temp.val);
            temp = temp.next;
        }

        // Sort array
        Collections.sort(arr);

        // Copy sorted values back to linked list
        temp = head;
        int i = 0;
        while (temp != null) {
            temp.val = arr.get(i++);
            temp = temp.next;
        }

        return head;
    }

    /*
    ---------------------------------------------------------
    Helper Function:
    Merge two sorted linked lists
    ---------------------------------------------------------
    */
    static Node merge(Node head1, Node head2) {
        Node t1 = head1;
        Node t2 = head2;

        Node dummy = new Node(-1);
        Node temp = dummy;

        while (t1 != null && t2 != null) {
            if (t1.val < t2.val) {
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

        return dummy.next;
    }

    /*
    ---------------------------------------------------------
    Helper Function:
    Find middle of linked list
    (Slow & fast pointer technique)
    ---------------------------------------------------------
    */
    static Node findMiddle(Node head) {
        Node slow = head;
        Node fast = head;

        while (fast.next != null && fast.next.next != null) {
            slow = slow.next;
            fast = fast.next.next;
        }

        return slow;
    }

    /*
    =========================================================
    APPROACH 2: OPTIMAL (MERGE SORT ON LINKED LIST)
    =========================================================
    INTUITION:
    - Merge sort is best suited for linked lists
    - No random access needed
    - Splitting and merging can be done with pointers

    STEPS:
    1. Find the middle of the list
    2. Split the list into two halves
    3. Recursively sort both halves
    4. Merge the sorted halves

    TIME COMPLEXITY:
    - O(N log N)

    SPACE COMPLEXITY:
    - O(log N) due to recursion stack
    =========================================================
    */
    static Node mergeSort(Node head) {
        // Base case
        if (head == null || head.next == null)
            return head;

        // Find middle and split list
        Node middle = findMiddle(head);
        Node rightHead = middle.next;
        middle.next = null;

        // Recursively sort both halves
        Node leftSorted = mergeSort(head);
        Node rightSorted = mergeSort(rightHead);

        // Merge sorted halves
        return merge(leftSorted, rightSorted);
    }

    /*
    ---------------------------------------------------------
    Utility Function:
    Print linked list
    ---------------------------------------------------------
    */
    static void printLL(Node head) {
        while (head != null) {
            System.out.print(head.val + " ");
            head = head.next;
        }
        System.out.println();
    }

    /*
    ---------------------------------------------------------
    Main Function (Test Case)
    ---------------------------------------------------------
    */
    public static void main(String[] args) {

        // Create unsorted linked list: 4 -> 2 -> 1 -> 3
        Node head = new Node(4);
        head.next = new Node(2);
        head.next.next = new Node(1);
        head.next.next.next = new Node(3);

        System.out.print("Original list: ");
        printLL(head);

        // Sort linked list using merge sort
        head = mergeSort(head);

        System.out.print("Sorted list: ");
        printLL(head);
    }
}

