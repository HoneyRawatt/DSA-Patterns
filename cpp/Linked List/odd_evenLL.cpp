#include<iostream>
#include<vector>
using namespace std;

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
    Brute Force Approach
    ====================================
    Intuition:
    - Store odd-position nodes first
    - Then store even-position nodes
    - Rewrite the linked list using stored values

    Time Complexity: O(n)
    Space Complexity: O(n)
    */
node* Odd_evenLL_brute(node* head) {
    if (head == nullptr || head->next == nullptr) return head;
    vector<int> arr;
    node* temp = head;
    int pos = 1;
    
    // Collect odd position nodes
    while (temp) {
        if (pos % 2 != 0) arr.push_back(temp->data);
        temp = temp->next;
        pos++;
    }
    
    // Collect even position nodes
    temp = head;
    pos = 1;
    while (temp) {
        if (pos % 2 == 0) arr.push_back(temp->data);
        temp = temp->next;
        pos++;
    }
    
    // Rewrite linked list
    temp = head;
    int i = 0;
    while (temp) {
        temp->data = arr[i++];
        temp = temp->next;
    }
    
    return head;
}

    /*
    ====================================
    Optimized Approach (Pointer Rearrangement)
    ====================================
    Intuition:
    - Separate odd and even nodes using pointers
    - Connect odd list with even list at the end

    Time Complexity: O(n)
    Space Complexity: O(1)
    */

node* Odd_evenLL_optimized(node* head) {
    if (head == nullptr || head->next == nullptr) return head;
    
    node* odd = head;
    node* even = head->next;
    node* evenhead = even;
    
    while (even != nullptr && even->next != nullptr) {
        odd->next = even->next;
        odd = odd->next;
        
        even->next = odd->next;
        even = even->next;
    }
    
    odd->next = evenhead; // connect odd list to even list
    return head;
}

// Helper functions
void insert(node*& head, int val) {
    if (!head) {
        head = new node(val);
        return;
    }
    node* temp = head;
    while (temp->next) temp = temp->next;
    temp->next = new node(val);
}

void printlist(node* head) {
    while (head) {
        cout << head->data;
        if (head->next) cout << " -> ";
        head = head->next;
    }
    cout << endl;
}

int main() {
    node* head = nullptr;
    insert(head, 1);
    insert(head, 2);
    insert(head, 3);
    insert(head, 4);
    insert(head, 5);
    
    cout << "Original: ";
    printlist(head);
    
    node* res1 = Odd_evenLL_brute(head);
    cout << "Brute Result: ";
    printlist(res1);
    
    // rebuild for optimized test
    node* head2 = nullptr;
    insert(head2, 1);
    insert(head2, 2);
    insert(head2, 3);
    insert(head2, 4);
    insert(head2, 5);
    
    node* res2 = Odd_evenLL_optimized(head2);
    cout << "Optimized Result: ";
    printlist(res2);
    
    return 0;
}
