#include<iostream>
#include<vector>
#include<climits>
using namespace std;

int subarrays_max_product_optimal(vector<int> arr) {
    int prefix = 1, suffix = 1, maxi = INT_MIN;
    int n = arr.size();

    for (int i = 0; i < n; i++) {
        prefix = (prefix == 0) ? 1 : prefix;
        suffix = (suffix == 0) ? 1 : suffix;

        prefix *= arr[i];
        suffix *= arr[n - i - 1];

        maxi = max(maxi, max(prefix, suffix));
    }

    return maxi;
}


int subarrays_max_product_brute(vector<int> arr) {
    int n = arr.size();
    int maxi = INT_MIN;

    for (int i = 0; i < n; i++) {
        int prd = 1;
        for (int j = i; j < n; j++) {
            prd *= arr[j];
            maxi = max(maxi, prd);  
        }
    }

    return maxi;
}

int main() {
    vector<int> arr = {2, 3, -2, 4};  // Output should be 6
    cout << "Brute: " << subarrays_max_product_brute(arr) << endl;
    cout << "Optimal: " << subarrays_max_product_optimal(arr) << endl;
    return 0;
}
