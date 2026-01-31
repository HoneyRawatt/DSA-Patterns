#include<iostream>
using namespace std;

/*
------------------------------------------------------------
Problem Statement:
------------------------------------------------------------
Given the head of a singly linked list, remove the N-th node
from the end of the list and return the head of the modified list.

The list contains at least one node, and 1 ≤ N ≤ length of list.
------------------------------------------------------------
*/

/*
------------------------------------------------------------
Node structure for singly linked list
------------------------------------------------------------
*/
class node {
public:
    int data;        // Value stored in node
    node* next;      // Pointer to next node

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
Brute Force Approach
------------------------------------------------------------
Intuition:
To remove the N-th node from the end, we need to know its
position from the beginning.

Steps:
1. Traverse the list to count total nodes (cnt).
2. The node to remove is at position (cnt - n) from the start.
3. Traverse again to reach just before that node.
4. Adjust pointers and delete the node.

This approach uses two traversals.
------------------------------------------------------------
*/

node* remove_nth_node_brute(node* head, int n) {
    int cnt = 0;
    node* temp = head;

    // First traversal: count total nodes
    while (temp != NULL) {
        cnt++;
        temp = temp->next;
    }

    // If the head node itself needs to be removed
    if (cnt == n) {
        node* newhead = head->next;
        delete head;
        return newhead;
    }

    // Find position just before the node to delete
    int res = cnt - n;
    temp = head;

    while (temp->next != NULL) {
        res--;
        if (res == 0) break;
        temp = temp->next;
    }

    // Delete the target node
    node* deletenode = temp->next;
    temp->next = temp->next->next; // update link
    delete deletenode;

    return head;
}

/*
------------------------------------------------------------
Optimal Approach (Two Pointer Technique)
------------------------------------------------------------
Intuition:
Maintain a gap of N nodes between two pointers.

Steps:
1. Create a dummy node before head to handle edge cases.
2. Move `fast` pointer N steps ahead.
3. Move both `fast` and `slow` until `fast` reaches the end.
4. `slow->next` will be the node to delete.
5. Adjust pointers and delete the node.

This requires only one traversal.
------------------------------------------------------------
*/

node* remove_nth_node(node* head, int n) {
    // Dummy node simplifies deletion of head
    node* dummy = new node(-1, head);
    node* fast = dummy;
    node* slow = dummy;

    // Move fast pointer n steps ahead
    for (int i = 0; i < n; i++) {
        fast = fast->next;
    }

    // Move both pointers until fast reaches last node
    while (fast->next != nullptr) {
        slow = slow->next;
        fast = fast->next;
    }

    // slow->next is the node to be removed
    node* deletenode = slow->next;
    slow->next = slow->next->next;
    delete deletenode;

    node* newhead = dummy->next;
    delete dummy; // cleanup dummy node
    return newhead;
}

/*
------------------------------------------------------------
Utility Function: Print Linked List
------------------------------------------------------------
*/
void printList(node* head) {
    while (head != NULL) {
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
    // Create sample linked lists
    node* head1 = new node(1, new node(2, new node(3, new node(4, new node(5)))));
    node* head2 = new node(1, new node(2, new node(3, new node(4, new node(5)))));

    cout << "Original list (for brute): ";
    printList(head1);
    head1 = remove_nth_node_brute(head1, 2); // remove 2nd node from end
    cout << "After brute removal: ";
    printList(head1);

    cout << "Original list (for optimal): ";
    printList(head2);
    head2 = remove_nth_node(head2, 2); // remove 2nd node from end
    cout << "After optimal removal: ";
    printList(head2);

    return 0;
}

/*
------------------------------------------------------------
Time & Space Complexity:
------------------------------------------------------------

Brute Force Approach:
- Time Complexity: O(N)
- Space Complexity: O(1)

Optimal Two Pointer Approach:
- Time Complexity: O(N)
- Space Complexity: O(1)

------------------------------------------------------------
*/
