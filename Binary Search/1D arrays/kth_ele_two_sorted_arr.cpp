#include <vector>
#include <climits>
#include <iostream>
using namespace std;

    /*
     * 🧠 INTUITION:
     * -------------
     * - We perform binary search on the smaller array.
     * - We partition both arrays such that:
     *     left part has exactly k elements.
     * - The k-th smallest element is:
     *     max(left part of array1, left part of array2)
     *
     * Time Complexity: O(log(min(n1, n2)))
     * Space Complexity: O(1)
     */
int find_kth_ele(vector<int> a, vector<int> b, int k) {
    int n1 = a.size();
    int n2 = b.size();
    if (n1 > n2) return find_kth_ele(b, a, k); // Always binary search on smaller array

    int low = max(0, k - n2), high = min(k, n1);
    while (low <= high) {
        int mid1 = (low + high) / 2;
        int mid2 = k - mid1;

        int l1 = (mid1 == 0) ? INT_MIN : a[mid1 - 1];
        int l2 = (mid2 == 0) ? INT_MIN : b[mid2 - 1];
        int r1 = (mid1 == n1) ? INT_MAX : a[mid1];
        int r2 = (mid2 == n2) ? INT_MAX : b[mid2];

        if (l1 <= r2 && l2 <= r1) {
            return max(l1, l2);
        } else if (l1 > r2) {
            high = mid1 - 1;
        } else {
            low = mid1 + 1;
        }
    }
    return 0;
}

int main() {
    vector<int> a = {2, 3, 6, 7, 9};
    vector<int> b = {1, 4, 8, 10};

    int k;
    cout << "Enter k (1-based index): ";
    cin >> k;

    int result = find_kth_ele(a, b, k);
    cout << "The " << k << "-th smallest element is: " << result << endl;

    return 0;
}
