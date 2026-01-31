#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

    /*
     * Time Complexity Intuition:
     * --------------------------
     * - The array is recursively divided into two halves → log₂(n) levels.
     * - At each level, merging takes O(n) time.
     *
     * Total Time Complexity:
     * Worst Case  : O(n log n)
     * Average Case: O(n log n)
     * Best Case   : O(n log n)
     *
     * Space Complexity Intuition:
     * ---------------------------
     * - A temporary array is used during each merge step.
     * - Extra space proportional to the size of the array is required.
     *
     * Space Complexity: O(n)
     */

void merge(vector<int>& arr, int low, int mid, int high) {
    vector<int> temp;
    int left = low;
    int right = mid + 1;

    while (left <= mid && right <= high) {
        if (arr[left] < arr[right]) temp.push_back(arr[left++]);
        else temp.push_back(arr[right++]);
    }

    while (left <= mid) temp.push_back(arr[left++]);
    while (right <= high) temp.push_back(arr[right++]);

    for (int i = low; i <= high; i++) {
        arr[i] = temp[i - low]; 
    }
}

void mergesort(vector<int>& arr, int low, int high) {
    if (low >= high) return;
    int mid = (low + high) / 2;
    mergesort(arr, low, mid);
    mergesort(arr, mid + 1, high);
    merge(arr, low, mid, high);
}

int main() {
    vector<int> arr = {64, 25, 12, 22, 11};
    mergesort(arr, 0, arr.size() - 1);
    cout << "Sorted array: ";
    for (int num : arr) {
        cout << num << " ";
    }
    return 0;
}
