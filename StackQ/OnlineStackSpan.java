package StackQ;

import java.util.*;

/*
=====================================================
PROBLEM STATEMENT (Stock Span Problem):
-----------------------------------------------------
The stock span of a day is the number of consecutive days
(including today) for which the stock price was
less than or equal to today’s price.

For each incoming price, return its span.
=====================================================
*/

/*
=====================================================
1️⃣ Brute Force Version
=====================================================
Intuition:
- Store all previous prices
- For each new price, move backward and count how many
  consecutive prices are <= current price

Time Complexity:
- Worst case per call: O(n)
- Overall: O(n^2)

Space Complexity:
- O(n) to store prices
*/
class StockSpannerBrute {
    private List<Integer> arr;

    public StockSpannerBrute() {
        arr = new ArrayList<>();
    }

    public int next(int price) {
        int cnt = 1;            // Span always includes today
        arr.add(price);

        // Traverse backward
        for (int i = arr.size() - 2; i >= 0; i--) {
            if (arr.get(i) <= price)
                cnt++;
            else
                break;
        }
        return cnt;
    }
}

/*
=====================================================
2️⃣ Optimized Version using Monotonic Stack
=====================================================
Intuition:
- Maintain a monotonic decreasing stack
- Stack stores {price, index}
- Remove all previous prices <= current price
- Span = current index - index of previous greater element

Why it works:
- Each element is pushed and popped at most once
- Amortized O(1) time per operation

Time Complexity:
- O(1) amortized per call
- O(n) overall

Space Complexity:
- O(n)
*/
class StockSpanner {
    private Stack<int[]> st; // {price, index}
    private int index;

    public StockSpanner() {
        st = new Stack<>();
        index = -1;
    }

    public int next(int price) {
        index++;

        // Remove all smaller or equal prices
        while (!st.isEmpty() && st.peek()[0] <= price) {
            st.pop();
        }

        // Previous greater element index
        int prevGreaterIndex = st.isEmpty() ? -1 : st.peek()[1];

        // Span calculation
        int span = index - prevGreaterIndex;

        // Push current price and index
        st.push(new int[]{price, index});
        return span;
    }
}

/*
=====================================================
Main Class
=====================================================
*/
public class OnlineStackSpan{
    public static void main(String[] args) {
        StockSpanner s = new StockSpanner();

        int[] prices = {100, 80, 60, 70, 60, 75, 85};

        for (int p : prices) {
            System.out.print(s.next(p) + " ");
        }
        // Output: 1 1 1 2 1 4 6
    }
}
