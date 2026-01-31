#include <iostream>
#include <vector>
#include <map>
using namespace std;

// Function to count number of subarrays whose sum equals k
int count_subarray_sum_k_optimize(vector<int>& arr, int k) {
    map<int, int> mpp;  // Map to store frequency of prefix sums
    mpp[0] = 1;         // Base case: one subarray with sum = 0 before starting
    int presum = 0, cnt = 0;

    for (int i = 0; i < arr.size(); i++) {
        presum += arr[i];              // Cumulative prefix sum
        int remove = presum - k;       // Required sum to be removed
        cnt += mpp[remove];            // If remove exists in map, we found subarray(s)
        mpp[presum] += 1;              // Store/update frequency of current prefix sum
    }

    return cnt;
}

int main() {
    vector<int> arr = {1, 2, 3, -2, 5, 1};  // Example array
    int k = 5;                              // Target subarray sum

    int result = count_subarray_sum_k_optimize(arr, k);

    cout << "Number of subarrays with sum = " << k << " is: " << result << endl;

    return 0;
}
