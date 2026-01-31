#include <iostream>
#include <map>
using namespace std;

/*
====================================================
Problem Statement:
----------------------------------------------------
Given the head of a singly linked list, determine
whether the linked list contains a loop (cycle).

A loop exists if some node in the list can be
reached again by continuously following the next
pointer.

Return:
- true  → if a loop is present
- false → if no loop is present
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
Approach 1: Brute Force using Map
----------------------------------------------------
Intuition:
- Traverse the linked list.
- Store every visited node’s address in a map.
- If a node is visited again, a loop exists.

Why it works:
- In a loop, the same node will be revisited.
- Map allows us to track visited nodes.

Time Complexity:  O(n)
Space Complexity: O(n)
====================================================
*/
bool detect_loop_brute(node* head) {
    map<node*, int> mpp;
    node* temp = head;

    while (temp != nullptr) {
        // If node already visited, loop exists
        if (mpp.find(temp) != mpp.end()) {
            return true;
        }
        mpp[temp] = 1;   // mark node as visited
        temp = temp->next;
    }

    return false; // no loop found
}

/*
====================================================
Approach 2: Optimal – Floyd’s Cycle Detection
----------------------------------------------------
(Intuition: Slow & Fast Pointers)

Intuition:
- Use two pointers:
  - slow moves 1 step at a time
  - fast moves 2 steps at a time
- If there is a loop, fast will eventually
  meet slow inside the loop.

Why it works:
- Fast pointer laps slow pointer in a cycle.
- If no cycle exists, fast reaches NULL.

Time Complexity:  O(n)
Space Complexity: O(1)
====================================================
*/
bool detect_loop(node* head) {
    node* slow = head;
    node* fast = head;

    while (fast != nullptr && fast->next != nullptr) {
        slow = slow->next;           // move by 1
        fast = fast->next->next;     // move by 2

        if (slow == fast)
            return true;             // loop detected
    }

    return false; // no loop
}

/*
====================================================
Main Function (Testing)
====================================================
*/
int main() {
    node* head = new node(1);
    head->next = new node(2);
    head->next->next = new node(3);
    head->next->next->next = new node(4);

    // Creating a loop: last node points to second node
    head->next->next->next->next = head->next;

    cout << "Brute: "
         << (detect_loop_brute(head) ? "Loop found" : "No loop")
         << endl;

    cout << "Optimal: "
         << (detect_loop(head) ? "Loop found" : "No loop")
         << endl;

    return 0;
}
