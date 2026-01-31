#include<iostream>
#include<vector>
#include<map>
using namespace std;

/*
 * Optimal Approach using Hash Map
 * Time Complexity: O(n)
 * Space Complexity: O(n) for map
 */
int subarray_with_sum_k(vector<int> a, int k) {
    int sum = 0;
    map<int, int> mp;
    int n = a.size();
    int cnt = 0;

    mp[sum] = 1; // Initialize with prefix sum 0

    for (int i = 0; i < n; i++) {
        sum += a[i];

        int x = sum - k;
        cnt += mp[x]; // Add number of times x has occurred so far

        mp[sum]++;
    }

    return cnt;
}

/*
 * Brute-force Approach
 * Time Complexity: O(n^2)
 * Space Complexity: O(1)
 */
int subarray_with_sum_k_brute(vector<int> a, int k) {
    int n = a.size();
    int cnt = 0;

    for (int i = 0; i < n; i++) {
        int sum = 0;
        for (int j = i; j < n; j++) {
            sum+= a[j]; 
            if (sum == k) cnt++;
        }
    }

    return cnt;
}
