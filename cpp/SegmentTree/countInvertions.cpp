#include <bits/stdc++.h>
using namespace std;

/*
====================================================
SEGMENT TREE (Range Sum Query + Point Update)
====================================================

Intuition:
-----------
- Segment Tree stores sum of a range
- Each node represents sum of frequencies in [low, high]
- Used here to count how many elements exist in a value range

Time Complexity:
----------------
Build Tree     : O(N)
Query          : O(log N)
Update         : O(log N)

Space Complexity:
-----------------
Segment Tree   : O(4N)
====================================================
*/

class SGTree {
    vector<int> seg;

public:
    SGTree(int n) {
        seg.resize(4 * n, 0);
    }

    /*
     * Build the segment tree from frequency array
     *
     * Time Complexity: O(N)
     * Space Complexity: O(4N)
     */
    void build(int ind, int low, int high, vector<int> &arr) {
        if (low == high) {
            seg[ind] = arr[low];
            return;
        }

        int mid = (low + high) / 2;
        build(2 * ind + 1, low, mid, arr);
        build(2 * ind + 2, mid + 1, high, arr);

        seg[ind] = seg[2 * ind + 1] + seg[2 * ind + 2];
    }

    /*
     * Range Sum Query
     *
     * Returns sum of frequencies in range [l, r]
     *
     * Time Complexity: O(log N)
     * Space Complexity: O(log N) (recursion stack)
     */
    int query(int ind, int low, int high, int l, int r) {
        // No overlap
        if (r < low || high < l)
            return 0;

        // Complete overlap
        if (l <= low && high <= r)
            return seg[ind];

        // Partial overlap
        int mid = (low + high) / 2;
        int left = query(2 * ind + 1, low, mid, l, r);
        int right = query(2 * ind + 2, mid + 1, high, l, r);

        return left + right;
    }

    /*
     * Point Update
     *
     * Updates index i with new value val
     *
     * Time Complexity: O(log N)
     * Space Complexity: O(log N)
     */
    void update(int ind, int low, int high, int i, int val) {
        if (low == high) {
            seg[ind] += val;
            return;
        }

        int mid = (low + high) / 2;
        if (i <= mid)
            update(2 * ind + 1, low, mid, i, val);
        else
            update(2 * ind + 2, mid + 1, high, i, val);

        seg[ind] = seg[2 * ind + 1] + seg[2 * ind + 2];
    }
};

/*
====================================================
INVERSION COUNT USING SEGMENT TREE
====================================================

Steps:
------
1. Read array
2. Build frequency array
3. Build segment tree on frequency array
4. Traverse original array:
   - Remove current element from frequency
   - Query how many smaller elements exist

Overall Time Complexity:
-----------------------
O(N log N)

Overall Space Complexity:
------------------------
O(N)
====================================================
*/

void solve() {
    int n;
    cin >> n;

    vector<int> arr(n);
    int mx = 0;

    for (int i = 0; i < n; i++) {
        cin >> arr[i];
        mx = max(mx, arr[i]);
    }

    // Frequency array size = max element + 1
    vector<int> freq(mx + 1, 0);
    for (int x : arr)
        freq[x]++;

    SGTree st(mx + 1);
    st.build(0, 0, mx, freq);

    long long cnt = 0;

    for (int i = 0; i < n; i++) {
        // Remove current element
        st.update(0, 0, mx, arr[i], -1);

        // Count how many smaller elements exist
        if (arr[i] > 0)
            cnt += st.query(0, 0, mx, 0, arr[i] - 1);
    }

    cout << cnt << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();
    return 0;
}
