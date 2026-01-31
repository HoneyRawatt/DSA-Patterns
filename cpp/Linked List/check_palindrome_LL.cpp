#include<iostream>
#include<stack>
using namespace std;

/*
------------------------------------------------------------
Problem Statement:
------------------------------------------------------------
Given the head of a singly linked list, check whether the
list is a palindrome (reads the same forwards and backwards).

Two approaches are considered:
1. Brute force using a stack.
2. Optimal approach using fast and slow pointers with in-place reversal.
------------------------------------------------------------
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
------------------------------------------------------------
Helper function: Reverse linked list
------------------------------------------------------------
Iterative method to reverse a linked list.
*/
node* reverse(node* head) {
    node* prev = nullptr;
    node* curr = head;
    node* front = nullptr;

    while (curr != nullptr) {
        front = curr->next;  // save next
        curr->next = prev;   // reverse link
        prev = curr;         // move prev
        curr = front;        // move forward
    }

    return prev; // new head
}

/*
------------------------------------------------------------
Brute Force Approach (using stack)
------------------------------------------------------------
Intuition:
- Push all node values into a stack.
- Traverse the list again and compare each value with top of stack.
- If all values match, it's a palindrome.
------------------------------------------------------------
*/
bool check_palindrome_brute(node* head) {
    stack<int> st;
    node* temp = head;

    // Push all values to stack
    while (temp != nullptr) {
        st.push(temp->data);
        temp = temp->next;
    }

    // Compare stack values with list
    temp = head;
    while (temp != nullptr) {
        if (temp->data != st.top()) return false;
        st.pop();
        temp = temp->next;
    }

    return true;
}

/*
------------------------------------------------------------
Optimal Approach (O(1) space)
------------------------------------------------------------
Intuition:
1. Find the middle of the list using slow and fast pointers.
2. Reverse the second half of the list.
3. Compare first half and reversed second half.
4. Restore the list (reverse second half back) and return result.
------------------------------------------------------------
*/
bool check_palindrome(node* head) {
    if (!head || !head->next) return true;

    node* slow = head;
    node* fast = head;

    // Find middle of the list
    while (fast->next != nullptr && fast->next->next != nullptr) {
        slow = slow->next;
        fast = fast->next->next;
    }

    // Reverse second half
    node* newhead = reverse(slow->next);

    // Compare first and second half
    node* first = head;
    node* second = newhead;
    bool isPalindrome = true;

    while (second != nullptr) {
        if (first->data != second->data) {
            isPalindrome = false;
            break;
        }
        first = first->next;
        second = second->next;
    }

    // Restore original list
    slow->next = reverse(newhead);

    return isPalindrome;
}

/*
------------------------------------------------------------
Utility: Print linked list
------------------------------------------------------------
*/
void printList(node* head) {
    while (head != nullptr) {
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
    node* head = new node(1, new node(2, new node(3, new node(2, new node(1)))));

    cout << "Original list: ";
    printList(head);

    cout << "Is palindrome (brute)? " << (check_palindrome_brute(head) ? "Yes" : "No") << endl;
    cout << "Is palindrome (optimal)? " << (check_palindrome(head) ? "Yes" : "No") << endl;

    return 0;
}

/*
------------------------------------------------------------
Time & Space Complexity
------------------------------------------------------------

1. Brute Force (Stack):
   - Time Complexity: O(N)
   - Space Complexity: O(N)  // stack stores all node values

2. Optimal Approach:
   - Time Complexity: O(N)
   - Space Complexity: O(1)  // only pointers used, second half reversed in-place
------------------------------------------------------------
*/
