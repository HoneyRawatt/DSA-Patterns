package Linkedlist;

import java.util.HashMap;

/*
====================================================
Problem Statement:
----------------------------------------------------
Given a singly linked list that may contain a loop,
find the length of the loop.

If no loop exists, return 0.
====================================================
*/

public class LengthOfLoopInLinkedList {

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
    - Store each visited node with a timestamp.
    - If a node is visited again, a loop exists.
    - Loop length = current_time - first_visit_time.

    Time Complexity:  O(n)
    Space Complexity: O(n)
    ====================================================
    */
    static int lengthLoopBrute(Node head) {
        HashMap<Node, Integer> map = new HashMap<>();
        Node temp = head;
        int timer = 1;

        while (temp != null) {
            if (map.containsKey(temp)) {
                int value = map.get(temp);
                return timer - value; // loop length
            }

            map.put(temp, timer);
            timer++;
            temp = temp.next;
        }

        return 0; // no loop
    }

    /*
    ====================================================
    Helper Function (for Floyd’s Algorithm)
    ----------------------------------------------------
    Purpose:
    - Counts the number of nodes in the loop once
      slow and fast pointers meet.
    ====================================================
    */
    static int findLength(Node slow, Node fast) {
        int cnt = 1;
        fast = fast.next;

        while (fast != slow) {
            cnt++;
            fast = fast.next;
        }

        return cnt;
    }

    /*
    ====================================================
    Approach 2: Optimal – Floyd’s Cycle Detection
    ----------------------------------------------------
    Intuition:
    - Detect loop using slow & fast pointers.
    - Once they meet, traverse the loop to count length.

    Time Complexity:  O(n)
    Space Complexity: O(1)
    ====================================================
    */
    static int lengthLoop(Node head) {
        Node slow = head;
        Node fast = head;

        while (fast != null && fast.next != null) {
            slow = slow.next;          // move 1 step
            fast = fast.next.next;    // move 2 steps

            if (slow == fast) {
                return findLength(slow, fast);
            }
        }

        return 0; // no loop
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

        // Creating a loop: 2 → 3 → 4 → 2
        head.next.next.next.next = head.next;

        System.out.println("Brute force loop length: " +
                lengthLoopBrute(head));

        System.out.println("Floyd loop length: " +
                lengthLoop(head));
    }
}
