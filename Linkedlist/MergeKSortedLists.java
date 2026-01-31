package Linkedlist;

import java.util.*;

/*
=========================================
PROBLEM STATEMENT
=========================================
You are given K sorted singly linked lists.
Each linked list is sorted in ascending order.

Your task is to merge all these K sorted
linked lists into one single sorted
linked list and return its head.
=========================================
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

public class MergeKSortedLists {

    /*
    -------------------------------------------------
    Helper Function:
    Convert a sorted array into a linked list
    -------------------------------------------------
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

    /*
    =================================================
    APPROACH 1: BRUTE FORCE
    =================================================
    INTUITION:
    - Traverse all K linked lists
    - Store every element into a single array
    - Sort the array
    - Convert the sorted array back into a linked list

    TIME COMPLEXITY:
    - Total nodes = N
    - Sorting: O(N log N)

    SPACE COMPLEXITY:
    - Extra array of size N
    => O(N)
    =================================================
    */
    static Node mergeKSortedLLBrute(List<Node> lists) {
        List<Integer> arr = new ArrayList<>();

        for (Node head : lists) {
            while (head != null) {
                arr.add(head.data);
                head = head.next;
            }
        }

        Collections.sort(arr);
        return convertArrToList(arr);
    }

    /*
    -------------------------------------------------
    Helper:
    Merge two sorted linked lists
    -------------------------------------------------
    */
    static Node mergeTwoSortedLL(Node head1, Node head2) {
        Node dummy = new Node(-1);
        Node temp = dummy;

        while (head1 != null && head2 != null) {
            if (head1.data < head2.data) {
                temp.next = head1;
                head1 = head1.next;
            } else {
                temp.next = head2;
                head2 = head2.next;
            }
            temp = temp.next;
        }

        if (head1 != null) temp.next = head1;
        else temp.next = head2;

        return dummy.next;
    }

    /*
    =================================================
    APPROACH 2: BETTER (ITERATIVE MERGING)
    =================================================
    INTUITION:
    - Merge lists one by one
    - Similar to repeated merge sort merge step

    TIME COMPLEXITY:
    - O(N * K)

    SPACE COMPLEXITY:
    - O(1) auxiliary
    =================================================
    */
    static Node mergeKSortedLLBetter(List<Node> lists) {
        if (lists.isEmpty()) return null;

        Node head = lists.get(0);
        for (int i = 1; i < lists.size(); i++) {
            head = mergeTwoSortedLL(head, lists.get(i));
        }
        return head;
    }

    /*
    =================================================
    APPROACH 3: OPTIMAL (MIN HEAP)
    =================================================
    INTUITION:
    - Use a min heap to always extract the smallest
      node among K lists
    - Push next node of extracted list into heap

    TIME COMPLEXITY:
    - O(N log K)

    SPACE COMPLEXITY:
    - O(K)
    =================================================
    */
    static Node mergeKSortedLLOptimal(List<Node> lists) {
        PriorityQueue<Node> pq = new PriorityQueue<>(
            (a, b) -> a.data - b.data
        );

        // Push head of each list
        for (Node head : lists) {
            if (head != null) pq.add(head);
        }

        Node dummy = new Node(-1);
        Node temp = dummy;

        while (!pq.isEmpty()) {
            Node curr = pq.poll();
            temp.next = curr;
            temp = temp.next;

            if (curr.next != null) {
                pq.add(curr.next);
            }
        }

        return dummy.next;
    }

    /*
    -------------------------------------------------
    Helper: Print linked list
    -------------------------------------------------
    */
    static void printList(Node head) {
        while (head != null) {
            System.out.print(head.data + " ");
            head = head.next;
        }
        System.out.println();
    }

    /*
    -------------------------------------------------
    Helper: Insert node at the end
    -------------------------------------------------
    */
    static Node insertEnd(Node head, int val) {
        if (head == null) return new Node(val);

        Node temp = head;
        while (temp.next != null) temp = temp.next;
        temp.next = new Node(val);

        return head;
    }

    public static void main(String[] args) {
        List<Node> lists = new ArrayList<>();

        // List 1: 1 -> 4 -> 7
        Node l1 = null;
        l1 = insertEnd(l1, 1);
        l1 = insertEnd(l1, 4);
        l1 = insertEnd(l1, 7);

        // List 2: 2 -> 5 -> 8
        Node l2 = null;
        l2 = insertEnd(l2, 2);
        l2 = insertEnd(l2, 5);
        l2 = insertEnd(l2, 8);

        // List 3: 3 -> 6 -> 9
        Node l3 = null;
        l3 = insertEnd(l3, 3);
        l3 = insertEnd(l3, 6);
        l3 = insertEnd(l3, 9);

        lists.add(l1);
        lists.add(l2);
        lists.add(l3);

        System.out.print("Brute Force Merge: ");
        printList(mergeKSortedLLBrute(lists));

        System.out.print("Better Merge: ");
        printList(mergeKSortedLLBetter(lists));

        System.out.print("Optimal Merge (Heap): ");
        printList(mergeKSortedLLOptimal(lists));
    }
}
