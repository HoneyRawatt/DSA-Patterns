#include <iostream>
#include <unordered_set>
using namespace std;

/*
====================================================
Problem Statement:
----------------------------------------------------
Given the heads of two singly linked lists, determine
the node at which the two linked lists intersect.

If the two linked lists have no intersection,
return NULL.

NOTE:
- Intersection is based on reference (address),
  not on value.
- After intersection point, both lists share
  the same nodes.
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
Approach 1: Brute Force using HashSet
----------------------------------------------------
Intuition:
- Store all nodes of the first linked list in a hash set.
- Traverse the second linked list.
- The first node found in the set is the intersection.

Why it works:
- HashSet allows O(1) lookup.
- Intersection node is the first common memory address.

Time Complexity:  O(n + m)
Space Complexity: O(n)
====================================================
*/
node* intersection_point_brute(node* head1, node* head2) {
    unordered_set<node*> st;
    node* temp = head1;

    // Store nodes of first list
    while (temp != nullptr) {
        st.insert(temp);
        temp = temp->next;
    }

    // Check nodes of second list
    temp = head2;
    while (temp != nullptr) {
        if (st.find(temp) != st.end())
            return temp;   // intersection found
        temp = temp->next;
    }

    return nullptr; // no intersection
}

/*
====================================================
Helper Function for Better Approach
----------------------------------------------------
Purpose:
- Moves the longer list forward by 'd' nodes
  so both lists align at same distance from end.
====================================================
*/
node* collisionPoint(node* t1, node* t2, int d) {

    // Move t2 ahead by d nodes
    while (d--) {
        if (t2 == nullptr) return nullptr;
        t2 = t2->next;
    }

    // Move both pointers until they meet
    while (t1 != nullptr && t2 != nullptr && t1 != t2) {
        t1 = t1->next;
        t2 = t2->next;
    }

    return t1; // intersection node or nullptr
}

/*
====================================================
Approach 2: Length Difference Method
----------------------------------------------------
Intuition:
- Find lengths of both lists.
- Move pointer of longer list ahead by the
  length difference.
- Traverse both lists together until nodes match.

Why it works:
- Aligns both lists so they reach intersection
  at the same time.

Time Complexity:  O(n + m)
Space Complexity: O(1)
====================================================
*/
node* intersection_point_better(node* head1, node* head2) {
    node *t1 = head1, *t2 = head2;
    int n1 = 0, n2 = 0;

    // Calculate length of first list
    while (t1 != nullptr) {
        n1++;
        t1 = t1->next;
    }

    // Calculate length of second list
    while (t2 != nullptr) {
        n2++;
        t2 = t2->next;
    }

    // Move longer list ahead
    if (n1 < n2)
        return collisionPoint(head1, head2, n2 - n1);
    else
        return collisionPoint(head2, head1, n1 - n2);
}

/*
====================================================
Approach 3: Optimal Two Pointer Method
----------------------------------------------------
Intuition:
- Traverse both lists with two pointers.
- When a pointer reaches end, redirect it to
  the head of the other list.
- If there is an intersection, both pointers
  will meet at the intersection node.

Why it works:
- Both pointers travel exactly (n + m) distance.
- Automatically balances length difference.

Time Complexity:  O(n + m)
Space Complexity: O(1)
====================================================
*/
node* intersection_point(node* head1, node* head2) {
    if (head1 == nullptr || head2 == nullptr)
        return nullptr;

    node *t1 = head1, *t2 = head2;

    // Continue until both pointers meet
    while (t1 != t2) {
        t1 = (t1 == nullptr) ? head2 : t1->next;
        t2 = (t2 == nullptr) ? head1 : t2->next;
    }

    return t1; // intersection node or nullptr
}
