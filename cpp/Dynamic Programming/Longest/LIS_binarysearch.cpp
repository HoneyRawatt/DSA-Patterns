#include <bits/stdc++.h>
using namespace std;

/*
    Intuition:
    - Maintain a temporary array `temp`
    - temp[k] stores the smallest possible tail of an
      increasing subsequence of length (k+1)
    - temp is NOT the actual LIS, only helps compute length
*/

int longestIncreasingSubsequence(int arr[], int n) {
    vector<int> temp;
    temp.push_back(arr[0]);

    for (int i = 1; i < n; i++) {
        if (arr[i] > temp.back()) {
            temp.push_back(arr[i]);
        } else {
            int ind = lower_bound(temp.begin(), temp.end(), arr[i]) - temp.begin();
            temp[ind] = arr[i];
        }
    }
    return temp.size();
}
