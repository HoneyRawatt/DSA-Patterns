package Linkedlist;

/*
------------------------------------------------------------
Problem Statement:
------------------------------------------------------------
Given a singly linked list consisting only of values 0, 1, and 2,
sort the linked list such that all 0s come first, followed by 1s,
and then 2s.

You are not allowed to use any sorting algorithm directly.
------------------------------------------------------------
*/

public class SortLinkedList012 {

    /*
    ------------------------------------------------------------
    Node structure for singly linked list
    ------------------------------------------------------------
    */
    static class Node {
        int data;     // Stores value (0, 1, or 2)
        Node next;    // Reference to next node

        // Constructor for single node
        Node(int val) {
            data = val;
            next = null;
        }

        // Constructor with next reference
        Node(int val, Node next) {
            data = val;
            this.next = next;
        }
    }

    /*
    ------------------------------------------------------------
    Brute Force Approach
    ------------------------------------------------------------
    Intuition:
    Since the list contains only 0s, 1s, and 2s, we can:
    1. Traverse the list and count how many 0s, 1s, and 2s exist.
    2. Traverse again and overwrite the node values in sorted order.

    This approach modifies data, not node links.
    ------------------------------------------------------------
    */
    static Node sortLL012Brute(Node head) {
        // Edge case: empty list or single node
        if (head == null || head.next == null)
            return head;

        int cnt0 = 0, cnt1 = 0, cnt2 = 0;
        Node temp = head;

        // Step 1: Count occurrences
        while (temp != null) {
            if (temp.data == 0) cnt0++;
            else if (temp.data == 1) cnt1++;
            else cnt2++;
            temp = temp.next;
        }

        // Step 2: Rewrite values in sorted order
        temp = head;

        while (cnt0-- > 0) {
            temp.data = 0;
            temp = temp.next;
        }

        while (cnt1-- > 0) {
            temp.data = 1;
            temp = temp.next;
        }

        while (cnt2-- > 0) {
            temp.data = 2;
            temp = temp.next;
        }

        return head;
    }

    /*
    ------------------------------------------------------------
    Optimal Approach (Link Manipulation)
    ------------------------------------------------------------
    Intuition:
    Instead of modifying node values, we:
    1. Create three separate linked lists for 0s, 1s, and 2s.
    2. Traverse the original list and attach nodes to their
       respective lists.
    3. Merge the three lists to get the sorted list.

    This preserves original nodes and only rearranges links.
    ------------------------------------------------------------
    */
    static Node sortLL012Optimal(Node head) {
        // Edge case
        if (head == null || head.next == null)
            return head;

        // Dummy heads to simplify list construction
        Node zeroHead = new Node(-1), zero = zeroHead;
        Node oneHead  = new Node(-1), one  = oneHead;
        Node twoHead  = new Node(-1), two  = twoHead;

        Node temp = head;

        // Distribute nodes into three lists
        while (temp != null) {
            if (temp.data == 0) {
                zero.next = temp;
                zero = zero.next;
            } 
            else if (temp.data == 1) {
                one.next = temp;
                one = one.next;
            } 
            else {
                two.next = temp;
                two = two.next;
            }
            temp = temp.next;
        }

        // Merge the three lists
        zero.next = (oneHead.next != null) ? oneHead.next : twoHead.next;
        one.next = twoHead.next;
        two.next = null;

        // New head of sorted list
        return zeroHead.next;
    }

    /*
    ------------------------------------------------------------
    Utility function to print the linked list
    ------------------------------------------------------------
    */
    static void printList(Node head) {
        while (head != null) {
            System.out.print(head.data + " ");
            head = head.next;
        }
        System.out.println();
    }

    /*
    ------------------------------------------------------------
    Driver Code
    ------------------------------------------------------------
    */
    public static void main(String[] args) {

        Node head1 = new Node(1,
                        new Node(0,
                        new Node(2,
                        new Node(1,
                        new Node(0,
                        new Node(2))))));

        Node head2 = new Node(1,
                        new Node(0,
                        new Node(2,
                        new Node(1,
                        new Node(0,
                        new Node(2))))));

        System.out.print("Original list: ");
        printList(head1);

        head1 = sortLL012Brute(head1);
        System.out.print("Sorted (Brute):   ");
        printList(head1);

        head2 = sortLL012Optimal(head2);
        System.out.print("Sorted (Optimal): ");
        printList(head2);
    }

    /*
    ------------------------------------------------------------
    Time & Space Complexity:
    ------------------------------------------------------------

    Brute Force Approach:
    - Time Complexity: O(N)
    - Space Complexity: O(1)

    Optimal Approach:
    - Time Complexity: O(N)
    - Space Complexity: O(1)

    ------------------------------------------------------------
    */
}

