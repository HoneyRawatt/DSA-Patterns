#include <bits/stdc++.h>
using namespace std;

/*
------------------------------------------------------------
🔹 Problem: Insert Interval (LeetCode 57)
------------------------------------------------------------
You are given an array of non-overlapping intervals sorted by start time,
and a new interval to insert.

Insert the new interval in the correct position, merging if necessary,
and return the resulting list of intervals.

Example:
Input: intervals = [[1,3],[6,9]], newInterval = [2,5]
Output: [[1,5],[6,9]]
------------------------------------------------------------
*/

class Solution {
public:
    vector<vector<int>> insert(vector<vector<int>>& intervals, vector<int>& newInterval) {
        vector<vector<int>> res;
        int i = 0;
        int n = intervals.size();  

        // 1️⃣ Add all intervals ending before newInterval starts (left side)
        while (i < n && intervals[i][1] < newInterval[0]) {
            res.push_back(intervals[i]);
            i++;
        }

        // 2️⃣ Merge all overlapping intervals
        while (i < n && intervals[i][0] <= newInterval[1]) {
            newInterval[0] = min(newInterval[0], intervals[i][0]);
            newInterval[1] = max(newInterval[1], intervals[i][1]);
            i++;
        }
        res.push_back(newInterval);  // push the merged new interval

        // 3️⃣ Add remaining intervals (right side)
        while (i < n) {
            res.push_back(intervals[i]);
            i++;
        }

        return res;
    }
};

/*
------------------------------------------------------------
🔹 MAIN FUNCTION (for testing)
------------------------------------------------------------
*/
int main() {
    Solution sol;
    vector<vector<int>> intervals = {{1,3}, {6,9}};
    vector<int> newInterval = {2,5};

    vector<vector<int>> result = sol.insert(intervals, newInterval);

    cout << "Resulting intervals: ";
    for (auto &it : result) {
        cout << "[" << it[0] << "," << it[1] << "] ";
    }
    cout << endl;

    return 0;
}

/*
------------------------------------------------------------
🔹 INTUITION
------------------------------------------------------------
1️⃣ Add all intervals that end before the new interval starts → no overlap.
2️⃣ Merge all overlapping intervals into a single combined interval.
3️⃣ Add all intervals that start after the merged new interval ends.

This ensures the final list remains sorted and non-overlapping.

🕒 Time Complexity:  O(N)
    → Single pass through all intervals.
💾 Space Complexity: O(N)
    → Result vector stores merged intervals.

✅ Example:
Input: [[1,3],[6,9]], newInterval = [2,5]
Step 1: Left part → [[1,3]] overlaps, so merge → [1,5]
Step 2: Add right part → [[1,5],[6,9]]
Output: [[1,5],[6,9]]
------------------------------------------------------------
*/
