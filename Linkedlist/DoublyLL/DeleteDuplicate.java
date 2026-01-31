package Linkedlist.DoublyLL;

/*
====================================================
PROBLEM STATEMENT:
----------------------------------------------------
Given the head of a SORTED doubly linked list,
remove all duplicate nodes such that each value
appears only once in the list.

The relative order of elements must be preserved.
====================================================
*/


class Node {
    int data;
    Node next, prev;

    Node(int x) {
        data = x;
        next = prev = null;
    }
}

class DeleteDuplicate{

    /*
    ====================================================
    INTUITION:
    ----------------------------------------------------
    1. Since the doubly linked list is SORTED,
       duplicate elements appear consecutively.
    2. Traverse the list using a pointer.
    3. For each node, remove all next nodes having
       the same value.
    4. Adjust next and prev pointers accordingly.
    ====================================================
    */

    public static Node removeDuplicates(Node head) {

        Node temp = head;

        // Traverse the list
        while (temp != null && temp.next != null) {

            Node nextNode = temp.next;

            // Remove consecutive duplicate nodes
            while (nextNode != null && nextNode.data == temp.data) {
                nextNode = nextNode.next;
            }

            // Link current node to the next distinct node
            temp.next = nextNode;

            // Update prev pointer if next distinct node exists
            if (nextNode != null) {
                nextNode.prev = temp;
            }

            // Move to the next distinct node
            temp = temp.next;
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
    - No extra space used.
    ====================================================
    */
}
