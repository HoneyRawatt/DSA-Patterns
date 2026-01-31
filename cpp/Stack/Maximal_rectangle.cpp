#include <iostream>
#include <vector>
#include <stack>
#include <climits>
using namespace std;

/*
=====================================================
PROBLEM STATEMENT (Largest Rectangle in Histogram):
-----------------------------------------------------
Given an array representing heights of histogram bars,
find the area of the largest rectangle that can be formed.

This function is used as a helper for the
"Maximal Rectangle in Binary Matrix" problem.
=====================================================
*/

/*
===============================
Optimal Histogram Solution
===============================
Intuition:
- Use a monotonic increasing stack to store indices
- When a smaller height is found, it means the rectangle
  for the popped height must end here
- Compute width using:
    width = NSE - PSE - 1

Time Complexity: O(n)
- Each index is pushed and popped at most once

Space Complexity: O(n)
- Stack stores indices
*/
int longest_rectangle_optimal(const vector<int>& arr) {
    int n = arr.size();
    stack<int> st;           // stores indices of histogram bars
    int maxarea = 0;

    // Traverse histogram
    for(int i = 0; i < n; i++) {

        // Pop until stack maintains increasing order
        while(!st.empty() && arr[st.top()] > arr[i]) {
            int ele = st.top(); // index of height forming rectangle
            st.pop();

            int nse = i;                       // Next Smaller Element
            int pse = st.empty() ? -1 : st.top(); // Previous Smaller Element

            // Calculate area with arr[ele] as smallest height
            maxarea = max(maxarea, arr[ele] * (nse - pse - 1));
        }
        st.push(i);
    }

    // Handle remaining bars in stack
    while(!st.empty()) {
        int ele = st.top();
        st.pop();

        int nse = n;                       // End of histogram
        int pse = st.empty() ? -1 : st.top();

        maxarea = max(maxarea, arr[ele] * (nse - pse - 1));
    }

    return maxarea;
}

/*
=====================================================
PROBLEM STATEMENT (Maximal Rectangle in Binary Matrix):
-----------------------------------------------------
Given a binary matrix filled with 0s and 1s,
find the largest rectangle containing only 1s
and return its area.
=====================================================
*/

/*
===============================
Maximal Rectangle Solution
===============================
Intuition:
- Treat each row as the base of a histogram
- Build column-wise prefix sums of consecutive 1s
- For each row, apply "Largest Rectangle in Histogram"
- Track the maximum area found

Time Complexity: O(n * m)
- Building prefix sum: O(n * m)
- Histogram per row: O(m)

Space Complexity: O(n * m)
- Prefix sum matrix
*/
int maximal_rectangle(vector<vector<int>> mat) {
    int n = mat.size();
    if(n == 0) return 0;
    int m = mat[0].size();
    int maxarea = 0;

    vector<vector<int>> psum(n, vector<int>(m, 0));

    /*
    Build prefix sum column-wise
    psum[i][j] = number of consecutive 1s ending at row i in column j
    */
    for(int j = 0; j < m; j++) {
        int sum = 0;
        for(int i = 0; i < n; i++) {
            if(mat[i][j] == 0) sum = 0; // reset when zero found
            else sum += 1;
            psum[i][j] = sum;
        }
    }

    // Apply histogram algorithm row by row
    for(int i = 0; i < n; i++) {
        maxarea = max(maxarea, longest_rectangle_optimal(psum[i]));
    }

    return maxarea;
}

/*
===============================
Main Function
===============================
*/
int main() {
    vector<vector<int>> mat = {
        {1, 0, 1, 0, 0},
        {1, 0, 1, 1, 1},
        {1, 1, 1, 1, 1},
        {1, 0, 0, 1, 0}
    };

    cout << maximal_rectangle(mat) << endl; // Expected Output: 6
    return 0;
}
