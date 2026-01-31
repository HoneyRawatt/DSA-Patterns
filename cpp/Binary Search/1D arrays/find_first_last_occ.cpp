#include<iostream>
#include<vector>
using namespace std;
    /*
     * Time Complexity (all methods):
     * ------------------------------
     * O(log n) → binary search
     *
     * Space Complexity:
     * -----------------
     * O(1) → iterative, no extra space
     */
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
    return ub-1;
}


// Custom binary search versions
int firstocc(const vector<int>& arr, int target) {
    int low = 0, high = arr.size() - 1, first = -1;
    while (low <= high) {
        int mid = low + ((high - low) / 2);
        if (arr[mid] == target) {
            first = mid;
            high = mid - 1;
        } else if (arr[mid] < target)
            low = mid + 1;
        else
            high = mid - 1;
    }
    return first;
}

int lastocc(const vector<int>& arr, int target) {
    int low = 0, high = arr.size() - 1, last = -1;
    while (low <= high) {
        int mid = low + ((high - low) / 2);
        if (arr[mid] == target) {
            last = mid;
            low = mid + 1;
        } else if (arr[mid] < target)
            low = mid + 1;
        else
            high = mid - 1;
    }
    return last;
}

int main() {
    vector<int> arr = {1, 2, 4, 4, 4, 7, 9};
    int target;
    cout << "Enter target: ";
    cin >> target;

    // Using lower_bound / upper_bound
    int lb = lower_bound(arr, target);
    int ub = upper_bound(arr, target);

    if (lb == arr.size() || arr[lb] != target)
        lb = ub = -1;

    cout << "\nUsing lower_bound / upper_bound approach:\n";
    cout << "First occurring index: " << lb << endl;
    cout << "Last occurring index: " << ub << endl;

    // Using custom binary search functions
    int first = firstocc(arr, target);
    int last = lastocc(arr, target);

    cout << "\nUsing custom binary search approach:\n";
    cout << "First occurring index: " << first << endl;
    cout << "Last occurring index: " << last << endl;

    return 0;
}
