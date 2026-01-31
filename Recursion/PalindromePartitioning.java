package Recursion;
import java.util.*;

public class PalindromePartitioning {


    /*
    ============================
    INTUITION
    ============================
    - We want to partition the given string such that
      every substring in the partition is a palindrome.
    - We use BACKTRACKING:
        • Start from index 0
        • Try every possible substring starting at current index
        • If the substring is a palindrome, pick it
        • Recurse for the remaining string
        • Backtrack and try other possibilities
    - When we reach the end of the string, one valid partition is formed.
    */

    // Utility function to check if substring s[start..end] is palindrome
    static boolean isPalindrome(String s, int start, int end) {
        while (start <= end) {
            if (s.charAt(start) != s.charAt(end))
                return false;
            start++;
            end--;
        }
        return true;
    }

    // Recursive backtracking function
    static void generatePartitions(
            int index,
            String s,
            List<String> path,
            List<List<String>> result
    ) {

        // Base case: reached end of string
        if (index == s.length()) {
            result.add(new ArrayList<>(path));
            return;
        }

        // Try all substrings starting from index
        for (int i = index; i < s.length(); i++) {

            // If s[index..i] is palindrome
            if (isPalindrome(s, index, i)) {

                // Pick the substring
                path.add(s.substring(index, i + 1));

                // Recurse for remaining string
                generatePartitions(i + 1, s, path, result);

                // Backtrack
                path.remove(path.size() - 1);
            }
        }
    }

    // Driver code for testing
    public static void main(String[] args) {

        String s = "aabb";

        List<List<String>> result = new ArrayList<>();
        List<String> path = new ArrayList<>();

        generatePartitions(0, s, path, result);

        // Print all palindrome partitions
        System.out.println("Palindrome Partitions of \"" + s + "\":");
        for (List<String> partition : result) {
            System.out.println(partition);
        }
    }
}

/*
============================
TIME & SPACE COMPLEXITY
============================

Time Complexity:
- There are 2^(N-1) possible ways to partition a string of length N.
- For each partition, palindrome checking takes O(N).
- Overall Time Complexity: O(2^N * N)

Space Complexity:
- Recursion stack depth: O(N)
- Path list: O(N)
- Result storage: O(2^N * N)
- Overall Auxiliary Space (excluding output): O(N)
*/
 
