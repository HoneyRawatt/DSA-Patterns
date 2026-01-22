#include <iostream>
#include <stack>
using namespace std;

/*
====================================================
PROBLEM STATEMENT:
----------------------------------------------------
Given an infix expression (e.g., A*(B+C)/D),
convert it into its equivalent postfix expression.

Infix  : Operators are written between operands (A + B)
Postfix: Operators are written after operands (AB+)

Rules:
- Operands appear in the same order
- Operator precedence must be preserved
- Parentheses must be handled correctly
====================================================
*/

/*
====================================================
INTUITION / APPROACH:
----------------------------------------------------
We use a STACK to temporarily store operators because
it allows us to manage precedence and parentheses.

Algorithm:
1. Traverse the infix expression from left to right.
2. If the character is an operand → add it to result.
3. If the character is '(' → push it onto the stack.
4. If the character is ')' → pop from stack until '('.
5. If the character is an operator:
   - Pop operators from stack while they have
     higher or equal precedence than current operator.
   - Push the current operator onto the stack.
6. After traversal, pop all remaining operators.
====================================================
*/

/*
Function to return precedence of operators.
Higher value means higher precedence.
*/
int priority(char c) {
    if (c == '^') return 3;
    else if (c == '*' || c == '/') return 2;
    else if (c == '+' || c == '-') return 1;
    else return -1;
}

/*
Function to convert infix expression to postfix expression.
*/
string infix_to_postfix(string s) {
    stack<char> st;   // Stack to store operators
    string ans = "";  // Result postfix expression

    // Traverse each character of the infix expression
    for (int i = 0; i < s.length(); i++) {
        char c = s[i];

        // If operand (letter or digit), add directly to result
        if ((c >= 'A' && c <= 'Z') ||
            (c >= 'a' && c <= 'z') ||
            (c >= '0' && c <= '9')) {
            ans += c;
        }

        // If opening parenthesis, push onto stack
        else if (c == '(') {
            st.push(c);
        }

        // If closing parenthesis, pop until '(' is found
        else if (c == ')') {
            while (!st.empty() && st.top() != '(') {
                ans += st.top();
                st.pop();
            }
            if (!st.empty()) st.pop(); // Remove '('
        }

        // If operator
        else {
            // Pop operators with higher or equal precedence
            while (!st.empty() && priority(c) <= priority(st.top())) {
                ans += st.top();
                st.pop();
            }
            // Push current operator
            st.push(c);
        }
    }

    // Pop all remaining operators from stack
    while (!st.empty()) {
        ans += st.top();
        st.pop();
    }

    return ans;
}

/*
====================================================
TIME & SPACE COMPLEXITY:
----------------------------------------------------
Let n = length of the expression

Time Complexity: O(n)
- Each character is processed once
- Each operator is pushed and popped at most once

Space Complexity: O(n)
- Stack may store up to n operators in worst case
====================================================
*/

int main() {
    string expr = "A*(B+C)/D";

    cout << "Infix: " << expr << endl;
    cout << "Postfix: " << infix_to_postfix(expr) << endl;

    return 0;
}
