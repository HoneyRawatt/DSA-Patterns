#include <iostream>
#include <stack>
using namespace std;

/*
============================================================
PROBLEM STATEMENT:
============================================================
Design a stack that supports the following operations in O(1) time:
1. push(x)
2. pop()
3. top()
4. getMin()  -> returns the minimum element in the stack

============================================================
APPROACH 1: BRUTE FORCE (Using Extra Space)
============================================================
Idea:
- Store a pair for each element:
    (value, minimum till this element)
- Minimum is always available at the top

Pros:
- Simple and easy to understand

Cons:
- Uses extra space for storing minimum with each element
*/

class min_stack_brute {
    // Stack stores pairs: {value, current minimum}
    stack<pair<int,int>> st;

public:
    // Push element into stack
    void push(int val) {
        // If stack is empty, value itself is the minimum
        if (st.empty())
            st.push({val, val});
        else
            // Store value and min till now
            st.push({val, min(val, st.top().second)});
    }

    // Remove top element
    void pop() {
        if (!st.empty())
            st.pop();
    }

    // Return top element
    int top() {
        if (st.empty()) {
            cout << "Stack empty\n";
            return -1;
        }
        return st.top().first;
    }

    // Return minimum element
    int getmin() {
        if (st.empty()) {
            cout << "Stack empty\n";
            return -1;
        }
        return st.top().second;
    }
};

/*
============================================================
APPROACH 2: OPTIMIZED (O(1) EXTRA SPACE)
============================================================
Key Idea:
- Do NOT use extra stack or pair
- Store a modified (encoded) value when pushing a new minimum

Encoding Formula:
    encoded = 2 * newVal - oldMin

Decoding Formula (while popping):
    previousMin = 2 * currentMin - encodedValue

Why it works?
- Encoded values are always smaller than current minimum
- Helps identify when minimum changes

Pros:
- O(1) space
- Very efficient

Cons:
- Slightly tricky to understand
*/

class min_stack {
    stack<int> st;  // stores actual or encoded values
    int mini;       // stores current minimum

public:
    // Push element
    void push(int val) {
        // If stack is empty
        if (st.empty()) {
            mini = val;
            st.push(val);
        } else {
            if (val >= mini) {
                // Normal push
                st.push(val);
            } else {
                // Encode value before pushing
                st.push(2 * val - mini);
                mini = val;
            }
        }
    }

    // Pop element
    void pop() {
        if (st.empty()) return;

        int x = st.top();
        st.pop();

        // If encoded value, restore previous minimum
        if (x < mini) {
            mini = 2 * mini - x;
        }
    }

    // Return top element
    int top() {
        if (st.empty()) {
            cout << "Stack empty\n";
            return -1;
        }

        int x = st.top();
        // If encoded, actual value is current minimum
        if (x >= mini)
            return x;
        return mini;
    }

    // Return minimum element
    int getmin() {
        if (st.empty()) {
            cout << "Stack empty\n";
            return -1;
        }
        return mini;
    }
};

// Driver code
int main() {
    min_stack s;
    s.push(5);
    s.push(3);
    s.push(7);

    cout << "Min: " << s.getmin() << endl; // 3

    s.pop();
    cout << "Top: " << s.top() << endl;    // 3
    cout << "Min: " << s.getmin() << endl; // 3

    s.pop();
    cout << "Min: " << s.getmin() << endl; // 5

    return 0;
}

/*
============================================================
TIME COMPLEXITY:
============================================================
push()   -> O(1)
pop()    -> O(1)
top()    -> O(1)
getMin() -> O(1)

============================================================
SPACE COMPLEXITY:
============================================================
Brute Force : O(N) extra space
Optimized   : O(1) extra space

============================================================
KEY TAKEAWAYS:
============================================================
- Brute force is easy but memory heavy
- Optimized approach uses math trick (encoding/decoding)
- Very popular interview & GFG problem
*/
