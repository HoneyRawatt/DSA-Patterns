#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

/*
=====================================================
PROBLEM STATEMENT:
-----------------------------------------------------
Given an array arr of non-negative integers representing
elevation heights where the width of each bar is 1, 
compute how much water it can trap after raining.

Example:
Input:  [0,1,0,2,1,0,1,3,2,1,2,1]
Output: 6
=====================================================
*/

/*
=====================================================
APPROACH 1: Using Precomputed Right Max (Prefix + Suffix)
-----------------------------------------------------
INTUITION:
- For each position i, the water it can hold is:
      min(max height to left, max height to right) - height[i]
- Precompute the maximum height to the right for each element
- Keep track of left maximum while traversing from left to right

TIME COMPLEXITY:
- O(n) for building suffixmax + O(n) for traversal => O(n)

SPACE COMPLEXITY:
- O(n) for suffixmax array
=====================================================
*/
int trapping_rain_water_2n(vector<int>& arr) {
    int n = arr.size();
    if (n == 0) return 0;

    // Precompute right max
    vector<int> suffixmax(n);
    suffixmax[n-1] = arr[n-1];
    for (int i = n-2; i >= 0; i--) {
        suffixmax[i] = max(suffixmax[i+1], arr[i]);
    }

    int total = 0, leftmax = 0;
    for (int i = 0; i < n; i++) {
        leftmax = max(leftmax, arr[i]);
        total += min(leftmax, suffixmax[i]) - arr[i];
    }

    return total;
}

/*
=====================================================
APPROACH 2: OPTIMAL TWO-POINTER METHOD
-----------------------------------------------------
INTUITION:
- Use two pointers, left (l) and right (r)
- Keep track of max height on left (lmax) and right (rmax)
- Water trapped at l or r depends on the smaller of lmax and rmax
- Move pointer from the side with smaller height

WHY THIS WORKS:
- At every step, the smaller boundary guarantees that water
  trapped is limited by it, so we can safely add water.

TIME COMPLEXITY:
- O(n), each element is processed once

SPACE COMPLEXITY:
- O(1), only variables used
=====================================================
*/
int trapping_rain_water(vector<int>& arr) {
    int n = arr.size();
    if (n == 0) return 0;

    int l = 0, r = n - 1;    // Two pointers
    int lmax = 0, rmax = 0;  // Maximum heights
    int total = 0;

    while (l <= r) {
        if (arr[l] <= arr[r]) {
            if (arr[l] >= lmax)
                lmax = arr[l];          // Update left max
            else
                total += lmax - arr[l]; // Water trapped at l
            l++;
        } else {
            if (arr[r] >= rmax)
                rmax = arr[r];          // Update right max
            else
                total += rmax - arr[r]; // Water trapped at r
            r--;
        }
    }
    return total;
}

int main() {
    vector<int> arr = {0,1,0,2,1,0,1,3,2,1,2,1};

    cout << "Brute Force: " << trapping_rain_water_2n(arr) << endl;
    cout << "Optimal: " << trapping_rain_water(arr) << endl;

    return 0;
}
