#include <iostream>
#include <stack>
using namespace std;

/*
------------------------------------------------------------
PROBLEM STATEMENT:
------------------------------------------------------------
Given a postfix expression, convert it into its equivalent
prefix expression.

Example:
Postfix : AB+C*
Prefix  : *+ABC

------------------------------------------------------------
INTUITION:
------------------------------------------------------------
Postfix expressions are processed from LEFT to RIGHT.

Rules:
- Operand → push onto stack
- Operator → pop two operands, combine them in prefix form
             and push the result back

Why stack?
- Stack helps maintain correct operand order using LIFO
- Expression conversion naturally fits stack behavior

------------------------------------------------------------
ALGORITHM:
------------------------------------------------------------
1. Create an empty stack of strings
2. Traverse the postfix expression from left to right
3. If character is an operand:
      - Push it as a string onto the stack
4. If character is an operator:
      - Pop two elements from stack
      - Form prefix: operator + operand2 + operand1
      - Push result back onto stack
5. After traversal, stack should contain exactly one element
6. That element is the final prefix expression
*/

string post2pre(string s) {
    stack<string> st;

    // Traverse postfix expression from LEFT to RIGHT
    for (int i = 0; i < s.length(); i++) {
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
            // Invalid postfix expression (not enough operands)
            if (st.size() < 2) {
                cout << "Invalid postfix expression\n";
                return "";
            }

            // Pop operands
            string op1 = st.top(); 
            st.pop();  // first operand (right operand)

            string op2 = st.top(); 
            st.pop();  // second operand (left operand)

            // Combine to form prefix expression
            // Prefix format: operator + left + right
            string res = c + op2 + op1;

            // Push combined result back to stack
            st.push(res);
        }
    }

    // Final validation
    if (st.size() != 1) {
        cout << "Invalid postfix expression\n";
        return "";
    }

    // Final prefix expression
    return st.top();
}

// Driver code
int main() {
    string postfix = "AB+C*"; // example: (A+B)*C
    string prefix = post2pre(postfix);

    cout << "Postfix: " << postfix << endl;
    cout << "Prefix: " << prefix << endl;

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
- Traverse postfix from LEFT to RIGHT
- Operand → push
- Operator → pop two operands
- Prefix format: operator + left + right
*/
