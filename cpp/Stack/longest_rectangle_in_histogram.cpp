#include <iostream>
#include <vector>
#include <stack>
#include <climits>
using namespace std;

/*
=====================================================
PROBLEM STATEMENT:
-----------------------------------------------------
Given an array representing heights of histogram bars,
find the area of the largest rectangle that can be
formed inside the histogram.

Each bar has:
- Width = 1
- Height = arr[i]

Return the maximum rectangular area possible.
=====================================================
*/

/*
=====================================================
INTUITION:
-----------------------------------------------------
For each bar, assume it is the smallest height of a
rectangle. The rectangle can expand:

- To the LEFT until a smaller bar is found
- To the RIGHT until a smaller bar is found

Area = height[i] * (right_smaller - left_smaller - 1)

To efficiently find nearest smaller bars:
- Use MONOTONIC STACK
=====================================================
*/

/*
=====================================================
FUNCTION: findNextSmaller
-----------------------------------------------------
Finds the index of the nearest smaller element
to the RIGHT for each bar.

If none exists, index = n
=====================================================
*/
vector<int> findNextSmaller(const vector<int>& arr) {
    int n = arr.size();
    vector<int> nse(n);
    stack<int> st; // stores indices

    // Traverse from right to left
    for(int i = n - 1; i >= 0; i--) {

        // Remove bars taller or equal to current bar
        while(!st.empty() && arr[st.top()] >= arr[i])
            st.pop();

        // If stack empty → no smaller element
        nse[i] = st.empty() ? n : st.top();

        // Push current index
        st.push(i);
    }
    return nse;
}

/*
=====================================================
FUNCTION: findPrevSmaller
-----------------------------------------------------
Finds the index of the nearest smaller element
to the LEFT for each bar.

If none exists, index = -1
=====================================================
*/
vector<int> findPrevSmaller(const vector<int>& arr) {
    int n = arr.size();
    vector<int> pse(n);
    stack<int> st; // stores indices

    // Traverse from left to right
    for(int i = 0; i < n; i++) {

        // Remove bars taller than current bar
        while(!st.empty() && arr[st.top()] > arr[i])
            st.pop();

        // If stack empty → no smaller element
        pse[i] = st.empty() ? -1 : st.top();

        // Push current index
        st.push(i);
    }
    return pse;
}

/*
=====================================================
BRUTE FORCE (USING NSE + PSE):
-----------------------------------------------------
Time Complexity: O(n)
Space Complexity: O(n)
=====================================================
*/
int longest_rectangle_brute(const vector<int>& arr) {
    vector<int> nse = findNextSmaller(arr);
    vector<int> pse = findPrevSmaller(arr);
    int maxi = 0;

    // Calculate max area for each bar
    for(int i = 0; i < arr.size(); i++) {
        int width = nse[i] - pse[i] - 1;
        maxi = max(maxi, arr[i] * width);
    }
    return maxi;
}

/*
=====================================================
OPTIMAL APPROACH (SINGLE PASS STACK):
-----------------------------------------------------
- Uses a monotonic increasing stack
- Calculates area when smaller element is found

Time Complexity: O(n)
Space Complexity: O(n)
=====================================================
*/
int longest_rectangle_optimal(const vector<int>& arr) {
    int n = arr.size();
    stack<int> st;
    int maxarea = 0;

    // Traverse histogram
    for(int i = 0; i < n; i++) {

        // Process bars taller than current
        while(!st.empty() && arr[st.top()] > arr[i]) {
            int ele = st.top();
            st.pop();

            int nse = i;
            int pse = st.empty() ? -1 : st.top();

            maxarea = max(maxarea, arr[ele] * (nse - pse - 1));
        }
        st.push(i);
    }

    // Process remaining bars
    while(!st.empty()) {
        int ele = st.top();
        st.pop();

        int nse = n;
        int pse = st.empty() ? -1 : st.top();

        maxarea = max(maxarea, arr[ele] * (nse - pse - 1));
    }

    return maxarea;
}

/*
=====================================================
MAIN FUNCTION
=====================================================
*/
int main() {
    vector<int> heights = {2, 1, 5, 6, 2, 3};

    cout << "Brute: " << longest_rectangle_brute(heights) << endl;
    cout << "Optimal: " << longest_rectangle_optimal(heights) << endl;

    return 0;
}
