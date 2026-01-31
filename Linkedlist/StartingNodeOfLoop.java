import java.util.HashMap;

/*
====================================================
Problem Statement:
----------------------------------------------------
Given a linked list, determine if it contains a loop.
If a loop exists, return the node where the loop
starts. Otherwise, return null.
====================================================
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

public class StartingNodeOfLoop {

    /*
    ====================================================
    Brute Force Approach (Using HashMap)
    ----------------------------------------------------
    Intuition:
    - Traverse the list and store each visited node.
    - If a node is encountered again, it is the start
      of the loop.

    Time Complexity: O(n)
    Space Complexity: O(n)
    ====================================================
    */
    static Node startingNodeLoopBrute(Node head) {
        HashMap<Node, Integer> map = new HashMap<>();
        Node temp = head;

        while (temp != null) {
            if (map.containsKey(temp))
                return temp;   // loop starting node
            map.put(temp, 1);
            temp = temp.next;
        }
        return null; // no loop
    }

    /*
    ====================================================
    Optimized Approach (Floyd’s Cycle Detection)
    ----------------------------------------------------
    Intuition:
    1. Use slow and fast pointers to detect loop.
    2. Once they meet, reset slow to head.
    3. Move both pointers one step at a time.
    4. The point where they meet again is the
       starting node of the loop.

    Time Complexity: O(n)
    Space Complexity: O(1)
    ====================================================
    */
    static Node startingNodeLoop(Node head) {
        Node slow = head;
        Node fast = head;

        while (fast != null && fast.next != null) {
            slow = slow.next;
            fast = fast.next.next;

            if (slow == fast) {   // loop detected
                slow = head;
                while (slow != fast) {
                    slow = slow.next;
                    fast = fast.next;
                }
                return slow; // start of loop
            }
        }
        return null; // no loop
    }

    // ---------------- Main ----------------
    public static void main(String[] args) {

        // Create linked list: 1 -> 2 -> 3 -> 4 -> 5
        Node head = new Node(1);
        head.next = new Node(2);
        head.next.next = new Node(3);
        head.next.next.next = new Node(4);
        head.next.next.next.next = new Node(5);

        // Create loop: 5 -> 3
        head.next.next.next.next.next = head.next.next;

        Node brute = startingNodeLoopBrute(head);
        if (brute != null)
            System.out.println("Brute: Loop starts at node " + brute.data);
        else
            System.out.println("Brute: No loop found");

        Node optimal = startingNodeLoop(head);
        if (optimal != null)
            System.out.println("Optimized: Loop starts at node " + optimal.data);
        else
            System.out.println("Optimized: No loop found");
    }
}
