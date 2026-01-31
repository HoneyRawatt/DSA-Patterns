#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

/*
=========================================================
PROBLEM STATEMENT
=========================================================
You are given the head of a singly linked list.
Your task is to sort the linked list in ascending order
and return the head of the sorted list.

This problem is commonly asked in interviews and is
equivalent to:
- LeetCode: Sort List
- GFG: Sort a linked list
=========================================================
*/

// Definition of linked list node
class node {
public:
    int val;
    node* next;
    node* child; // (not used here, but kept for consistency)

    node(int val) {
        this->val = val;
        next = nullptr;
        child = nullptr;
    }

    node(int val, node* next, node* child) {
        this->val = val;
        this->next = next;
        this->child = child; 
    }
};

/*
=========================================================
APPROACH 1: BRUTE FORCE (USING ARRAY)
=========================================================
INTUITION:
- Traverse the linked list and store all values in an array
- Sort the array
- Traverse the linked list again and overwrite values
  with sorted values

WHY IT WORKS:
- Sorting the array ensures correct order
- We reuse the existing linked list nodes

TIME COMPLEXITY:
- Traversal: O(N)
- Sorting: O(N log N)
- Rewrite values: O(N)
=> Overall: O(N log N)

SPACE COMPLEXITY:
- Extra array of size N
=> O(N)
=========================================================
*/
node* sort_LL_brute(node* head) {
    vector<int> arr;
    node* temp = head;

    // Store linked list values in array
    while (temp != nullptr) {
        arr.push_back(temp->val);
        temp = temp->next;
    }

    // Sort the array
    sort(arr.begin(), arr.end());

    // Put sorted values back into linked list
    int i = 0;
    temp = head;
    while (temp != nullptr) {
        temp->val = arr[i++];
        temp = temp->next;
    }
    return head;
}

/*
---------------------------------------------------------
Helper Function:
Merge two sorted linked lists
(Same logic as merge step of merge sort)
---------------------------------------------------------
*/
node* merge(node* head1, node* head2) {
    node* t1 = head1;
    node* t2 = head2;

    node* dummy = new node(-1);
    node* temp = dummy;

    while (t1 && t2) {
        if (t1->val < t2->val) {
            temp->next = t1;
            temp = t1;
            t1 = t1->next;
        } else {
            temp->next = t2;
            temp = t2;
            t2 = t2->next;
        }
    }

    // Attach remaining nodes
    if (t1) temp->next = t1;
    else temp->next = t2;

    return dummy->next;
}

/*
---------------------------------------------------------
Helper Function:
Find the middle of a linked list
(using slow & fast pointer technique)
---------------------------------------------------------
*/
node* findmiddle(node* head) {
    node* slow = head;
    node* fast = head;

    // fast moves 2 steps, slow moves 1 step
    while (fast->next != nullptr && fast->next->next != nullptr) {
        slow = slow->next;
        fast = fast->next->next;
    }

    // slow will point to middle
    return slow;
}

/*
=========================================================
APPROACH 2: OPTIMAL (MERGE SORT ON LINKED LIST)
=========================================================
INTUITION:
- Linked lists are ideal for merge sort
- No random access required
- Splitting and merging can be done using pointers

STEPS:
1. Find the middle of the list
2. Split the list into two halves
3. Recursively sort both halves
4. Merge the two sorted halves

TIME COMPLEXITY:
- Each level does O(N) merging
- Depth of recursion = log N
=> O(N log N)

SPACE COMPLEXITY:
- Recursive stack space
=> O(log N)
=========================================================
*/
node* merge_sort(node* head) {
    // Base case: empty list or single node
    if (head == nullptr || head->next == nullptr)
        return head;

    // Find middle and split
    node* middle = findmiddle(head);
    node* righthead = middle->next;
    middle->next = nullptr;

    // Recursively sort left and right halves
    node* lefthead = merge_sort(head);
    righthead = merge_sort(righthead);

    // Merge sorted halves
    return merge(lefthead, righthead);
}

/*
---------------------------------------------------------
Utility Function:
Print linked list
---------------------------------------------------------
*/
void printLL(node* head) {
    while (head) {
        cout << head->val << " ";
        head = head->next;
    }
    cout << endl;
}

/*
---------------------------------------------------------
Main Function (Test Case)
---------------------------------------------------------
*/
int main() {
    // Create unsorted linked list: 4 -> 2 -> 1 -> 3
    node* head = new node(4);
    head->next = new node(2);
    head->next->next = new node(1);
    head->next->next->next = new node(3);

    cout << "Original list: ";
    printLL(head);

    // Sort using merge sort
    head = merge_sort(head);

    cout << "Sorted list: ";
    printLL(head);

    return 0;
}
