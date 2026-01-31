#include<iostream>
#include<vector>
using namespace std;

    /*
     * CASE 1: Array has UNIQUE elements
     *
     * Time Complexity:
     * ----------------
     * O(log n) → normal binary search
     *
     * Space Complexity:
     * -----------------
     * O(1)
     */

// Search in rotated sorted array
int find_element_unique(vector<int> arr, int target) {
    int low = 0, high = arr.size() - 1;

    while (low <= high) {
        int mid = low + ((high - low) / 2);

        if (arr[mid] == target)
            return mid;

        // Left half is sorted
        if (arr[low] <= arr[mid]) {
            if (arr[low] <= target && target <= arr[mid])
                high = mid - 1;
            else
                low = mid + 1;
        }
        // Right half is sorted
        else {
            if (arr[mid] <= target && target <= arr[high])
                low = mid + 1;
            else
                high = mid - 1;
        }
    }

    return -1;
}

    /*
     * CASE 2: Array has DUPLICATE elements
     *
     * Time Complexity:
     * ----------------
     * Average Case: O(log n)
     * Worst Case  : O(n)  → when many duplicates exist
     *
     * Space Complexity:
     * -----------------
     * O(1)
     */
int find_element_duplicate(vector<int> arr, int target) {
    int low = 0, high = arr.size() - 1;

    while (low <= high) {
        int mid = low + ((high - low) / 2);
    
        if (arr[mid] == target)
            return mid;
        //srink the array while duplicate occurs
        if(arr[low]==arr[mid] && arr[mid]==arr[high]){
            low++;
            high--;
            continue;
        }
        // Left half is sorted
        if (arr[low] <= arr[mid]) {
            if (arr[low] <= target && target <= arr[mid])
                high = mid - 1;
            else
                low = mid + 1;
        }
        // Right half is sorted
        else {
            if (arr[mid] <= target && target <= arr[high])
                low = mid + 1;
            else
                high = mid - 1;
        }
    }

    return -1;
}

int main(){
    vector<int> uniqueArr = {4, 5, 6, 7, 0, 1, 2};
    int target1 = 0;
    cout << "Unique: " << find_element_unique(uniqueArr, target1) << endl;

    vector<int> dupArr = {2, 5, 6, 0, 0, 1, 2};
    int target2 = 0;
    cout << "Duplicate: " << find_element_duplicate(dupArr, target2) << endl;
}
