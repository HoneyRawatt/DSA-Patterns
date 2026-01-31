#include <iostream>
#include <vector>
using namespace std;

    // Binary Search approach
    // Time Complexity: O(log n)
    // Space Complexity: O(1)
    //
    // Intuition:
    // - A peak element is greater than its neighbors
    // - If the slope is rising, a peak lies on the right
    // - If the slope is falling, a peak lies on the left
// Function to find a peak element index in an array
int find_peak(vector<int>& arr) {
    int n = arr.size();

    // Handle edge cases
    if (n == 1) return 0;
    if (arr[0] > arr[1]) return 0;
    if (arr[n - 1] > arr[n - 2]) return n - 1;

    int low = 1, high = n - 2;

    while (low <= high) {
        int mid = low + (high - low) / 2;

        // Check if mid is a peak
        if (arr[mid] > arr[mid - 1] && arr[mid] > arr[mid + 1])
            return mid;

        // If the slope is increasing, move right
        if (arr[mid] > arr[mid - 1])
            low = mid + 1;

        // If the slope is decreasing or flat, move left
        else
            high = mid - 1;
    }

    return -1; // Should never reach here if input has at least one peak
}

    // Linear search approach
    // Time Complexity: O(n)
    // Space Complexity: O(1)
// Function to find a peak using linear search
int find_peak_linear(vector<int>& arr) {
    int n = arr.size();

    // Handle edge cases
    if (n == 1) return 0;
    if (arr[0] >= arr[1]) return 0;
    if (arr[n - 1] >= arr[n - 2]) return n - 1;

    // Traverse from index 1 to n-2
    for (int i = 1; i < n - 1; i++) {
        if (arr[i] >= arr[i - 1] && arr[i] >= arr[i + 1])
            return i;
    }

    return -1; // No peak found (shouldn't happen for valid input)
} 

int main() {
    vector<int> arr = {1, 3, 20, 4, 1, 0};
    int peakIndex = find_peak(arr);

    if (peakIndex != -1)
        cout << "Peak element is " << arr[peakIndex] << " at index " << peakIndex << endl;
    else
        cout << "No peak element found.\n";

    return 0;
}
