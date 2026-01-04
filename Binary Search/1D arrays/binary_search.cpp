#include<iostream>
#include<vector>
using namespace std;
    /*
     * Binary Search Prerequisite:
     * ---------------------------
     * The array MUST be sorted.
     */

    /*
     * Time Complexity Intuition (Iterative & Recursive):
     * --------------------------------------------------
     * At each step, the search space is reduced to half.
     *
     * Time Complexity:
     * Best Case   : O(1)    (target found at mid)
     * Average Case: O(log n)
     * Worst Case  : O(log n)
     *
     * Space Complexity:
     * -----------------
     * Iterative Version : O(1)  (no recursion stack)
     * Recursive Version : O(log n) (due to recursion stack)
     */
int iterative_binarySearch(vector<int>arr,int target){
    int low=0;
    int high=arr.size()-1;
    while(low<=high){
        int mid=low+((high-low)/2);
        if(arr[mid]==target) return mid+1;
        else if(arr[mid]<target) low=mid+1;
        else high=mid-1; 
    }
    return -1;
}

int recursive_binarySearch(vector<int>arr,int low,int high,int target){
    if(low>high) return -1;
    int mid=low+((high-low)/2);
    if(arr[mid]==target) return mid+1;
    else if(arr[mid]<target) return recursive_binarySearch(arr,mid+1,high,target);
    else return recursive_binarySearch(arr,low,mid-1,target);
}

int main() {
    vector<int> arr = {2, 4, 6, 8, 10, 12, 14};  // sorted array
    int target;
    cout << "Enter target element to search: ";
    cin >> target;

    // Iterative Search
    int result_iter = iterative_binarySearch(arr, target);
    if (result_iter != -1)
        cout << "Iterative: Element found at position (1-based index): " << result_iter << endl;
    else
        cout << "Iterative: Element not found.\n";

    // Recursive Search
    int result_rec = recursive_binarySearch(arr, 0, arr.size() - 1, target);
    if (result_rec != -1)
        cout << "Recursive: Element found at position (1-based index): " << result_rec << endl;
    else
        cout << "Recursive: Element not found.\n";

    return 0;
}
