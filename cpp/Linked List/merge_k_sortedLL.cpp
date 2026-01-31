#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

/*
=========================================
PROBLEM STATEMENT
=========================================
You are given K sorted singly linked lists.
Each linked list is sorted in ascending order.

Your task is to merge all these K sorted
linked lists into one single sorted
linked list and return its head.

This is a classic problem often asked in
interviews (LeetCode: Merge K Sorted Lists).
=========================================
*/

// Definition of a singly linked list node
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
-------------------------------------------------
Helper Function:
Convert a sorted array into a linked list
-------------------------------------------------
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
=================================================
APPROACH 1: BRUTE FORCE
=================================================
INTUITION:
- Traverse all K linked lists
- Store every element into a single array
- Sort the array
- Convert the sorted array back into a linked list

WHY IT WORKS:
- Sorting puts elements in correct order
- Linked list is rebuilt from sorted data

TIME COMPLEXITY:
- Let total nodes = N
- Collect elements: O(N)
- Sorting: O(N log N)
- Building list: O(N)
=> Overall: O(N log N)

SPACE COMPLEXITY:
- Extra array of size N
=> O(N)
=================================================
*/
node* merge_k_sorted_ll_brute(vector<node*> lists) {
    vector<int> arr;

    // Collect all elements from all lists
    for (int i = 0; i < lists.size(); i++) {
        node* temp = lists[i];
        while (temp != nullptr) {
            arr.push_back(temp->data);
            temp = temp->next;
        }
    }

    // Sort the collected elements
    sort(arr.begin(), arr.end());

    // Convert sorted array to linked list
    return convertArrToList(arr);
}

/*
-------------------------------------------------
Helper:
Merge two sorted linked lists
(Same logic as merge step of Merge Sort)
-------------------------------------------------
*/
node* merge_two_sorted_ll(node* head1, node* head2) {
    node* t1 = head1;
    node* t2 = head2;

    // Dummy node to simplify pointer handling
    node* dnode = new node(-1);
    node* temp = dnode;

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

    return dnode->next;
}

/*
=================================================
APPROACH 2: BETTER (ITERATIVE MERGING)
=================================================
INTUITION:
- Merge lists one by one
- First merge list[0] and list[1]
- Then merge the result with list[2], and so on

WHY BETTER THAN BRUTE:
- No extra array
- Directly merges linked lists

TIME COMPLEXITY:
- Each merge takes O(N)
- Performed K times
=> O(N * K) in worst case

SPACE COMPLEXITY:
- Only pointers used
=> O(1) auxiliary space
=================================================
*/
node* merge_k_sorted_ll_better(vector<node*> lists) {
    if (lists.empty()) return nullptr;

    node* head = lists[0];
    for (int i = 1; i < lists.size(); i++) {
        head = merge_two_sorted_ll(head, lists[i]);
    }
    return head;
}

/*
=================================================
APPROACH 3: OPTIMAL (MIN HEAP / PRIORITY QUEUE)
=================================================
INTUITION:
- At any time, we only need the smallest
  element among the K lists
- Use a min-heap to always extract the
  smallest node
- Push the next node of the extracted list
  into the heap

WHY OPTIMAL:
- Heap size never exceeds K
- Each node is pushed and popped exactly once

TIME COMPLEXITY:
- N total nodes
- Heap operations take O(log K)
=> O(N log K)

SPACE COMPLEXITY:
- Heap stores at most K elements
=> O(K)
=================================================
*/
node* merge_k_sorted_ll(vector<node*> lists) {
    priority_queue<
        pair<int, node*>,               // {value, node}
        vector<pair<int, node*>>,
        greater<pair<int, node*>>
    > pq;

    // Push first node of each list into heap
    for (int i = 0; i < lists.size(); i++) {
        if (lists[i]) {
            pq.push({lists[i]->data, lists[i]});
        }
    }

    node* dummynode = new node(-1);
    node* temp = dummynode;

    // Extract minimum and push next element
    while (!pq.empty()) {
        auto it = pq.top();
        pq.pop();

        temp->next = it.second;
        temp = temp->next;

        if (it.second->next) {
            pq.push({it.second->next->data, it.second->next});
        }
    }

    return dummynode->next;
}

/*
-------------------------------------------------
Helper: Print linked list
-------------------------------------------------
*/
void printList(node* head) {
    while (head) {
        cout << head->data << " ";
        head = head->next;
    }
    cout << endl;
}

/*
-------------------------------------------------
Helper: Insert node at the end
-------------------------------------------------
*/
node* insertEnd(node* head, int val) {
    if (!head) return new node(val);

    node* temp = head;
    while (temp->next) temp = temp->next;
    temp->next = new node(val);

    return head;
}

int main() {
    vector<node*> lists(3, nullptr);

    // List 1: 1 -> 4 -> 7
    lists[0] = insertEnd(lists[0], 1);
    lists[0] = insertEnd(lists[0], 4);
    lists[0] = insertEnd(lists[0], 7);

    // List 2: 2 -> 5 -> 8
    lists[1] = insertEnd(lists[1], 2);
    lists[1] = insertEnd(lists[1], 5);
    lists[1] = insertEnd(lists[1], 8);

    // List 3: 3 -> 6 -> 9
    lists[2] = insertEnd(lists[2], 3);
    lists[2] = insertEnd(lists[2], 6);
    lists[2] = insertEnd(lists[2], 9);

    cout << "Brute Force Merge: ";
    printList(merge_k_sorted_ll_brute(lists));

    cout << "Better Merge: ";
    printList(merge_k_sorted_ll_better(lists));

    cout << "Optimal Merge (Heap): ";
    printList(merge_k_sorted_ll(lists));

    return 0;
}
