#include <iostream>
using namespace std;

/*
====================================================
Problem Statement:
----------------------------------------------------
Given the head of a singly linked list, find and
return the middle node of the linked list.

Rules:
- If the number of nodes is odd → return the exact middle.
- If the number of nodes is even → return the second middle.

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
Approach 1: Brute Force (Length Counting)
----------------------------------------------------
Intuition:
- First count the total number of nodes.
- Middle index = length / 2.
- Traverse again to reach the middle node.

Why it works:
- Linked list allows sequential access.
- Two passes give exact middle position.

Time Complexity:  O(n)
Space Complexity: O(1)
====================================================
*/
node* middle_brute(node* head) {
    if (head == nullptr) return nullptr;

    int cnt = 0;
    node* temp = head;

    // Count total nodes
    while (temp != nullptr) {
        cnt++;
        temp = temp->next;
    }

    // Move to middle node
    int mid = cnt / 2;   // 0-based indexing
    temp = head;
    while (mid--) {
        temp = temp->next;
    }

    return temp;
}

/*
====================================================
Approach 2: Optimal (Slow–Fast Pointer)
----------------------------------------------------
Intuition:
- Use two pointers:
  - slow moves 1 step
  - fast moves 2 steps
- When fast reaches the end,
  slow will be at the middle.

Why it works:
- Fast pointer covers list twice as fast.
- When fast finishes, slow is halfway.

Edge Case:
- For even length, this returns the second middle.

Time Complexity:  O(n)
Space Complexity: O(1)
====================================================
*/
node* middle(node* head) {
    if (head == nullptr) return nullptr;

    node* slow = head;
    node* fast = head;

    while (fast != nullptr && fast->next != nullptr) {
        slow = slow->next;
        fast = fast->next->next;
    }

    return slow; // middle node
}

/*
====================================================
Main Function (Testing)
====================================================
*/
int main() {
    node* head = new node(1,
                    new node(2,
                    new node(3,
                    new node(4,
                    new node(5)))));

    node* mid1 = middle_brute(head);
    cout << "Middle (brute): " << mid1->data << endl;

    node* mid2 = middle(head);
    cout << "Middle (optimal): " << mid2->data << endl;

    return 0;
}
