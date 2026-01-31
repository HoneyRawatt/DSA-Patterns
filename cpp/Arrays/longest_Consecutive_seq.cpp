#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_set>
#include <climits>

using namespace std;

// 🔴 Brute Force (O(n^2))
int longest_consecutive_seq_brute(vector<int>& a) {
    int n = a.size();
    if (n == 0) return 0;

    int longest = 1;

    for (int i = 0; i < n; i++) {
        int x = a[i];
        int cnt = 1;

        // Linear search for next consecutive numbers
        while (find(a.begin(), a.end(), x + 1) != a.end()) {
            x = x + 1;
            cnt++;
        }

        longest = max(longest, cnt);
    }

    return longest;
}

// 🟠 Better (O(n log n))
int longest_consecutive_seq_better(vector<int>& a) {
    int n = a.size();
    if (n == 0) return 0;

    sort(a.begin(), a.end());
    int lastsmall = INT_MIN, longest = 1, cnt = 0;

    for (int i = 0; i < n; i++) {
        if (a[i] - 1 == lastsmall) {
            cnt++;
            lastsmall = a[i];
        } else if (a[i] != lastsmall) {  // skip duplicates
            cnt = 1;
            lastsmall = a[i];
        }
        longest = max(cnt, longest);
    }

    return longest;
}

// 🟢 Optimal using unordered_set (O(n))
int longest_consecutive_seq_usingset(vector<int>& a) {
    int n = a.size();
    if (n == 0) return 0;

    unordered_set<int> st;
    for (int i = 0; i < n; i++) {
        st.insert(a[i]);
    }

    int longest = 1;

    for (auto it : st) {
        // Check if it's the start of a sequence
        if (st.find(it - 1) == st.end()) {
            int cnt = 1;
            int x = it;

            while (st.find(x + 1) != st.end()) {
                x = x + 1;
                cnt++;
            }

            longest = max(longest, cnt);
        }
    }

    return longest;
}

int main() {
    vector<int> arr = {100, 4, 200, 1, 3, 2};

    cout << "Original Array: ";
    for (int num : arr) {
        cout << num << " ";
    }
    cout << "\n";

    cout << "\n🔴 Brute Force Answer: " << longest_consecutive_seq_brute(arr);
    cout << "\n🟠 Better (Sorted) Answer: " << longest_consecutive_seq_better(arr);
    cout << "\n🟢 Optimal (Using Set) Answer: " << longest_consecutive_seq_usingset(arr);

    return 0;
}
