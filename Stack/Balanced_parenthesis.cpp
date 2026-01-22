#include <iostream>
#include <stack>
using namespace std;

/*
====================================================
PROBLEM STATEMENT:
----------------------------------------------------
Given a string consisting of parentheses characters:
'(', ')', '{', '}', '[', ']',
determine whether the input string is balanced.

A string is said to be balanced if:
1. Every opening bracket has a corresponding closing bracket.
2. Brackets are closed in the correct order.
3. The type of opening and closing brackets must match.

Examples:
"{[()]}"  -> Balanced
"{[(])}"  -> Not Balanced
"((()))"  -> Balanced
"([)]"    -> Not Balanced
====================================================
*/

/*
====================================================
INTUITION / APPROACH:
----------------------------------------------------
We use a STACK because it follows LIFO (Last In, First Out),
which perfectly matches the bracket closing behavior.

1. Traverse the string character by character.
2. If the character is an opening bracket ('(', '{', '['):
   - Push it onto the stack.
3. If the character is a closing bracket (')', '}', ']'):
   - If stack is empty → no matching opening bracket → return false.
   - Pop the top element from the stack.
   - Check if the popped opening bracket matches the current closing bracket.
     If not → return false.
4. After processing the entire string:
   - If stack is empty → all brackets matched → balanced.
   - If stack is not empty → extra opening brackets → not balanced.
====================================================
*/

bool balanced_parenthesis(string s) {
    stack<char> st;

    // Traverse each character in the string
    for (int i = 0; i < s.length(); i++) {

        // If opening bracket, push onto stack
        if (s[i] == '(' || s[i] == '{' || s[i] == '[') {
            st.push(s[i]);
        } 
        // If closing bracket
        else {
            // If stack is empty, no opening bracket to match
            if (st.empty()) return false;

            // Get the last opening bracket
            char ch = st.top();
            st.pop();

            // Check for mismatched brackets
            if ((s[i] == ')' && ch != '(') ||
                (s[i] == '}' && ch != '{') ||
                (s[i] == ']' && ch != '[')) {
                return false;
            }
        }
    }

    // If stack is empty, all brackets are matched
    return st.empty();
}

/*
====================================================
TIME & SPACE COMPLEXITY:
----------------------------------------------------
Let n = length of the string

Time Complexity: O(n)
- Each character is processed once.
- Each push and pop operation is O(1).

Space Complexity: O(n)
- In the worst case (all opening brackets),
  the stack stores n characters.
====================================================
*/

int main() {
    string s1 = "{[()]}";
    string s2 = "{[(])}";
    string s3 = "((()))";
    string s4 = "([)]";

    cout << s1 << " -> " << (balanced_parenthesis(s1) ? "Balanced" : "Not Balanced") << endl;
    cout << s2 << " -> " << (balanced_parenthesis(s2) ? "Balanced" : "Not Balanced") << endl;
    cout << s3 << " -> " << (balanced_parenthesis(s3) ? "Balanced" : "Not Balanced") << endl;
    cout << s4 << " -> " << (balanced_parenthesis(s4) ? "Balanced" : "Not Balanced") << endl;

    return 0;
}
