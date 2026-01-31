#include <iostream>
#include <stack>
#include <vector>
using namespace std;

/*
=====================================================
PROBLEM STATEMENT:
-----------------------------------------------------
Given a CIRCULAR array arr of size n, find the
Next Greater Element (NGE) for each element.

The Next Greater Element of an element x is the first
element greater than x when traversing the array
in a circular manner (wrapping around to the start).

If no such element exists, store -1.

Example:
Input:  [1, 2, 1]
Output: [2, -1, 2]
=====================================================
*/

/*
=====================================================
BRUTE FORCE APPROACH (Circular)
-----------------------------------------------------
INTUITION:
For every element arr[i], we check the next n elements
in circular order to find the first element greater
than arr[i].

- We use modulo (%) to simulate circular traversal
- If a greater element is found, store it and stop

TIME COMPLEXITY:
- For each element, we may scan up to n elements
=> O(n^2)

SPACE COMPLEXITY:
- O(n) for the result array
=====================================================
*/
vector<int> next_greater_ele_brute(vector<int>& arr) {
    int n = arr.size();

    // Result array initialized with -1
    vector<int> res(n, -1);

    // Check for each element
    for (int i = 0; i < n; i++) {

        // Traverse next n elements circularly
        for (int j = i + 1; j < i + n; j++) {
            int idx = j % n; // Convert to circular index

            // First greater element found
            if (arr[idx] > arr[i]) {
                res[i] = arr[idx];
                break;
            }
        }
    }
    return res;
}

/*
=====================================================
OPTIMIZED APPROACH (Using Stack – Circular Array)
-----------------------------------------------------
INTUITION:
We simulate circular traversal by iterating the array
twice (2n times) and use a MONOTONIC DECREASING STACK.

- Stack stores possible next greater elements
- We traverse from right to left
- For each element, remove smaller or equal values
- The top of the stack gives the next greater element

WHY 2n ITERATIONS?
Because the array is circular and elements at the end
may find their next greater element at the beginning.

WHY STORE ANSWER ONLY WHEN i < n?
Because results are needed only for original indices,
not for the duplicated traversal.

TIME COMPLEXITY:
- Each element is pushed and popped at most once
=> O(n)

SPACE COMPLEXITY:
- O(n) for stack + result array
=====================================================
*/
vector<int> next_greater_ele(vector<int>& arr) {
    int n = arr.size();
    stack<int> st;              // Stack to maintain candidates
    vector<int> res(n, -1);     // Result initialized with -1

    // Traverse array twice in reverse order
    for (int i = 2 * n - 1; i >= 0; i--) {
        int idx = i % n;        // Circular index

        // Remove elements smaller or equal to current
        while (!st.empty() && st.top() <= arr[idx]) {
            st.pop();
        }

        // Store result only for first n elements
        if (i < n) {
            if (!st.empty()) {
                res[idx] = st.top();
            }
        }

        // Push current element into stack
        st.push(arr[idx]);
    }
    return res;
}

int main() {
    vector<int> arr = {1, 2, 1};

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
