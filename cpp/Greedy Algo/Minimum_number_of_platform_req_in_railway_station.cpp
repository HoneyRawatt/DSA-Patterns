#include <bits/stdc++.h>
using namespace std;

/*
------------------------------------------------------------
🔹 PROBLEM: Minimum Number of Platforms (GFG)
------------------------------------------------------------
Given arrival and departure times of trains at a station, 
find the minimum number of platforms required so that no train 
has to wait for another to leave.

Example:
Input:
arr[] = [900, 940, 950, 1100, 1500, 1800]
dep[] = [910, 1200, 1120, 1130, 1900, 2000]
Output: 3
------------------------------------------------------------
*/


// 🔸 Brute Force O(N²)
int minNumberOfPlatformBrute(vector<int>& arr, vector<int>& dep) {
    int n = arr.size();
    int maxCnt = 0;

    for (int i = 0; i < n; i++) {
        int cnt = 1; // platform needed for current train
        for (int j = i + 1; j < n; j++) {
            // Overlapping condition: another train arrives before current departs
            if (arr[j] <= dep[i] && arr[i] <= dep[j])
                cnt++;
        }
        maxCnt = max(maxCnt, cnt);
    }
    return maxCnt;
}


/*
------------------------------------------------------------
🔹 Optimized Greedy O(N log N)
------------------------------------------------------------
Approach:
1️⃣ Sort both arrival and departure times.
2️⃣ Use two pointers (i for arrival, j for departure):
     - If a train arrives before or at the same time as a departure,
       → need a new platform → increment count.
     - If a train departs before the next arrives,
       → free a platform → decrement count.
3️⃣ Track the maximum count at any point — that’s the answer.
------------------------------------------------------------
*/
int minNumberOfPlatform(vector<int>& arr, vector<int>& dep) {
    int n = arr.size();
    sort(arr.begin(), arr.end());
    sort(dep.begin(), dep.end());

    int i = 0, j = 0;
    int cnt = 0, maxCnt = 0;

    while (i < n && j < n) {
        if (arr[i] <= dep[j]) {   // a train arrives before previous departs
            cnt++;
            i++;
        } else {                  // a train departs → free a platform
            cnt--;
            j++;
        }
        maxCnt = max(maxCnt, cnt);
    }

    return maxCnt;
}


/*
------------------------------------------------------------
🔹 MAIN FUNCTION (for testing)
------------------------------------------------------------
*/
int main() {
    vector<int> arr = {900, 940, 950, 1100, 1500, 1800};
    vector<int> dep = {910, 1200, 1120, 1130, 1900, 2000};

    cout << "Brute Force: " << minNumberOfPlatformBrute(arr, dep) << endl;
    cout << "Optimized: " << minNumberOfPlatform(arr, dep) << endl;

    return 0;
}

/*
------------------------------------------------------------
🔹 INTUITION
------------------------------------------------------------
- Each train arrival either increases or decreases the platform need.
- We simulate the train station timeline by sorting arrivals and departures.
- Whenever an arrival happens before a departure → need one more platform.
- Whenever a departure happens → one platform becomes free.
- Keep track of the max platforms needed at any moment.

🕒 Time Complexity:
  - Brute Force: O(N²)
  - Optimized:   O(N log N)   (sorting dominates)
💾 Space Complexity:
  - O(1) extra space
------------------------------------------------------------
*/
