#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

    /*
     * Time Complexity Intuition:
     * --------------------------
     * Best Case: O(n log n)
     * - Pivot divides the array into two nearly equal halves.
     *
     * Average Case: O(n log n)
     * - Random distribution of elements around pivot.
     *
     * Worst Case: O(n^2)
     * - Occurs when the array is already sorted or reverse sorted
     *   and a bad pivot (first or last element) is chosen.
     *
     * Space Complexity Intuition:
     * ---------------------------
     * - Sorting is done in-place.
     * - Extra space is used only by the recursion stack.
     *
     * Space Complexity: O(log n) on average
     * Worst Case Space: O(n) (skewed recursion tree)
     */
    
// Partition function using Lomuto partition scheme
int partition(vector<int>& arr, int low, int high) {
    int pivot = arr[low];  // Choosing the first element as pivot
    int i = low;
    int j = high;

    // Rearranging elements based on pivot
    while (i < j) {
        // Move `i` right until an element greater than pivot is found
        while (arr[i] <= pivot && i <= high - 1) {
            i++;
        }
        // Move `j` left until an element less than or equal to pivot is found
        while (arr[j] > pivot && j >= low + 1) {
            j--;
        }
        // Swap only if i < j
        if (i < j) swap(arr[i], arr[j]);
    }

    // Place pivot at its correct position
    swap(arr[low], arr[j]);
    return j;  // Return the pivot index
}

// QuickSort function
void quicksort(vector<int>& arr, int low, int high) {
    if (low < high) {
        int parti = partition(arr, low, high); // Get partition index
        quicksort(arr, low, parti - 1);        // Sort left subarray
        quicksort(arr, parti + 1, high);       // Sort right subarray
    }
}

// Main function
int main() {
    vector<int> arr = {64, 25, 12, 22, 11};
    quicksort(arr, 0, arr.size() - 1);  // Call quicksort on full array

    // Output sorted array
    cout << "Sorted array: ";
    for (int num : arr) {
        cout << num << " ";
    }
    return 0;
}
