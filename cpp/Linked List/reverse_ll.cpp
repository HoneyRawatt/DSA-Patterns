#include<iostream>
#include<stack>
using namespace std;

/*
------------------------------------------------------------
Problem Statement:
------------------------------------------------------------
Given the head of a singly linked list, reverse the linked list
and return the head of the reversed list.

Multiple approaches can be used:
1. Using extra memory (stack)
2. Iterative in-place reversal
3. Recursive reversal
------------------------------------------------------------
*/

class node {
public:
    int data;      // Value stored in node
    node* next;    // Pointer to next node

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
------------------------------------------------------------
Brute Force Approach (Using Stack)
------------------------------------------------------------
Intuition:
- Traverse the list and push all node values into a stack.
- Traverse the list again and pop values from the stack,
  replacing the node data to reverse the list.

Note: This reverses the list values, not the links.
------------------------------------------------------------
*/
node* reverse_brute(node* head) {
    if (!head) return head;

    stack<int> st;
    node* temp = head;

    // Push all values into stack
    while (temp != NULL) {
        st.push(temp->data);
        temp = temp->next;
    }

    // Pop values and overwrite nodes
    temp = head;
    while (temp != NULL) {
        temp->data = st.top();
        st.pop();
        temp = temp->next;
    }

    return head;
}

/*
------------------------------------------------------------
Iterative In-place Approach
------------------------------------------------------------
Intuition:
- Reverse the links one by one using three pointers:
  prev, curr, front.
- At the end, prev points to the new head.
------------------------------------------------------------
*/
node* reverse(node* head) {
    node* prev = nullptr;
    node* curr = head;
    node* front = nullptr;

    while (curr != nullptr) {
        front = curr->next;   // save next node
        curr->next = prev;    // reverse current link
        prev = curr;          // move prev forward
        curr = front;         // move curr forward
    }

    return prev; // new head
}

/*
------------------------------------------------------------
Recursive Approach
------------------------------------------------------------
Intuition:
- Recursively reverse the sublist starting from head->next.
- Adjust pointers such that the next node points back to head.
- Base case: head is null or single node.
------------------------------------------------------------
*/
node* reverse_recursion(node* head) {
    if (head == NULL || head->next == NULL) return head;

    node* newhead = reverse_recursion(head->next);
    node* front = head->next;
    front->next = head;
    head->next = nullptr;

    return newhead;
}

/*
------------------------------------------------------------
Utility function to print linked list
------------------------------------------------------------
*/
void printList(node* head) {
    while (head != NULL) {
        cout << head->data << " ";
        head = head->next;
    }
    cout << endl;
}

/*
------------------------------------------------------------
Driver Code
------------------------------------------------------------
*/
int main() {
    node* head = new node(1, new node(2, new node(3, new node(4, new node(5)))));

    cout << "Original list: ";
    printList(head);

    // Brute force using stack
    head = reverse_brute(head);
    cout << "Reversed (Brute force): ";
    printList(head);

    // Iterative in-place reversal
    head = reverse(head);
    cout << "Reversed (Iterative): ";
    printList(head);

    // Recursive reversal
    head = reverse_recursion(head);
    cout << "Reversed (Recursive): ";
    printList(head);

    return 0;
}

/*
------------------------------------------------------------
Time & Space Complexity:
------------------------------------------------------------

1. Brute Force (Stack):
   - Time Complexity: O(N)
   - Space Complexity: O(N)  // stack stores all node values

2. Iterative In-place:
   - Time Complexity: O(N)
   - Space Complexity: O(1)

3. Recursive:
   - Time Complexity: O(N)
   - Space Complexity: O(N) // recursion stack
------------------------------------------------------------
*/
