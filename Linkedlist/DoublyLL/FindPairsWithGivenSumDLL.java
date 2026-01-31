package Linkedlist.DoublyLL;

import java.util.*;

/*
====================================================
PROBLEM STATEMENT:
----------------------------------------------------
Given a SORTED doubly linked list and an integer sum,
find all pairs of nodes such that the sum of their
data values is equal to the given sum.

Return all such pairs as (first, second).
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

public class FindPairsWithGivenSumDLL {

    /*
    ====================================================
    BRUTE-FORCE APPROACH:
    ----------------------------------------------------
    INTUITION:
    - Fix one node and try all nodes after it.
    - Since the list is sorted, break early when
      sum exceeds the target.

    TIME COMPLEXITY: O(N^2)
    SPACE COMPLEXITY: O(1) (excluding output)
    ====================================================
    */

    public static List<int[]> findPairsWithGivenSumBrute(Node head, int sum) {
        Node temp1 = head;
        List<int[]> res = new ArrayList<>();

        // Outer loop for first pointer
        while (temp1 != null) {

            // Inner loop for second pointer
            Node temp2 = temp1.next;
            while (temp2 != null && temp1.data + temp2.data <= sum) {

                // If valid pair is found
                if (temp1.data + temp2.data == sum) {
                    res.add(new int[]{temp1.data, temp2.data});
                }
                temp2 = temp2.next;
            }
            temp1 = temp1.next;
        }
        return res;
    }

    /*
    ====================================================
    HELPER FUNCTION:
    ----------------------------------------------------
    Returns the tail node of the doubly linked list.
    ====================================================
    */

    public static Node findTail(Node head) {
        Node temp = head;
        while (temp.next != null) {
            temp = temp.next;
        }
        return temp;
    }

    /*
    ====================================================
    OPTIMAL APPROACH (Two Pointers):
    ----------------------------------------------------
    INTUITION:
    - Use two pointers:
        left  → start of list
        right → end of list
    - If sum is smaller → move left forward
    - If sum is greater → move right backward
    - If equal → store pair and move both pointers

    TIME COMPLEXITY: O(N)
    SPACE COMPLEXITY: O(1) (excluding output)
    ====================================================
    */

    public static List<int[]> findPairsWithGivenSum(Node head, int sum) {

        Node left = head;
        Node right = findTail(head);
        List<int[]> res = new ArrayList<>();

        // Continue until pointers cross
        while (left != null && right != null &&
               left != right && left.prev != right) {

            int currentSum = left.data + right.data;

            if (currentSum < sum) {
                left = left.next;          // Increase sum
            } else if (currentSum > sum) {
                right = right.prev;        // Decrease sum
            } else {
                // Valid pair found
                res.add(new int[]{left.data, right.data});
                left = left.next;
                right = right.prev;
            }
        }
        return res;
    }

    /*
    ====================================================
    UTILITY FUNCTION:
    ----------------------------------------------------
    Prints all pairs.
    ====================================================
    */

    public static void printPairs(List<int[]> pairs) {
        for (int[] p : pairs) {
            System.out.print("(" + p[0] + "," + p[1] + ") ");
        }
        System.out.println();
    }

    public static void main(String[] args) {

        /*
        Creating sorted doubly linked list:
        1 <-> 2 <-> 3 <-> 4 <-> 5
        */

        Node head = new Node(1);

        head.next = new Node(2);
        head.next.prev = head;

        head.next.next = new Node(3);
        head.next.next.prev = head.next;

        head.next.next.next = new Node(4);
        head.next.next.next.prev = head.next.next;

        head.next.next.next.next = new Node(5);
        head.next.next.next.next.prev = head.next.next.next;

        int sum = 5;

        // Brute-force solution
        System.out.print("Brute-force pairs with sum " + sum + ": ");
        List<int[]> brutePairs = findPairsWithGivenSumBrute(head, sum);
        printPairs(brutePairs);

        // Optimal solution
        System.out.print("Optimal pairs with sum " + sum + ": ");
        List<int[]> optimalPairs = findPairsWithGivenSum(head, sum);
        printPairs(optimalPairs);
    }
}

