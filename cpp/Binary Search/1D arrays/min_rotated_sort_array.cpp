#include<iostream>
#include<vector>
#include<climits>
using namespace std;

    /*
     * Time Complexity: O(log n) on average
     * Worst Case with duplicates: O(n) (due to boundary shrinking)
     * Space Complexity: O(1)
     */
// Function to find the number of times a sorted array is rotated
int findRotationCount(vector<int>& arr) {
    int low = 0, high = arr.size() - 1;
    int index = -1;
    int ans = INT_MAX;

    while (low <= high) {
        int mid = low + (high - low) / 2;

        // Update answer and index at each iteration
        if (arr[mid] < ans) {
            ans = arr[mid];
            index = mid;
        }

        // Shrink boundaries if duplicates exist
        if (arr[low] == arr[mid] && arr[mid] == arr[high]) {
            low++;
            high--;
            continue;
        }

        // Left half is sorted
        if (arr[low] <= arr[mid]) {
            if (arr[low] < ans) {
                ans = arr[low];
                index = low;
            }
            low = mid + 1;
        }
        // Right half is sorted
        else {
            if (arr[mid] < ans) {
                ans = arr[mid];
                index = mid;
            }
            high = mid - 1;
        }
    }

    return index;
}


// Function to find the minimum element in a rotated sorted array (no duplicates)
int min_element_unique(vector<int> arr) {
    int low = 0;
    int high = arr.size() - 1;
    int ans = INT_MAX;

    while (low <= high) {
        int mid = low + ((high - low) / 2);

        // If current segment is sorted
        if (arr[low] <= arr[high]) {
            ans = min(ans, arr[low]);
            break;
        }

        // Left half is sorted
        if (arr[low] <= arr[mid]) {
            ans = min(ans, arr[low]);
            low = mid + 1;
        }
        // Right half is sorted
        else {
            ans = min(ans, arr[mid]);
            high = mid - 1;
        }
    }

    return ans;
}

// Function to find the minimum element in a rotated sorted array (with duplicates)
int min_element_duplicates(vector<int> arr) {
    int low = 0;
    int high = arr.size() - 1;
    int ans = INT_MAX;

    while (low <= high) {
        int mid = low + ((high - low) / 2);

          ans = min(ans, arr[low]);

        // Shrink boundaries when duplicates at both ends
        if (arr[low] == arr[mid] && arr[mid] == arr[high]) {
            low++, high--;
            continue;
        }

        // Left half is sorted
        if (arr[low] <= arr[mid]) {
            ans = min(ans, arr[low]);
            low = mid + 1;
        }
        // Right half is sorted
        else {
            ans = min(ans, arr[mid]);
            high = mid - 1;
        }
    }

    return ans;
}

int main() {
    // Test arrays
    vector<int> uniqueArr = {4, 5, 6, 7, 0, 1, 2}; // No duplicates
    vector<int> duplicateArr = {2, 2, 2, 0, 1, 2}; // With duplicates
    
    vector<int> arr = {15, 18, 2, 3, 6, 12};
    cout << "Array is rotated " <<findRotationCount(arr) << " times.\n";
    // Calling both functions
    cout << "Minimum (unique): " << min_element_unique(uniqueArr) << endl;       // Output: 0
    cout << "Minimum (duplicates): " << min_element_duplicates(duplicateArr) << endl; // Output: 0

    return 0;
}
