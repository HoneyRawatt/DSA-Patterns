#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

    /*
     * INTUITION:
     * ----------
     * We are looking for the smallest divisor such that:
     * sum( ceil(nums[i] / divisor) ) <= limit
     *
     * If divisor is SMALL  → division result is LARGE → sum is LARGE
     * If divisor is LARGE  → division result is SMALL → sum is SMALL
     *
     * Hence, the sum function is MONOTONICALLY DECREASING.
     * This allows us to apply BINARY SEARCH on the answer (divisor).
     *
     * TIME COMPLEXITY:
     * ----------------
     * For one divisor check: O(n)
     * Binary search range: log(max(nums))
     * Overall: O(n * log(max(nums)))
     *
     * SPACE COMPLEXITY:
     * -----------------
     * O(1) – No extra space used
     */

    // Helper function to calculate:
    // sum = Σ ceil(nums[i] / div)
int sumbyd(vector<int> arr, int div,int limit) {
    int sum = 0;
    for (int i = 0; i < arr.size(); i++) {
        // Same as ceil(arr[i] / div)
        sum += (arr[i] + div - 1) / div;
        if(sum>limit) break;
    }
    return sum;
}

    /*
     * BRUTE FORCE APPROACH
     *
     * Try every possible divisor from 1 to max(nums)
     * Return the first divisor for which sumByDiv <= limit
     *
     * TIME COMPLEXITY: O(n * max(nums))
     * SPACE COMPLEXITY: O(1)
     *
     * This approach is slow and not suitable for large inputs.
     */
int smallestDivisorBrute(vector<int> arr, int limit) {
    int maxVal = *max_element(arr.begin(), arr.end());

    for (int div = 1; div <= maxVal; div++) {
        if (sumbyd(arr, div, limit) <= limit) {
            return div; // First valid divisor found
        }
    }

    return maxVal; // Fallback, though this line should never be reached
}

    /*
     * OPTIMAL APPROACH – BINARY SEARCH ON ANSWER
     *
     * Search space:
     * low  = 1
     * high = max(nums)
     *
     * For each mid divisor:
     *  - If sumByDiv(mid) <= limit → valid divisor, try smaller
     *  - Else → divisor too small, try bigger
     *
     * TIME COMPLEXITY:
     * O(n * log(max(nums)))
     *
     * SPACE COMPLEXITY:
     * O(1)
     */
int smallestDivisor(vector<int> arr, int limit) {
    int low = 1;
    int high = *max_element(arr.begin(), arr.end()); // max value in array

    while (low <= high) {
        int mid = low + ((high - low) / 2);
        if (sumbyd(arr, mid,limit) <= limit)
            high = mid - 1; // try smaller divisor
        else
            low = mid + 1;  // try bigger divisor
    }

    return low; // lowest valid divisor
}

// Driver code with example input
int main() {
    vector<int> nums = {1, 2, 5, 9};  // Input array
    int limit = 6;                    // Maximum allowed sum after division

    int result = smallestDivisor(nums, limit);
    cout << "Smallest divisor such that the division sum is <= " << limit << " is: " << result << endl;
    result = smallestDivisorBrute(nums, limit);
    cout << "Smallest divisor (brute) such that division sum <= " << limit << " is: " << result << endl;
    return 0;
}
