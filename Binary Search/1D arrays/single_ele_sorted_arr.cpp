#include <iostream>
#include <vector>
using namespace std;

// Brute-force approach
// Time Complexity: O(n)
// Space Complexity: O(1)
// Idea: Compare each element with its neighbors
// Brute-force: Linear scan comparing neighbors
int find_single_element_brute(vector<int> arr) {
    int n = arr.size();

    // Edge cases
    if (n == 1) return arr[0];
    if (arr[0] != arr[1]) return arr[0];
    if (arr[n - 1] != arr[n - 2]) return arr[n - 1];

    // Check middle elements
    for (int i = 1; i < n - 1; i++) {
        if (arr[i] != arr[i - 1] && arr[i] != arr[i + 1]) {
            return arr[i];
        }
    }

    return -1; // Should not happen for valid input
}

// Optimized Binary Search approach
// Time Complexity: O(log n)
// Space Complexity: O(1)
// Intuition:
// - Before the single element → pairs start at EVEN index
// - After the single element  → pairs start at ODD index
// Function to find the single element in a sorted array
int find_single_element(vector<int> arr) {
    int n = arr.size();
    int low = 0;
    int high = n - 1;

    // Edge cases
    if (n == 1) return arr[0];
    if (arr[0] != arr[1]) return arr[0];
    if (arr[n - 1] != arr[n - 2]) return arr[n - 1];

    low++;
    high--;

    while (low <= high) {
        int mid = low + (high - low) / 2;

        // If arr[mid] is the unique element
        if (arr[mid] != arr[mid - 1] && arr[mid] != arr[mid + 1])
            return arr[mid];

        // Check pairing to determine direction
        if ((mid % 2 == 0 && arr[mid] == arr[mid + 1]) || 
            (mid % 2 == 1 && arr[mid] == arr[mid - 1])) {
            low = mid + 1; // Single element lies to the right
        } else {
            high = mid - 1; // Single element lies to the left
        }
    }

    return -1; // Should never reach here if input is valid
}

int main() {
    vector<int> arr = {1, 1, 2, 2, 3, 4, 4, 5, 5}; // Single element is 3
    cout << "Single element (brute): " << find_single_element_brute(arr) << endl;
    cout << "Single element: " << find_single_element(arr) << endl;
    return 0;
}
