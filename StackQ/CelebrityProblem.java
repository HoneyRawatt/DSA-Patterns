package StackQ;

import java.util.*;

public class CelebrityProblem {

    /*
    =====================================================
    BRUTE FORCE APPROACH — O(n²)
    -----------------------------------------------------
    Idea:
    A celebrity is a person who:
    1) Is known by everyone else  → knowMe[i] == n-1
    2) Knows no one               → iKnow[i] == 0
    =====================================================
    */
    public static int celebrityBrute(int[][] mat) {
        int n = mat.length;

        // knowMe[i] -> number of people who know person i
        // iKnow[i]  -> number of people person i knows
        int[] knowMe = new int[n];
        int[] iKnow = new int[n];

        // Fill knowMe and iKnow arrays
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (mat[i][j] == 1) {
                    knowMe[j]++;  // j is known by i
                    iKnow[i]++;   // i knows j
                }
            }
        }

        // Check celebrity condition
        for (int i = 0; i < n; i++) {
            if (knowMe[i] == n - 1 && iKnow[i] == 0) {
                return i; // celebrity found
            }
        }

        return -1; // no celebrity
    }

    /*
    =====================================================
    OPTIMAL APPROACH — O(n)
    -----------------------------------------------------
    Two-pointer elimination technique
    =====================================================
    */
    public static int celebrity(int[][] mat) {
        int n = mat.length;
        int top = 0, down = n - 1;

        // Step 1: Find potential celebrity
        while (top < down) {
            if (mat[top][down] == 1) {
                top++;     // top knows down → top not celebrity
            } else {
                down--;    // top doesn't know down → down not celebrity
            }
        }

        int candidate = top;

        // Step 2: Verify candidate
        for (int i = 0; i < n; i++) {
            if (i == candidate) continue;

            // Celebrity should not know anyone
            // Everyone should know the celebrity
            if (mat[candidate][i] == 1 || mat[i][candidate] == 0) {
                return -1;
            }
        }

        return candidate;
    }

    // Driver code
    public static void main(String[] args) {
        int[][] mat = {
            {0, 1, 1},
            {0, 0, 1},
            {0, 0, 0}
        };

        System.out.println("Brute Force Celebrity: " + celebrityBrute(mat));
        System.out.println("Optimal Celebrity: " + celebrity(mat));
    }
}

