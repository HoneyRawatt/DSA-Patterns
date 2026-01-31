package Linkedlist.DoublyLL;
/*
====================================================
PROBLEM STATEMENT:
----------------------------------------------------
Given the head of a Doubly Linked List and an integer
key, delete ALL nodes from the list whose data is
equal to the given key.

You must correctly update:
- prev pointers
- next pointers
- head reference (if the head node itself is deleted)

Return the new head of the modified list.
====================================================
*/

class Node {
    int data;
    Node prev;
    Node next;

    // Constructor
    Node(int val) {
        this.data = val;
        this.prev = null;
        this.next = null;
    }
}

public class DeleteAllOccurrencesInDLL {

    /*
    ====================================================
    INTUITION:
    ----------------------------------------------------
    1. Traverse the doubly linked list using a pointer.
    2. If the current node's data matches the key:
       - Store references to its previous and next nodes.
       - Re-link prev.next and next.prev to bypass
         the current node.
       - If the current node is the head, update head.
    3. Move forward safely using the stored next node.
    4. Return the updated head.
    ====================================================
    */

    public static Node deleteAllOccurrences(Node head, int key) {
        Node temp = head;

        // Traverse the entire list
        while (temp != null) {

            // If key is found
            if (temp.data == key) {

                Node nextNode = temp.next;
                Node prevNode = temp.prev;

                // Update previous node's next
                if (prevNode != null) {
                    prevNode.next = nextNode;
                }

                // Update next node's prev
                if (nextNode != null) {
                    nextNode.prev = prevNode;
                }

                // If head node is deleted, update head
                if (temp == head) {
                    head = nextNode;
                }

                // Move to the next node
                temp = nextNode;
            } else {
                temp = temp.next;
            }
        }

        return head;
    }

    /*
    ====================================================
    TIME COMPLEXITY:
    ----------------------------------------------------
    O(N)
    - Each node is visited once.

    SPACE COMPLEXITY:
    ----------------------------------------------------
    O(1)
    - Only constant extra space is used.
    ====================================================
    */

    // Utility function to print the doubly linked list
    public static void printList(Node head) {
        Node temp = head;
        while (temp != null) {
            System.out.print(temp.data + " ");
            temp = temp.next;
        }
        System.out.println();
    }

    public static void main(String[] args) {

        /*
        Creating doubly linked list:
        1 <-> 2 <-> 3 <-> 2 <-> 4
        */

        Node head = new Node(1);

        head.next = new Node(2);
        head.next.prev = head;

        head.next.next = new Node(3);
        head.next.next.prev = head.next;

        head.next.next.next = new Node(2);
        head.next.next.next.prev = head.next.next;

        head.next.next.next.next = new Node(4);
        head.next.next.next.next.prev = head.next.next.next;

        System.out.print("Original list: ");
        printList(head);

        int key = 2;

        head = deleteAllOccurrences(head, key);

        System.out.print("List after deleting all occurrences of " + key + ": ");
        printList(head);
    }
}
