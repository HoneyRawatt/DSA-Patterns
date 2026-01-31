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
You are given an integer array `fruits` where each
element represents a type of fruit.

You have two baskets, and each basket can hold only
one type of fruit, but unlimited quantity.

Rules:
- You must pick fruits from a contiguous subarray.
- You can store at most 2 different fruit types.

Goal:
- Return the maximum number of fruits you can collect.

--------------------------------------------------------
EXAMPLE:
Input:  fruits = [1, 2, 1, 2, 3, 2, 2, 1]
Output: 4
Explanation: The longest subarray is [1,2,1,2]

========================================================
*/


    /*
    ========================================================
    BRUTE FORCE APPROACH:
    --------------------------------------------------------
    Idea:
    - Try every possible subarray
    - Use a set to track distinct fruit types
    - If types ≤ 2, update answer

    --------------------------------------------------------
    INTUITION:
    --------------------------------------------------------
    Generate all subarrays and stop expanding when more
    than 2 fruit types appear.

    --------------------------------------------------------
    TIME COMPLEXITY:
    - O(n²)

    SPACE COMPLEXITY:
    - O(1) (at most 3 elements in set)
    ========================================================
    */
int totalFruits_brute(vector<int>& arr) {
    int maxlen = 0;
    for (int i = 0; i < arr.size(); i++) {
        set<int> st;
        for (int j = i; j < arr.size(); j++) {
            st.insert(arr[j]);
            if (st.size() <= 2) {
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
    - Store fruit counts in a hashmap
    - Shrink window when distinct fruits exceed 2

    --------------------------------------------------------
    INTUITION:
    --------------------------------------------------------
    Maintain a window with at most 2 fruit types.
    Expand right, shrink left only when constraint breaks.

    --------------------------------------------------------
    TIME COMPLEXITY:
    - O(2n) ≈ O(n)

    SPACE COMPLEXITY:
    - O(n)
    ========================================================
    */
int totalFruit_better(vector<int>& fruits) {
    int l = 0, r = 0, maxlen = 0;
    unordered_map<int, int> mpp;

    while (r < fruits.size()) {
        mpp[fruits[r]]++;

        // Shrink window if more than 2 types
        if (mpp.size() > 2) {
            while (mpp.size() > 2) {
                mpp[fruits[l]]--;
                if (mpp[fruits[l]] == 0) mpp.erase(fruits[l]);
                l++;
            }
        }

        // Update max length
        if (mpp.size() <= 2) {
            maxlen = max(maxlen, r - l + 1);
        }
        r++;
    }

    return maxlen;
}

    /*
    ========================================================
    OPTIMAL APPROACH (CLEAN SLIDING WINDOW):
    --------------------------------------------------------
    Same logic as above but with a cleaner shrinking step.

    --------------------------------------------------------
    INTUITION:
    --------------------------------------------------------
    - Expand window using right pointer
    - Shrink only once per iteration when needed
    - Window always remains valid

    --------------------------------------------------------
    TIME COMPLEXITY:
    - O(n)

    SPACE COMPLEXITY:
    - O(n)
    ========================================================
    */
int totalFruit_optimal(vector<int>& fruits) {
    int l = 0, r = 0, maxlen = 0;
    unordered_map<int, int> mpp;

    while (r < fruits.size()) {
        mpp[fruits[r]]++;

        // Shrink window when more than 2 types
        if (mpp.size() > 2) {
            mpp[fruits[l]]--;
            if (mpp[fruits[l]] == 0) mpp.erase(fruits[l]);
            l++;
        }

        if(mpp.size()<=2){
        // Update maxlen
        maxlen = max(maxlen, r - l + 1);
        }
        r++;
    }

    return maxlen;
}

// ---------------- MAIN FUNCTION ----------------
int main() {
    vector<int> fruits = {1, 2, 1, 2, 3, 2, 2, 1};

    cout << "Brute Force: " << totalFruits_brute(fruits) << endl;
    cout << "Better (Sliding Window): " << totalFruit_better(fruits) << endl;
    cout << "Optimal (Cleaned Sliding Window): " << totalFruit_optimal(fruits) << endl;

    return 0;
}
