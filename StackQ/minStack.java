package StackQ;

import java.util.Stack;

/*
============================================================
PROBLEM STATEMENT:
============================================================
Design a stack that supports the following operations in O(1):
1. push(x)
2. pop()
3. top()
4. getMin() → returns minimum element in the stack
*/

/*
============================================================
APPROACH 1: BRUTE FORCE (Extra Space using Pair)
============================================================
Idea:
- Store value along with minimum till that element
- Minimum is always available at top

Time Complexity: O(1)
Space Complexity: O(N)
*/

class MinStackBrute {

    // Pair class to store value and minimum
    static class Pair {
        int val, min;
        Pair(int v, int m) {
            val = v;
            min = m;
        }
    }

    Stack<Pair> st = new Stack<>();

    void push(int val) {
        if (st.isEmpty())
            st.push(new Pair(val, val));
        else
            st.push(new Pair(val, Math.min(val, st.peek().min)));
    }

    void pop() {
        if (!st.isEmpty())
            st.pop();
    }

    int top() {
        if (st.isEmpty())
            return -1;
        return st.peek().val;
    }

    int getMin() {
        if (st.isEmpty())
            return -1;
        return st.peek().min;
    }
}

/*
============================================================
APPROACH 2: OPTIMIZED (O(1) EXTRA SPACE)
============================================================
Key Trick:
- Encode values when pushing smaller elements

Encoding:
    encoded = 2 * val - min

Decoding (while popping):
    previousMin = 2 * min - encoded

Time Complexity: O(1)
Space Complexity: O(1)
*/

class MinStack {

    Stack<Integer> st = new Stack<>();
    int min;

    void push(int val) {
        if (st.isEmpty()) {
            min = val;
            st.push(val);
        } else if (val >= min) {
            st.push(val);
        } else {
            // Encode value
            st.push(2 * val - min);
            min = val;
        }
    }

    void pop() {
        if (st.isEmpty())
            return;

        int top = st.pop();

        // If encoded value, restore previous minimum
        if (top < min) {
            min = 2 * min - top;
        }
    }

    int top() {
        if (st.isEmpty())
            return -1;

        int top = st.peek();
        // If encoded, actual top is min
        return top >= min ? top : min;
    }

    int getMin() {
        if (st.isEmpty())
            return -1;
        return min;
    }
}

/*
============================================================
DRIVER CODE
============================================================
*/

public class minStack{
    public static void main(String[] args) {

        MinStack s = new MinStack();

        s.push(5);
        s.push(3);
        s.push(7);

        System.out.println("Min: " + s.getMin()); // 3

        s.pop();
        System.out.println("Top: " + s.top());    // 3
        System.out.println("Min: " + s.getMin()); // 3

        s.pop();
        System.out.println("Min: " + s.getMin()); // 5
    }
}
