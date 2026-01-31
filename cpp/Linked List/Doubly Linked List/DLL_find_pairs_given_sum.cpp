#include <iostream>
#include <vector>
using namespace std;

/*
====================================================
PROBLEM STATEMENT:
----------------------------------------------------
Given a SORTED doubly linked list and an integer sum,
find all pairs of nodes such that the sum of their
data values is equal to the given sum.

Return all such pairs as (first, second).
====================================================
*/

// Definition of a doubly linked list node
class node {
public:
    int data;
    node* prev;
    node* next;

    node(int val) {
        data = val;
        next = nullptr;
        prev = nullptr;
    }
};

/*
====================================================
BRUTE-FORCE APPROACH:
----------------------------------------------------
INTUITION:
- Use two nested loops.
- Fix the first node using temp1.
- For each temp1, traverse the remaining list using
  temp2 and check if the sum equals the target.
- Since the list is sorted, stop inner loop early
  when sum exceeds the target.

TIME COMPLEXITY: O(N^2)
SPACE COMPLEXITY: O(1) (excluding output storage)
====================================================
*/

vector<pair<int,int>> find_pairs_with_given_sum_brute(node* head, int sum) {
    node* temp1 = head;
    vector<pair<int,int>> res;

    // Traverse first pointer
    while(temp1 != nullptr) {

        // Second pointer starts from next node
        node* temp2 = temp1->next;

        // Move second pointer while sum is <= target
        while(temp2 != nullptr && temp1->data + temp2->data <= sum) {

            // If exact sum is found, store the pair
            if(temp1->data + temp2->data == sum) {
                res.push_back({temp1->data, temp2->data});
            }
            temp2 = temp2->next;
        }
        temp1 = temp1->next;
    }
    return res;
}

/*
====================================================
HELPER FUNCTION:
----------------------------------------------------
Finds the tail (last node) of the doubly linked list.
====================================================
*/

node* findtail(node* head) {
    node* temp = head;
    while(temp->next != nullptr)
        temp = temp->next;
    return temp;
}

/*
====================================================
OPTIMAL APPROACH (Two Pointers):
----------------------------------------------------
INTUITION:
- Since the doubly linked list is SORTED:
  - Use two pointers:
    left  -> start of list
    right -> end of list
- Calculate sum = left->data + right->data
  - If sum < target → move left forward
  - If sum > target → move right backward
  - If sum == target → store pair and move both

This avoids unnecessary comparisons.

TIME COMPLEXITY: O(N)
SPACE COMPLEXITY: O(1) (excluding output storage)
====================================================
*/

vector<pair<int,int>> find_pairs_with_given_sum(node* head, int sum) {

    node* left = head;           // Pointer at start
    node* right = findtail(head); // Pointer at end
    vector<pair<int,int>> res;

    // Stop when pointers cross
    while(left != nullptr && right != nullptr &&
          left != right && left->prev != right) {

        int s = left->data + right->data;

        if(s < sum)
            left = left->next;      // Increase sum
        else if(s > sum)
            right = right->prev;    // Decrease sum
        else {
            // Found a valid pair
            res.push_back({left->data, right->data});
            left = left->next;
            right = right->prev;
        }
    }
    return res;
}

/*
====================================================
UTILITY FUNCTION:
----------------------------------------------------
Prints vector of pairs.
====================================================
*/

void printPairs(const vector<pair<int,int>>& pairs) {
    for(auto p : pairs) {
        cout << "(" << p.first << "," << p.second << ") ";
    }
    cout << endl;
}

int main() {

    /*
    Creating sorted doubly linked list:
    1 <-> 2 <-> 3 <-> 4 <-> 5
    */

    node* head = new node(1);

    head->next = new node(2);
    head->next->prev = head;

    head->next->next = new node(3);
    head->next->next->prev = head->next;

    head->next->next->next = new node(4);
    head->next->next->next->prev = head->next->next;

    head->next->next->next->next = new node(5);
    head->next->next->next->next->prev = head->next->next->next;

    int sum = 5;

    // Brute-force solution
    cout << "Brute-force pairs with sum " << sum << ": ";
    vector<pair<int,int>> brutePairs =
        find_pairs_with_given_sum_brute(head, sum);
    printPairs(brutePairs);

    // Optimal two-pointer solution
    cout << "Optimal pairs with sum " << sum << ": ";
    vector<pair<int,int>> optimalPairs =
        find_pairs_with_given_sum(head, sum);
    printPairs(optimalPairs);

    return 0;
}
