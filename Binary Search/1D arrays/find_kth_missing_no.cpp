,#include <iostream>
#include <vector>
using namespace std;
    /*
     * ------------------------------------------------------------
     * INTUITION (Linear Scan):
     * ------------------------------------------------------------
     * We walk through the array and compare each element with k.
     * If arr[i] <= k, it means one missing number is "pushed ahead",
     * so we increment k.
     * Once arr[i] > k, we stop because further elements won't affect k.
     *
     * Example:
     * arr = [2,3,4,7,11], k = 5
     * i=0 → arr[0]=2 <= 5 → k becomes 6
     * i=1 → arr[1]=3 <= 6 → k becomes 7
     * i=2 → arr[2]=4 <= 7 → k becomes 8
     * i=3 → arr[3]=7 <= 8 → k becomes 9
     * i=4 → arr[4]=11 > 9 → stop
     * Answer = 9
     *
     * ------------------------------------------------------------
     * TIME COMPLEXITY: O(n)
     * SPACE COMPLEXITY: O(1)
     * ------------------------------------------------------------
     */
int findKthPositive_Linear(vector<int>& arr, int k) {
   for(int i=0;i<arr.size();i++){
    if(arr[i]<=k) k++;
    else break;
   }
   return k;
}


    /*
     * ------------------------------------------------------------
     * INTUITION (Binary Search):
     * ------------------------------------------------------------
     * In a perfect array [1,2,3,...], element at index i should be (i+1).
     * If arr[mid] != mid+1, then some numbers are missing.
     *
     * Missing numbers before index mid:
     * missing = arr[mid] - (mid + 1)
     *
     * If missing < k → kth missing lies to the right
     * If missing >= k → kth missing lies to the left
     *
     * Final Answer:
     * After binary search ends, kth missing number is:
     * high + k + 1
     *
     * ------------------------------------------------------------
     * TIME COMPLEXITY: O(log n)
     * SPACE COMPLEXITY: O(1)
     * ------------------------------------------------------------
     */
// Binary Search to find the Kth missing positive number
int findKthPositive_Binary(vector<int>& arr, int k) {
    int low = 0, high = arr.size() - 1;

    while (low <= high) {
        int mid = low + (high - low) / 2;
        int missing = arr[mid] - (mid + 1);  // Missing numbers before index mid

        if (missing < k)
            low = mid + 1;
        else
            high = mid - 1;
    }

    return high + k + 1;
}
int main() {
    vector<int> arr = {2, 3, 4, 7, 11};
    int k = 5;

    int result = findKthPositive_Binary(arr, k);
    cout << "Binary Search: " << k << "th missing number is: " << result << endl;

    result = findKthPositive_Linear(arr, k);
    cout << "Linear Search: " << k << "th missing number is: " << result << endl;

    return 0;
}