#include <iostream>
using namespace std;

/*
====================================================
PROBLEM STATEMENT:
----------------------------------------------------
Given the head of a Doubly Linked List and an integer
key, delete ALL nodes from the list whose data is
equal to the given key.

You must correctly update:
- prev pointers
- next pointers
- head pointer (if the head node itself is deleted)

Return the new head of the modified list.
====================================================
*/

// Definition of a doubly linked list node
class node {
public:
    int data;
    node* prev;
    node* next;

    // Constructor to initialize a node
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
1. Traverse the doubly linked list node by node.
2. If the current node's data matches the key:
   - Store its next and previous nodes.
   - Re-link prev->next and next->prev to bypass
     the current node.
   - If the node is the head, update the head.
   - Delete the current node to free memory.
3. Continue traversal safely using the stored
   next pointer.
4. Return the updated head.
====================================================
*/

// Function to delete all occurrences of key
node* Delete_all_occurence_of_key(node* head, int key) {
    node* temp = head;

    // Traverse the entire list
    while (temp != nullptr) {

        // If current node contains the key
        if (temp->data == key) {

            // Store adjacent nodes
            node* nextnode = temp->next;
            node* prevnode = temp->prev;

            // Link previous node to next node
            if (prevnode)
                prevnode->next = nextnode;

            // Link next node to previous node
            if (nextnode)
                nextnode->prev = prevnode;

            // If head node is being deleted, update head
            if (temp == head)
                head = nextnode;

            // Delete the current node
            delete temp;

            // Move to the next node
            temp = nextnode;
        }
        else {
            // If data doesn't match, just move forward
            temp = temp->next;
        }
    }

    return head;
}

/*
====================================================
TIME COMPLEXITY:
----------------------------------------------------
O(N)
- Each node in the doubly linked list is visited
  exactly once.

SPACE COMPLEXITY:
----------------------------------------------------
O(1)
- No extra data structures are used.
- Only constant extra pointers.
====================================================
*/

// Function to print the doubly linked list
void printList(node* head) {
    node* temp = head;
    while (temp != nullptr) {
        cout << temp->data << " ";
        temp = temp->next;
    }
    cout << endl;
}

int main() {

    /*
    Creating doubly linked list:
    1 <-> 2 <-> 3 <-> 2 <-> 4
    */

    node* head = new node(1);

    head->next = new node(2);
    head->next->prev = head;

    head->next->next = new node(3);
    head->next->next->prev = head->next;

    head->next->next->next = new node(2);
    head->next->next->next->prev = head->next->next;

    head->next->next->next->next = new node(4);
    head->next->next->next->next->prev = head->next->next->next;

    cout << "Original list: ";
    printList(head);

    int key = 2;

    // Delete all occurrences of key
    head = Delete_all_occurence_of_key(head, key);

    cout << "List after deleting all occurrences of " << key << ": ";
    printList(head);

    return 0;
}
