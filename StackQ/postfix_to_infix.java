package StackQ;

import java.util.Stack;

class postfix_to_infix{

    /*
    ------------------------------------------------------------
    PROBLEM STATEMENT:
    ------------------------------------------------------------
    Given a postfix expression, convert it into an equivalent
    infix expression.

    Example:
    Postfix : AB+C*
    Infix   : (A+B)*C
    */

    /*
    ------------------------------------------------------------
    INTUITION:
    ------------------------------------------------------------
    - Use a stack to store operands as strings
    - When an operator is found:
        pop two operands
        combine them as (operand2 operator operand1)
        push back the result
    - Final stack element is the infix expression
    */

    public static String postfixToInfix(String s) {
        Stack<String> st = new Stack<>();

        // Traverse the postfix expression
        for (int i = 0; i < s.length(); i++) {
            char c = s.charAt(i);

            // If operand, push to stack
            if (Character.isLetterOrDigit(c)) {
                st.push(String.valueOf(c));
            }
            // If operator
            else {
                // Invalid postfix expression
                if (st.size() < 2) {
                    return "";
                }

                // Pop operands (right first, then left)
                String op1 = st.pop();
                String op2 = st.pop();

                // Form infix expression with parentheses
                String expr = "(" + op2 + c + op1 + ")";

                // Push back to stack
                st.push(expr);
            }
        }

        // Stack should contain exactly one element
        if (st.size() != 1) {
            return "";
        }

        return st.peek();
    }

    // Demo
    public static void main(String[] args) {
        String postfix = "AB+C*";
        System.out.println(postfixToInfix(postfix)); // (A+B)*C
    }

    /*
    ------------------------------------------------------------
    TIME COMPLEXITY:
    ------------------------------------------------------------
    O(N)

    ------------------------------------------------------------
    SPACE COMPLEXITY:
    ------------------------------------------------------------
    O(N)
    */
}
