#include <iostream>
using namespace std;

/*
====================================================
PROBLEM STATEMENT:
----------------------------------------------------
Given the head of a singly linked list and an integer
k, reverse the nodes of the list k at a time and
return the modified list.

If the number of nodes left is less than k,
they should remain as it is.
====================================================
*/

// Definition of a singly linked list node
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
====================================================
HELPER FUNCTION 1:
----------------------------------------------------
Returns the k-th node starting from the given node.
If fewer than k nodes are present, returns nullptr.
====================================================
*/

node* getKnode(node* temp, int k) {
    // Move k-1 steps forward
    while (temp != nullptr && k > 1) {
        k--;
        temp = temp->next;
    }
    return temp;
}

/*
====================================================
HELPER FUNCTION 2:
----------------------------------------------------
Reverses a linked list segment starting at 'head'.
Standard iterative linked list reversal.
====================================================
*/

void reverseList(node* head) {
    node* prev = nullptr;
    node* curr = head;

    while (curr != nullptr) {
        node* nxt = curr->next; // store next node
        curr->next = prev;      // reverse link
        prev = curr;            // move prev forward
        curr = nxt;             // move curr forward
    }
}

/*
====================================================
MAIN FUNCTION:
----------------------------------------------------
INTUITION:
1. Process the list in chunks of size k.
2. For each group:
   - Find the k-th node.
   - Temporarily detach the group.
   - Reverse the group.
   - Attach it back to the main list.
3. If fewer than k nodes remain, leave them unchanged.
====================================================
*/

node* K_reverse(node* head, int k) {

    node* temp = head;      // Pointer to current group
    node* prevnode = nullptr; // Last node of previous group

    while (temp != nullptr) {

        // Find k-th node of current group
        node* kthnode = getKnode(temp, k);

        // If fewer than k nodes left, connect and break
        if (kthnode == nullptr) {
            if (prevnode)
                prevnode->next = temp;
            break;
        }

        // Store the next group head
        node* nextnode = kthnode->next;

        // Detach current k-group
        kthnode->next = nullptr;

        // Reverse current group
        reverseList(temp);

        // Update head for the first group
        if (temp == head) {
            head = kthnode;
        } else {
            prevnode->next = kthnode;
        }

        // Prepare for next iteration
        prevnode = temp;   // temp becomes tail after reverse
        temp = nextnode;   // move to next group
    }

    return head;
}

/*
====================================================
TIME COMPLEXITY:
----------------------------------------------------
O(N)
- Each node is visited once during reversal.

SPACE COMPLEXITY:
----------------------------------------------------
O(1)
- In-place reversal, no extra data structures.
====================================================
*/

// Utility function to print linked list
void printList(node* head) {
    while (head != nullptr) {
        cout << head->data << " ";
        head = head->next;
    }
    cout << endl;
}

// Driver code
int main() {

    /*
    Creating linked list:
    1 -> 2 -> 3 -> 4 -> 5
    */

    node* head = new node(1);
    head->next = new node(2);
    head->next->next = new node(3);
    head->next->next->next = new node(4);
    head->next->next->next->next = new node(5);

    cout << "Original list: ";
    printList(head);

    // Reverse in groups of k = 2
    head = K_reverse(head, 2);

    cout << "After reversing in groups of 2: ";
    printList(head);

    return 0;
}
