#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

vector<int> next_greater_permutation(vector<int>& arr) { 
    int indx = -1;
    int n = arr.size();

    // Step 1: Find the first index from right where arr[i] < arr[i+1]
    for (int i = n - 2; i >= 0; i--) {
        if (arr[i] < arr[i + 1]) {
            indx = i;
            break;
        }
    }

    // Step 2: If no such index found, reverse the entire array
    if (indx == -1) {
        reverse(arr.begin(), arr.end());
        return arr;
    }

    // Step 3: Find the smallest element greater than arr[indx] from the right
    for (int i = n - 1; i > indx; i--) {
        if (arr[i] > arr[indx]) {
            swap(arr[i], arr[indx]);
            break;
        }
    }

    // Step 4: Reverse the subarray after indx
    reverse(arr.begin() + indx + 1, arr.end());

    return arr;
}

int main() {
    vector<int> arr = {1, 2, 3,2,1};

    cout << "Original permutation: ";
    for (int num : arr)
        cout << num << " ";
    cout << endl;

    vector<int> nextPerm = next_greater_permutation(arr);

    cout << "Next greater permutation: ";
    for (int num : nextPerm)
        cout << num << " ";
    cout << endl;

    return 0;
}
