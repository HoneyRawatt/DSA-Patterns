package Linkedlist;

import java.util.Stack;

/*
------------------------------------------------------------
Problem Statement:
------------------------------------------------------------
Given the head of a singly linked list, check whether the
list is a palindrome (reads the same forwards and backwards).

Two approaches are implemented:
1. Brute force using a stack.
2. Optimal approach using fast and slow pointers with in-place reversal.
------------------------------------------------------------
*/

public class PalindromeLinkedList {

    // Node class for singly linked list
    static class Node {
        int data;
        Node next;

        Node(int val) {
            this.data = val;
            this.next = null;
        }

        Node(int val, Node next) {
            this.data = val;
            this.next = next;
        }
    }

    /*
    ------------------------------------------------------------
    Helper function: Reverse a linked list
    ------------------------------------------------------------
    */
    static Node reverse(Node head) {
        Node prev = null;
        Node curr = head;

        while (curr != null) {
            Node next = curr.next;
            curr.next = prev;
            prev = curr;
            curr = next;
        }

        return prev;
    }

    /*
    ------------------------------------------------------------
    Brute Force Approach (Using Stack)
    ------------------------------------------------------------
    Intuition:
    - Push all node values into a stack.
    - Compare stack values with nodes while traversing.
    - Returns true if all match.
    ------------------------------------------------------------
    */
    static boolean checkPalindromeBrute(Node head) {
        Stack<Integer> st = new Stack<>();
        Node temp = head;

        while (temp != null) {
            st.push(temp.data);
            temp = temp.next;
        }

        temp = head;
        while (temp != null) {
            if (temp.data != st.pop()) return false;
            temp = temp.next;
        }

        return true;
    }

    /*
    ------------------------------------------------------------
    Optimal Approach (Fast & Slow Pointers)
    ------------------------------------------------------------
    Intuition:
    1. Find the middle of the list using slow & fast pointers.
    2. Reverse the second half.
    3. Compare first and second half.
    4. Restore the original list.
    ------------------------------------------------------------
    */
    static boolean checkPalindromeOptimal(Node head) {
        if (head == null || head.next == null) return true;

        Node slow = head, fast = head;

        // Find middle node
        while (fast.next != null && fast.next.next != null) {
            slow = slow.next;
            fast = fast.next.next;
        }

        // Reverse second half
        Node secondHalf = reverse(slow.next);

        // Compare first and second half
        Node firstHalf = head;
        Node temp = secondHalf;
        boolean isPalindrome = true;

        while (temp != null) {
            if (firstHalf.data != temp.data) {
                isPalindrome = false;
                break;
            }
            firstHalf = firstHalf.next;
            temp = temp.next;
        }

        // Restore original list
        slow.next = reverse(secondHalf);

        return isPalindrome;
    }

    // Utility function to print linked list
    static void printList(Node head) {
        while (head != null) {
            System.out.print(head.data + " ");
            head = head.next;
        }
        System.out.println();
    }

    // Driver code
    public static void main(String[] args) {
        Node head = new Node(1, new Node(2, new Node(3, new Node(2, new Node(1)))));

        System.out.print("Original list: ");
        printList(head);

        System.out.println("Is palindrome (brute)? " + (checkPalindromeBrute(head) ? "Yes" : "No"));
        System.out.println("Is palindrome (optimal)? " + (checkPalindromeOptimal(head) ? "Yes" : "No"));
    }

    /*
    ------------------------------------------------------------
    Time & Space Complexity
    ------------------------------------------------------------

    1. Brute Force (Stack):
       - Time Complexity: O(N)
       - Space Complexity: O(N)

    2. Optimal Approach (Fast & Slow + Reverse):
       - Time Complexity: O(N)
       - Space Complexity: O(1)
    ------------------------------------------------------------
    */
}
