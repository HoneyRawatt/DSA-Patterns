#include <iostream>
using namespace std;

/*
====================================================
PROBLEM STATEMENT:
----------------------------------------------------
Given the head of a SORTED doubly linked list,
remove all duplicate nodes such that each value
appears only once in the list.

The relative order of elements must be preserved.
====================================================
*/

// Definition of a doubly linked list node
class node {
public:
    int data;
    node* prev;
    node* next;

    node(int val) {
        data = val;
        next = nullptr;
        prev = nullptr;
    }
};

/*
====================================================
INTUITION:
----------------------------------------------------
1. Since the doubly linked list is SORTED,
   duplicate elements will always be adjacent.
2. Traverse the list using a pointer `temp`.
3. For each node:
   - Compare it with the next node.
   - If duplicate values are found, delete all
     consecutive nodes with the same value.
4. Reconnect the list by updating next and prev
   pointers correctly.
====================================================
*/

// Function to remove duplicates from a sorted DLL
node* remove_duplicate_from_Sorted_DLL(node* head) {

    node* temp = head;

    // Traverse until the end of the list
    while (temp != nullptr && temp->next != nullptr) {

        node* nextnode = temp->next;

        // Remove all consecutive duplicate nodes
        while (nextnode != nullptr && nextnode->data == temp->data) {

            node* dupli = nextnode;     // Node to be deleted
            nextnode = nextnode->next; // Move forward
            delete dupli;               // Free memory
        }

        // Link current node to the next distinct node
        temp->next = nextnode;

        // Update prev pointer of next distinct node
        if (nextnode)
            nextnode->prev = temp;

        // Move to the next distinct node
        temp = temp->next;
    }

    return head;
}

/*
====================================================
TIME COMPLEXITY:
----------------------------------------------------
O(N)
- Each node is visited once.

SPACE COMPLEXITY:
----------------------------------------------------
O(1)
- No extra data structures are used.
====================================================
*/

// Helper function to print the doubly linked list
void printDLL(node* head) {
    while (head != nullptr) {
        cout << head->data << " ";
        head = head->next;
    }
    cout << endl;
}

// Driver code
int main() {

    /*
    Creating sorted doubly linked list:
    1 <-> 2 <-> 2 <-> 3 <-> 3
    */

    node* head = new node(1);

    head->next = new node(2);
    head->next->prev = head;

    head->next->next = new node(2);
    head->next->next->prev = head->next;

    head->next->next->next = new node(3);
    head->next->next->next->prev = head->next->next;

    head->next->next->next->next = new node(3);
    head->next->next->next->next->prev = head->next->next->next;

    cout << "Original DLL: ";
    printDLL(head);

    // Remove duplicates
    head = remove_duplicate_from_Sorted_DLL(head);

    cout << "After removing duplicates: ";
    printDLL(head);

    return 0;
}
