#include <iostream>
#include <map>
using namespace std;

/*
PROBLEM:
---------
Given a linked list where each node has:
1) next pointer → normal linked list next
2) random pointer → can point to any node or NULL

Task: Create a DEEP COPY of the linked list such that:
- All nodes are newly created
- next and random pointers are correctly copied
*/

/*
Node structure:
val    → value of node
next   → pointer to next node
random → pointer to any node in the list (or NULL)
*/
class node {
public:
    int val;
    node* next;
    node* random;

    node(int val) {
        this->val = val;
        next = nullptr;
        random = nullptr;
    }

    node(int val, node* next, node* random) {
        this->val = val;
        this->next = next;
        this->random = random; 
    }
};

/*
===========================
BRUTE FORCE APPROACH
===========================
INTUITION:
-----------
1. Create a copy of every node and store mapping:
   original node → copied node
2. Traverse again and assign:
   - next pointer using map
   - random pointer using map

Uses extra space for map.

TIME COMPLEXITY:  O(n)
SPACE COMPLEXITY: O(n)
*/
node* copy_LL_brute(node* head) {
    node* temp = head;

    // map to store original node -> copied node
    map<node*, node*> mpp;

    // Step 1: Create copy of each node (without links)
    while (temp != nullptr) {
        node* newnode = new node(temp->val);
        mpp[temp] = newnode;
        temp = temp->next;
    }

    // Step 2: Assign next and random pointers
    temp = head;
    while (temp != nullptr) {
        node* copynode = mpp[temp];
        copynode->next = mpp[temp->next];     // map handles NULL safely
        copynode->random = mpp[temp->random]; // map handles NULL safely
        temp = temp->next;
    }

    // return head of copied list
    return mpp[head];
}

/*
===========================
OPTIMIZED APPROACH (O(1) SPACE)
===========================
INTUITION:
-----------
We avoid extra space by modifying the list temporarily.

STEPS:
------
1. Insert copied nodes in between original nodes
   A → B → C
   becomes
   A → A' → B → B' → C → C'

2. Set random pointers of copied nodes using:
   copy->random = original->random->next

3. Separate original and copied lists

TIME COMPLEXITY:  O(n)
SPACE COMPLEXITY: O(1)
*/
node* copy_LL(node* head) {
    if (!head) return nullptr;

    /*
    STEP 1:
    Insert copy nodes after each original node
    */
    node* temp = head;
    while (temp != nullptr) {
        node* copyNode = new node(temp->val);
        copyNode->next = temp->next;
        temp->next = copyNode;
        temp = temp->next->next;
    }

    /*
    STEP 2:
    Assign random pointers to copied nodes
    */
    temp = head;
    while (temp != nullptr) {
        if (temp->random)
            temp->next->random = temp->random->next;
        else
            temp->next->random = nullptr;

        temp = temp->next->next;
    }

    /*
    STEP 3:
    Separate original list and copied list
    */
    temp = head;
    node* copyHead = head->next;

    while (temp != nullptr) {
        node* copyNode = temp->next;

        // restore original list
        temp->next = copyNode->next;

        // fix copied list next pointer
        if (copyNode->next)
            copyNode->next = copyNode->next->next;
        else
            copyNode->next = nullptr;

        temp = temp->next;
    }

    return copyHead;
}

/*
UTILITY FUNCTION:
-----------------
Prints value and random pointer value for each node
*/
void printLL(node* head) {
    while (head) {
        cout << head->val << " -> ";
        if (head->random)
            cout << head->random->val;
        else
            cout << "NULL";
        cout << endl;
        head = head->next;
    }
}

/*
DRIVER CODE
-----------
Creates a linked list:
1 -> 2 -> 3

Random pointers:
1 -> 3
2 -> 1
3 -> 2
*/
int main() {
    node* head = new node(1);
    head->next = new node(2);
    head->next->next = new node(3);

    head->random = head->next->next;       // 1->3
    head->next->random = head;             // 2->1
    head->next->next->random = head->next; // 3->2

    cout << "Original list:\n";
    printLL(head);

    node* copied = copy_LL(head);

    cout << "\nCopied list:\n";
    printLL(copied);

    return 0;
}
