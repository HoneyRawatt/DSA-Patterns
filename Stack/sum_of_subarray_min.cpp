#include <iostream>
#include <vector>
#include <stack>
#include <climits>
using namespace std;

/*
=====================================================
PROBLEM STATEMENT:
-----------------------------------------------------
Given an integer array arr, find the sum of the
minimum element of all possible contiguous subarrays.

Example:
Input:  [3, 1, 2, 4]
Output: 17
Explanation:
Subarrays and their minimums:
[3] -> 3, [3,1] -> 1, [3,1,2] -> 1, [3,1,2,4] -> 1,
[1] -> 1, [1,2] -> 1, [1,2,4] -> 1,
[2] -> 2, [2,4] -> 2, [4] -> 4
Sum = 3+1+1+1+1+1+1+2+2+4 = 17
=====================================================
*/

/*
=====================================================
BRUTE FORCE APPROACH
-----------------------------------------------------
INTUITION:
- For every subarray starting at i, keep track of 
  the running minimum while extending the subarray
- Add this minimum to the total sum

TIME COMPLEXITY:
- O(n^2) nested loops

SPACE COMPLEXITY:
- O(1), only variables used
=====================================================
*/
int sumOfSubarrayMinimumsBrute(const vector<int>& arr) {
    int n = arr.size();
    long long total = 0;
    const int mod = 1e9 + 7;

    for (int i = 0; i < n; i++) {
        int mini = INT_MAX; // running minimum for subarray starting at i
        for (int j = i; j < n; j++) {
            mini = min(mini, arr[j]);  // update running minimum
            total = (total + mini) % mod;
        }
    }
    return (int)total;
}

/*
=====================================================
HELPER FUNCTION: Next Smaller Element (NSE)
-----------------------------------------------------
- For each index i, finds the index of the next element
  smaller than arr[i] to its right
- If no such element, store n (size of array)
- Used for optimized counting in sumOfSubarrayMinimums
TIME: O(n), SPACE: O(n)
=====================================================
*/
vector<int> findNSE(const vector<int>& arr) {
    int n = arr.size();
    vector<int> nse(n);
    stack<int> st;

    for (int i = n - 1; i >= 0; i--) {
        while (!st.empty() && arr[st.top()] >= arr[i])
            st.pop();
        nse[i] = st.empty() ? n : st.top();
        st.push(i);
    }
    return nse;
}

/*
=====================================================
HELPER FUNCTION: Previous Smaller Element (PSE)
-----------------------------------------------------
- For each index i, finds the index of the previous element
  smaller than arr[i] to its left
- If no such element, store -1
- Used for optimized counting in sumOfSubarrayMinimums
TIME: O(n), SPACE: O(n)
=====================================================
*/
vector<int> findPSE(const vector<int>& arr) {
    int n = arr.size();
    vector<int> pse(n);
    stack<int> st;

    for (int i = 0; i < n; i++) {
        while (!st.empty() && arr[st.top()] > arr[i])
            st.pop();
        pse[i] = st.empty() ? -1 : st.top();
        st.push(i);
    }
    return pse;
}

/*
=====================================================
OPTIMIZED APPROACH (Using NSE + PSE)
-----------------------------------------------------
INTUITION:
- Each element arr[i] contributes as the minimum in
  multiple subarrays:
  - Left: number of elements to the previous smaller element
  - Right: number of elements to the next smaller element
- Contribution formula: arr[i] * left * right
- Sum contributions for all elements

TIME COMPLEXITY:
- O(n) due to single pass for NSE, PSE, and contribution
SPACE COMPLEXITY:
- O(n) for NSE, PSE arrays + stack
=====================================================
*/
int sumOfSubarrayMinimums(const vector<int>& arr) {
    int n = arr.size();
    vector<int> nse = findNSE(arr);
    vector<int> pse = findPSE(arr);
    long long total = 0;
    const int mod = 1e9 + 7;

    for (int i = 0; i < n; i++) {
        long long left = i - pse[i];        // #subarrays ending at i where arr[i] is min
        long long right = nse[i] - i;       // #subarrays starting at i where arr[i] is min
        total = (total + (left * right % mod) * arr[i] % mod) % mod;
    }
    return (int)total;
}

int main() {
    vector<int> arr = {3, 1, 2, 4};
    
    cout << "Brute Force Result: " << sumOfSubarrayMinimumsBrute(arr) << endl;
    cout << "Optimized Result: " << sumOfSubarrayMinimums(arr) << endl;
    return 0;
}
