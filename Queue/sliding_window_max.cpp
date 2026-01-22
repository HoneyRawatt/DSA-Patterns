#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>
using namespace std;

/*
=====================================================
PROBLEM STATEMENT (Sliding Window Maximum):
-----------------------------------------------------
Given an integer array `arr` and a window size `k`,
find the maximum element in every contiguous subarray
(window) of size `k`.

Example:
arr = [1,3,-1,-3,5,3,6,7], k = 3
Output = [3,3,5,5,6,7]
=====================================================
*/

/*
=====================================================
1️⃣ Optimal O(n) Solution using Deque
=====================================================
Intuition:
- Use a deque to store indices of useful elements
- Deque maintains elements in decreasing order of values
- Front of deque always contains index of current window's maximum

Key Observations:
- Remove indices that are out of the current window
- Remove all smaller elements from the back (they can never be max)

Time Complexity: O(n)
- Each index is added and removed at most once

Space Complexity: O(k)
- Deque stores at most k elements
*/
vector<int> sliding_window_max(vector<int> arr, int k) {
    deque<int> dq;           // Stores indices of elements
    vector<int> ls;          // Stores result (max of each window)

    int n = arr.size();

    for (int i = 0; i < n; i++) {

        // Remove indices that are outside the current window
        if (!dq.empty() && dq.front() <= i - k)
            dq.pop_front();

        // Maintain decreasing order in deque
        // Remove all elements smaller than or equal to current element
        while (!dq.empty() && arr[dq.back()] <= arr[i])
            dq.pop_back();

        // Push current index
        dq.push_back(i);

        // Window starts producing results when i >= k - 1
        if (i >= k - 1)
            ls.push_back(arr[dq.front()]); // Max of current window
    }

    return ls;
}

/*
=====================================================
2️⃣ Brute-force O(n * k) Solution
=====================================================
Intuition:
- For each window, scan all k elements
- Track maximum and store it

Time Complexity: O(n * k)
- For each window, k comparisons

Space Complexity: O(1)
- Only result array used
*/
vector<int> sliding_window_max_brute(vector<int> arr, int k) {
    vector<int> ls;
    int n = arr.size();

    // Traverse all possible windows
    for (int i = 0; i <= n - k; i++) {
        int maxi = arr[i];

        // Find max in current window
        for (int j = i; j < i + k; j++)
            maxi = max(maxi, arr[j]);

        ls.push_back(maxi);
    }

    return ls;
}

/*
=====================================================
Main Function
=====================================================
*/
int main() {
    vector<int> arr = {1, 3, -1, -3, 5, 3, 6, 7};
    int k = 3;

    vector<int> res1 = sliding_window_max(arr, k);
    vector<int> res2 = sliding_window_max_brute(arr, k);

    cout << "Optimal: ";
    for (int x : res1) cout << x << " ";

    cout << "\nBrute: ";
    for (int x : res2) cout << x << " ";

    cout << endl;
    return 0;
}
