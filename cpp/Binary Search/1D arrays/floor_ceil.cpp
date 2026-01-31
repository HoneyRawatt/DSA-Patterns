#include<iostream>
#include<vector>
using namespace std;

    /*
     * Ceil:
     * -----
     * Smallest element in the array that is >= target
     *
     * Floor:
     * ------
     * Largest element in the array that is <= target
     *
     * Prerequisite:
     * -------------
     * Array must be sorted.
     *
     * Time Complexity:
     * ----------------
     * O(log n) for both ceil and floor
     * (binary search halves the search space each time)
     *
     * Space Complexity:
     * -----------------
     * O(1) → iterative binary search, no extra space
     */
    
int ceil(const vector<int>& arr, int target) {
    int low = 0;
    int high = arr.size() - 1;

    while (low <= high) {
        int mid = low + ((high - low) / 2);
        if (arr[mid] >= target) {
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }

    return (low < arr.size()) ? arr[low] : -1; // arr[low] is the smallest ≥ target
}
int floor(const vector<int>& arr, int target) {
    int low = 0;
    int high = arr.size() - 1;

    while (low <= high) {
        int mid = low + ((high - low) / 2);
        if (arr[mid] <= target) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }

    return (high >= 0) ? arr[high] : -1; // arr[high] is the largest ≤ target
}

int main(){
    vector<int> arr = {1, 3, 5, 7, 9};

cout << "Ceil of 6: " << ceil(arr, 6) << endl;   // 7
cout << "Floor of 6: " << floor(arr, 6) << endl; // 5

}