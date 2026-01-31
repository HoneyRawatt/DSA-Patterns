package Linkedlist;
import java.util.HashMap;

/*
====================================================
Problem Statement:
----------------------------------------------------
Given the head of a singly linked list, determine
whether the linked list contains a loop (cycle).

A loop exists if some node in the list can be
revisited by continuously following the next
pointer.

Return:
- true  → if a loop is present
- false → if no loop is present
====================================================
*/

public class DetectLoopInLinkedList {

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
    Approach 1: Brute Force using HashMap
    ----------------------------------------------------
    Intuition:
    - Traverse the linked list.
    - Store each visited node reference in a HashMap.
    - If a node is visited again, a loop exists.

    Why it works:
    - In a cyclic list, the same node is revisited.
    - HashMap provides O(1) average lookup time.

    Time Complexity:  O(n)
    Space Complexity: O(n)
    ====================================================
    */
    static boolean detectLoopBrute(Node head) {
        HashMap<Node, Integer> map = new HashMap<>();
        Node temp = head;

        while (temp != null) {
            if (map.containsKey(temp)) {
                return true; // loop found
            }
            map.put(temp, 1); // mark node as visited
            temp = temp.next;
        }

        return false; // no loop
    }

    /*
    ====================================================
    Approach 2: Optimal – Floyd’s Cycle Detection
    ----------------------------------------------------
    (Slow & Fast Pointer Method)

    Intuition:
    - Use two pointers:
      - slow moves one step
      - fast moves two steps
    - If a loop exists, fast will eventually
      meet slow inside the loop.

    Why it works:
    - Fast pointer laps slow pointer in a cycle.
    - If no loop exists, fast reaches null.

    Time Complexity:  O(n)
    Space Complexity: O(1)
    ====================================================
    */
    static boolean detectLoop(Node head) {
        Node slow = head;
        Node fast = head;

        while (fast != null && fast.next != null) {
            slow = slow.next;          // move 1 step
            fast = fast.next.next;    // move 2 steps

            if (slow == fast)
                return true;           // loop detected
        }

        return false; // no loop
    }

    /*
    ====================================================
    Main Function (Testing)
    ====================================================
    */
    public static void main(String[] args) {
        Node head = new Node(1);
        head.next = new Node(2);
        head.next.next = new Node(3);
        head.next.next.next = new Node(4);

        // Creating a loop: last node points to second node
        head.next.next.next.next = head.next;

        System.out.println("Brute: " +
                (detectLoopBrute(head) ? "Loop found" : "No loop"));

        System.out.println("Optimal: " +
                (detectLoop(head) ? "Loop found" : "No loop"));
    }
}
