#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

/*
 * Brute-force Approach
 * Time Complexity: O(n^2) (due to nested loop)
 * Space Complexity: O(n) for result
 */
vector<vector<int>> merge_overlapping_intervals_brute(vector<vector<int>>& arr) {
    int n = arr.size();
    sort(arr.begin(), arr.end());  // Sort by start times

    vector<vector<int>> ans;
    for (int i = 0; i < n; i++) {
        int start = arr[i][0];
        int end = arr[i][1];

        // Skip if current interval is already covered
        if (!ans.empty() && end <= ans.back()[1]) continue;

        // Try to merge with upcoming intervals
        for (int j = i + 1; j < n; j++) {
            if (arr[j][0] <= end) {
                end = max(end, arr[j][1]);
            } else {
                break;
            }
        }

        ans.push_back({start, end});
    }

    return ans;
}

/*
 * Optimal Approach
 * Time Complexity: O(n log n) (due to sorting + linear traversal)
 * Space Complexity: O(n) for result
 */
vector<vector<int>> merge_overlapping_intervals_optimized(vector<vector<int>>& arr) {
    int n = arr.size();
    sort(arr.begin(), arr.end());  // Sort by start times

    vector<vector<int>> ans;

    for (int i = 0; i < n; i++) {
        if (ans.empty() || arr[i][0] > ans.back()[1]) {
            ans.push_back(arr[i]);  // No overlap
        } else {
            // Overlap: merge with last interval
            ans.back()[1] = max(ans.back()[1], arr[i][1]);
        }
    }

    return ans;
}

void print_intervals(const vector<vector<int>>& intervals) {
    for (auto interval : intervals) {
        cout << "[" << interval[0] << ", " << interval[1] << "] ";
    }
    cout << endl;
}

int main() {
    vector<vector<int>> intervals = {
        {1, 3}, {2, 6}, {8, 10}, {15, 18}, {17, 20}
    };

    auto brute = merge_overlapping_intervals_brute(intervals);
    auto opt = merge_overlapping_intervals_optimized(intervals);

    cout << "Brute-force Merged Intervals: ";
    print_intervals(brute);

    cout << "Optimized Merged Intervals: ";
    print_intervals(opt);

    return 0;
}
