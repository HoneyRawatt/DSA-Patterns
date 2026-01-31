#include <bits/stdc++.h>
using namespace std;

/*
===================================================================
🔹 PROBLEM: N Meetings in One Room
===================================================================
Given start[] and end[] times of N meetings, find the maximum number 
of meetings that can be accommodated in a single room such that 
no two meetings overlap.

Approach:
---------
1️⃣ Store each meeting with (start, end, position)
2️⃣ Sort meetings by end time (ascending)
3️⃣ Always pick the next meeting whose start time is 
    greater than the end time of the last selected meeting.

🕒 Time Complexity:  O(N log N)
💾 Space Complexity: O(N)
===================================================================
*/

// Structure for meeting data
struct Meeting {
    int start;
    int end;
    int pos;
};

// Comparator — sort by earliest end time
bool comp(Meeting a, Meeting b) {
    if (a.end == b.end) return a.pos < b.pos;
    return a.end < b.end;
}

// Function to find maximum number of meetings
vector<int> max_meeting(vector<int>& start, vector<int>& end, int n) {
    vector<Meeting> arr(n);
    for (int i = 0; i < n; i++) {
        arr[i].start = start[i];
        arr[i].end = end[i];
        arr[i].pos = i + 1; // store 1-based index
    }

    // Sort meetings by end time
    sort(arr.begin(), arr.end(), comp);

    vector<int> ans;
    ans.push_back(arr[0].pos);
    int lastEnd = arr[0].end;

    // Select meetings greedily
    for (int i = 1; i < n; i++) {
        if (arr[i].start > lastEnd) {
            ans.push_back(arr[i].pos);
            lastEnd = arr[i].end;
        }
    }

    return ans;
}

/*
===================================================================
🔹 INTUITION
===================================================================
- This is a greedy scheduling problem.
- By always choosing the meeting that ends earliest, we maximize
  the time left for future meetings.
===================================================================
*/

// ---------------- MAIN FUNCTION ----------------
int main() {
    vector<int> start = {1, 3, 0, 5, 8, 5};
    vector<int> end   = {2, 4, 6, 7, 9, 9};
    int n = start.size();

    vector<int> ans = max_meeting(start, end, n);

    cout << "Meetings that can be scheduled (by position): ";
    for (int x : ans) cout << x << " ";
    cout << endl;

    return 0;
}

/*
===================================================================
✅ OUTPUT EXAMPLE:
Meetings that can be scheduled (by position): 1 2 4 5

✅ TIME COMPLEXITY:
O(N log N)  → sorting + single pass selection

✅ SPACE COMPLEXITY:
O(N)        → for meeting storage

🔗 GFG Link:
https://www.geeksforgeeks.org/problems/n-meetings-in-one-room-1587115620
===================================================================
*/