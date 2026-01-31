package StackQ;

import java.util.Stack;

public class balanced_Parenthesis {

    /*
    ====================================================
    PROBLEM STATEMENT:
    ----------------------------------------------------
    Given a string containing the characters '(', ')', '{', '}', '[' and ']',
    determine whether the parentheses in the expression are balanced.

    A string is balanced if:
    1. Every opening bracket has a corresponding closing bracket of the same type.
    2. Brackets are closed in the correct order (matching nesting).
    ====================================================
    */

    public static boolean balancedParenthesis(String s) {
        Stack<Character> st = new Stack<>();

        // Traverse each character in the string
        for (int i = 0; i < s.length(); i++) {
            char ch = s.charAt(i);

            // If opening bracket, push it
            if (ch == '(' || ch == '{' || ch == '[') {
                st.push(ch);
            } else {
                // If there's a closing bracket without a matching opening
                if (st.isEmpty()) {
                    return false;
                }

                char top = st.pop();

                // If types don't match, it's unbalanced
                if ((ch == ')' && top != '(') ||
                    (ch == '}' && top != '{') ||
                    (ch == ']' && top != '[')) {
                    return false;
                }
            }
        }

        // If stack is empty at the end, all brackets matched
        return st.isEmpty();
    }

    /*
    ====================================================
    TIME & SPACE COMPLEXITY:
    ----------------------------------------------------
    Let n = length of the input string

    Time Complexity: O(n)
    - We process each character once.
    - Stack operations (push/pop) are O(1).

    Space Complexity: O(n)
    - In the worst case (all opening brackets), the stack can hold up to n characters.
    ====================================================
    */

    public static void main(String[] args) {
        String s1 = "{[()]}";
        String s2 = "{[(])}";
        String s3 = "((()))";
        String s4 = "([)]";

        System.out.println(s1 + " -> " + (balancedParenthesis(s1) ? "Balanced" : "Not Balanced"));
        System.out.println(s2 + " -> " + (balancedParenthesis(s2) ? "Balanced" : "Not Balanced"));
        System.out.println(s3 + " -> " + (balancedParenthesis(s3) ? "Balanced" : "Not Balanced"));
        System.out.println(s4 + " -> " + (balancedParenthesis(s4) ? "Balanced" : "Not Balanced"));
    }
}
