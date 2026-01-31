package StackQ;

import java.util.Stack;

class postfix_to_prefix{

    /*
    ------------------------------------------------------------
    PROBLEM STATEMENT:
    ------------------------------------------------------------
    Given a postfix expression, convert it into its equivalent
    prefix expression.

    Example:
    Postfix : AB+C*
    Prefix  : *+ABC
    */

    public static String postfixToPrefix(String s) {
        Stack<String> st = new Stack<>();

        // Traverse postfix expression from LEFT to RIGHT
        for (int i = 0; i < s.length(); i++) {
            char c = s.charAt(i);

            // Case 1: Operand (letter or digit)
            if (Character.isLetterOrDigit(c)) {
                st.push(String.valueOf(c));
            }
            // Case 2: Operator
            else {
                // Invalid postfix expression
                if (st.size() < 2) {
                    return "";
                }

                // Pop operands
                String op1 = st.pop(); // right operand
                String op2 = st.pop(); // left operand

                // Form prefix expression
                // Prefix = operator + left + right
                String expr = c + op2 + op1;

                // Push result back to stack
                st.push(expr);
            }
        }

        // Final validation
        if (st.size() != 1) {
            return "";
        }

        return st.peek();
    }

    // Demo
    public static void main(String[] args) {
        String postfix = "AB+C*";
        System.out.println(postfixToPrefix(postfix)); // *+ABC
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
