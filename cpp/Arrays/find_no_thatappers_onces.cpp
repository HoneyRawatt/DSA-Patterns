#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
using namespace std;

int find_no_that_appears_once_brute(vector<int>& arr, int n) {
    for (int i = 0; i < n; i++) {
        int cnt = 0;
        int num = arr[i];
        for (int j = 0; j < n; j++) {
            if (arr[j] == num) cnt++;
        }
        if (cnt == 1) return arr[i];
    }
    return -1;
}

int find_no_that_appears_once_hashing(vector<int>& arr, int n) {
    int maxi = 0;
    for (int i = 0; i < n; i++) maxi = max(arr[i], maxi);
    vector<int> hash(maxi + 1, 0); 

    for (int i = 0; i < n; i++) hash[arr[i]]++;

    for (int i = 0; i < n; i++) {
        if (hash[arr[i]] == 1) return arr[i];
    }
    return -1;
}

int find_no_that_appears_once_map(vector<int>& arr, int n) {
    map<long long, int> mp;
    for (int i = 0; i < n; i++) {
        mp[arr[i]]++;
    }
    for (auto it : mp) {
        if (it.second == 1)
            return it.first;
    }
    return -1;
}

int find_no_that_appears_once_xor(vector<int>& arr, int n) {
    int xor1 = 0;
    for (int i = 0; i < n; i++) {
        xor1 ^= arr[i];
    }
    return xor1;
}

int main() {
    int n;
    cin >> n;
    vector<int> arr(n);
    cout << "Enter the elements: ";
    for (int i = 0; i < n; ++i) {
        cin >> arr[i];
    }

    cout << "Appears once (Brute): " << find_no_that_appears_once_brute(arr, n) << endl;
    cout << "Appears once (Hashing): " << find_no_that_appears_once_hashing(arr, n) << endl;
    cout << "Appears once (Map): " << find_no_that_appears_once_map(arr, n) << endl;
    cout << "Appears once (XOR): " << find_no_that_appears_once_xor(arr, n) << endl;

    return 0;
}
