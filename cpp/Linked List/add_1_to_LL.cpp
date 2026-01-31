#include <iostream>
using namespace std;

/*
------------------------------------------------------------
Problem Statement:
------------------------------------------------------------
Given a non-empty singly linked list representing a non-negative
integer, add 1 to the number and return the updated linked list.

Example:
Input: 1 -> 2 -> 9 -> 9 -> 9
Output: 1 -> 3 -> 0 -> 0 -> 0
------------------------------------------------------------
*/

class node {
public:
    int data;
    node* next;

    node(int val) {
        data = val;
        next = nullptr;
    }

    node(int val, node* next) {
        data = val;
        this->next = next; 
    }
};

/*
------------------------------------------------------------
Helper Function: Reverse linked list
------------------------------------------------------------
Iterative reversal of a singly linked list.
Used in iterative approach to simplify addition from least significant digit.
*/
node* reverse(node* head) {
    node* prev = nullptr;
    node* curr = head;
    node* front = nullptr;

    while (curr != nullptr) {
        front = curr->next;   // store next node
        curr->next = prev;    // reverse link
        prev = curr;          // move prev forward
        curr = front;         // move curr forward
    }

    return prev; // new head
}

/*
------------------------------------------------------------
Iterative Approach to Add 1
------------------------------------------------------------
Steps:
1. Reverse the linked list to process from least significant digit.
2. Add 1 and propagate carry if needed.
3. Reverse back to restore original order.
4. If carry remains after last node, create a new node at head.
------------------------------------------------------------
*/
node* add_1_iterative(node* head) {
    head = reverse(head);
    node* temp = head;
    int carry = 1;

    while (temp != nullptr) {
        temp->data += carry;
        if (temp->data < 10) {
            carry = 0;
            break;
        } else {
            temp->data = 0;
            carry = 1;
        }

        if (temp->next == nullptr) break;
        temp = temp->next;
    }

    if (carry == 1) {
        node* newnode = new node(1);
        head = reverse(head);
        newnode->next = head;
        return newnode;
    }

    head = reverse(head);
    return head;
}

/*
------------------------------------------------------------
Recursive Helper Function
------------------------------------------------------------
Recursively traverse to the end of the list, adding 1
from the least significant digit upwards.
Returns carry to the previous node.
*/
int helper_add(node* temp) {
    if (temp == nullptr) return 1; // base case: add 1 at the end

    int carry = helper_add(temp->next); // recursive call
    temp->data += carry;

    if (temp->data < 10) return 0;     // no further carry
    temp->data = 0;
    return 1;                           // carry 1 to previous node
}

/*
------------------------------------------------------------
Recursive Approach to Add 1
------------------------------------------------------------
Steps:
1. Call helper_add to propagate addition recursively.
2. If a carry remains at the head, create a new node with 1.
------------------------------------------------------------
*/
node* add_1_recursive(node* head) {
    int carry = helper_add(head);
    if (carry == 1) {
        node* newnode = new node(1, head);
        return newnode;
    }
    return head;
}

/*
------------------------------------------------------------
Utility Function: Print Linked List
------------------------------------------------------------
*/
void printList(node* head) {
    while (head != nullptr) {
        cout << head->data << " ";
        head = head->next;
    }
    cout << endl;
}

/*
------------------------------------------------------------
Driver Code
------------------------------------------------------------
*/
int main() {
    node* head1 = new node(1, new node(2, new node(9, new node(9, new node(9)))));
    cout << "Original number: ";
    printList(head1);

    node* addedIter = add_1_iterative(head1);
    cout << "After adding 1 (iterative): ";
    printList(addedIter);

    node* head2 = new node(1, new node(2, new node(9, new node(9, new node(9)))));
    node* addedRec = add_1_recursive(head2);
    cout << "After adding 1 (recursive): ";
    printList(addedRec);

    return 0;
}

/*
------------------------------------------------------------
Time & Space Complexity
------------------------------------------------------------

1. Iterative Approach:
   - Time Complexity: O(N)   // reverse + addition + reverse
   - Space Complexity: O(1)

2. Recursive Approach:
   - Time Complexity: O(N)
   - Space Complexity: O(N)   // recursion stack
------------------------------------------------------------
*/
