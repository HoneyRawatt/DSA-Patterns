#include<iostream>
#include<vector>
#include<climits>
using namespace std;


    // Helper function to check feasibility
    // Can we make at least m bouquets by 'days'?
    //
    // Time Complexity: O(n)
    // Space Complexity: O(1)
// Helper function to check if it's possible to make 'm' bouquets
// on or before day 'mid', using 'k' adjacent flowers per bouquet
bool possible(vector<int> arr, int days, int m, int k) {
    int cnt = 0, noofb = 0;
    for (int i = 0; i < arr.size(); i++) {
        if (arr[i] <= days) cnt++;
        else {
            noofb += cnt / k; // Form as m  any bouquets as possible
            cnt = 0;
        }
    }
    noofb += cnt / k; // In case bouquet(s) form at end
    return noofb >= m;
}

    // Brute Force Approach
    // Time Complexity: O((maxDay - minDay) * n)
    // Space Complexity: O(1)
// Brute-force approach to try every day
int roseGardenBrute(vector<int> arr, int m, int k) {
    long long required = 1LL * m * k;
    if (required > arr.size()) return -1;

    int mini = INT_MAX, maxi = INT_MIN;
    for (int x : arr) {
        mini = min(mini, x);
        maxi = max(maxi, x);
    }

    // Try every day from earliest to latest
    for (int day = mini; day <= maxi; day++) {
        if (possible(arr, day, m, k)) {
            return day;
        }
    }

    return -1; // Should not reach here unless invalid input
}

    // Optimized Binary Search Approach
    // Time Complexity: O(n log(maxDay - minDay))
    // Space Complexity: O(1)
    //
    // Intuition:
    // - Answer lies between minimum and maximum bloom day
    // - If we can make bouquets on day = mid,
    //   try earlier days (minimize answer)
// Main function to find the minimum day to make 'm' bouquets of 'k' flowers
int roseGarden(vector<int> arr, int m, int k) {
    long long val = 1LL * m * k;
    if (val > arr.size()) return -1; // Not enough flowers

    int mini = INT_MAX, maxi = INT_MIN;
    for (int i = 0; i < arr.size(); i++) {
        mini = min(arr[i], mini);
        maxi = max(arr[i], maxi);
    }

    int low = mini, high = maxi;
    while (low <= high) {
        int mid = low + ((high - low) / 2);
        if (possible(arr, mid, m, k)) {
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }
    return low;
}

// Main function for testing
int main() {
    vector<int> bloomDay = {1, 10, 3, 10, 2};
    int m = 3, k = 1;

    int result = roseGarden(bloomDay, m, k);
    if (result == -1)
        cout << "It's not possible to make " << m << " bouquets." << endl;
    else
        cout << "Minimum day to make " << m << " bouquets: " << result << endl;

    return 0;
}
