#include<iostream>
using namespace std;

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

/*
------------------------------------------------------------
Node structure for singly linked list
------------------------------------------------------------
*/
class node {
public:
    int data;       // Stores value (0, 1, or 2)
    node* next;     // Pointer to the next node

    // Constructor for single node
    node(int val) {
        data = val;
        next = nullptr;
    }

    // Constructor with next pointer
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
Since the list contains only 0s, 1s, and 2s, we can:
1. Traverse the list and count how many 0s, 1s, and 2s exist.
2. Traverse again and overwrite the node values in sorted order.

This approach modifies data, not links.
------------------------------------------------------------
*/

node* sort_ll_0s_1s_2s_brute(node* head) {
    // Edge case: empty list or single node
    if (head == NULL || head->next == NULL) return head;

    int cnt0 = 0, cnt1 = 0, cnt2 = 0;
    node* temp = head;

    // Step 1: Count occurrences of 0s, 1s, and 2s
    while (temp != NULL) {
        if (temp->data == 0) cnt0++;
        else if (temp->data == 1) cnt1++;
        else cnt2++;
        temp = temp->next;
    }

    // Step 2: Overwrite the list with sorted values
    temp = head;

    while (cnt0--) {
        temp->data = 0;
        temp = temp->next;
    }

    while (cnt1--) {
        temp->data = 1;
        temp = temp->next;
    }

    while (cnt2--) {
        temp->data = 2;
        temp = temp->next;
    }

    return head;
}

/*
------------------------------------------------------------
Optimal Approach (Link Manipulation)
------------------------------------------------------------
Intuition:
Instead of modifying node values, we:
1. Create three separate linked lists:
   - one for nodes with value 0
   - one for nodes with value 1
   - one for nodes with value 2
2. Traverse the original list and attach each node to its
   respective list.
3. Merge the three lists together.

This preserves original nodes and only changes pointers.
------------------------------------------------------------
*/

node* sort_ll_0s_1s_2s(node* head) {
    // Edge case
    if (head == NULL || head->next == NULL) return head;

    // Dummy heads to simplify list construction
    node* zerohead = new node(-1), *zero = zerohead;
    node* onehead  = new node(-1), *one  = onehead;
    node* twohead  = new node(-1), *two  = twohead;

    node* temp = head;

    // Distribute nodes into three lists
    while (temp != NULL) {
        if (temp->data == 0) {
            zero->next = temp;
            zero = zero->next;
        } 
        else if (temp->data == 1) {
            one->next = temp;
            one = one->next;
        } 
        else {
            two->next = temp;
            two = two->next;
        }
        temp = temp->next;
    }

    // Merge the three lists
    zero->next = (onehead->next) ? onehead->next : twohead->next;
    one->next = twohead->next;
    two->next = NULL;

    // New head of sorted list
    head = zerohead->next;

    // Delete dummy nodes to avoid memory leak
    delete zerohead;
    delete onehead;
    delete twohead;

    return head;
}

/*
------------------------------------------------------------
Utility function to print the linked list
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
    node* head1 = new node(1, new node(0, new node(2, new node(1, new node(0, new node(2))))));
    node* head2 = new node(1, new node(0, new node(2, new node(1, new node(0, new node(2))))));

    cout << "Original list: ";
    printList(head1);

    head1 = sort_ll_0s_1s_2s_brute(head1);
    cout << "Sorted (Brute):   ";
    printList(head1);

    head2 = sort_ll_0s_1s_2s(head2);
    cout << "Sorted (Optimal): ";
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

Optimal Approach:
- Time Complexity: O(N)
- Space Complexity: O(1)

------------------------------------------------------------
*/
