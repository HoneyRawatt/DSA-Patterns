#include <iostream>
#include <map>
using namespace std;

/*
====================================================
Node structure for singly linked list
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
Brute Force Approach (Using Map)
----------------------------------------------------
Intuition:
- Traverse the linked list.
- Store each visited node in a map.
- If a node is encountered again, it is the
  starting point of the loop.

Time Complexity: O(n)
Space Complexity: O(n)
====================================================
*/
node* starting_node_loop_brute(node* head) {
    map<node*, int> mpp;
    node* temp = head;

    while (temp != nullptr) {
        if (mpp.find(temp) != mpp.end())
            return temp;   // starting node of loop

        mpp[temp] = 1;
        temp = temp->next;
    }
    return nullptr; // no loop
}

/*
====================================================
Optimized Approach (Floyd’s Cycle Detection)
----------------------------------------------------
Intuition:
1. Use slow & fast pointers.
2. If they meet, a loop exists.
3. Move slow to head.
4. Move both one step at a time.
5. The meeting point is the start of the loop.

Time Complexity: O(n)
Space Complexity: O(1)
====================================================
*/
node* starting_node_loop(node* head) {
    node* slow = head;
    node* fast = head;

    while (fast != nullptr && fast->next != nullptr) {
        slow = slow->next;
        fast = fast->next->next;

        if (slow == fast) {   // loop detected
            slow = head;
            while (slow != fast) {
                slow = slow->next;
                fast = fast->next;
            }
            return slow; // starting node of loop
        }
    }
    return nullptr; // no loop
}

/*
====================================================
Driver Code
====================================================
*/
int main() {
    // Create linked list: 1 -> 2 -> 3 -> 4 -> 5
    node* head = new node(1);
    head->next = new node(2);
    head->next->next = new node(3);
    head->next->next->next = new node(4);
    head->next->next->next->next = new node(5);

    // Create loop: 5 -> 3
    head->next->next->next->next->next = head->next->next;

    node* brute = starting_node_loop_brute(head);
    if (brute)
        cout << "Brute: Loop starts at node " << brute->data << endl;
    else
        cout << "Brute: No loop found" << endl;

    node* optimal = starting_node_loop(head);
    if (optimal)
        cout << "Optimized: Loop starts at node " << optimal->data << endl;
    else
        cout << "Optimized: No loop found" << endl;

    return 0;
}
