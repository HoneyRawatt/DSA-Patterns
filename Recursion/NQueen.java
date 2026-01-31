package Recursion;

import java.util.*;

public class NQueen {

    /*
    ====================================================
    TIME & SPACE COMPLEXITY (Overall)
    ----------------------------------------------------
    Time Complexity:
        O(N! * N)
        - N! ways to place queens column-wise
        - Each placement may take O(N) safety checks

    Space Complexity:
        Board            -> O(N^2)
        Recursion Stack  -> O(N)
        Answers Storage  -> O(N! * N^2)
    ====================================================
    */

    /*
    ====================================================
    INTUITION (Brute Force):
    ----------------------------------------------------
    - Place one queen per column.
    - For each cell, check if it is safe:
        1) Upper-left diagonal
        2) Left side (same row)
        3) Lower-left diagonal
    - If safe, place queen and move to next column.
    ====================================================
    */

    static boolean isSafe(int row, int col, char[][] board, int n) {

        int dupRow = row;
        int dupCol = col;

        // Upper-left diagonal
        while (row >= 0 && col >= 0) {
            if (board[row][col] == 'Q') return false;
            row--;
            col--;
        }

        // Left side
        row = dupRow;
        col = dupCol;
        while (col >= 0) {
            if (board[row][col] == 'Q') return false;
            col--;
        }

        // Lower-left diagonal
        row = dupRow;
        col = dupCol;
        while (row < n && col >= 0) {
            if (board[row][col] == 'Q') return false;
            row++;
            col--;
        }

        return true;
    }

    static void solve(int col, char[][] board,
                      List<List<String>> ans, int n) {

        // Base case: all queens placed
        if (col == n) {
            ans.add(construct(board));
            return;
        }

        for (int row = 0; row < n; row++) {
            if (isSafe(row, col, board, n)) {
                board[row][col] = 'Q';
                solve(col + 1, board, ans, n);
                board[row][col] = '.'; // backtrack
            }
        }
    }

    /*
    ====================================================
    OPTIMIZED SOLUTION (Using Hashing)
    ----------------------------------------------------
    - Use 3 arrays to track attacks:
        leftRow[row]
        lowerDiagonal[row + col]
        upperDiagonal[n - 1 + col - row]
    - Safety check becomes O(1)
    ====================================================
    */

    static void solveOptimized(int col, char[][] board,
                               List<List<String>> ans,
                               int[] leftRow,
                               int[] upperDiagonal,
                               int[] lowerDiagonal,
                               int n) {

        if (col == n) {
            ans.add(construct(board));
            return;
        }

        for (int row = 0; row < n; row++) {
            if (leftRow[row] == 0 &&
                lowerDiagonal[row + col] == 0 &&
                upperDiagonal[n - 1 + col - row] == 0) {

                board[row][col] = 'Q';
                leftRow[row] = 1;
                lowerDiagonal[row + col] = 1;
                upperDiagonal[n - 1 + col - row] = 1;

                solveOptimized(col + 1, board, ans,
                               leftRow, upperDiagonal, lowerDiagonal, n);

                // BACKTRACK
                board[row][col] = '.';
                leftRow[row] = 0;
                lowerDiagonal[row + col] = 0;
                upperDiagonal[n - 1 + col - row] = 0;
            }
        }
    }

    // Convert board to list of strings
    static List<String> construct(char[][] board) {
        List<String> res = new ArrayList<>();
        for (char[] row : board) {
            res.add(new String(row));
        }
        return res;
    }

    public static void main(String[] args) {

        int n = 4;
        char[][] board = new char[n][n];

        for (int i = 0; i < n; i++) {
            Arrays.fill(board[i], '.');
        }

        List<List<String>> ans = new ArrayList<>();

        // -------- Brute Force Solution --------
        solve(0, board, ans, n);

        System.out.println("Brute Force Solutions:");
        for (List<String> sol : ans) {
            for (String row : sol)
                System.out.println(row);
            System.out.println();
        }

        // Clear previous results
        ans.clear();

        // -------- Optimized Solution --------
        int[] leftRow = new int[n];
        int[] upperDiagonal = new int[2 * n - 1];
        int[] lowerDiagonal = new int[2 * n - 1];

        solveOptimized(0, board, ans,
                       leftRow, upperDiagonal, lowerDiagonal, n);

        System.out.println("Optimized Solutions:");
        for (List<String> sol : ans) {
            for (String row : sol)
                System.out.println(row);
            System.out.println();
        }
    }
}
