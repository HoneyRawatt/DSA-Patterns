#include <iostream>
#include <map>
using namespace std;

/*
====================================================
Problem Statement:
----------------------------------------------------
Given a singly linked list that may contain a loop,
find the length of the loop.

If no loop exists, return 0.
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
- Store each visited node with a timestamp.
- If a node is visited again, a loop exists.
- Loop length = current_time - first_visit_time.

Why it works:
- In a loop, nodes repeat.
- The difference in visit times gives the loop length.

Time Complexity:  O(n)
Space Complexity: O(n)
====================================================
*/
int length_loop_brute(node* head) {
    map<node*, int> mpp;
    node* temp = head;
    int timer = 1;

    while (temp != nullptr) {
        // If node already visited, loop detected
        if (mpp.find(temp) != mpp.end()) {
            int value = mpp[temp];
            return (timer - value); // loop length
        }

        mpp[temp] = timer;  // store visit time
        timer++;
        temp = temp->next;
    }

    return 0; // no loop
}

/*
====================================================
Helper Function (for Floyd’s Algorithm)
----------------------------------------------------
Purpose:
- Counts the number of nodes in the loop once
  slow and fast pointers meet.
====================================================
*/
int findlength(node* slow, node* fast) {
    int cnt = 1;
    fast = fast->next;

    while (fast != slow) {
        cnt++;
        fast = fast->next;
    }

    return cnt;
}

/*
====================================================
Approach 2: Optimal – Floyd’s Cycle Detection
----------------------------------------------------
Intuition:
- Use slow & fast pointers to detect a loop.
- Once slow == fast, a loop exists.
- Traverse the loop to count its length.

Why it works:
- Fast pointer laps slow pointer inside a cycle.

Time Complexity:  O(n)
Space Complexity: O(1)
====================================================
*/
int length_loop(node* head) {
    node* slow = head;
    node* fast = head;

    while (fast != nullptr && fast->next != nullptr) {
        slow = slow->next;          // move by 1
        fast = fast->next->next;   // move by 2

        if (slow == fast)
            return findlength(slow, fast); // loop length
    }

    return 0; // no loop
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

    // Creating a loop: 2 → 3 → 4 → 2
    head->next->next->next->next = head->next;

    cout << "Brute force loop length: "
         << length_loop_brute(head) << endl;

    cout << "Floyd loop length: "
         << length_loop(head) << endl;

    return 0;
}
