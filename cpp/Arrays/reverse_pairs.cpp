#include <bits/stdc++.h>
using namespace std;


int reverse_pairs_brute(vector<int>arr){
      int n=arr.size();
    int cnt=0;
    for(int i=0;i<n;i++){
        for(int j=i+1;j<n;j++){
            if(arr[i]>2*arr[j]) cnt++;
        }
    }
    return cnt;
}
// Type	                 Complexity
// Time	                 O(n log n)
// Space (Auxiliary)	 O(n)
// Count pairs where arr[i] > 2*arr[j]
int countPairs(vector<int>& arr, int low, int mid, int high) {
    int cnt = 0;
    int right = mid + 1;

    for (int i = low; i <= mid; i++) {
        while (right <= high && arr[i] > 2LL * arr[right]) {
            right++;
        }
        cnt += (right - (mid + 1));
    }

    return cnt;
}

// Merge function to sort the two halves
void merge(vector<int>& arr, int low, int mid, int high) {
    vector<int> temp;
    int left = low;
    int right = mid + 1;

    while (left <= mid && right <= high) {
        if (arr[left] <= arr[right]) {
            temp.push_back(arr[left++]);
        } else {
            temp.push_back(arr[right++]);
        }
    }

    while (left <= mid) {
        temp.push_back(arr[left++]);
    }

    while (right <= high) {
        temp.push_back(arr[right++]);
    }

    for (int i = low; i <= high; i++) {
        arr[i] = temp[i - low];
    }
}

// Merge sort with reverse pair counting
int mergesort(vector<int>& arr, int low, int high) {
    if (low >= high) return 0;
    
    int mid = (low + high) / 2;
    int cnt = 0;
    cnt += mergesort(arr, low, mid);
    cnt += mergesort(arr, mid + 1, high);
    cnt += countPairs(arr, low, mid, high);
    merge(arr, low, mid, high);

    return cnt;
}

// Wrapper function
int countReversePairs(vector<int>& nums) {
    return mergesort(nums, 0, nums.size() - 1);
}

int main() {
    vector<int> arr = {1, 3, 2, 3, 1};

    cout << "Original Array: ";
    for (int x : arr) cout << x << " ";
    cout << "\n\n";

    // Brute-force
    cout << "Brute-force Reverse Pairs Count: "
         << reverse_pairs_brute(arr) << endl;

    // Optimized
    vector<int> arr_copy = arr; // To avoid in-place modification
    cout << "Optimized Merge Sort Reverse Pairs Count: "
         << countReversePairs(arr_copy) << endl;

    return 0;
}