package Linkedlist;

import java.util.HashSet;

/*
====================================================
Problem Statement:
----------------------------------------------------
Given the heads of two singly linked lists, determine
the node at which the two linked lists intersect.

If the two linked lists have no intersection,
return null.

NOTE:
- Intersection is based on reference (memory address),
  not on node value.
- After intersection point, both linked lists share
  the same nodes.
====================================================
*/

public class IntersectionOfLinkedLists {

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
    Approach 1: Brute Force using HashSet
    ----------------------------------------------------
    Intuition:
    - Store all nodes of the first linked list in a HashSet.
    - Traverse the second linked list.
    - The first node found in the HashSet is the intersection.

    Why it works:
    - HashSet allows O(1) lookup.
    - Intersection is detected by comparing references.

    Time Complexity:  O(n + m)
    Space Complexity: O(n)
    ====================================================
    */
    static Node intersectionPointBrute(Node head1, Node head2) {
        HashSet<Node> set = new HashSet<>();
        Node temp = head1;

        // Store nodes of first list
        while (temp != null) {
            set.add(temp);
            temp = temp.next;
        }

        // Check nodes of second list
        temp = head2;
        while (temp != null) {
            if (set.contains(temp))
                return temp; // intersection found
            temp = temp.next;
        }

        return null; // no intersection
    }

    /*
    ====================================================
    Helper Function (for Better Approach)
    ----------------------------------------------------
    Purpose:
    - Moves the longer list ahead by 'd' nodes
      to align both lists at equal distance from end.
    ====================================================
    */
    static Node collisionPoint(Node t1, Node t2, int d) {

        // Move t2 ahead by d nodes
        while (d-- > 0) {
            if (t2 == null) return null;
            t2 = t2.next;
        }

        // Traverse both lists together
        while (t1 != null && t2 != null && t1 != t2) {
            t1 = t1.next;
            t2 = t2.next;
        }

        return t1; // intersection node or null
    }

    /*
    ====================================================
    Approach 2: Length Difference Method
    ----------------------------------------------------
    Intuition:
    - Find lengths of both linked lists.
    - Move pointer of longer list ahead by the
      difference in lengths.
    - Traverse both lists together until nodes match.

    Time Complexity:  O(n + m)
    Space Complexity: O(1)
    ====================================================
    */
    static Node intersectionPointBetter(Node head1, Node head2) {
        Node t1 = head1, t2 = head2;
        int n1 = 0, n2 = 0;

        // Calculate length of first list
        while (t1 != null) {
            n1++;
            t1 = t1.next;
        }

        // Calculate length of second list
        while (t2 != null) {
            n2++;
            t2 = t2.next;
        }

        // Align both lists
        if (n1 < n2)
            return collisionPoint(head1, head2, n2 - n1);
        else
            return collisionPoint(head2, head1, n1 - n2);
    }

    /*
    ====================================================
    Approach 3: Optimal Two Pointer Method
    ----------------------------------------------------
    Intuition:
    - Traverse both lists using two pointers.
    - When a pointer reaches the end, redirect it to
      the head of the other list.
    - If an intersection exists, both pointers will
      meet at the intersection node.

    Why it works:
    - Both pointers travel exactly (n + m) distance.
    - Automatically balances length difference.

    Time Complexity:  O(n + m)
    Space Complexity: O(1)
    ====================================================
    */
    static Node intersectionPoint(Node head1, Node head2) {
        if (head1 == null || head2 == null) return null;

        Node t1 = head1, t2 = head2;

        while (t1 != t2) {
            t1 = (t1 == null) ? head2 : t1.next;
            t2 = (t2 == null) ? head1 : t2.next;
        }

        return t1; // intersection node or null
    }
}
