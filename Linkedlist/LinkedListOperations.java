package Linkedlist;
/*
========================
Linked List Node Class
========================
Intuition:
- Each node stores:
  1) data
  2) reference to the next node
- This is a singly linked list

Time Complexity:
- Node creation: O(1)

Space Complexity:
- O(1) per node
*/
class Node {
    int data;
    Node next;

    // Constructor for single node
    Node(int val) {
        data = val;
        next = null;
    }

    // Constructor when next node is known
    Node(int val, Node next) {
        data = val;
        this.next = next;
    }
}

public class LinkedListOperations {

    /*
    =====================================
    Convert Array to Linked List
    =====================================
    Intuition:
    - First element becomes the head
    - Use a pointer (mover) to keep adding nodes at the end
    - Traverse array once and link nodes sequentially

    Time Complexity:
    - O(n)

    Space Complexity:
    - O(n)
    */
    static Node convertArrToLL(int[] arr) {
        if (arr.length == 0) return null;

        Node head = new Node(arr[0]);
        Node mover = head;

        for (int i = 1; i < arr.length; i++) {
            mover.next = new Node(arr[i]);
            mover = mover.next;
        }
        return head;
    }

    /*
    ========================
    Display Linked List
    ========================
    Intuition:
    - Traverse from head to null
    - Print each node's data

    Time Complexity:
    - O(n)

    Space Complexity:
    - O(1)
    */
    static void display(Node head) {
        if (head == null) {
            System.out.println("linked list is empty");
            return;
        }

        Node temp = head;
        while (temp != null) {
            System.out.print(temp.data + " ");
            temp = temp.next;
        }
        System.out.println();
    }

    /*
    ========================
    Length of Linked List
    ========================
    Intuition:
    - Traverse and count nodes

    Time Complexity:
    - O(n)

    Space Complexity:
    - O(1)
    */
    static int lengthOfLL(Node head) {
        int cnt = 0;
        Node temp = head;

        while (temp != null) {
            cnt++;
            temp = temp.next;
        }
        return cnt;
    }

    /*
    ========================
    Search Element in LL
    ========================
    Intuition:
    - Traverse list
    - Compare each node’s data with target value

    Time Complexity:
    - O(n)

    Space Complexity:
    - O(1)
    */
    static boolean checkIfPresent(Node head, int val) {
        Node temp = head;
        while (temp != null) {
            if (temp.data == val) return true;
            temp = temp.next;
        }
        return false;
    }

    /*
    ========================
    Delete Head Node
    ========================
    Intuition:
    - Move head to next node

    Time Complexity:
    - O(1)

    Space Complexity:
    - O(1)
    */
    static Node deleteHead(Node head) {
        if (head == null) return null;
        return head.next;
    }

    /*
    ========================
    Delete Last Node
    ========================
    Intuition:
    - Traverse to second last node
    - Remove reference to last node

    Time Complexity:
    - O(n)

    Space Complexity:
    - O(1)
    */
    static Node deleteLast(Node head) {
        if (head == null || head.next == null) return null;

        Node temp = head;
        while (temp.next.next != null) {
            temp = temp.next;
        }
        temp.next = null;
        return head;
    }

    /*
    ========================
    Delete Kth Node
    ========================
    Intuition:
    - If k == 1 → delete head
    - Else traverse while counting
    - Re-link previous node

    Time Complexity:
    - O(n)

    Space Complexity:
    - O(1)
    */
    static Node deleteKth(Node head, int k) {
        if (head == null) return null;
        if (k == 1) return deleteHead(head);

        int cnt = 1;
        Node temp = head;
        Node prev = null;

        while (temp != null) {
            if (cnt == k) {
                prev.next = temp.next;
                break;
            }
            prev = temp;
            temp = temp.next;
            cnt++;
        }
        return head;
    }

    /*
    ========================
    Delete Node by Value
    ========================
    Intuition:
    - If value at head → delete head
    - Else find matching node and unlink it

    Time Complexity:
    - O(n)

    Space Complexity:
    - O(1)
    */
    static Node deleteByValue(Node head, int val) {
        if (head == null) return null;
        if (head.data == val) return deleteHead(head);

        Node temp = head;
        Node prev = null;

        while (temp != null) {
            if (temp.data == val) {
                prev.next = temp.next;
                break;
            }
            prev = temp;
            temp = temp.next;
        }
        return head;
    }

    /*
    ========================
    Insert at Head
    ========================
    Intuition:
    - New node points to old head

    Time Complexity:
    - O(1)

    Space Complexity:
    - O(1)
    */
    static Node insertHead(Node head, int val) {
        return new Node(val, head);
    }

    /*
    ========================
    Insert at Tail
    ========================
    Intuition:
    - Traverse to last node
    - Attach new node

    Time Complexity:
    - O(n)

    Space Complexity:
    - O(1)
    */
    static Node insertTail(Node head, int val) {
        if (head == null) return new Node(val);

        Node temp = head;
        while (temp.next != null) {
            temp = temp.next;
        }
        temp.next = new Node(val);
        return head;
    }

    /*
    ========================
    Insert at Given Position
    ========================
    Intuition:
    - If pos == 1 → insert at head
    - Traverse till (pos-1)th node

    Time Complexity:
    - O(n)

    Space Complexity:
    - O(1)
    */
    static Node insertAtPosition(Node head, int val, int pos) {
        if (pos == 1) return new Node(val, head);

        int cnt = 1;
        Node temp = head;

        while (temp != null) {
            if (cnt == pos - 1) {
                temp.next = new Node(val, temp.next);
                break;
            }
            cnt++;
            temp = temp.next;
        }
        return head;
    }

    /*
    ========================
    Insert Before Given Value
    ========================
    Intuition:
    - If value at head → insert before head
    - Else check next node’s value

    Time Complexity:
    - O(n)

    Space Complexity:
    - O(1)
    */
    static Node insertBeforeValue(Node head, int el, int val) {
        if (head == null) return null;
        if (head.data == val) return new Node(el, head);

        Node temp = head;
        while (temp.next != null) {
            if (temp.next.data == val) {
                temp.next = new Node(el, temp.next);
                break;
            }
            temp = temp.next;
        }
        return head;
    }

    /*
    ========================
    Main Function (Testing)
    ========================
    */
    public static void main(String[] args) {
        int[] arr = {2, 5, 0, 7};
        Node head = convertArrToLL(arr);

        System.out.print("Linked List created from array: ");
        display(head);

        System.out.println("Length of LL: " + lengthOfLL(head));
        System.out.println("Check if element is present: " +
                (checkIfPresent(head, 5) ? "YES" : "NO"));

        head = deleteKth(head, 3);
        System.out.print("After deleting 3rd node: ");
        display(head);

        head = deleteByValue(head, 7);
        System.out.print("After deleting node with value 7: ");
        display(head);

        head = insertHead(head, 10);
        System.out.print("After inserting 10 at head: ");
        display(head);

        head = insertTail(head, 99);
        System.out.print("After inserting 99 at tail: ");
        display(head);

        head = insertAtPosition(head, 77, 3);
        System.out.print("After inserting 77 at position 3: ");
        display(head);

        head = insertBeforeValue(head, 88, 5);
        System.out.print("After inserting 88 before 5: ");
        display(head);
    }
}
