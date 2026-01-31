#include <iostream>
using namespace std;

/*
====================================================
PROBLEM STATEMENT:
----------------------------------------------------
Given the head of a singly linked list and an integer k,
rotate the linked list to the right by k positions.

Example:
Input : 1 -> 2 -> 3 -> 4 -> 5 , k = 2
Output: 4 -> 5 -> 1 -> 2 -> 3
====================================================
*/

// Definition of singly linked list node
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
UTILITY FUNCTION:
----------------------------------------------------
Prints the linked list.
====================================================
*/
void printList(node* head) {
    while (head != nullptr) {
        cout << head->data << " ";
        head = head->next;
    }
    cout << endl;
}

/*
====================================================
HELPER FUNCTION:
----------------------------------------------------
Finds and returns the k-th node (1-based indexing)
from the given node.
====================================================
*/
node* findNthnode(node* temp, int k) {
    int cnt = 1;
    while (temp != nullptr) {
        if (cnt == k) return temp;
        cnt++;
        temp = temp->next;
    }
    return temp;
}

/*
====================================================
MAIN FUNCTION:
----------------------------------------------------
INTUITION:
1. Find the length of the linked list.
2. Reduce k using k = k % length.
3. Make the linked list circular by connecting
   the last node to the head.
4. Find the new last node at position (length - k).
5. Break the circular link to get the rotated list.
====================================================
*/

node* rotate_k(node* head, int k) {

    // Edge cases
    if (head == nullptr || head->next == nullptr || k == 0)
        return head;

    // Find length and tail
    int len = 1;
    node* tail = head;
    while (tail->next != nullptr) {
        len++;
        tail = tail->next;
    }

    // If rotation is multiple of length, list remains same
    if (k % len == 0)
        return head;

    k = k % len;

    // Make list circular
    tail->next = head;

    // Find new last node
    node* newLastNode = findNthnode(head, len - k);

    // Update head and break the circle
    head = newLastNode->next;
    newLastNode->next = nullptr;

    return head;
}

/*
====================================================
TIME COMPLEXITY:
----------------------------------------------------
O(N)
- Traversing list to find length and rotation point.

SPACE COMPLEXITY:
----------------------------------------------------
O(1)
- No extra space used.
====================================================
*/

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

    int k = 2;
    head = rotate_k(head, k);

    cout << "After rotating by " << k << ": ";
    printList(head);

    return 0;
}
