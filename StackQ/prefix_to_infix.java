package StackQ;

import java.util.Stack;

class prefix_to_infix{

    /*
    ------------------------------------------------------------
    PROBLEM STATEMENT:
    ------------------------------------------------------------
    Given a prefix expression, convert it into its equivalent
    infix expression.

    Example:
    Prefix : *+AB-C
    Infix  : (A+B)*(C-?)
    */

    public static String prefixToInfix(String s) {
        Stack<String> st = new Stack<>();
        int n = s.length();

        // Traverse the prefix expression from RIGHT to LEFT
        for (int i = n - 1; i >= 0; i--) {
            char c = s.charAt(i);

            // If operand, push to stack
            if (Character.isLetterOrDigit(c)) {
                st.push(String.valueOf(c));
            }
            // If operator
            else {
                // Invalid prefix expression
                if (st.size() < 2) {
                    return "";
                }

                // Pop operands
                String op1 = st.pop(); // first operand
                String op2 = st.pop(); // second operand

                // Form infix expression with parentheses
                String expr = "(" + op1 + c + op2 + ")";

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
        String prefix = "*+AB-C";
        System.out.println(prefixToInfix(prefix)); // (A+B)*(C-?)
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
