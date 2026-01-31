#include<iostream>
#include<vector>
#include<map>
using namespace std;

/*
 * Optimal Approach using Hash Map
 * Time Complexity: O(n)
 * Space Complexity: O(n) for map
 */
int subarray_with_xor_k(vector<int> a, int k) {
    int xr = 0;
    map<int, int> mp;
    int n = a.size();
    int cnt = 0;

    mp[xr] = 1; // Initialize with prefix XOR 0

    for (int i = 0; i < n; i++) {
        xr ^= a[i];

        // We need prefix XOR = xr ^ k to satisfy: (prefix_xor) ^ (xr) = k
        int x = xr ^ k;
        cnt += mp[x]; // Add number of times x has occurred so far

        mp[xr]++;
    }

    return cnt;
}

/*
 * Brute-force Approach
 * Time Complexity: O(n^2)
 * Space Complexity: O(1)
 */
int subarray_with_xor_k_brute(vector<int> a, int k) {
    int n = a.size();
    int cnt = 0;

    for (int i = 0; i < n; i++) {
        int xr = 0;
        for (int j = i; j < n; j++) {
            xr ^= a[j]; 
            if (xr == k) cnt++;
        }
    }

    return cnt;
}
