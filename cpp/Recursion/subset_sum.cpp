#include <bits/stdc++.h>
using namespace std;

void subset_sum(int ind, int sum, vector<int>& arr, vector<int>& ans) {
    if (ind == arr.size()) {
        ans.push_back(sum);
        return;
    }
    // pick the element
    subset_sum(ind + 1, sum + arr[ind], arr, ans);

    // do not pick the element
    subset_sum(ind + 1, sum, arr, ans);
}

int main() {
    vector<int> arr = {3, 1, 4};
    vector<int> ans;

    subset_sum(0, 0, arr, ans);
    sort(ans.begin(), ans.end());

    for (auto& v : ans) {
        cout << v << " ";
    }

    return 0;
}

// ⏱️ Time Complexity
// O(2^n)
// Each element has two choices (pick / not pick)
// Total subsets = 2^n

// 📦 Space Complexity
// O(n)
// Maximum recursion depth = n
// Auxiliary space for current recursion
// Output list ans not counted in auxiliary space
