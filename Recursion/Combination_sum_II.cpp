#include <bits/stdc++.h>
using namespace std;

void find_combo(int ind, int arr[], int n, int target, vector<vector<int>>& ans, vector<int>& ds) {
    if (target == 0) {
        ans.push_back(ds);
        return;
    }

    for (int i = ind; i < n; i++) {
        // Skip duplicates
        if (i > ind && arr[i] == arr[i - 1]) continue;

        // Stop if the current number exceeds the remaining target
        if (arr[i] > target) break;

        ds.push_back(arr[i]);
        find_combo(i + 1, arr, n, target - arr[i], ans, ds); // i+1 ensures each element is used once
        ds.pop_back(); // backtrack
    }
}

int main() {
    int arr[] = {1, 1, 1, 2, 2};
    int n = sizeof(arr) / sizeof(arr[0]);
    int target = 4;

    // Sort to handle duplicates
    sort(arr, arr + n);

    vector<int> ds;
    vector<vector<int>> ans;

    find_combo(0, arr, n, target, ans, ds);

    // Print all combinations
    for (auto& v : ans) {
        for (int num : v)
            cout << num << " ";
        cout << endl;
    }

    return 0;
}

// ⏱️ Time Complexity
// O(2^n * k)
// n = number of elements
// Each subset explored once
// Copying a valid combination costs O(k)
// Pruning + duplicate skipping reduces actual runtime

// 📦 Space Complexity
// O(k)
// k = maximum depth of recursion
// Output space not counted