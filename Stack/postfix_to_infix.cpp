#include <iostream>
#include <stack>
using namespace std;

/*
------------------------------------------------------------
PROBLEM STATEMENT:
------------------------------------------------------------
Given a postfix (Reverse Polish Notation) expression,
convert it into its equivalent infix expression.

Example:
Postfix : AB+C*
Infix   : (A+B)*C

------------------------------------------------------------
INTUITION:
------------------------------------------------------------
Postfix expression evaluation is best handled using a stack.

Rule:
- Operand → push onto stack
- Operator → pop top two operands, combine them in infix form
  using parentheses, and push back the result

Why parentheses?
- To preserve the correct order of operations

------------------------------------------------------------
ALGORITHM:
------------------------------------------------------------
1. Create an empty stack of strings
2. Traverse the postfix expression from left to right
3. If character is an operand:
      - Convert it to string and push to stack
4. If character is an operator:
      - Pop two elements from stack (right operand first)
      - Form: (operand2 operator operand1)
      - Push result back to stack
5. At the end, stack should contain exactly one element
6. That element is the final infix expression
*/

string postfix_to_infix(string &s) {
    stack<string> st;

    for (int i = 0; i < s.length(); i++) {
        char c = s[i];

        // Case 1: Operand (letter or digit)
        // Push operand as a string into stack
        if ((c >= 'A' && c <= 'Z') || 
            (c >= 'a' && c <= 'z') || 
            (c >= '0' && c <= '9')) {

            st.push(string(1, c));
        } 
        // Case 2: Operator
        else {
            // Invalid case: not enough operands
            if (st.size() < 2) {
                cout << "Invalid postfix expression\n";
                return "";
            }

            // Pop operands (note order!)
            string t1 = st.top(); 
            st.pop();           // right operand
            string t2 = st.top(); 
            st.pop();           // left operand

            // Form infix expression with parentheses
            string res = "(" + t2 + c + t1 + ")";

            // Push back to stack
            st.push(res);
        }
    }

    // After processing, stack must contain exactly one expression
    if (st.size() != 1) {
        cout << "Invalid postfix expression\n";
        return "";
    }

    return st.top();
}

// Driver code
int main() {
    string postfix = "AB+C*"; // example: (A+B)*C
    string infix = postfix_to_infix(postfix);

    cout << "Postfix: " << postfix << endl;
    cout << "Infix: " << infix << endl;

    return 0;
}

/*
------------------------------------------------------------
TIME COMPLEXITY:
------------------------------------------------------------
O(N)
- Each character is pushed and popped once

------------------------------------------------------------
SPACE COMPLEXITY:
------------------------------------------------------------
O(N)
- Stack can store up to N operands/expressions

------------------------------------------------------------
KEY TAKEAWAYS:
------------------------------------------------------------
- Stack is ideal for postfix expression problems
- Order of popping operands is very important
- Parentheses are necessary to preserve correctness
*/
