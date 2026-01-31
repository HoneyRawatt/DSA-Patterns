package Linkedlist;

import java.util.*;

/*
=========================================================
PROBLEM STATEMENT
=========================================================
You are given a multilevel linked list where:
- Each node has two pointers:
    1. next  -> points to the next node in the main list
    2. child -> points to a sorted linked list

Each individual list (both main list and child lists)
is already sorted.

Your task is to FLATTEN the multilevel linked list
into a single sorted linked list using ONLY the
child pointers.

The final flattened list should be sorted.
=========================================================
*/

// Node definition for multilevel linked list
class Node {
    int val;
    Node next;
    Node child;

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

public class FlattenMultilevelLinkedList {

    /*
    ---------------------------------------------------------
    Helper Function:
    Convert array to linked list using ONLY child pointers
    ---------------------------------------------------------
    */
    static Node convertArrToLL(List<Integer> arr) {
        if (arr.isEmpty()) return null;

        Node head = new Node(arr.get(0));
        Node temp = head;

        for (int i = 1; i < arr.size(); i++) {
            Node newNode = new Node(arr.get(i));
            temp.child = newNode;
            temp = temp.child;
        }
        return head;
    }

    /*
    =========================================================
    APPROACH 1: BRUTE FORCE
    =========================================================
    INTUITION:
    - Traverse the entire multilevel linked list
    - Store all node values into an array
    - Sort the array
    - Convert the sorted array back into a linked list

    TIME COMPLEXITY:
    - O(N log N)

    SPACE COMPLEXITY:
    - O(N)
    =========================================================
    */
    static Node flattenBrute(Node head) {
        List<Integer> arr = new ArrayList<>();

        Node temp = head;
        while (temp != null) {
            Node t2 = temp;
            while (t2 != null) {
                arr.add(t2.val);
                t2 = t2.child;
            }
            temp = temp.next;
        }

        Collections.sort(arr);
        return convertArrToLL(arr);
    }

    /*
    ---------------------------------------------------------
    Helper Function:
    Merge two sorted linked lists using child pointers
    ---------------------------------------------------------
    */
    static Node merge2LL(Node list1, Node list2) {
        Node dummy = new Node(-1);
        Node res = dummy;

        while (list1 != null && list2 != null) {
            if (list1.val < list2.val) {
                res.child = list1;
                res = list1;
                list1 = list1.child;
            } else {
                res.child = list2;
                res = list2;
                list2 = list2.child;
            }
            // next pointer is irrelevant in flattened list
            res.next = null;
        }

        if (list1 != null) res.child = list1;
        else res.child = list2;

        return dummy.child;
    }

    /*
    =========================================================
    APPROACH 2: OPTIMAL (RECURSION + MERGE)
    =========================================================
    INTUITION:
    - Recursively flatten the list on the right (next)
    - Merge current list with the already flattened list
    - Similar to merging K sorted linked lists

    TIME COMPLEXITY:
    - O(N)

    SPACE COMPLEXITY:
    - O(depth of recursion)
    =========================================================
    */
    static Node flatten(Node head) {
        // Base case
        if (head == null || head.next == null)
            return head;

        // Flatten the rest of the list
        Node mergedHead = flatten(head.next);

        // Merge current list with flattened list
        return merge2LL(head, mergedHead);
    }

    /*
    ---------------------------------------------------------
    Helper:
    Print flattened linked list using child pointers
    ---------------------------------------------------------
    */
    static void printLL(Node head) {
        while (head != null) {
            System.out.print(head.val + " ");
            head = head.child;
        }
        System.out.println();
    }

    public static void main(String[] args) {

        /*
        Constructing the multilevel linked list:

        Main list:
        5 -> 10 -> 19 -> 28

        Child lists:
        5  -> 7 -> 8 -> 30
        10 -> 20
        19 -> 22 -> 50
        28 -> 35 -> 40 -> 45
        */

        Node head = new Node(5);
        head.next = new Node(10);
        head.next.next = new Node(19);
        head.next.next.next = new Node(28);

        head.child = new Node(7);
        head.child.child = new Node(8);
        head.child.child.child = new Node(30);

        head.next.child = new Node(20);

        head.next.next.child = new Node(22);
        head.next.next.child.child = new Node(50);

        head.next.next.next.child = new Node(35);
        head.next.next.next.child.child = new Node(40);
        head.next.next.next.child.child.child = new Node(45);

        System.out.println("Flattened Linked List (Optimal):");
        Node flatHead = flatten(head);
        printLL(flatHead);
    }
}
