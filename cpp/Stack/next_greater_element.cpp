#include <iostream>
#include <stack>
#include <vector>
using namespace std;

/*
=====================================================
PROBLEM STATEMENT:
-----------------------------------------------------
Given an array arr of size n, for each element,
find the Next Greater Element (NGE).

The Next Greater Element for an element x is the
first element to the right of x that is greater than x.
If no such element exists, return -1 for that position.

Example:
Input:  [4, 5, 2, 25]
Output: [5, 25, 25, -1]
=====================================================
*/

/*
=====================================================
BRUTE FORCE APPROACH
-----------------------------------------------------
INTUITION:
For every element arr[i], look at all elements
to its right (j > i) and find the first element
greater than arr[i].

If found, store it and break.
If not found, result remains -1.

TIME COMPLEXITY:
- Outer loop runs n times
- Inner loop runs up to n times
=> O(n^2)

SPACE COMPLEXITY:
- O(n) for the result array
=====================================================
*/
vector<int> next_greater_ele_brute(vector<int>& arr) {
    int n = arr.size();

    // Result array initialized with -1
    vector<int> res(n, -1);

    // For each element
    for (int i = 0; i < n; i++) {
        // Check elements to the right
        for (int j = i + 1; j < n; j++) {
            if (arr[j] > arr[i]) {
                res[i] = arr[j]; // Next greater found
                break;           // Stop at first greater
            }
        }
    }
    return res;
}

/*
=====================================================
OPTIMIZED APPROACH (Using Stack)
-----------------------------------------------------
INTUITION:
We process elements from RIGHT to LEFT and maintain
a MONOTONIC DECREASING STACK.

- The stack stores potential "next greater elements"
- Before pushing the current element, remove all
  elements smaller than or equal to it
- The top of the stack (if exists) is the next greater
  element for the current value

WHY RIGHT TO LEFT?
Because we want the "next" greater element, which
must be on the right side.

TIME COMPLEXITY:
- Each element is pushed and popped at most once
=> O(n)

SPACE COMPLEXITY:
- O(n) for stack + result array
=====================================================
*/
vector<int> next_greater_ele(vector<int>& arr) {
    int n = arr.size();
    stack<int> st;              // Stack to store candidates
    vector<int> res(n, -1);     // Result initialized with -1

    // Traverse from right to left
    for (int i = n - 1; i >= 0; i--) {

        // Remove elements that cannot be next greater
        while (!st.empty() && st.top() <= arr[i]) {
            st.pop();
        }

        // If stack is not empty, top is next greater
        if (!st.empty()) {
            res[i] = st.top();
        }

        // Push current element into stack
        st.push(arr[i]);
    }
    return res;
}

int main() {
    vector<int> arr = {4, 5, 2, 25};

    // Brute force solution
    vector<int> res1 = next_greater_ele_brute(arr);

    // Optimized stack-based solution
    vector<int> res2 = next_greater_ele(arr);

    cout << "Brute force result: ";
    for (int x : res1) cout << x << " ";
    cout << endl;

    cout << "Optimized result: ";
    for (int x : res2) cout << x << " ";
    cout << endl;

    return 0;
}
