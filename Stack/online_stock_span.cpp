#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
using namespace std;

/*
=====================================================
PROBLEM STATEMENT (Stock Span Problem):
-----------------------------------------------------
The stock span of a day is the number of consecutive days
(including today) for which the price of the stock was
less than or equal to today's price.

You are given stock prices day by day.
For each price, return its stock span.
=====================================================
*/

/*
=====================================================
1️⃣ Brute Force Version
=====================================================
Intuition:
- For every new price, move backward in the array
- Count how many consecutive previous prices are
  less than or equal to the current price
- Stop when a greater price is found

Time Complexity:
- Worst case: O(n) per query
- Overall: O(n²) for n days

Space Complexity:
- O(n) to store prices
*/
class StockSpannerBrute {
public:
    vector<int> arr;   // Stores all previous prices

    StockSpannerBrute() {}

    int next(int price) {
        int cnt = 1;           // Span always includes today
        arr.push_back(price); // Store today's price

        // Traverse backward to count span
        for (int i = arr.size() - 2; i >= 0; i--) {
            if (arr[i] <= price)
                cnt++;
            else
                break;         // Stop when higher price found
        }
        return cnt;
    }
};

/*
=====================================================
2️⃣ Optimized Version using Monotonic Stack
=====================================================
Intuition:
- Use a monotonic decreasing stack
- Stack stores pairs: {price, index}
- Remove all previous prices that are <= current price
- The span is the difference between current index
  and the index of the previous greater element

Why it works:
- Each element is pushed and popped at most once
- Ensures amortized O(1) time per operation

Time Complexity:
- Amortized O(1) per next()
- Overall O(n)

Space Complexity:
- O(n) for stack storage
*/
class StockSpanner {
public:
    stack<pair<int, int>> st; // {price, index}
    int ind;                  // Current day index

    StockSpanner() {
        ind = -1;
        while (!st.empty()) st.pop();
    }

    int next(int price) {
        ind++; // Move to next day

        // Remove all prices smaller than or equal to current
        while (!st.empty() && st.top().first <= price)
            st.pop();

        // Index of previous greater price
        int prevGreaterIndex = st.empty() ? -1 : st.top().second;

        // Span calculation
        int ans = ind - prevGreaterIndex;

        // Push current price with its index
        st.push({price, ind});
        return ans;
    }
};

/*
=====================================================
Main Function
=====================================================
*/
int main() {
    StockSpanner s;

    vector<int> prices = {100, 80, 60, 70, 60, 75, 85};

    for (int p : prices) {
        cout << s.next(p) << " ";
    }
    // Output: 1 1 1 2 1 4 6

    return 0;
}
