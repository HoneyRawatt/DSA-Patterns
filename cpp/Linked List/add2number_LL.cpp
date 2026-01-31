#include<iostream>
using namespace std;

/*
====================================
Singly Linked List Node
====================================
Intuition:
- Each node stores:
  1) a single digit (0–9)
  2) pointer to the next node
- Numbers are stored in reverse order

Time Complexity:
- Node creation: O(1)

Space Complexity:
- O(1) per node
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
====================================
Add Two Numbers (Linked Lists)
====================================
Intuition:
- Each linked list represents a number in reverse order
  Example:
    2 -> 4 -> 3  represents 342
    5 -> 6 -> 4  represents 465

- Add digits one by one like normal addition:
  digit sum = digit1 + digit2 + carry
- Store (sum % 10) in new node
- Carry = sum / 10

Why dummy node?
- Simplifies list construction
- Avoids special handling for first node

Time Complexity:
- O(max(n, m))
  where n = length of first list
        m = length of second list

Space Complexity:
- O(max(n, m)) for result list
*/
node* addtwonumbers(node* head1, node* head2) {
    node* temp1 = head1;
    node* temp2 = head2;

    node* dummynode = new node(-1); // dummy head
    node* curr = dummynode;

    int carry = 0;

    while (temp1 != NULL || temp2 != NULL) {
        int sum = carry;

        if (temp1) sum += temp1->data;
        if (temp2) sum += temp2->data;

        node* newnode = new node(sum % 10);
        carry = sum / 10;

        curr->next = newnode;
        curr = curr->next;

        if (temp1) temp1 = temp1->next;
        if (temp2) temp2 = temp2->next;
    }

    // If carry remains after last addition
    if (carry) {
        curr->next = new node(carry);
    }

    return dummynode->next; // skip dummy node
}

/*
====================================
Insert Node at End (Helper Function)
====================================
Intuition:
- Traverse till last node
- Attach new node at the end

Time Complexity:
- O(n)

Space Complexity:
- O(1)
*/
void insert(node*& head, int val) {
    if (!head) {
        head = new node(val);
        return;
    }

    node* temp = head;
    while (temp->next) temp = temp->next;
    temp->next = new node(val);
}

/*
====================================
Print Linked List (Helper Function)
====================================
Time Complexity:
- O(n)

Space Complexity:
- O(1)
*/
void printlist(node* head) {
    while (head) {
        cout << head->data;
        if (head->next) cout << " -> ";
        head = head->next;
    }
    cout << endl;
}

/*
====================================
Main Function (Testing)
====================================
*/
int main() {
    node* head1 = nullptr;
    node* head2 = nullptr;

    /*
    First number: 342
    Stored as: 2 -> 4 -> 3
    */
    insert(head1, 2);
    insert(head1, 4);
    insert(head1, 3);

    /*
    Second number: 465
    Stored as: 5 -> 6 -> 4
    */
    insert(head2, 5);
    insert(head2, 6);
    insert(head2, 4);

    cout << "First number: ";
    printlist(head1);

    cout << "Second number: ";
    printlist(head2);

    node* result = addtwonumbers(head1, head2);

    /*
    Expected Result:
    342 + 465 = 807
    Stored as: 7 -> 0 -> 8
    */
    cout << "Sum: ";
    printlist(result);

    return 0;
}
