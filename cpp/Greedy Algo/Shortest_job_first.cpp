#include <bits/stdc++.h>
using namespace std;

// 🧩 Function: shortestjobfirst
// ---------------------------------------------------------
// Given an array of job durations, this function computes
// the total waiting time when jobs are scheduled using
// the Shortest Job First (SJF) order.
//
// Intuition:
//  - To minimize total waiting time, execute shorter jobs first.
//  - Sort job durations in ascending order.
//  - For each job, waiting time = sum of all previous job durations.
//
// Example: [3,1,4,2] → sort → [1,2,3,4]
//  Waiting times: [0,1,3,6] → Total = 10
// ---------------------------------------------------------
int shortestjobfirst(vector<int>& arr) {
    // Sort job durations ascending: shortest jobs first
    sort(arr.begin(), arr.end());
    
    int t = 0;    // t = cumulative elapsed time so far
    int wt = 0;   // wt = total waiting time
    
    // Calculate total waiting time
    for (int i = 0; i < (int)arr.size(); i++) {
        wt += t;      // current job waits for all previous jobs
        t += arr[i];  // add current job's duration to elapsed time
    }

    return wt;
}

int main() {
    vector<int> jobs = {3, 1, 4, 2};
    int totalWaiting = shortestjobfirst(jobs);
    cout << "Total waiting time: " << totalWaiting << endl;
    return 0;
}

/*
---------------------------------------------------------
🧠 Intuition:
---------------------------------------------------------
The Shortest Job First (SJF) scheduling minimizes total waiting time
by always executing the smallest-duration job first.
Sorting ensures we handle shorter jobs before longer ones.

Each job's waiting time = sum of all previous job durations.
Total waiting time = sum of all such waiting times.

---------------------------------------------------------
⏱️ Time Complexity:
---------------------------------------------------------
Sorting the array: O(n log n)
Loop to sum waiting times: O(n)
➡️ Overall Time Complexity: O(n log n)

---------------------------------------------------------
💾 Space Complexity:
---------------------------------------------------------
STL sort is in-place → O(1) extra space
Only a few integer variables are used
➡️ Overall Space Complexity: O(1)
-------------------------------------
