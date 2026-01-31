/*
PROBLEM STATEMENT:
You are given two sorted singly linked lists.
Your task is to merge both linked lists into a single sorted linked list
and return the head of the merged list.

Both input linked lists are already sorted in ascending order.
*/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

/*
Definition of a singly linked list node
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
Helper Function:
Insert a new node with given value at the end of the linked list
*/
node* insertEnd(node* head, int val) {
    if (head == nullptr) return new node(val);

    node* temp = head;
    while (temp->next != nullptr)
        temp = temp->next;

    temp->next = new node(val);
    return head;
}

/*
Helper Function:
Print all elements of the linked list
*/
void printList(node* head) {
    while (head != nullptr) {
        cout << head->data << " ";
        head = head->next;
    }
    cout << endl;
}

/*
Helper Function:
Convert an array into a linked list
*/
node* convertArrToList(vector<int>& arr) {
    if (arr.empty()) return nullptr;

    node* head = new node(arr[0]);
    node* temp = head;

    for (int i = 1; i < arr.size(); i++) {
        temp->next = new node(arr[i]);
        temp = temp->next;
    }
    return head;
}

/*
---------------- BRUTE FORCE APPROACH ----------------

INTUITION:
Store all elements of both linked lists into an array,
sort the array, and then create a new sorted linked list.

STEPS:
1. Traverse first list and store elements
2. Traverse second list and store elements
3. Sort the array
4. Convert array back to linked list

TIME COMPLEXITY:
O((N + M) log(N + M))

SPACE COMPLEXITY:
O(N + M)
*/
node* merge_two_sorted_ll_brute(node* head1, node* head2) {
    vector<int> arr;

    // Store elements of first list
    node* t1 = head1;
    while (t1 != nullptr) {
        arr.push_back(t1->data);
        t1 = t1->next;
    }

    // Store elements of second list
    node* t2 = head2;
    while (t2 != nullptr) {
        arr.push_back(t2->data);
        t2 = t2->next;
    }

    // Sort combined elements
    sort(arr.begin(), arr.end());

    // Convert sorted array to linked list
    return convertArrToList(arr);
}

/*
---------------- OPTIMAL APPROACH (Two Pointer) ----------------

INTUITION:
Since both linked lists are already sorted,
we can merge them in-place using two pointers,
similar to merging two sorted arrays.

STEPS:
1. Use two pointers for both lists
2. Compare current nodes
3. Attach the smaller node to the merged list
4. Move the pointer forward
5. Attach remaining nodes at the end

TIME COMPLEXITY:
O(N + M)

SPACE COMPLEXITY:
O(1)  (No extra data structure used)
*/
node* merge_two_sorted_ll(node* head1, node* head2) {
    node* t1 = head1;
    node* t2 = head2;

    // Dummy node to simplify merging logic
    node* dnode = new node(-1);
    node* temp = dnode;

    // Merge while both lists have nodes
    while (t1 && t2) {
        if (t1->data < t2->data) {
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

    // Return merged list head
    return dnode->next;
}

/*
Driver Code
*/
int main() {
    node* head1 = nullptr;
    node* head2 = nullptr;

    // First sorted list: 1 -> 3 -> 5
    head1 = insertEnd(head1, 1);
    head1 = insertEnd(head1, 3);
    head1 = insertEnd(head1, 5);

    // Second sorted list: 2 -> 4 -> 6
    head2 = insertEnd(head2, 2);
    head2 = insertEnd(head2, 4);
    head2 = insertEnd(head2, 6);

    cout << "List 1: ";
    printList(head1);

    cout << "List 2: ";
    printList(head2);

    // Brute force merge
    node* merged = merge_two_sorted_ll_brute(head1, head2);
    cout << "Merged List (Brute Force): ";
    printList(merged);

    // Optimal merge
    merged = merge_two_sorted_ll(head1, head2);
    cout << "Merged List (Optimal): ";
    printList(merged);

    return 0;
}
