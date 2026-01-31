#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

/*
=========================================================
PROBLEM STATEMENT
=========================================================
You are given a multilevel linked list where:
- Each node has two pointers:
    1. next  -> points to the next node in the main list
    2. child -> points to a sorted linked list

Each individual list (both main list and child lists)
is already sorted.

Your task is to FLATTEN the multilevel linked list
into a single sorted linked list using ONLY the
child pointers.

The final flattened list should be sorted.
=========================================================
*/

// Node definition for multilevel linked list
class node {
public:
    int val;
    node* next;
    node* child;

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
---------------------------------------------------------
Helper Function:
Convert array to linked list using ONLY child pointers
---------------------------------------------------------
*/
node* convertArrtoLL(vector<int>& arr) {
    if (arr.size() == 0) return nullptr;

    node* head = new node(arr[0]);
    node* temp = head;

    for (int i = 1; i < arr.size(); i++) {
        node* newnode = new node(arr[i]);
        temp->child = newnode;
        temp = temp->child;
    }
    return head;
}

/*
=========================================================
APPROACH 1: BRUTE FORCE
=========================================================
INTUITION:
- Traverse the entire multilevel linked list
- Store all node values into an array
- Sort the array
- Convert the sorted array back into a linked list

WHY IT WORKS:
- Sorting guarantees correct order
- Child pointers are rebuilt sequentially

TIME COMPLEXITY:
- Let total nodes = N
- Traversal: O(N)
- Sorting: O(N log N)
=> Overall: O(N log N)

SPACE COMPLEXITY:
- Extra array of size N
=> O(N)
=========================================================
*/
node* flatten_brute(node* head) {
    vector<int> arr;

    node* temp = head;
    while (temp != nullptr) {
        node* t2 = temp;
        while (t2 != nullptr) {
            arr.push_back(t2->val);
            t2 = t2->child;
        }
        temp = temp->next;
    }

    sort(arr.begin(), arr.end());
    head = convertArrtoLL(arr);
    return head;
}

/*
---------------------------------------------------------
Helper Function:
Merge two sorted linked lists using child pointers
(Same logic as merging two sorted lists)
---------------------------------------------------------
*/
node* merge2LL(node* list1, node* list2) {
    node* dummynode = new node(-1);
    node* res = dummynode;

    while (list1 != nullptr && list2 != nullptr) {
        if (list1->val < list2->val) {
            res->child = list1;
            res = list1;
            list1 = list1->child;
        } else {
            res->child = list2;
            res = list2;
            list2 = list2->child;
        }
        // next pointer is not needed in flattened list
        res->next = nullptr;
    }

    if (list1) res->child = list1;
    else res->child = list2;

    return dummynode->child;
}

/*
=========================================================
APPROACH 2: OPTIMAL (RECURSION + MERGE)
=========================================================
INTUITION:
- Treat each "next" node as a separate sorted list
- Recursively flatten the list to the right
- Merge current list with the already flattened list

WHY THIS WORKS:
- Each child list is already sorted
- Recursive flatten ensures right side is flattened
- Merge two sorted lists at each step

This is similar to merging K sorted linked lists
using divide-and-conquer.

TIME COMPLEXITY:
- Let total nodes = N
- Each merge takes linear time
=> Overall: O(N)

SPACE COMPLEXITY:
- Recursive call stack
=> O(depth of next pointers)
=========================================================
*/
node* flatten(node* head) {
    // Base case: empty list or single list
    if (head == nullptr || head->next == nullptr)
        return head;

    // Recursively flatten the rest of the list
    node* mergehead = flatten(head->next);

    // Merge current list with flattened list
    return merge2LL(head, mergehead);
}

/*
---------------------------------------------------------
Helper:
Print flattened linked list using child pointers
---------------------------------------------------------
*/
void printLL(node* head) {
    while (head != nullptr) {
        cout << head->val << " ";
        head = head->child;
    }
    cout << endl;
}

int main() {
    /*
    Constructing the multilevel linked list:

    Main list:
    5 -> 10 -> 19 -> 28

    Child lists:
    5  -> 7 -> 8 -> 30
    10 -> 20
    19 -> 22 -> 50
    28 -> 35 -> 40 -> 45
    */

    node* head = new node(5);
    head->next = new node(10);
    head->next->next = new node(19);
    head->next->next->next = new node(28);

    head->child = new node(7);
    head->child->child = new node(8);
    head->child->child->child = new node(30);

    head->next->child = new node(20);

    head->next->next->child = new node(22);
    head->next->next->child->child = new node(50);

    head->next->next->next->child = new node(35);
    head->next->next->next->child->child = new node(40);
    head->next->next->next->child->child->child = new node(45);

    cout << "Flattened Linked List (Optimal):\n";
    node* flatHead = flatten(head);
    printLL(flatHead);

    return 0;
}
