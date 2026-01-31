package Linkedlist;


/*
====================================
Singly Linked List Node
====================================
Intuition:
- Each node stores:
  1) a single digit (0–9)
  2) reference to the next node
- Numbers are stored in reverse order

Time Complexity:
- Node creation: O(1)

Space Complexity:
- O(1) per node
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

public class AddTwoNumbersLL {

    /*
    ====================================
    Add Two Numbers (Linked Lists)
    ====================================
    Intuition:
    - Each linked list represents a number in reverse order
      Example:
        2 -> 4 -> 3  represents 342
        5 -> 6 -> 4  represents 465

    - Perform digit-by-digit addition just like manual math
    - Use a carry to handle sums >= 10
    - Dummy node simplifies list creation

    Time Complexity:
    - O(max(n, m))
      where n = length of first list
            m = length of second list

    Space Complexity:
    - O(max(n, m)) for the result list
    */
    static Node addTwoNumbers(Node head1, Node head2) {
        Node temp1 = head1;
        Node temp2 = head2;

        // Dummy node to simplify result construction
        Node dummyNode = new Node(-1);
        Node curr = dummyNode;

        int carry = 0;

        while (temp1 != null || temp2 != null) {
            int sum = carry;

            if (temp1 != null) sum += temp1.data;
            if (temp2 != null) sum += temp2.data;

            // Create node with last digit of sum
            curr.next = new Node(sum % 10);
            carry = sum / 10;

            curr = curr.next;

            if (temp1 != null) temp1 = temp1.next;
            if (temp2 != null) temp2 = temp2.next;
        }

        // If carry remains, add one more node
        if (carry != 0) {
            curr.next = new Node(carry);
        }

        return dummyNode.next; // skip dummy node
    }

    /*
    ====================================
    Insert Node at End (Helper)
    ====================================
    Time Complexity:
    - O(n)

    Space Complexity:
    - O(1)
    */
    static Node insert(Node head, int val) {
        if (head == null) {
            return new Node(val);
        }

        Node temp = head;
        while (temp.next != null) temp = temp.next;
        temp.next = new Node(val);
        return head;
    }

    /*
    ====================================
    Print Linked List (Helper)
    ====================================
    Time Complexity:
    - O(n)

    Space Complexity:
    - O(1)
    */
    static void printList(Node head) {
        while (head != null) {
            System.out.print(head.data);
            if (head.next != null) System.out.print(" -> ");
            head = head.next;
        }
        System.out.println();
    }

    /*
    ====================================
    Main Function (Testing)
    ====================================
    */
    public static void main(String[] args) {

        Node head1 = null;
        Node head2 = null;

        /*
        First number: 342
        Stored as: 2 -> 4 -> 3
        */
        head1 = insert(head1, 2);
        head1 = insert(head1, 4);
        head1 = insert(head1, 3);

        /*
        Second number: 465
        Stored as: 5 -> 6 -> 4
        */
        head2 = insert(head2, 5);
        head2 = insert(head2, 6);
        head2 = insert(head2, 4);

        System.out.print("First number: ");
        printList(head1);

        System.out.print("Second number: ");
        printList(head2);

        Node result = addTwoNumbers(head1, head2);

        /*
        Expected:
        342 + 465 = 807
        Stored as: 7 -> 0 -> 8
        */
        System.out.print("Sum: ");
        printList(result);
    }
}

