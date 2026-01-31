package StackQ;

import java.util.Stack;

class prefix_to_postfix{

    /*
    ------------------------------------------------------------
    PROBLEM STATEMENT:
    ------------------------------------------------------------
    Given a prefix expression, convert it into its equivalent
    postfix expression.

    Example:
    Prefix  : *+AB-CD
    Postfix : AB+CD-*
    */

    public static String prefixToPostfix(String s) {
        Stack<String> st = new Stack<>();
        int n = s.length();

        // Traverse prefix expression from RIGHT to LEFT
        for (int i = n - 1; i >= 0; i--) {
            char c = s.charAt(i);

            // Case 1: Operand (letter or digit)
            if (Character.isLetterOrDigit(c)) {
                st.push(String.valueOf(c));
            }
            // Case 2: Operator
            else {
                // Invalid prefix expression
                if (st.size() < 2) {
                    return "";
                }

                // Pop operands
                String op1 = st.pop(); // first operand
                String op2 = st.pop(); // second operand

                // Form postfix expression
                String expr = op1 + op2 + c;

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
        String prefix = "*+AB-CD";
        System.out.println(prefixToPostfix(prefix)); // AB+CD-*
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
