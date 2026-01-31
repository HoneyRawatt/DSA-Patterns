#include <iostream>
#include <vector>
using namespace std;
//Time Complexity	Space Complexity
//  O(n²)	         O(1)
vector<int> find_missing_Repeating_num_brute(vector<int> a) {
    int n = a.size();
    int repeating = -1, missing = -1;
    for (int val = 1; val <= n; val++) {  // Loop over possible values, not indices
        int cnt = 0
        for (int j = 0; j < n; j++) {
            if (a[j] == val) cnt++;
        }
        if (cnt == 2) repeating = val;
        else if (cnt == 0) missing = val;
        if (repeating != -1 && missing != -1) break;
    }
    return {repeating, missing};
}

// ✅ 1. Hashing Approach
vector<int> find_missing_Repeating_num_hashing(vector<int> a) {
    int n = a.size();
    vector<int> hasharr(n + 1, 0);
    for (int i = 0; i < n; i++) {
        hasharr[a[i]]++;
    }
    int repeating = -1, missing = -1;
    for (int i = 1; i <= n; i++) {
        if (hasharr[i] == 2) repeating = i;
        else if (hasharr[i] == 0) missing = i;
    }
    return {repeating, missing};
}

// ✅ 2. Math Approach
vector<int> find_missing_Repeating_num_Math(vector<int> a) {
    long long n = a.size();
    long long sn = (n * (n + 1)) / 2;
    long long s2n = (n * (n + 1) * (2 * n + 1)) / 6;
    long long s = 0, s2 = 0;
    for (int i = 0; i < n; i++) {
        s += a[i];
        s2 += 1LL * a[i] * a[i];
    }
    long long val1 = s - sn;       // x - y
    long long val2 = s2 - s2n;     // x^2 - y^2 = (x - y)(x + y)
    val2 = val2 / val1;            // x + y

    long long x = (val1 + val2) / 2;
    long long y = x - val1;

    return {(int)x, (int)y};
}

// ✅ 3. XOR Approach (Corrected)
vector<int> find_missing_Repeating_num_xor(vector<int> a) {
    int n = a.size();
    int xr = 0;

    for (int i = 0; i < n; i++) {
        xr ^= a[i];     // XOR of array elements
        xr ^= (i + 1);  // XOR of 1 to n
    }

    // Find rightmost set bit
    int bitno = 0;
    while ((xr & (1 << bitno)) == 0) bitno++;

    int one = 0, zero = 0;

    for (int i = 0; i < n; i++) {
        if (a[i] & (1 << bitno)) one ^= a[i];
        else zero ^= a[i];
    }
    for (int i = 1; i <= n; i++) {
        if (i & (1 << bitno)) one ^= i;
        else zero ^= i;
    }

    // Determine which is repeating and which is missing
    int count = 0;
    for (int i = 0; i < n; i++) {
        if (a[i] == one) count++;
    }
    if (count == 2) return {one, zero};  // one is repeating
    else return {zero, one};            // zero is repeating
}

// ✅ Utility to print output
void print_result(const vector<int>& res) {
    cout << "Repeating: " << res[0] << ", Missing: " << res[1] << endl;
}

// ✅ Main Function
int main() {
    vector<int> arr = {4, 3, 6, 2, 1, 1}; // 1 is repeating, 5 is missing

    cout << "Brute Force Approach:\n";
    print_result(find_missing_Repeating_num_brute(arr));

    cout << "\nHashing Approach:\n";
    print_result(find_missing_Repeating_num_hashing(arr));

    cout << "\nMath Approach:\n";
    print_result(find_missing_Repeating_num_Math(arr));

    cout << "\nXOR Approach:\n";
    print_result(find_missing_Repeating_num_xor(arr));

    return 0;
}
