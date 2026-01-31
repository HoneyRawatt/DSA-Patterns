#include <iostream>
#include <vector>
using namespace std;

/*
 * Brute-force: Check every element.
 * Time: O(n * m)
 * Space: O(1)
 */
vector<int> search_element_brute(vector<vector<int>>& mat, int target) {
    int n = mat.size(), m = mat[0].size();
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (mat[i][j] == target) return {i, j};
        }
    }
    return {-1, -1};
}

/*
 * Binary search on 1D row.
 * Time: O(log m)
 * Space: O(1)
 */
int binary_search(vector<int> arr, int target) {
    int low = 0, high = arr.size() - 1;
    while (low <= high) {
        int mid = low + ((high - low) / 2);
        if (arr[mid] == target) return mid;
        else if (arr[mid] > target) high = mid - 1;
        else low = mid + 1;
    }
    return -1;
}

/*
 * Better search with row filtering + binary search
 * Time: O(n * log m)
 * Space: O(1)
 */
vector<int> search_element_better(vector<vector<int>>& mat, int target) {
    int n = mat.size(), m = mat[0].size();
    for (int i = 0; i < n; i++) {
        int j = binary_search(mat[i], target);
        if (j != -1) return {i, j};
    }
    return {-1, -1};
}

/*
 * Optimal search from top-right corner
 * Time: O(n + m)
 * Space: O(1)
 */
vector<int> searchMatrix(vector<vector<int>>& matrix, int target) {
    int n = matrix.size(), m = matrix[0].size();
    int row = 0, col = m - 1;
    while (row < n && col >= 0) {
        if (matrix[row][col] == target) return {row, col};
        else if (matrix[row][col] < target) row++;
        else col--;
    }
    return {-1, -1};
}

// --------- MAIN FUNCTION ---------
int main() {
    // Sample matrix (sorted rows and columns)
    vector<vector<int>> matrix = {
        {1, 3, 5, 7},
        {10, 11, 16, 20},
        {23, 30, 34, 60}
    };

    int target;
    cout << "Enter element to search: ";
    cin >> target;

    vector<int> res;

    cout << "\n--- Brute Force ---\n";
    res = search_element_brute(matrix, target);
    if (res[0] != -1) cout << "Found at: [" << res[0] << ", " << res[1] << "]\n";
    else cout << "Not Found\n";

    cout << "\n--- Better (Row-wise Binary Search) ---\n";
    res = search_element_better(matrix, target);
    if (res[0] != -1) cout << "Found at: [" << res[0] << ", " << res[1] << "]\n";
    else cout << "Not Found\n";

    cout << "\n--- Optimal (Top-Right Search) ---\n";
    res = searchMatrix(matrix, target);
    if (res[0] != -1) cout << "Found at: [" << res[0] << ", " << res[1] << "]\n";
    else cout << "Not Found\n";

    return 0;
}
