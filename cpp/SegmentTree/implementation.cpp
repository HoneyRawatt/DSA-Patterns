#include <bits/stdc++.h>
using namespace std;

/*
====================================================
SEGMENT TREE (Range Minimum Query + Point Update)
====================================================

Intuition:
-----------
- Segment Tree stores information (here: minimum)
  of array segments.
- Each node represents a range [low, high].
- Root -> whole array
- Left child -> left half
- Right child -> right half

Why Segment Tree?
-----------------
- Query min in a range efficiently
- Update a single element efficiently
- Much faster than brute force for large queries

----------------------------------------------------
Time Complexity:
----------------------------------------------------
Build Tree     : O(N)
Query (RMQ)    : O(log N)
Update         : O(log N)

----------------------------------------------------
Space Complexity:
----------------------------------------------------
Segment Tree uses ~4 * N space
=> O(N)
====================================================
*/

class SGTree {
    vector<int> seg;

public:
    SGTree(int n) {
        seg.resize(4 * n);
    }

    /* Build the segment tree */
    void build(int ind, int low, int high, vector<int> &arr) {
        if (low == high) {
            seg[ind] = arr[low];
            return;
        }

        int mid = (low + high) / 2;
        build(2 * ind + 1, low, mid, arr);
        build(2 * ind + 2, mid + 1, high, arr);

        seg[ind] = min(seg[2 * ind + 1], seg[2 * ind + 2]);
    }

    /* Range Minimum Query */
    int query(int ind, int low, int high, int l, int r) {

        // No overlap
        if (r < low || high < l) {
            return INT_MAX;
        }

        // Complete overlap
        if (l <= low && high <= r) {
            return seg[ind];
        }

        // Partial overlap
        int mid = (low + high) / 2;
        int left = query(2 * ind + 1, low, mid, l, r);
        int right = query(2 * ind + 2, mid + 1, high, l, r);

        return min(left, right);
    }

    /* Point Update */
    void update(int ind, int low, int high, int i, int val) {
        if (low == high) {
            seg[ind] = val;
            return;
        }

        int mid = (low + high) / 2;
        if (i <= mid)
            update(2 * ind + 1, low, mid, i, val);
        else
            update(2 * ind + 2, mid + 1, high, i, val);

        seg[ind] = min(seg[2 * ind + 1], seg[2 * ind + 2]);
    }
};

/*
====================================================
SOLUTION WITH TWO ARRAYS
====================================================
- Each array has its own segment tree
- Query minimum across both arrays
- Update either array independently
====================================================
*/

void solve2() {
    int n1;
    cin >> n1;
    vector<int> arr1(n1);
    for (int i = 0; i < n1; i++) cin >> arr1[i];

    SGTree sg1(n1);
    sg1.build(0, 0, n1 - 1, arr1);

    int n2;
    cin >> n2;
    vector<int> arr2(n2);
    for (int i = 0; i < n2; i++) cin >> arr2[i];

    SGTree sg2(n2);
    sg2.build(0, 0, n2 - 1, arr2);

    int q;
    cin >> q;

    while (q--) {
        int type;
        cin >> type;

        // Query minimum in ranges
        if (type == 1) {
            int l1, r1, l2, r2;
            cin >> l1 >> r1 >> l2 >> r2;

            int min1 = sg1.query(0, 0, n1 - 1, l1, r1);
            int min2 = sg2.query(0, 0, n2 - 1, l2, r2);

            cout << min(min1, min2) << endl;
        }
        // Update value
        else {
            int arrNo, idx, val;
            cin >> arrNo >> idx >> val;

            if (arrNo == 1) {
                sg1.update(0, 0, n1 - 1, idx, val);
                arr1[idx] = val;
            } else {
                sg2.update(0, 0, n2 - 1, idx, val);
                arr2[idx] = val;
            }
        }
    }
}

int main() {
    solve2();
    return 0;
}
