#include <iostream> 
#include <stack>
#include <vector>
using namespace std;

/*
=====================================================
PROBLEM STATEMENT:
-----------------------------------------------------
Given an array arr of size n, find the Nearest
Smaller Element to the LEFT for every element.

For each index i, find the closest element on the
left side of arr[i] that is strictly smaller than
arr[i]. If no such element exists, store -1.

Example:
Input:  [4, 5, 2, 8, 9, 3]
Output: [-1, 4, -1, 2, 8, 2]
=====================================================
*/

/*
=====================================================
BRUTE FORCE APPROACH
-----------------------------------------------------
INTUITION:
For each element arr[i], scan all elements to its
left (i-1 to 0) and find the first element that is
smaller than arr[i].

As soon as a smaller element is found, store it and
stop checking further.

TIME COMPLEXITY:
- For each element, we may scan up to n elements
=> O(n^2)

SPACE COMPLEXITY:
- O(n) for the result array
=====================================================
*/
vector<int> nearest_smaller_ele_brute(vector<int>& arr) {
    int n = arr.size();

    // Result array initialized with -1
    vector<int> res(n, -1);

    // Traverse each element
    for (int i = 0; i < n; i++) {

        // Check elements on the left of i
        for (int j = i - 1; j >= 0; j--) {
            if (arr[j] < arr[i]) {
                res[i] = arr[j]; // Nearest smaller found
                break;           // Stop at first smaller
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
We use a MONOTONIC INCREASING STACK to efficiently
track the nearest smaller elements.

- Stack stores elements in increasing order
- Before pushing current element, remove all
  elements greater than or equal to it
- The top of the stack (if exists) is the nearest
  smaller element to the left

WHY LEFT TO RIGHT?
Because we are finding the nearest smaller element
on the LEFT side.

TIME COMPLEXITY:
- Each element is pushed and popped at most once
=> O(n)

SPACE COMPLEXITY:
- O(n) for stack + result array
=====================================================
*/
vector<int> nearest_smaller_ele(vector<int>& arr) {
    int n = arr.size();
    stack<int> st;              // Stack to store candidates
    vector<int> res(n, -1);     // Result initialized with -1

    // Traverse array from left to right
    for (int i = 0; i < n; i++) {

        // Remove elements that are >= current element
        while (!st.empty() && st.top() >= arr[i]) {
            st.pop();
        }

        // If stack is not empty, top is nearest smaller
        if (!st.empty()) {
            res[i] = st.top();
        }

        // Push current element to stack
        st.push(arr[i]);
    }
    return res;
}

int main() {
    vector<int> arr = {4, 5, 2, 8, 9, 3};

    // Brute force solution
    vector<int> res = nearest_smaller_ele_brute(arr);
    cout << "Brute: ";
    for (auto it : res) cout << it << " ";
    cout << endl;

    // Optimized stack-based solution
    res = nearest_smaller_ele(arr);
    cout << "Optimal: ";
    for (auto it : res) cout << it << " ";
    cout << endl;
}
