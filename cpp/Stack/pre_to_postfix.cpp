#include <iostream>
#include <stack>
using namespace std;

/*
------------------------------------------------------------
PROBLEM STATEMENT:
------------------------------------------------------------
Given a prefix expression, convert it into its equivalent
postfix expression.

Example:
Prefix  : *+AB-CD
Postfix : AB+CD-*

------------------------------------------------------------
INTUITION:
------------------------------------------------------------
Prefix expressions are processed most easily from RIGHT to LEFT.

Rules:
- Operand → push onto stack
- Operator → pop two operands, combine them in postfix form
             and push the result back

Why stack?
- Prefix/postfix conversion requires temporary storage
- Stack naturally supports LIFO ordering

------------------------------------------------------------
ALGORITHM:
------------------------------------------------------------
1. Create an empty stack of strings
2. Traverse the prefix expression from right to left
3. If character is an operand:
      - Convert it to string and push onto stack
4. If character is an operator:
      - Pop two elements from stack
      - Form postfix: operand1 + operand2 + operator
      - Push result back onto stack
5. After traversal, stack should contain exactly one element
6. That element is the final postfix expression
*/

string pre2post(string s) {
    stack<string> st;
    int n = s.length();

    // Traverse prefix expression from RIGHT to LEFT
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
            st.pop();  // first operand
            string op2 = st.top(); 
            st.pop();  // second operand

            // Combine operands in postfix format
            // Postfix = operand1 operand2 operator
            string res = op1 + op2 + c;

            // Push combined result back to stack
            st.push(res);
        }
    }

    // Final validation
    if (st.size() != 1) {
        cout << "Invalid prefix expression\n";
        return "";
    }

    // Final postfix expression
    return st.top();
}

// Driver code
int main() {
    string prefix = "*+AB-CD"; // example: (A+B)*(C-D)
    string postfix = pre2post(prefix);

    cout << "Prefix: " << prefix << endl;
    cout << "Postfix: " << postfix << endl;

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
- Always traverse prefix from RIGHT to LEFT
- Operand → push
- Operator → pop two operands
- Correct postfix format: op1 + op2 + operator
*/
