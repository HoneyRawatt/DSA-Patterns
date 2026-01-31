package StackQ;

import java.util.Stack;

public class infix_to_postfix{

    /*
    ====================================================
    PROBLEM STATEMENT:
    ----------------------------------------------------
    Given an infix expression (example: A*(B+C)/D),
    convert it into its equivalent postfix expression.

    Infix  : Operators are written between operands (A + B)
    Postfix: Operators are written after operands (AB+)

    Rules:
    - Operand order must be preserved
    - Operator precedence must be maintained
    - Parentheses must be handled correctly
    ====================================================
    */

    /*
    ====================================================
    INTUITION / APPROACH:
    ----------------------------------------------------
    We use a STACK to store operators temporarily.

    Algorithm:
    1. Traverse the infix expression from left to right.
    2. If the character is an operand, add it to the result.
    3. If '(' is found, push it onto the stack.
    4. If ')' is found, pop from stack until '(' is encountered.
    5. If an operator is found:
       - Pop operators from stack while they have
         higher or equal precedence.
       - Push the current operator.
    6. After traversal, pop all remaining operators.
    ====================================================
    */

    // Function to return precedence of operators
    static int priority(char c) {
        if (c == '^') return 3;
        else if (c == '*' || c == '/') return 2;
        else if (c == '+' || c == '-') return 1;
        else return -1;
    }

    // Function to convert infix expression to postfix
    static String infixToPostfix(String s) {
        Stack<Character> st = new Stack<>();
        StringBuilder ans = new StringBuilder();

        // Traverse each character
        for (int i = 0; i < s.length(); i++) {
            char c = s.charAt(i);

            // If operand, add to result
            if (Character.isLetterOrDigit(c)) {
                ans.append(c);
            }

            // If '(', push to stack
            else if (c == '(') {
                st.push(c);
            }

            // If ')', pop until '('
            else if (c == ')') {
                while (!st.isEmpty() && st.peek() != '(') {
                    ans.append(st.pop());
                }
                if (!st.isEmpty()) st.pop(); // remove '('
            }

            // If operator
            else {
                while (!st.isEmpty() && priority(c) <= priority(st.peek())) {
                    ans.append(st.pop());
                }
                st.push(c);
            }
        }

        // Pop remaining operators
        while (!st.isEmpty()) {
            ans.append(st.pop());
        }

        return ans.toString();
    }

    /*
    ====================================================
    TIME & SPACE COMPLEXITY:
    ----------------------------------------------------
    Let n = length of the expression

    Time Complexity: O(n)
    - Each character is processed once

    Space Complexity: O(n)
    - Stack can store up to n operators
    ====================================================
    */

    public static void main(String[] args) {
        String expr = "A*(B+C)/D";

        System.out.println("Infix: " + expr);
        System.out.println("Postfix: " + infixToPostfix(expr));
    }
}
