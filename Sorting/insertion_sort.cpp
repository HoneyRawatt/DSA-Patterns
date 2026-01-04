#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
    /*
     * Worst Case Time Complexity: O(n^2)
     * ---------------------------------
     * Occurs when the array is sorted in reverse order.
     * Each new element is compared and shifted across the entire sorted part.
     *
     * Best Case Time Complexity: O(n)
     * -------------------------------
     * Occurs when the array is already sorted.
     * The while loop never executes (early stopping).
     *
     * Average Case Time Complexity: O(n^2)
     *
     * Space Complexity: O(1)
     * ----------------------
     * In-place sorting.
     * Only constant extra space is used.
     */


void insertion_sort(vector<int>&arr){
for(int i=0;i<arr.size();i++){
    int j=i;
    while(j>0 && arr[j-1]>arr[j]){
        swap(arr[j],arr[j-1]);
        j--;
    }
}   
}

int main() {
    vector<int> arr = {64, 25, 12, 22, 11};
    insertion_sort(arr);
    cout << "Sorted array: ";
    for(int num : arr) {
        cout << num << " ";
    }

    return 0;
}
