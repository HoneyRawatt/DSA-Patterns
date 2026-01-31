#include<iostream>
#include<vector>
using namespace std;

    /*
     * Time Complexity (Both lower & upper bound):
     * -------------------------------------------
     * Each function uses binary search.
     * The search space is halved every iteration.
     *
     * Time Complexity: O(log n)
     *
     * Space Complexity:
     * -----------------
     * Iterative approach → no recursion stack.
     *
     * Space Complexity: O(1)
     */
//search insert index problem
int lower_bound(const vector<int>& arr, int target) {
    int low = 0;
    int lb = arr.size();
    int high = lb - 1;
    while (low <= high) {
        int mid = low + ((high - low) / 2);
        if (arr[mid] >= target) {
            high = mid - 1;
            lb = mid;
        } else {
            low = mid + 1;
        }
    }
    return lb;
}

int upper_bound(const vector<int>& arr, int target) {
    int low = 0;
    int ub = arr.size();
    int high = ub - 1;
    while (low <= high) {
        int mid = low + ((high - low) / 2);
        if (arr[mid] > target) {
            high = mid - 1;
            ub = mid;
        } else {
            low = mid + 1;
        }
    }
    return ub;
}

int main() {
    vector<int> arr = {1, 2, 4, 4, 4, 7, 9};
    int target;
    cout << "Enter target: ";
    cin >> target;

    int lb = lower_bound(arr, target);
    int ub = upper_bound(arr, target);

    cout << "Lower Bound index: " << lb << endl;
    cout << "Upper Bound index: " << ub << endl;

    // Occurrence count of target:
    if (lb == arr.size() || arr[lb] != target)
        cout << "Target not found\n";
    else
        cout << "Target occurs " << (ub - lb) << " times\n";

    return 0;
}
