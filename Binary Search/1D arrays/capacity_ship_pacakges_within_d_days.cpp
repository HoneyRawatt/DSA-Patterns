#include<iostream>
#include<vector>
#include<algorithm>
#include<numeric>  // For accumulate()
using namespace std;

    /*
     * INTUITION:
     * ------------
     * We are given weights of packages in order.
     * Each day we can ship packages in sequence, but total weight per day
     * cannot exceed the ship capacity.
     *
     * We want the MINIMUM ship capacity such that all packages
     * can be shipped within 'd' days.
     *
     * Observations:
     * - Minimum possible capacity = max weight (at least one package must fit)
     * - Maximum possible capacity = sum of all weights (ship everything in one day)
     *
     * The answer lies between [maxWeight, sumWeights]
     * and the condition "can ship within D days" is MONOTONIC.
     *
     * Hence → Binary Search on answer.
     */
// Helper function: simulate number of days needed for a given capacity
int findDays(vector<int> arr, int cap) {
    int days = 1, load = 0;
    for (int i = 0; i < arr.size(); i++) {
        if (load + arr[i] > cap) {
            days++;         // Need one more day
            load = arr[i];  // Start new day with current item
        } else {
            load += arr[i]; // Add to current day's load
        }
    }
    return days;
}

    /*
     * BRUTE FORCE APPROACH
     * --------------------
     * Try every capacity from maxWeight to sumWeights
     * and return the first capacity that can ship in <= D days.
     *
     * Time Complexity: O((sum - max) * N)
     * Space Complexity: O(1)
     * (Too slow for large inputs)
     */
// Brute-force version: Try every possible capacity from max to sum
int leastWeightCapacityBrute(vector<int> arr, int d) {
    int low = *max_element(arr.begin(), arr.end());
    int high = accumulate(arr.begin(), arr.end(), 0);

    for (int cap = low; cap <= high; cap++) {
        if (findDays(arr, cap) <= d) {
            return cap; // First capacity that works
        }
    }

    return high; // Fallback, shouldn't be needed
}

    /*
     * OPTIMAL APPROACH (Binary Search)
     * --------------------------------
     * Search space: [maxWeight, sumWeights]
     *
     * If capacity works (days <= D):
     *     try smaller capacity
     * else:
     *     increase capacity
     *
     * Time Complexity:
     * O(N * log(sumWeights - maxWeight))
     *
     * Space Complexity:
     * O(1)
     */
// Binary Search to find least capacity to ship within 'd' days
int leastWeightCapacity(vector<int> arr, int d) {
    int low = *max_element(arr.begin(), arr.end());               // Minimum capacity needed
    int high = accumulate(arr.begin(), arr.end(), 0);             // Max capacity = all in one day

    while (low <= high) {
        int mid = low + (high - low) / 2;
        int requiredDays = findDays(arr, mid);
        if (requiredDays <= d)
            high = mid - 1;  // Try smaller capacity
        else
            low = mid + 1;   // Need more capacity
    }
    return low;
}

int main() {
    vector<int> weights = {1, 2, 3, 1, 1};
    int days = 4;
    cout << "Least capacity to ship in " << days << " days: "
         << leastWeightCapacity(weights, days) << endl;
    cout << "Least capacity (brute) to ship in " << days << " days: "
         << leastWeightCapacityBrute(weights, days) << endl;
    return 0;
}
