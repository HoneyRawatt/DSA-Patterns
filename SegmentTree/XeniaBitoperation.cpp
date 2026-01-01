#include <bits/stdc++.h>
using namespace std;

/*
 build() function
 ----------------
 Builds the segment tree from the given array.

 ind  -> current index in segment tree
 low  -> starting index of the range
 high -> ending index of the range
 arr  -> original array
 seg  -> segment tree array
 orr  -> true  => OR operation at this level
         false => XOR operation at this level
*/
void build(int ind, int low, int high, int arr[], int seg[], bool orr) {
    // Base case: leaf node
    if (low == high) {
        seg[ind] = arr[low];   // store array value
        return;
    }

    int mid = (low + high) >> 1;

    // Build left and right subtrees
    // Operation alternates at each level
    build(2 * ind + 1, low, mid, arr, seg, !orr);
    build(2 * ind + 2, mid + 1, high, arr, seg, !orr);

    // Combine children based on current operation
    if (orr)
        seg[ind] = seg[2 * ind + 1] | seg[2 * ind + 2];
    else
        seg[ind] = seg[2 * ind + 1] ^ seg[2 * ind + 2];
}

/*
 update() function
 -----------------
 Updates a single index in the array and
 propagates changes up the segment tree.

 ind  -> current index in segment tree
 low  -> starting index of the range
 high -> ending index of the range
 seg  -> segment tree array
 orr  -> current operation (OR / XOR)
 i    -> index to be updated
 val  -> new value
*/
void update(int ind, int low, int high, int seg[], bool orr, int i, int val) {
    // Base case: leaf node
    if (low == high) {
        seg[ind] = val;    // update value
        return;
    }

    int mid = (low + high) >> 1;

    // Move to the required child
    if (i <= mid)
        update(2 * ind + 1, low, mid, seg, !orr, i, val);
    else
        update(2 * ind + 2, mid + 1, high, seg, !orr, i, val);

    // Recompute current node after update
    if (orr)
        seg[ind] = seg[2 * ind + 1] | seg[2 * ind + 2];
    else
        seg[ind] = seg[2 * ind + 1] ^ seg[2 * ind + 2];
}

int main() {
    int n, q;
    cin >> n >> q;

    // Size of array = 2^n
    int el = 1 << n;

    int arr[el];
    for (int i = 0; i < el; i++)
        cin >> arr[i];

    // Segment tree size (safe allocation)
    int seg[4 * el];

    /*
     If n is odd -> root operation is OR
     If n is even -> root operation is XOR
    */
    bool orr = (n % 2 == 1);

    // Build the segment tree
    build(0, 0, el - 1, arr, seg, orr);

    // Process queries
    while (q--) {
        int i, val;
        cin >> i >> val;

        i--; // Convert to 0-based indexing

        // Update and print result at root
        update(0, 0, el - 1, seg, orr, i, val);
        cout << seg[0] << '\n';
    }
}

// | Operation | Time       | Space    |
// | --------- | ---------- | -------- |
// | Build     | O(N)       | O(N)     |
// | Update    | O(log N)   | O(log N) |
// | Total     | O(Q log N) | O(N)     |
