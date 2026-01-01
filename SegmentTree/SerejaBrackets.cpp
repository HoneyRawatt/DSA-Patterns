#include <bits/stdc++.h>
using namespace std;

/*
 * info structure stores:
 * open  -> number of unmatched '('
 * close -> number of unmatched ')'
 * full  -> number of matched pairs "()"
 */
class Info {
public:
    int open, close, full;

    Info(int o = 0, int c = 0, int f = 0) {
        open = o;
        close = c;
        full = f;
    }
};

/*
 * Merge two segment tree nodes
 *
 * Intuition:
 * - We can match min(left.open, right.close) brackets
 * - Those matches increase full
 * - Remaining unmatched brackets are adjusted
 *
 * Time Complexity: O(1)
 * Space Complexity: O(1)
 */
Info mergeInfo(const Info &left, const Info &right) {
    Info ans;
    int matched = min(left.open, right.close);

    ans.full  = left.full + right.full + matched;
    ans.open  = left.open + right.open - matched;
    ans.close = left.close + right.close - matched;

    return ans;
}

/*
 * Build Segment Tree
 *
 * Leaf Node:
 * '(' -> open = 1
 * ')' -> close = 1
 *
 * Internal Node:
 * Merge left and right children
 *
 * Time Complexity: O(n)
 * Space Complexity: O(4n)
 */
void build(int ind, int low, int high, const string &s, vector<Info> &seg) {
    if (low == high) {
        if (s[low] == '(')
            seg[ind] = Info(1, 0, 0);
        else
            seg[ind] = Info(0, 1, 0);
        return;
    }

    int mid = (low + high) / 2;
    build(2 * ind + 1, low, mid, s, seg);
    build(2 * ind + 2, mid + 1, high, s, seg);

    seg[ind] = mergeInfo(seg[2 * ind + 1], seg[2 * ind + 2]);
}

/*
 * Query Segment Tree for range [l, r]
 *
 * Cases:
 * - No overlap      -> return empty Info
 * - Complete overlap -> return current node
 * - Partial overlap -> merge left & right results
 *
 * Time Complexity: O(log n)
 * Space Complexity: O(log n) (recursive stack)
 */
Info query(int ind, int low, int high, int l, int r, vector<Info> &seg) {
    // No overlap
    if (r < low || high < l)
        return Info();

    // Complete overlap
    if (l <= low && high <= r)
        return seg[ind];

    // Partial overlap
    int mid = (low + high) / 2;
    Info left  = query(2 * ind + 1, low, mid, l, r, seg);
    Info right = query(2 * ind + 2, mid + 1, high, l, r, seg);

    return mergeInfo(left, right);
}

/*
 * Driver function
 *
 * For each query:
 * - Get number of matched pairs
 * - Multiply by 2 to get length of valid bracket subsequence
 *
 * Time Complexity:
 * - Build: O(n)
 * - Queries: O(q log n)
 *
 * Space Complexity:
 * - Segment Tree: O(4n)
 */
void solve() {
    string s;
    cin >> s;

    int n = s.size();
    vector<Info> seg(4 * n);

    build(0, 0, n - 1, s, seg);

    int q;
    cin >> q;

    while (q--) {
        int l, r;
        cin >> l >> r;

        // Convert to 0-based indexing
        l--;
        r--;

        Info ans = query(0, 0, n - 1, l, r, seg);

        // Each matched pair contributes 2 characters
        cout << ans.full * 2 << "\n";
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();
    return 0;
}

// | Part               | Time Complexity    | Space Complexity |
// | ------------------ | ------------------ | ---------------- |
// | Build Segment Tree | **O(n)**           | **O(4n)**        |
// | Each Query         | **O(log n)**       | **O(log n)**     |
// | Total              | **O(n + q log n)** | **O(n)**         |
