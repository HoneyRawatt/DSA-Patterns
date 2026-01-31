#include <iostream>
#include <vector>
#include <numeric>  // for accumulate
using namespace std;

    /*
     * Custom lower bound function
     * Returns the first index where arr[index] >= x
     *
     * Time Complexity: O(log m)
     * Space Complexity: O(1)
     */
int lowerbound(const vector<int>& arr, int n, int x) {
    int low = 0, high = n - 1;
    while (low <= high) {
        int mid = (low + high) / 2;
        if (arr[mid] >= x) high = mid - 1;
        else low = mid + 1;
    }
    return low;
}

    /*
     * Approach 1: Binary Search (Rows are sorted)
     * -------------------------------------------
     * - Find first occurrence of 1 using lower bound
     * - Number of ones = m - index
     *
     * Time Complexity: O(n * log m)
     * Space Complexity: O(1)
     */
int rowWithMax1s(vector<vector<int>>& matrix, int n, int m) {
    int cnt_max = 0;
    int ind = -1;
    for (int i = 0; i < n; i++) {
        int cnt_ones = m - lowerbound(matrix[i], m, 1);
        if (cnt_ones > cnt_max) {  
            ind = i;
            cnt_max = cnt_ones;
        }
    }
    return ind;
}

    /*
     * Approach 2: General Case (No sorting assumption)
     * -------------------------------------------------
     * - Count number of 1s using summation
     *
     * Time Complexity: O(n * m)
     * Space Complexity: O(1)
     */
vector<int> rowAndMaximumOnes(vector<vector<int>>& mat) {
    int n = mat.size(), m = mat[0].size();
    int cnt_max = 0, ind = -1;
    for (int i = 0; i < n; i++) {
        int cnt_ones = accumulate(mat[i].begin(), mat[i].end(), 0);
        if (cnt_ones > cnt_max) {
            cnt_max = cnt_ones;
            ind = i;
        }
    }
    return {ind, cnt_max};
}

        /*
     * 🚀 OPTIMAL APPROACH (Top-Right Traversal)
     * -----------------------------------------
     * 🧠 INTUITION:
     * - Rows are sorted (0s then 1s).
     * - Start from top-right corner.
     * - If matrix[row][col] == 1:
     *      -> move left (more 1s possible in same row)
     *      -> update answer row
     * - If matrix[row][col] == 0:
     *      -> move down (this row cannot have more 1s)
     *
     * Time Complexity: O(n + m)
     * Space Complexity: O(1)
     */
    int rowWithMax1sOptimal(int[][] mat) {
        int n = mat.length;
        int m = mat[0].length;

        int row = 0;
        int col = m - 1;
        int ans = -1;

        while (row < n && col >= 0) {
            if (mat[row][col] == 1) {
                ans = row;   // current row has more 1s
                col--;       // move left
            } else {
                row++;       // move down
            }
        }
        return ans;
    }
int main() {
    vector<vector<int>> mat = {
        {0, 0, 0, 1},
        {0, 1, 1, 1},
        {0, 0, 1, 1},
        {0, 0, 0, 0}
    };

    int n = mat.size(), m = mat[0].size();

    // Use the function depending on assumptions
    int index = rowWithMax1s(mat, n, m); // for sorted rows
    cout << "Row with max 1s (binary search): " << index << endl;

    vector<int> result = rowAndMaximumOnes(mat); // for general case
    cout << "Row with max 1s (accumulate): " << result[0] << " with count = " << result[1] << endl;

    return 0;
}
