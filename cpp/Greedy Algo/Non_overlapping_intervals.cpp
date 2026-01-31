#include <bits/stdc++.h>
using namespace std;

/*
------------------------------------------------------------
🔹 Problem: Non-overlapping Intervals (LeetCode 435)
------------------------------------------------------------
Given an array of intervals where intervals[i] = [start_i, end_i],
return the minimum number of intervals you need to remove to make
the rest of the intervals non-overlapping.

Example:
Input: [[1,2],[2,3],[3,4],[1,3]]
Output: 1  → Remove [1,3]
------------------------------------------------------------
*/

/* Comparator function to sort intervals by end time (ascending) */
bool comp(const vector<int>& a, const vector<int>& b) {
    return a[1] < b[1];
}

/*
------------------------------------------------------------
🔹 eraseOverlapIntervals FUNCTION
------------------------------------------------------------
Approach (Greedy):
1️⃣ Sort intervals by their ending time (earliest end first).
2️⃣ Keep track of the last selected interval’s end time.
3️⃣ Iterate through intervals:
      - If the current interval starts after or at `lastEnd`,
        it does NOT overlap → include it.
      - Else → it overlaps → skip it.
4️⃣ Answer = total_intervals - count_of_non_overlapping_intervals

This ensures we always choose intervals that end earlier,
leaving more room for future intervals.
------------------------------------------------------------
*/
int eraseOverlapIntervals(vector<vector<int>>& intervals) {
    if (intervals.empty()) return 0;

    // Step 1: Sort intervals by end time
    sort(intervals.begin(), intervals.end(), comp);

    int n = intervals.size();
    int count = 1;              // number of non-overlapping intervals
    int lastEnd = intervals[0][1]; // end time of the last selected interval

    // Step 2: Iterate through intervals
    for (int i = 1; i < n; i++) {
        // If current interval starts after or at lastEnd → no overlap
        if (intervals[i][0] >= lastEnd) {
            count++;
            lastEnd = intervals[i][1]; // update last end
        }
        // else → overlapping → skip this interval
    }

    // Step 3: Minimum to remove = total - non-overlapping
    return n - count;
}

/*
------------------------------------------------------------
🔹 MAIN FUNCTION (for testing)
------------------------------------------------------------
*/
int main() {
    vector<vector<int>> intervals = {{1,2}, {2,3}, {3,4}, {1,3}};
    
    int result = eraseOverlapIntervals(intervals);
    cout << "Minimum intervals to remove: " << result << endl;
    
    return 0;
}

/*
------------------------------------------------------------
🔹 INTUITION
------------------------------------------------------------
- Sorting by end time ensures we always pick the interval that 
  finishes earliest — leaving maximum room for future ones.
- Whenever the next interval starts before the current one ends,
  it overlaps → we skip it.
- Count how many intervals do NOT overlap, and subtract from total.

🕒 Time Complexity:  O(N log N)
    → Sorting dominates (N intervals)
💾 Space Complexity: O(1)
    → Only constant extra variables used
------------------------------------------------------------
*/
