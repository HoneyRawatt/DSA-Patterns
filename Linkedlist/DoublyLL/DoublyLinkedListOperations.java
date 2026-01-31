package Linkedlist.DoublyLL;

/*
====================================
Doubly Linked List Node
====================================
Intuition:
- Each node stores:
  1) data
  2) reference to previous node
  3) reference to next node
- Allows traversal in both forward and backward directions

Time Complexity:
- Node creation: O(1)

Space Complexity:
- O(1) per node
*/
class Node {
    int data;
    Node prev;
    Node next;

    Node(int val) {
        data = val;
        prev = null;
        next = null;
    }

    Node(int val, Node next, Node prev) {
        data = val;
        this.next = next;
        this.prev = prev;
    }
}

public class DoublyLinkedListOperations {

    /*
    ====================================
    Convert Array to Doubly Linked List
    ====================================
    Intuition:
    - First element becomes head
    - Maintain a `prev` pointer to link nodes both ways
    - Traverse array once

    Time Complexity:
    - O(n)

    Space Complexity:
    - O(n)
    */
    static Node convertArr(int[] arr) {
        if (arr.length == 0) return null;

        Node head = new Node(arr[0]);
        Node prev = head;

        for (int i = 1; i < arr.length; i++) {
            Node temp = new Node(arr[i]);
            prev.next = temp;
            temp.prev = prev;
            prev = temp;
        }
        return head;
    }

    /*
    ====================================
    Delete Head Node
    ====================================
    Intuition:
    - Move head to next node
    - Set new head's prev to null

    Time Complexity:
    - O(1)

    Space Complexity:
    - O(1)
    */
    static Node deleteHead(Node head) {
        if (head == null) return null;

        head = head.next;
        if (head != null) head.prev = null;
        return head;
    }

    /*
    ====================================
    Delete Tail Node
    ====================================
    Intuition:
    - Traverse to last node
    - Use prev pointer to unlink tail

    Time Complexity:
    - O(n)

    Space Complexity:
    - O(1)
    */
    static Node deleteTail(Node head) {
        if (head == null || head.next == null) return null;

        Node tail = head;
        while (tail.next != null) tail = tail.next;

        tail.prev.next = null;
        return head;
    }

    /*
    ====================================
    Delete Given Node (by reference)
    ====================================
    Intuition:
    - Handle 4 cases:
      1) Only one node
      2) Head node
      3) Tail node
      4) Middle node

    Time Complexity:
    - O(1)

    Space Complexity:
    - O(1)
    */
    static Node deleteNode(Node head, Node temp) {
        if (temp == null) return head;

        Node prev = temp.prev;
        Node front = temp.next;

        if (prev == null && front == null) { // only one node
            return null;
        }
        if (prev == null) { // head
            head = head.next;
            head.prev = null;
            return head;
        }
        if (front == null) { // tail
            prev.next = null;
            return head;
        }

        // middle node
        prev.next = front;
        front.prev = prev;
        return head;
    }

    /*
    ====================================
    Delete Kth Node (1-based index)
    ====================================
    Intuition:
    - Traverse till kth node
    - Reuse delete-by-reference logic

    Time Complexity:
    - O(n)

    Space Complexity:
    - O(1)
    */
    static Node deleteKthNode(Node head, int k) {
        if (head == null) return null;

        int cnt = 1;
        Node temp = head;

        while (temp != null && cnt < k) {
            temp = temp.next;
            cnt++;
        }

        if (temp == null) return head; // k > length
        return deleteNode(head, temp);
    }

    /*
    ====================================
    Insert at Head
    ====================================
    Intuition:
    - New node becomes head
    - Old head’s prev points to new node

    Time Complexity:
    - O(1)

    Space Complexity:
    - O(1)
    */
    static Node insertHead(Node head, int val) {
        Node newNode = new Node(val);
        if (head == null) return newNode;

        newNode.next = head;
        head.prev = newNode;
        return newNode;
    }

    /*
    ====================================
    Insert at Tail
    ====================================
    Intuition:
    - Traverse to last node
    - Link new node using prev pointer

    Time Complexity:
    - O(n)

    Space Complexity:
    - O(1)
    */
    static Node insertTail(Node head, int val) {
        Node newNode = new Node(val);
        if (head == null) return newNode;

        Node tail = head;
        while (tail.next != null) tail = tail.next;

        tail.next = newNode;
        newNode.prev = tail;
        return head;
    }

    /*
    ====================================
    Insert at Kth Position (1-based)
    ====================================
    Intuition:
    - Traverse to (k-1)th node
    - Adjust prev and next pointers

    Time Complexity:
    - O(n)

    Space Complexity:
    - O(1)
    */
    static Node insertAtK(Node head, int k, int val) {
        if (k <= 1) return insertHead(head, val);

        int cnt = 1;
        Node temp = head;

        while (temp != null && cnt < k - 1) {
            temp = temp.next;
            cnt++;
        }

        if (temp == null || temp.next == null) {
            return insertTail(head, val);
        }

        Node newNode = new Node(val);
        Node front = temp.next;

        temp.next = newNode;
        newNode.prev = temp;
        newNode.next = front;
        front.prev = newNode;

        return head;
    }

    /*
    ====================================
    Insert Before Given Node
    ====================================
    Time Complexity:
    - O(1)

    Space Complexity:
    - O(1)
    */
    static Node insertBefore(Node head, Node temp, int val) {
        if (temp == null) return head;
        if (temp.prev == null) return insertHead(head, val);

        Node newNode = new Node(val);
        Node prev = temp.prev;

        prev.next = newNode;
        newNode.prev = prev;
        newNode.next = temp;
        temp.prev = newNode;

        return head;
    }

    /*
    ====================================
    Insert After Given Node
    ====================================
    Time Complexity:
    - O(1)

    Space Complexity:
    - O(1)
    */
    static Node insertAfter(Node head, Node temp, int val) {
        if (temp == null) return head;

        Node newNode = new Node(val);
        Node front = temp.next;

        temp.next = newNode;
        newNode.prev = temp;
        newNode.next = front;

        if (front != null) front.prev = newNode;
        return head;
    }

    /*
    ====================================
    Print List Forward
    ====================================
    Time Complexity:
    - O(n)

    Space Complexity:
    - O(1)
    */
    static void print(Node head) {
        Node temp = head;
        while (temp != null) {
            System.out.print(temp.data + " ");
            temp = temp.next;
        }
        System.out.println();
    }

    /*
    ====================================
    Print List in Reverse
    ====================================
    Time Complexity:
    - O(n)

    Space Complexity:
    - O(1)
    */
    static void printReverse(Node head) {
        if (head == null) return;

        Node tail = head;
        while (tail.next != null) tail = tail.next;

        while (tail != null) {
            System.out.print(tail.data + " ");
            tail = tail.prev;
        }
        System.out.println();
    }

    /*
    ====================================
    Reverse Doubly Linked List
    ====================================
    Intuition:
    - Swap prev and next for each node
    - Last processed node becomes new head

    Time Complexity:
    - O(n)

    Space Complexity:
    - O(1)
    */
    static Node reverse(Node head) {
        if (head == null || head.next == null) return head;

        Node curr = head;
        Node last = null;

        while (curr != null) {
            last = curr.prev;
            curr.prev = curr.next;
            curr.next = last;
            curr = curr.prev;
        }

        if (last != null) head = last.prev;
        return head;
    }

    /*
    ====================================
    Main Function (Testing)
    ====================================
    */
    public static void main(String[] args) {
        int[] arr = {12, 2, 3, 4, 6};
        Node head = convertArr(arr);

        System.out.print("Original list: ");
        print(head);

        head = deleteHead(head);
        System.out.print("After deleting head: ");
        print(head);

        head = deleteTail(head);
        System.out.print("After deleting tail: ");
        print(head);

        head = deleteKthNode(head, 2);
        System.out.print("After deleting 2nd node: ");
        print(head);

        head = insertHead(head, 99);
        System.out.print("After inserting 99 at head: ");
        print(head);

        head = insertTail(head, 77);
        System.out.print("After inserting 77 at tail: ");
        print(head);

        head = insertAtK(head, 2, 55);
        System.out.print("After inserting 55 at pos 2: ");
        print(head);

        head = insertBefore(head, head.next, 44);
        System.out.print("After inserting 44 before 2nd node: ");
        print(head);

        head = insertAfter(head, head.next, 11);
        System.out.print("After inserting 11 after 2nd node: ");
        print(head);

        System.out.print("List in reverse order: ");
        printReverse(head);

        head = reverse(head);
        System.out.print("List after reversing: ");
        print(head);
    }
}
