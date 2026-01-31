package Linkedlist;

import java.util.HashMap;

/*
PROBLEM:
---------
Given a linked list where each node has:
1) next pointer
2) random pointer (can point to any node or null)

Create a DEEP COPY of the linked list.
*/

class Node {
    int val;
    Node next;
    Node random;

    Node(int val) {
        this.val = val;
        this.next = null;
        this.random = null;
    }

    Node(int val, Node next, Node random) {
        this.val = val;
        this.next = next;
        this.random = random;
    }
}

public class CopyLinkedListWithRandomPointer {

    /*
    ===========================
    BRUTE FORCE APPROACH
    ===========================
    INTUITION:
    -----------
    1. Create a copy of every node and store mapping:
       original node → copied node
    2. Traverse again and assign next & random pointers using the map

    TIME COMPLEXITY:  O(n)
    SPACE COMPLEXITY: O(n)
    */
    static Node copyLLBrute(Node head) {
        if (head == null) return null;

        HashMap<Node, Node> map = new HashMap<>();
        Node temp = head;

        // Step 1: Create copy of each node
        while (temp != null) {
            map.put(temp, new Node(temp.val));
            temp = temp.next;
        }

        // Step 2: Assign next and random pointers
        temp = head;
        while (temp != null) {
            Node copyNode = map.get(temp);
            copyNode.next = map.get(temp.next);       // safe for null
            copyNode.random = map.get(temp.random);   // safe for null
            temp = temp.next;
        }

        return map.get(head);
    }

    /*
    ===========================
    OPTIMIZED APPROACH (O(1) SPACE)
    ===========================
    INTUITION:
    -----------
    1. Insert copied nodes after original nodes
    2. Assign random pointers using original->random->next
    3. Separate original and copied lists

    TIME COMPLEXITY:  O(n)
    SPACE COMPLEXITY: O(1)
    */
    static Node copyLL(Node head) {
        if (head == null) return null;

        Node temp = head;

        // Step 1: Insert copy nodes in between
        while (temp != null) {
            Node copyNode = new Node(temp.val);
            copyNode.next = temp.next;
            temp.next = copyNode;
            temp = copyNode.next;
        }

        // Step 2: Assign random pointers
        temp = head;
        while (temp != null) {
            if (temp.random != null)
                temp.next.random = temp.random.next;
            temp = temp.next.next;
        }

        // Step 3: Separate the two lists
        temp = head;
        Node copyHead = head.next;

        while (temp != null) {
            Node copyNode = temp.next;
            temp.next = copyNode.next; // restore original list

            if (copyNode.next != null)
                copyNode.next = copyNode.next.next;

            temp = temp.next;
        }

        return copyHead;
    }

    /*
    UTILITY FUNCTION:
    -----------------
    Prints node value and random pointer value
    */
    static void printLL(Node head) {
        while (head != null) {
            System.out.print(head.val + " -> ");
            if (head.random != null)
                System.out.println(head.random.val);
            else
                System.out.println("NULL");
            head = head.next;
        }
    }

    /*
    DRIVER CODE
    -----------
    Creates:
    1 -> 2 -> 3

    Random pointers:
    1 -> 3
    2 -> 1
    3 -> 2
    */
    public static void main(String[] args) {
        Node head = new Node(1);
        head.next = new Node(2);
        head.next.next = new Node(3);

        head.random = head.next.next;       // 1 -> 3
        head.next.random = head;            // 2 -> 1
        head.next.next.random = head.next;  // 3 -> 2

        System.out.println("Original list:");
        printLL(head);

        Node copied = copyLL(head);

        System.out.println("\nCopied list:");
        printLL(copied);
    }
}

