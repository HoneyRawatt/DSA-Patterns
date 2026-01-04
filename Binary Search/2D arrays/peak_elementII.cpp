#include <iostream>
#include <vector>
using namespace std;

    /*
     * 🧠 Find the row index with the maximum value in a given column
     * --------------------------------------------------------------
     * Time Complexity: O(n)
     * Space Complexity: O(1)
     */
    int findmaxind(vector<vector<int>>& mat, int n, int col) {
        int maxvalue = -1;
        int ind = -1;
        for (int i = 0; i < n; i++) {
            if (mat[i][col] > maxvalue) {
                maxvalue = mat[i][col];
                ind = i;
            }
        }
        return ind;
    }
    /*
     * 🚀 Binary Search on Columns to find a peak element
     * -------------------------------------------------
     * 🧠 INTUITION:
     * - At each column, find the row with the largest value.
     * - Compare with left & right neighbors.
     * - Move towards the direction with a larger neighbor.
     *
     * Time Complexity: O(n * log m)
     * Space Complexity: O(1)
     */
    vector<int> findPeakGrid(vector<vector<int>>& mat) {
        int n = mat.size(), m = mat[0].size();
        int low = 0, high = m - 1;

        while (low <= high) {
            int mid = low + ((high - low) / 2);
            int maxrowind = findmaxind(mat, n, mid);

            int leftVal = (mid - 1 >= 0) ? mat[maxrowind][mid - 1] : -1;
            int rightVal = (mid + 1 < m) ? mat[maxrowind][mid + 1] : -1;

            if (mat[maxrowind][mid] > leftVal && mat[maxrowind][mid] > rightVal)
                return {maxrowind, mid}; // Peak found
            else if (mat[maxrowind][mid] < leftVal)
                high = mid - 1; // Move to left half
            else
                low = mid + 1; // Move to right half
        }

        return {-1, -1}; // Fallback (not expected for valid input)
    }

// ----------- MAIN FUNCTION FOR TESTING -----------
int main() {

    // Example 2D matrix (input)
    vector<vector<int>> mat = {
        {10, 8, 10, 10},
        {14, 13, 12, 11},
        {15, 9, 11, 21},
        {16, 17, 19, 20}
    };

    // Find peak
    vector<int> peak = findPeakGrid(mat);

    // Output result
    cout << "Peak found at: [" << peak[0] << ", " << peak[1] << "] with value = "
         << mat[peak[0]][peak[1]] << endl;

    return 0;
}
