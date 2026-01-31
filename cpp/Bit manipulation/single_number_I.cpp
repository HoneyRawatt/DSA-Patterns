#include <iostream>
#include <vector>
using namespace std;

/*
Function: single_number
Purpose: Find the element that appears only once where all others appear twice.
Approach: XOR property (a ^ a = 0, a ^ 0 = a).
Time Complexity: O(n)  where n = size of array
Space Complexity: O(1)  no extra space used
*/
int single_number(vector<int> &arr) {
    int result = 0; // XOR accumulator
    for (int i = 0; i < arr.size(); i++) {
        result ^= arr[i]; // Cancel out pairs, leave single number
    }
    return result;
}

int main() {
    int n;
    cout << "Enter number of elements: ";
    cin >> n;

    vector<int> arr(n);
    cout << "Enter " << n << " numbers: ";
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    cout << "Single number is: " << single_number(arr) << endl;

    /*
    Time Complexity:
        - O(n): single pass through array
    Space Complexity:
        - O(1): constant extra space
    */

    return 0;
}
