#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <set>
using namespace std;
/*
========================================================
PROBLEM STATEMENT:
--------------------------------------------------------
Given an integer array `arr` and an integer `k`,
find the length of the longest contiguous subarray
that contains at most `k` distinct elements.

--------------------------------------------------------
EXAMPLE:
Input:  arr = [1, 2, 1, 2, 3], k = 2
Output: 4
Explanation:
The longest subarray with at most 2 distinct elements
is [1, 2, 1, 2]

========================================================
*/


    /*
    ========================================================
    BRUTE FORCE APPROACH:
    --------------------------------------------------------
    Idea:
    - Generate all possible subarrays
    - Use a set to track distinct elements
    - Stop expanding when distinct count exceeds k

    --------------------------------------------------------
    INTUITION:
    --------------------------------------------------------
    Try every starting index and extend the subarray
    until the constraint (≤ k distinct elements) breaks.

    --------------------------------------------------------
    TIME COMPLEXITY:
    - O(n²)

    SPACE COMPLEXITY:
    - O(1) (set size ≤ k)
    ========================================================
    */
int longest_substr_brute(vector<int>& arr, int k) {
    int maxlen = 0;
    for (int i = 0; i < arr.size(); i++) {
        set<int> st;
        for (int j = i; j < arr.size(); j++) {
            st.insert(arr[j]);
            if (st.size() <= k) {
                maxlen = max(maxlen, j - i + 1);
            } else break;
        }
    }
    return maxlen;
}

  /*
    ========================================================
    BETTER APPROACH (SLIDING WINDOW + HASHMAP):
    --------------------------------------------------------
    Idea:
    - Use two pointers (left & right)
    - Maintain frequency of elements in a hashmap
    - Shrink window when distinct elements exceed k

    --------------------------------------------------------
    INTUITION:
    --------------------------------------------------------
    Keep a window that always satisfies:
        number of distinct elements ≤ k

    Expand right pointer.
    Shrink left pointer only when constraint breaks.

    --------------------------------------------------------
    TIME COMPLEXITY:
    - O(2n) ≈ O(n)

    SPACE COMPLEXITY:
    - O(n)
    ========================================================
    */
int longest_substr_better(vector<int>& arr, int k) {
    int l = 0, r = 0, maxlen = 0;
    unordered_map<int, int> mpp;

    while (r < arr.size()) {
        mpp[arr[r]]++;

        while (mpp.size() > k) {
            mpp[arr[l]]--;
            if (mpp[arr[l]] == 0) mpp.erase(arr[l]);
            l++;
        }
        if(mpp.size()<=k) maxlen = max(maxlen, r - l + 1);
        r++;
    }

    return maxlen;
}

    /*
    ========================================================
    OPTIMAL APPROACH (CLEAN SLIDING WINDOW):
    --------------------------------------------------------
    Same logic as the better approach, written more cleanly.

    --------------------------------------------------------
    INTUITION:
    --------------------------------------------------------
    - Expand window using right pointer
    - Shrink from left only when needed
    - Always keep the window valid

    --------------------------------------------------------
    TIME COMPLEXITY:
    - O(n)

    SPACE COMPLEXITY:
    - O(n)
    ========================================================
    */

int longest_substr_optimal(vector<int>& arr, int k) {
    int l = 0, r = 0, maxlen = 0;
    unordered_map<int, int> mpp;

    while (r < arr.size()) {
        mpp[arr[r]]++;

        if (mpp.size() > k) {
            mpp[arr[l]]--;
            if (mpp[arr[l]] == 0) mpp.erase(arr[l]);
            l++;
        }

        if(mpp.size()<=k) maxlen = max(maxlen, r - l + 1);
        r++;
    }

    return maxlen;
}

// ---------------- MAIN ----------------
int main() {
    vector<int> arr = {1, 2, 1, 2, 3};
    int k = 2;

    cout << "Brute Force: " << longest_substr_brute(arr, k) << endl;
    cout << "Better: " << longest_substr_better(arr, k) << endl;
    cout << "Optimal: " << longest_substr_optimal(arr, k) << endl;

    return 0;
}
