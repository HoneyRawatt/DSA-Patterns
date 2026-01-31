#include<iostream>
#include<vector>
using namespace std;

/*
========================
Linked List Node Class
========================
Intuition:
- Each node stores:
  1) data
  2) pointer to the next node
- This is a singly linked list (one-directional)

Time Complexity:
- Node creation: O(1)

Space Complexity:
- O(1) per node (heap allocation)
*/
class node {
public:
    int data;
    node* next;

    // Constructor for single node
    node(int val) {
        data = val;
        next = nullptr;
    }

    // Constructor when next node is known
    node(int val, node* next) {
        data = val;
        this->next = next; 
    }
};

/*
=====================================
Convert Array to Linked List
=====================================
Intuition:
- First element becomes the head
- Use a pointer (mover) to keep adding nodes at the end
- Traverse array once and link nodes sequentially

Time Complexity:
- O(n), where n = size of array

Space Complexity:
- O(n) for creating n linked list nodes
*/
node* convertarrtoll(vector<int> arr) {
    if (arr.empty()) return nullptr;

    node* head = new node(arr[0]);
    node* mover = head;

    for (int i = 1; i < arr.size(); i++) {
        mover->next = new node(arr[i]);
        mover = mover->next;
    }
    return head;
}

/*
========================
Display Linked List
========================
Intuition:
- Traverse from head to NULL
- Print data of each node

Time Complexity:
- O(n)

Space Complexity:
- O(1)
*/
void display(node* head) {
    if (head == nullptr) {
        cout << "linked list is empty" << endl;
        return;
    }

    node* current = head;
    while (current != nullptr) {
        cout << current->data << " ";
        current = current->next;
    }
    cout << endl;
}

/*
========================
Length of Linked List
========================
Intuition:
- Traverse list and count nodes

Time Complexity:
- O(n)

Space Complexity:
- O(1)
*/
int lengthofll(node* head) {
    int cnt = 0;
    node* temp = head;

    while (temp != nullptr) {
        cnt++;
        temp = temp->next;
    }
    return cnt;
}

/*
========================
Search Element in LL
========================
Intuition:
- Traverse list
- Compare each node's data with target value

Time Complexity:
- O(n)

Space Complexity:
- O(1)
*/
bool Checkifpersent(node* head, int val) {
    node* temp = head;
    while (temp != nullptr) {
        if (temp->data == val) return true;
        temp = temp->next;
    }
    return false;
}

/*
========================
Delete Head Node
========================
Intuition:
- Move head to next node
- Delete old head

Time Complexity:
- O(1)

Space Complexity:
- O(1)
*/
node* deletehead(node* head) {
    if (head == nullptr) return head;

    node* temp = head;
    head = head->next;
    delete temp;
    return head;
}

/*
========================
Delete Last Node
========================
Intuition:
- Traverse till second last node
- Delete last node
- Set second last node's next to NULL

Time Complexity:
- O(n)

Space Complexity:
- O(1)
*/
node* deletelast(node* head) {
    if (head == nullptr || head->next == nullptr) {
        delete head;
        return nullptr;
    }

    node* temp = head;
    while (temp->next->next != nullptr) {
        temp = temp->next;
    }

    delete temp->next;
    temp->next = nullptr;
    return head;
}

/*
========================
Delete Kth Node
========================
Intuition:
- If k == 1 → delete head
- Else traverse while counting nodes
- Use prev pointer to unlink kth node

Time Complexity:
- O(n)

Space Complexity:
- O(1)
*/
node* deleteKth(node* head, int k) {
    if (head == nullptr) return head;
    if (k == 1) return deletehead(head);

    int cnt = 0;
    node* temp = head;
    node* prev = nullptr;

    while (temp != nullptr) {
        cnt++;
        if (cnt == k) {
            prev->next = temp->next;
            delete temp;
            break;
        }
        prev = temp;
        temp = temp->next;
    }
    return head;
}

/*
========================
Delete Node by Value
========================
Intuition:
- If value is at head → delete head
- Else find node with matching value
- Re-link previous node

Time Complexity:
- O(n)

Space Complexity:
- O(1)
*/
node* deleteByValue(node* head, int val) {
    if (head == nullptr) return head;
    if (head->data == val) return deletehead(head);

    node* temp = head;
    node* prev = nullptr;

    while (temp != nullptr) {
        if (temp->data == val) {
            prev->next = temp->next;
            delete temp;
            break;
        }
        prev = temp;
        temp = temp->next;
    }
    return head;
}

/*
========================
Insert at Head
========================
Intuition:
- Create new node
- Point it to old head
- Return new node as head

Time Complexity:
- O(1)

Space Complexity:
- O(1)
*/
node* inserthead(node* head, int val) {
    return new node(val, head);
}

/*
========================
Insert at Tail
========================
Intuition:
- Traverse to last node
- Attach new node at the end

Time Complexity:
- O(n)

Space Complexity:
- O(1)
*/
node* inserttail(node* head, int val) {
    if (head == NULL) return new node(val);

    node* temp = head;
    while (temp->next != NULL) {
        temp = temp->next;
    }

    temp->next = new node(val);
    return head;
}

/*
========================
Insert at Given Position
========================
Intuition:
- If pos == 1 → insert at head
- Traverse till (pos-1)th node
- Adjust pointers

Time Complexity:
- O(n)

Space Complexity:
- O(1)
*/
node* insertposition(node* head, int val, int pos) {
    if (head == NULL) {
        if (pos == 1) return new node(val);
        return head;
    }

    if (pos == 1) return new node(val, head);

    int cnt = 1;
    node* temp = head;

    while (temp != NULL) {
        if (cnt == pos - 1) {
            node* x = new node(val, temp->next);
            temp->next = x;
            break;
        }
        cnt++;
        temp = temp->next;
    }
    return head;
}

/*
========================
Insert Before Given Value
========================
Intuition:
- If value is at head → insert before head
- Else traverse and check next node's value
- Insert in between

Time Complexity:
- O(n)

Space Complexity:
- O(1)
*/
node* insertbeforeval(node* head, int el, int val) {
    if (head == NULL) return head;
    if (head->data == val) return new node(el, head);

    node* temp = head;
    while (temp->next != NULL) {
        if (temp->next->data == val) {
            node* x = new node(el, temp->next);
            temp->next = x;
            break;
        }
        temp = temp->next;
    }
    return head;
}

/*
========================
Main Function (Testing)
========================
*/
int main() {
    vector<int> arr = {2, 5, 0, 7};
    node* head = convertarrtoll(arr);

    cout << "Linked List created from array: ";
    display(head);

    cout << "Length of LL: " << lengthofll(head) << endl;
    cout << "Check if element is present: " 
         << (Checkifpersent(head, 5) ? "YES" : "NO") << endl;

    head = deleteKth(head, 3);
    cout << "After deleting 3rd node: ";
    display(head);

    head = deleteByValue(head, 7);
    cout << "After deleting node with value 7: ";
    display(head);

    head = inserthead(head, 10);
    cout << "After inserting 10 at head: ";
    display(head);

    head = inserttail(head, 99);
    cout << "After inserting 99 at tail: ";
    display(head);

    head = insertposition(head, 77, 3);
    cout << "After inserting 77 at position 3: ";
    display(head);

    head = insertbeforeval(head, 88, 5);
    cout << "After inserting 88 before 5: ";
    display(head);

    return 0;
}
