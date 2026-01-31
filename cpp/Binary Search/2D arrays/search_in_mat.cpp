#include<iostream>
#include<vector>
using namespace std;

/*
 * Brute-force: Check every element.
 * Time: O(n * m)
 * Space: O(1)
 */
bool search_element_brute(vector<vector<int>>& mat, int target) {
    int n = mat.size(), m = mat[0].size();
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (mat[i][j] == target) return true;
        }
    }
    return false;
}

/*
 * Binary search on 1D array.
 * Time: O(log m)
 * Space: O(1)
 */
bool binary_search(vector<int> arr, int target) {
    int low = 0, high = arr.size() - 1;
    while (low <= high) {
        int mid = low + ((high - low) / 2);
        if (arr[mid] == target) return true;
        else if (arr[mid] > target) high = mid - 1;
        else low = mid + 1;
    }
    return false;
}
/*
 * Better search with row filtering
 * Only search rows where target could lie, using first and last element of row.
 * 
 * Time: O(n + log m) in best case if early row matches
 *       O(n * log m) in worst case if all rows are checked
 * Space: O(1)
 */
bool search_element_better(vector<vector<int>>& mat, int target) {
    int n = mat.size(), m = mat[0].size();
    for (int i = 0; i < n; i++) {
        // Check if target can possibly be in row i
        if (mat[i][0] <= target && mat[i][m - 1] >= target) {
            if (binary_search(mat[i], target)) return true;
        }
    }
    return false;
}

/*
 * Optimal approach: Treat 2D matrix as a sorted 1D array.
 * Condition: Matrix is sorted row-wise and rows are connected in increasing order
 * Time: O(log(n * m))
 * Space: O(1)
 */
bool searchMatrix(vector<vector<int>>& matrix, int target) {
    int n = matrix.size(), m = matrix[0].size();
    int low = 0, high = n * m - 1;
    
    while (low <= high) {
        int mid = low + ((high - low) / 2);
        int row = mid / m;  // Get the row index
        int col = mid % m;  // Get the column index

        if (matrix[row][col] == target) return true;
        else if (matrix[row][col] < target) low = mid + 1;
        else high = mid - 1;
    }
    return false;
}

int main() {
    vector<vector<int>> matrix = {
        {1, 3, 5, 7},
        {10, 11, 16, 20},
        {23, 30, 34, 50}
    };
    
    int target;
    cout << "Enter element to search: ";
    cin >> target;

    cout << "\n--- Brute Force ---\n";
    cout << (search_element_brute(matrix, target) ? "Found" : "Not Found") << endl;

    cout << "\n--- Better (Row-wise Binary Search) ---\n";
    cout << (search_element_better(matrix, target) ? "Found" : "Not Found") << endl;

    cout << "\n--- Optimal (Matrix as 1D) ---\n";
    cout << (searchMatrix(matrix, target) ? "Found" : "Not Found") << endl;

    return 0;
}