#include <iostream>
using namespace std;

/*
====================================================
Problem Statement:
----------------------------------------------------
Given the head of a singly linked list, delete the
middle node of the linked list and return the head
of the modified list.

If the list has only one node, return NULL.

For even length lists, delete the second middle node.
====================================================
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
====================================================
Brute Force Approach
----------------------------------------------------
Intuition:
1. Find the total number of nodes in the list.
2. The middle index is count / 2.
3. Traverse again to the node just before the middle.
4. Delete the middle node by changing pointers.

Why it works:
Knowing the length allows direct access to the
middle node.

Time Complexity:
- First traversal: O(n)
- Second traversal: O(n)
Total: O(n)

Space Complexity:
- O(1) (no extra data structures used)
====================================================
*/
node* delete_middle_brute(node* head) {
    if (head == nullptr || head->next == nullptr)
        return nullptr;

    // Step 1: Count total nodes
    int cnt = 0;
    node* temp = head;
    while (temp != nullptr) {
        cnt++;
        temp = temp->next;
    }

    // Step 2: Find middle index
    int mid = cnt / 2;

    // Step 3: Traverse to node before middle
    temp = head;
    while (temp != nullptr) {
        mid--;
        if (mid == 0) {
            node* middle = temp->next;
            temp->next = temp->next->next;
            delete middle;
            break;
        }
        temp = temp->next;   
    }
    return head;
}

/*
====================================================
Optimized Approach (Slow & Fast Pointer)
----------------------------------------------------
Intuition:
- Use two pointers:
  slow moves 1 step
  fast moves 2 steps
- When fast reaches the end, slow is just before
  the middle node.

Why it works:
Fast pointer skips nodes, so slow pointer reaches
the middle position naturally.

Time Complexity:
- O(n) (single traversal)

Space Complexity:
- O(1)
====================================================
*/
node* delete_middle(node* head) {
    if (head == nullptr || head->next == nullptr)
        return nullptr;

    node* slow = head;
    node* fast = head;

    // Move fast ahead initially
    fast = fast->next->next;

    // Traverse until fast reaches end
    while (fast != nullptr && fast->next != nullptr) {
        slow = slow->next;
        fast = fast->next->next;
    }

    // Delete middle node
    node* middle = slow->next;
    slow->next = slow->next->next;
    delete middle;

    return head;
}

/*
Utility Function:
Prints the linked list
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
Main Function (Testing)
====================================================
*/
int main() {
    // Create linked list: 1 -> 2 -> 3 -> 4 -> 5
    node* head1 = new node(1, new node(2, new node(3, new node(4, new node(5)))));
    node* head2 = new node(1, new node(2, new node(3, new node(4, new node(5)))));

    cout << "Original List: ";
    printList(head1);

    head1 = delete_middle_brute(head1);
    cout << "After delete_middle_brute
