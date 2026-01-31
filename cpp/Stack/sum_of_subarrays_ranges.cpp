#include <iostream>
#include <vector>
#include <stack>
#include <climits>
using namespace std;

/* 
=====================================================
PROBLEM STATEMENT:
-----------------------------------------------------
Given an integer array `arr`, find the sum of the ranges
(max - min) of all possible subarrays.

Example:
arr = [3,1,2,4]

Subarrays:
[3] → max-min = 0
[3,1] → max-min = 2
[3,1,2] → max-min = 2
[3,1,2,4] → max-min = 3
...
Sum all ranges = ?

=====================================================
*/

/* 
=====================================================
1️⃣ Brute-force Method
=====================================================
Intuition:
- For each subarray starting at index i, 
  we can iterate to all ending indices j >= i
- Keep track of min and max in the subarray [i,j]
- Add (max-min) to the sum

Time Complexity: O(n^2)
- Two nested loops → n*(n+1)/2 iterations
- Constant time operations inside → O(n^2)

Space Complexity: O(1)
- Only variables for min, max, sum
*/
int sum_of_subarr_range_brute(vector<int> arr){
    int sum = 0;
    int n = arr.size();
    for(int i = 0; i < n; i++){
        int largest = arr[i];
        int smallest = arr[i];
        for(int j = i; j < n; j++){
            largest = max(largest, arr[j]); // Update current maximum
            smallest = min(smallest, arr[j]); // Update current minimum
            sum += (largest - smallest); // Add the range to sum
        }
    }
    return sum;
}

/* 
=====================================================
2️⃣ Optimized Method using Monotonic Stacks
=====================================================
Intuition:
- Each element contributes as:
  - maximum in some subarrays
  - minimum in some subarrays
- Find:
  - Next Greater / Previous Greater → number of subarrays where element is max
  - Next Smaller / Previous Smaller → number of subarrays where element is min
- Contribution = arr[i] * (#subarrays where it's max) - arr[i] * (#subarrays where it's min)
- Sum contributions for all elements → answer

Time Complexity: O(n)
- Each element pushed/popped from stack at most once
- ~2n operations per stack → O(n)

Space Complexity: O(n)
- Stacks + helper arrays (NGE, PGE, NSE, PSE)
*/

/* ----- Minimum Helpers ----- */
vector<int> findNextSmaller(const vector<int>& arr) {
    int n = arr.size();
    vector<int> nse(n);
    stack<int> st;
    for(int i = n-1; i >= 0; i--){
        while(!st.empty() && arr[st.top()] >= arr[i]) st.pop();
        nse[i] = st.empty() ? n : st.top(); // index of next smaller element
        st.push(i);
    }
    return nse;
}

vector<int> findPrevSmaller(const vector<int>& arr) {
    int n = arr.size();
    vector<int> pse(n);
    stack<int> st;
    for(int i = 0; i < n; i++){
        while(!st.empty() && arr[st.top()] > arr[i]) st.pop();
        pse[i] = st.empty() ? -1 : st.top(); // index of previous smaller element
        st.push(i);
    }
    return pse;
}

int sumSubarrayMinimums(const vector<int>& arr){
    int n = arr.size();
    vector<int> nse = findNextSmaller(arr);
    vector<int> pse = findPrevSmaller(arr);
    long long total = 0;
    const int mod = 1e9+7;

    for(int i = 0; i < n; i++){
        long long left = i - pse[i];  // #subarrays ending at i
        long long right = nse[i] - i; // #subarrays starting at i
        total = (total + (left * right % mod) * arr[i] % mod) % mod;
    }
    return (int)total;
}

/* ----- Maximum Helpers ----- */
vector<int> findNextGreater(const vector<int>& arr) {
    int n = arr.size();
    vector<int> nge(n);
    stack<int> st;
    for(int i = n-1; i >= 0; i--){
        while(!st.empty() && arr[st.top()] <= arr[i]) st.pop();
        nge[i] = st.empty() ? n : st.top(); // index of next greater element
        st.push(i);
    }
    return nge;
}

vector<int> findPrevGreater(const vector<int>& arr) {
    int n = arr.size();
    vector<int> pge(n);
    stack<int> st;
    for(int i = 0; i < n; i++){
        while(!st.empty() && arr[st.top()] < arr[i]) st.pop();
        pge[i] = st.empty() ? -1 : st.top(); // index of previous greater element
        st.push(i);
    }
    return pge;
}

int sumSubarrayMaximums(const vector<int>& arr){
    int n = arr.size();
    vector<int> nge = findNextGreater(arr);
    vector<int> pge = findPrevGreater(arr);
    long long total = 0;
    const int mod = 1e9+7;

    for(int i = 0; i < n; i++){
        long long left = i - pge[i];
        long long right = nge[i] - i;
        total = (total + (left * right % mod) * arr[i] % mod) % mod;
    }
    return (int)total;
}

/* ----- Sum of Subarray Ranges ----- */
int sumOfSubarrayRanges(const vector<int>& arr){
    // Contribution of each element as maximum minus minimum
    int maxSum = sumSubarrayMaximums(arr);
    int minSum = sumSubarrayMinimums(arr);
    const int mod = 1e9+7;
    long long ans = ((long long)maxSum - minSum + mod) % mod; // Ensure non-negative
    return (int)ans;
}

/* ----- Main ----- */
int main(){
    vector<int> arr = {3, 1, 2, 4};

    cout << "Brute-force sum of subarray ranges: " 
         << sum_of_subarr_range_brute(arr) << endl; // O(n^2)

    cout << "Optimized sum of subarray ranges: " 
         << sumOfSubarrayRanges(arr) << endl; // O(n) ~ 10n operations

    return 0;
}
