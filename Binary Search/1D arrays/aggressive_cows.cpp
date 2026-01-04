#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

    /*
     * 🧠 INTUITION (Helper Function):
     * --------------------------------
     * We try to place cows greedily.
     * - Place the first cow in the first stall.
     * - For every next stall, place a cow only if
     *   the distance from the last placed cow is >= dist.
     * - If we can place at least 'cows' cows, return true.
     *
     * Time Complexity: O(N)
     * Space Complexity: O(1)
     */
bool canWePlace(vector<int>& arr, int dist, int cows) {
    int countCows = 1;         // Place first cow at the first stall
    int lastPlaced = arr[0];   // Last cow was placed at index 0

    for (int i = 1; i < arr.size(); i++) {
        if (arr[i] - lastPlaced >= dist) {
            countCows++;
            lastPlaced = arr[i];
        }
    }

    return countCows >= cows;
}

    /*
     * 🐢 BRUTE FORCE APPROACH
     * ------------------------
     * - Sort stall positions.
     * - Try every possible minimum distance from 1 to maxDist.
     * - For each distance, check if placement is possible.
     * - Stop when placement fails.
     *
     * Time Complexity:
     *   Sorting → O(N log N)
     *   Checking distances → O(maxDist * N)
     *   Overall → O(N log N + maxDist * N)
     *
     * Space Complexity: O(1)
     */
int aggressiveCowsBrute(vector<int>& arr, int cows) {
    sort(arr.begin(), arr.end());

    int maxDist = arr.back() - arr[0];
    int ans = 0;

    for (int dist = 1; dist <= maxDist; dist++) {
        if (canWePlace(arr, dist, cows)) {
            ans = dist; // Update answer if placement is possible
        } else {
            break; // Further distances will also fail
        }
    }

    return ans;
}

    /*
     * 🚀 OPTIMIZED APPROACH (Binary Search on Answer)
     * -----------------------------------------------
     * 🧠 INTUITION:
     * - We are maximizing the minimum distance.
     * - If we can place cows with distance 'd',
     *   then we can also place them with any smaller distance.
     * - If we cannot place cows with distance 'd',
     *   then any larger distance will also fail.
     *
     * Search Space:
     * - Minimum distance = 1
     * - Maximum distance = last stall - first stall
     *
     * Time Complexity:
     *   Sorting → O(N log N)
     *   Binary Search → O(log(maxDist))
     *   Placement check per mid → O(N)
     *   Overall → O(N log N)
     *
     * Space Complexity: O(1)
     */
int aggressive_cows(vector<int>& arr, int cows) {
    sort(arr.begin(), arr.end()); // Sort stall positions

    int low = 1;
    int high = arr.back() - arr[0]; // Max possible distance
    int ans = 0;

    while (low <= high) {
        int mid = low + (high - low) / 2;

        if (canWePlace(arr, mid, cows)) {
            ans = mid;       // Store current possible answer
            low = mid + 1;   // Try for a bigger distance
        } else {
            high = mid - 1;  // Try for a smaller distance
        }
    }

    return ans; //high
}

int main() {
    vector<int> stalls = {1, 2, 8, 4, 9};
    int cows = 3;

    int result = aggressive_cows(stalls, cows);
    cout << "Maximum minimum distance to place all cows: " << result << endl;
    result = aggressiveCowsBrute(stalls, cows);
    cout << "Maximum minimum distance (brute) to place all cows: " << result << endl;

    return 0;
}
