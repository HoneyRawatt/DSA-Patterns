package Recursion;

import java.util.*;

public class SudokuSolver{

    /*
    =====================================================
    INTUITION:
    -----------------------------------------------------
    - Sudoku is a classic backtracking problem.
    - We try to fill empty cells ('.') one by one.
    - For each empty cell, try digits '1' to '9'.
    - Place a digit only if it is VALID:
        1) Not in the same row
        2) Not in the same column
        3) Not in the same 3x3 sub-grid
    - If placing a digit leads to a solution → return true.
    - Otherwise, BACKTRACK (remove the digit and try next).
    =====================================================
    */

    /*
    =====================================================
    TIME & SPACE COMPLEXITY:
    -----------------------------------------------------
    Time Complexity:
        O(9^(N))
        - N = number of empty cells
        - Each cell has at most 9 choices

    Space Complexity:
        O(1) extra space (ignoring recursion stack)
        - Board is modified in-place
        - Recursion depth ≤ 81
    =====================================================
    */

    // Check if placing character c at board[row][col] is valid
    static boolean isValid(char[][] board, int row, int col, char c) {

        for (int i = 0; i < 9; i++) {

            // Check row
            if (board[row][i] == c) return false;

            // Check column
            if (board[i][col] == c) return false;

            // Check 3x3 sub-grid
            int subRow = 3 * (row / 3) + i / 3;
            int subCol = 3 * (col / 3) + i % 3;
            if (board[subRow][subCol] == c) return false;
        }
        return true;
    }

    // Backtracking solver
    static boolean solveSudoku(char[][] board) {

        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {

                // Found an empty cell
                if (board[i][j] == '.') {

                    // Try digits 1 to 9
                    for (char c = '1'; c <= '9'; c++) {

                        if (isValid(board, i, j, c)) {
                            board[i][j] = c;

                            // Recur for next empty cell
                            if (solveSudoku(board)) return true;

                            // Backtrack
                            board[i][j] = '.';
                        }
                    }
                    return false; // no valid number found
                }
            }
        }
        return true; // all cells filled
    }

    public static void main(String[] args) {

        char[][] board = {
            {'5','3','.','.','7','.','.','.','.'},
            {'6','.','.','1','9','5','.','.','.'},
            {'.','9','8','.','.','.','.','6','.'},
            {'8','.','.','.','6','.','.','.','3'},
            {'4','.','.','8','.','3','.','.','1'},
            {'7','.','.','.','2','.','.','.','6'},
            {'.','6','.','.','.','.','2','8','.'},
            {'.','.','.','4','1','9','.','.','5'},
            {'.','.','.','.','8','.','.','7','9'}
        };

        if (solveSudoku(board)) {
            System.out.println("Solved Sudoku:");
            for (char[] row : board) {
                for (char c : row) {
                    System.out.print(c + " ");
                }
                System.out.println();
            }
        } else {
            System.out.println("No solution exists.");
        }
    }
}
