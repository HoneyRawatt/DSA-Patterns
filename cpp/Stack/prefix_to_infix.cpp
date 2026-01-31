#include <iostream>
#include <stack>
using namespace std;

/*
------------------------------------------------------------
PROBLEM STATEMENT:
------------------------------------------------------------
Given a prefix expression, convert it into its equivalent
infix expression.

Example:
Prefix : *+AB-C
Infix  : (A+B)*(C-?)
(Note: Example assumes valid operands)

------------------------------------------------------------
INTUITION:
------------------------------------------------------------
Prefix expressions are best handled using a stack.

Key idea:
- Traverse the prefix expression from RIGHT to LEFT
- Operand  → push onto stack
- Operator → pop two operands, combine them into infix
             form with parentheses, then push back

Parentheses are necessary to preserve operator precedence.

------------------------------------------------------------
ALGORITHM:
------------------------------------------------------------
1. Create an empty stack of strings
2. Traverse the prefix string from right to left
3. If character is an operand:
      - Push it as a string onto the stack
4. If character is an operator:
      - Pop two elements from stack
      - Form expression: (operand1 operator operand2)
      - Push result back to stack
5. At the end, stack should contain exactly one element
6. That element is the final infix expression
*/

string prefix_to_infix(string &s) {
    stack<string> st;
    int n = s.length();

    // Traverse prefix expression from right to left
    for (int i = n - 1; i >= 0; i--) {
        char c = s[i];

        // Case 1: Operand (letter or digit)
        if ((c >= 'A' && c <= 'Z') || 
            (c >= 'a' && c <= 'z') || 
            (c >= '0' && c <= '9')) {

            // Push operand as a string
            st.push(string(1, c));
        } 
        // Case 2: Operator
        else {
            // Invalid prefix expression (not enough operands)
            if (st.size() < 2) {
                cout << "Invalid prefix expression\n";
                return "";
            }

            // Pop operands
            string op1 = st.top(); 
            st.pop();   // first operand
            string op2 = st.top(); 
            st.pop();   // second operand

            // Form infix expression with parentheses
            string res = "(" + op1 + c + op2 + ")";

            // Push result back to stack
            st.push(res);
        }
    }

    // After processing, stack must contain exactly one expression
    if (st.size() != 1) {
        cout << "Invalid prefix expression\n";
        return "";
    }

    return st.top();
}

// Driver code
int main() {
    string prefix = "*+AB-C";   // example
    string infix = prefix_to_infix(prefix);

    cout << "Prefix: " << prefix << endl;
    cout << "Infix: " << infix << endl;

    return 0;
}

/*
------------------------------------------------------------
TIME COMPLEXITY:
------------------------------------------------------------
O(N)
- Each character is processed once

------------------------------------------------------------
SPACE COMPLEXITY:
------------------------------------------------------------
O(N)
- Stack can store up to N operands/expressions

------------------------------------------------------------
KEY TAKEAWAYS:
------------------------------------------------------------
- Traverse prefix from RIGHT to LEFT
- Operand → push
- Operator → pop 2 operands
- Parentheses preserve correctness
*/
