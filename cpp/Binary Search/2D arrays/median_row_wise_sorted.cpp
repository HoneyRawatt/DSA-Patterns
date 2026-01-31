#include <iostream>
#include <vector>
#include <climits>
#include<algorithm>
using namespace std;

// Step 1: Flatten matrix → O(n * m)
// Step 2: Sort the array → O(n * m * log(n * m))
// Step 3: Return middle → O(1)
// Storing flattened array: O(n × m)
int median_brute_force(vector<vector<int>>& matrix, int n, int m) {
    vector<int> elements;

    // Step 1: Flatten the matrix into a 1D array
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            elements.push_back(matrix[i][j]);
        }
    }

    // Step 2: Sort the flattened array
    sort(elements.begin(), elements.end());

    // Step 3: Return the middle element
    return elements[(n * m) / 2];  // integer division
}

/*
 * Custom upper_bound: returns index of first element > x
 * If no such element, returns n (size of row)
 */
int upperbound(vector<int>& arr, int x, int n) {
    int low = 0, high = n - 1;
    int ans = n;  // default to n (if all elements ≤ x)
    while (low <= high) {
        int mid = (low + high) / 2;
        if (arr[mid] > x) {
            ans = mid;
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }
    return ans;
}

/*
 * Count number of elements ≤ mid in entire matrix
 */
int countSmallEqual(vector<vector<int>>& matrix, int n, int m, int mid) {
    int cnt = 0;
    for (int i = 0; i < n; i++) {
        cnt += upperbound(matrix[i], mid, m); // because row is sorted
    }
    return cnt;
}

/*
 * Binary search on answer to find median
 * Time: O(32 * n * log m)
 * Space: O(1)
 */
int median(vector<vector<int>>& matrix, int n, int m) {
    int low = INT_MAX, high = INT_MIN;

    // Find global min and max
    for (int i = 0; i < n; i++) {
        low = min(low, matrix[i][0]);
        high = max(high, matrix[i][m - 1]);
    }

    int req = (n * m) / 2; // Half the total elements

    while (low <= high) {
        int mid = low + (high - low) / 2;
        int count = countSmallEqual(matrix, n, m, mid);

        if (count <= req) low = mid + 1;
        else high = mid - 1;
    }

    return low; // Median
}

// ----------- MAIN FUNCTION FOR TESTING -----------
int main() {
    vector<vector<int>> matrix = {
        {1, 3, 5},
        {2, 6, 9},
        {3, 6, 9}
    };
    int n = matrix.size();
    int m = matrix[0].size();

    int result = median(matrix, n, m);
    cout << "Median is: " << result << endl;
     result = median_brute_force(matrix, n, m);
    cout << "Median (brute-force) is: " << result << endl;

    return 0;
}
