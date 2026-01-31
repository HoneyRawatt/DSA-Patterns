#include <iostream>
#include <stack>
#include <algorithm>
using namespace std;

/*
PROBLEM STATEMENT:
Given an infix expression, convert it into prefix expression.
Example:
Infix  : (A-B/C)*(A/K-L)
Prefix : *-A/BC-/AKL
*/

// Function to return precedence of operators
// Higher value = higher precedence
int priority(char c) {
    if (c == '^') return 3;                 // highest precedence
    else if (c == '*' || c == '/') return 2;
    else if (c == '+' || c == '-') return 1;
    else return -1;                         // non-operator
}

/*
INTUITION (Infix → Postfix):
- Operands are directly added to result
- '(' is pushed to stack
- ')' causes popping until '('
- Operators are pushed after popping higher/equal precedence operators
*/

// Function to convert infix expression to postfix
string infix_to_postfix(string s) {
    stack<char> st;     // stack to store operators
    string ans;         // result postfix expression

    for (int i = 0; i < s.length(); i++) {
        char c = s[i];

        // If operand (letter or digit), add directly to answer
        if ((c >= 'A' && c <= 'Z') ||
            (c >= 'a' && c <= 'z') ||
            (c >= '0' && c <= '9')) {
            ans += c;
        }
        // If left parenthesis, push to stack
        else if (c == '(') {
            st.push(c);
        }
        // If right parenthesis, pop until '(' is found
        else if (c == ')') {
            while (!st.empty() && st.top() != '(') {
                ans += st.top();
                st.pop();
            }
            if (!st.empty()) st.pop(); // remove '('
        }
        // If operator
        else {
            // Pop operators with higher or equal precedence
            while (!st.empty() && priority(c) <= priority(st.top())) {
                ans += st.top();
                st.pop();
            }
            st.push(c);
        }
    }

    // Pop any remaining operators
    while (!st.empty()) {
        ans += st.top();
        st.pop();
    }

    return ans;
}

/*
INTUITION (Infix → Prefix):
1. Reverse the infix expression
2. Swap '(' with ')'
3. Convert the modified expression to postfix
4. Reverse the postfix result to get prefix
*/

// Function to convert infix expression to prefix
string infix_to_prefix(string s) {

    // Step 1: Reverse the infix expression
    reverse(s.begin(), s.end());

    // Step 2: Swap '(' and ')'
    for (int i = 0; i < s.length(); i++) {
        if (s[i] == '(') s[i] = ')';
        else if (s[i] == ')') s[i] = '(';
    }

    // Step 3: Convert modified expression to postfix
    string postfix = infix_to_postfix(s);

    // Step 4: Reverse postfix to get prefix
    reverse(postfix.begin(), postfix.end());
    return postfix;
}

// Driver code
int main() {
    string expr = "(A-B/C)*(A/K-L)";
    cout << "Infix: " << expr << endl;
    cout << "Prefix: " << infix_to_prefix(expr) << endl;
    return 0;
}

/*
TIME COMPLEXITY:
- O(N), where N is the length of the expression
  (each character is pushed/popped at most once)

SPACE COMPLEXITY:
- O(N) for stack usage
*/
