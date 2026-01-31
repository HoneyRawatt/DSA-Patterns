#include<iostream>
#include<vector>
using namespace std;

/*
====================================
Doubly Linked List Node
====================================
Intuition:
- Each node stores:
  1) data
  2) pointer to previous node
  3) pointer to next node
- Allows traversal in both directions

Time Complexity:
- Node creation: O(1)

Space Complexity:
- O(1) per node
*/
class node {
public:
    int data;
    node* prev;
    node* next;

    node(int val, node* next, node* prev) {
        data = val;
        this->prev = prev;
        this->next = next;
    }

    node(int val) {
        data = val;
        next = nullptr;
        prev = nullptr;
    }
};

/*
====================================
Convert Array to Doubly Linked List
====================================
Intuition:
- First element becomes head
- Maintain a `prev` pointer to link nodes both ways
- Traverse array once

Time Complexity:
- O(n)

Space Complexity:
- O(n) (for n nodes)
*/
node* convertArr(vector<int> arr) {
    node* head = new node(arr[0]);
    node* prev = head;

    for (int i = 1; i < arr.size(); i++) {
        node* temp = new node(arr[i]);
        prev->next = temp;
        temp->prev = prev;
        prev = temp;
    }
    return head;
}

/*
====================================
Delete Head Node
====================================
Intuition:
- Move head to next node
- Set new head's prev to NULL
- Delete old head

Time Complexity:
- O(1)

Space Complexity:
- O(1)
*/
node* deletehead(node* head) {
    if (head == nullptr) return nullptr;

    node* temp = head;
    head = head->next;

    if (head != nullptr) head->prev = nullptr;
    temp->next = nullptr;

    delete temp;
    return head;
}

/*
====================================
Delete Tail Node
====================================
Intuition:
- Traverse till last node
- Use prev pointer to unlink tail

Time Complexity:
- O(n)

Space Complexity:
- O(1)
*/
node* deletetail(node* head) {
    if (head == nullptr) return nullptr;
    if (head->next == nullptr) {
        delete head;
        return nullptr;
    }

    node* tail = head;
    while (tail->next != nullptr) tail = tail->next;

    node* prev = tail->prev;
    prev->next = nullptr;
    tail->prev = nullptr;

    delete tail;
    return head;
}

/*
====================================
Delete Given Node (by pointer)
====================================
Intuition:
- Handle 4 cases:
  1) Only one node
  2) Head node
  3) Tail node
  4) Middle node
- Adjust prev & next pointers accordingly

Time Complexity:
- O(1)

Space Complexity:
- O(1)
*/
node* deltetenode(node* head, node* temp) {
    if (temp == nullptr) return head;

    node* prev = temp->prev;
    node* front = temp->next;

    if (prev == nullptr && front == nullptr) { // only one node
        delete temp;
        return nullptr;
    }
    if (prev == nullptr) { // head
        head = head->next;
        head->prev = nullptr;
        temp->next = nullptr;
        delete temp;
        return head;
    }
    if (front == nullptr) { // tail
        prev->next = nullptr;
        temp->prev = nullptr;
        delete temp;
        return head;
    }

    // middle node
    prev->next = front;
    front->prev = prev;

    temp->next = temp->prev = nullptr;
    delete temp;
    return head;
}

/*
====================================
Delete Kth Node (1-based index)
====================================
Intuition:
- Traverse till kth node
- Reuse delete-by-pointer logic

Time Complexity:
- O(n)

Space Complexity:
- O(1)
*/
node* delete_kth_node(node* head, int k) {
    if (head == nullptr) return nullptr;

    int cnt = 1;
    node* temp = head;
    while (temp != nullptr && cnt < k) {
        temp = temp->next;
        cnt++;
    }

    if (temp == nullptr) return head; // k > length
    return deltetenode(head, temp);
}

/*
====================================
Insert at Head
====================================
Intuition:
- New node becomes head
- Old head's prev points to new node

Time Complexity:
- O(1)

Space Complexity:
- O(1)
*/
node* insertHead(node* head, int val) {
    node* newNode = new node(val);
    if (head == nullptr) return newNode;

    newNode->next = head;
    head->prev = newNode;
    return newNode;
}

/*
====================================
Insert at Tail
====================================
Intuition:
- Traverse to last node
- Link new node using prev pointer

Time Complexity:
- O(n)

Space Complexity:
- O(1)
*/
node* insertTail(node* head, int val) {
    node* newNode = new node(val);
    if (head == nullptr) return newNode;

    node* tail = head;
    while (tail->next != nullptr) tail = tail->next;

    tail->next = newNode;
    newNode->prev = tail;
    return head;
}

/*
====================================
Insert at Kth Position (1-based)
====================================
Intuition:
- Traverse to (k-1)th node
- Adjust prev and next pointers

Time Complexity:
- O(n)

Space Complexity:
- O(1)
*/
node* insertAtK(node* head, int k, int val) {
    if (k <= 1) return insertHead(head, val);

    int cnt = 1;
    node* temp = head;
    while (temp != nullptr && cnt < k - 1) {
        temp = temp->next;
        cnt++;
    }

    if (temp == nullptr || temp->next == nullptr) {
        return insertTail(head, val);
    }

    node* newNode = new node(val);
    node* front = temp->next;

    temp->next = newNode;
    newNode->prev = temp;
    newNode->next = front;
    front->prev = newNode;

    return head;
}

/*
====================================
Insert Before Given Node
====================================
Intuition:
- If node is head → insert at head
- Else link between prev and current

Time Complexity:
- O(1)

Space Complexity:
- O(1)
*/
node* insertBefore(node* head, node* temp, int val) {
    if (temp == nullptr) return head;

    if (temp->prev == nullptr) {
        return insertHead(head, val);
    }

    node* newNode = new node(val);
    node* prev = temp->prev;

    prev->next = newNode;
    newNode->prev = prev;
    newNode->next = temp;
    temp->prev = newNode;

    return head;
}

/*
====================================
Insert After Given Node
====================================
Intuition:
- Insert node between temp and temp->next

Time Complexity:
- O(1)

Space Complexity:
- O(1)
*/
node* insertAfter(node* head, node* temp, int val) {
    if (temp == nullptr) return head;

    node* newNode = new node(val);
    node* front = temp->next;

    temp->next = newNode;
    newNode->prev = temp;
    newNode->next = front;

    if (front != nullptr) front->prev = newNode;

    return head;
}

/*
====================================
Print Doubly Linked List (Forward)
====================================
Time Complexity:
- O(n)

Space Complexity:
- O(1)
*/
void print(node* head) {
    node* temp = head;
    while (temp != nullptr) {
        cout << temp->data << " ";
        temp = temp->next;
    }
    cout << endl;
}

/*
====================================
Print Doubly Linked List (Reverse)
====================================
Intuition:
- Move to tail
- Traverse using prev pointer

Time Complexity:
- O(n)

Space Complexity:
- O(1)
*/
void printReverse(node* head) {
    if (head == nullptr) return;

    node* tail = head;
    while (tail->next != nullptr) tail = tail->next;

    while (tail != nullptr) {
        cout << tail->data << " ";
        tail = tail->prev;
    }
    cout << endl;
}

/*
====================================
Reverse Doubly Linked List
====================================
Intuition:
- Swap prev and next for each node
- Move using swapped pointers
- Last processed node becomes new head

Time Complexity:
- O(n)

Space Complexity:
- O(1)
*/
node* reverse(node* head) {
    if (head == nullptr || head->next == nullptr) return head;

    node* curr = head;
    node* last = nullptr;

    while (curr != nullptr) {
        last = curr->prev;
        curr->prev = curr->next;
        curr->next = last;
        curr = curr->prev;
    }

    if (last != nullptr) {
        head = last->prev;
    }
    return head;
}

/*
====================================
Main Function (Testing)
====================================
*/
int main() {
    vector<int> arr = {12, 2, 3, 4, 6};
    node* head = convertArr(arr);

    cout << "Original list: ";
    print(head);

    head = deletehead(head);
    cout << "After deleting head: ";
    print(head);

    head = deletetail(head);
    cout << "After deleting tail: ";
    print(head);

    head = delete_kth_node(head, 2);
    cout << "After deleting 2nd node: ";
    print(head);

    head = insertHead(head, 99);
    cout << "After inserting 99 at head: ";
    print(head);

    head = insertTail(head, 77);
    cout << "After inserting 77 at tail: ";
    print(head);

    head = insertAtK(head, 2, 55);
    cout << "After inserting 55 at pos 2: ";
    print(head);

    head = insertBefore(head, head->next, 44);
    cout << "After inserting 44 before 2nd node: ";
    print(head);

    head = insertAfter(head, head->next, 11);
    cout << "After inserting 11 after 2nd node: ";
    print(head);

    cout << "List in reverse order: ";
    printReverse(head);

    head = reverse(head);
    cout << "List after reversing: ";
    print(head);

    return 0;
}
