package StackQ;

import java.util.Stack;

/*
PROBLEM STATEMENT:
Given an infix expression, convert it into prefix expression.
Example:
Infix  : (A-B/C)*(A/K-L)
Prefix : *-A/BC-/AKL
*/
class infix_to_prefix{

    // Function to return precedence of operators
    static int priority(char c) {
        if (c == '^') return 3;
        else if (c == '*' || c == '/') return 2;
        else if (c == '+' || c == '-') return 1;
        else return -1;
    }

    // Function to convert infix to postfix
    static String infixToPostfix(String s) {
        Stack<Character> st = new Stack<>();
        StringBuilder ans = new StringBuilder();

        for (int i = 0; i < s.length(); i++) {
            char c = s.charAt(i);

            // Operand → add to answer
            if (Character.isLetterOrDigit(c)) {
                ans.append(c);
            }

            // '(' → push to stack
            else if (c == '(') {
                st.push(c);
            }

            // ')' → pop until '('
            else if (c == ')') {
                while (!st.isEmpty() && st.peek() != '(') {
                    ans.append(st.pop());
                }
                if (!st.isEmpty()) st.pop(); // remove '('
            }

            // Operator
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

    // Function to convert infix to prefix
    static String infixToPrefix(String s) {

        // Step 1: Reverse the infix expression
        StringBuilder sb = new StringBuilder(s);
        sb.reverse();

        // Step 2: Swap '(' and ')'
        for (int i = 0; i < sb.length(); i++) {
            if (sb.charAt(i) == '(')
                sb.setCharAt(i, ')');
            else if (sb.charAt(i) == ')')
                sb.setCharAt(i, '(');
        }

        // Step 3: Convert modified expression to postfix
        String postfix = infixToPostfix(sb.toString());

        // Step 4: Reverse postfix to get prefix
        return new StringBuilder(postfix).reverse().toString();
    }
}
/*
TIME COMPLEXITY:
- O(N), where N is the length of the expression
  (each character is pushed/popped at most once)

SPACE COMPLEXITY:
- O(N) for stack usage
*/