#include <bits/stdc++.h>
using namespace std;


int count_inversion_brute(vector<int>arr){
    int n=arr.size();
    int cnt=0;
    for(int i=0;i<n;i++){
        for(int j=i+1;j<n;j++){
            if(arr[i]>arr[j]) cnt++;
        }
    }
    return cnt;
}
// Time Complexity: O(n log n)

// Space Complexity: O(n) for the temporary array during merge.

// Merge function with inversion count
int merge(vector<int>& arr, int low, int mid, int high) {
    vector<int> temp;
    int left = low;
    int right = mid + 1;
    int cnt = 0;

    while (left <= mid && right <= high) {
        if (arr[left] <= arr[right]) {
            temp.push_back(arr[left]);
            left++;
        } else {
            temp.push_back(arr[right]);
            cnt += (mid - left + 1); // All remaining elements in left subarray are greater
            right++;
        }
    }

    while (left <= mid) {
        temp.push_back(arr[left]);
        left++;
    }
    while (right <= high) {
        temp.push_back(arr[right]);
        right++;
    }

    for (int i = low; i <= high; i++) {
        arr[i] = temp[i - low];
    }

    return cnt;
}

// Recursive merge sort with inversion count
int mergesort(vector<int>& arr, int low, int high) {
    int cnt = 0;
    if (low >= high) return 0;

    int mid = (low + high) / 2;
    cnt += mergesort(arr, low, mid);
    cnt += mergesort(arr, mid + 1, high);
    cnt += merge(arr, low, mid, high);

    return cnt;
}

// Utility: Count total inversions
int countInversions(vector<int>& arr) {
    return mergesort(arr, 0, arr.size() - 1);
}

// Main function for test
int main() {
    vector<int> arr = {5, 3, 2, 4, 1};
    cout << "Brute-force Count: " << count_inversion_brute(arr) << endl;
    cout << "Inversion Count: " << countInversions(arr) << endl;

    return 0;
}
