#include <bits/stdc++.h>
using namespace std;

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

bool isValid(vector<vector<char>> &board, int row, int col, char c) {
    for (int i = 0; i < 9; i++) {
        if (board[i][col] == c) return false; // check column
        if (board[row][i] == c) return false; // check row
        if (board[3 * (row / 3) + i / 3][3 * (col / 3) + i % 3] == c)
            return false; // check 3x3 block
    }
    return true;
}

bool solveSudoko(vector<vector<char>> &board) {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (board[i][j] == '.') {
                for (char c = '1'; c <= '9'; c++) {
                    if (isValid(board, i, j, c)) {
                        board[i][j] = c;

                        if (solveSudoko(board)) return true;
                        board[i][j] = '.';
                    }
                }
                return false;
            }
        }
    }
    return true;
}

int main() {
    vector<vector<char>> board = {
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

    if (solveSudoko(board)) {
        cout << "Solved Sudoku:\n";
        for (auto& row : board) {
            for (char c : row)
                cout << c << " ";
            cout << endl;
        }
    } else {
        cout << "No solution exists.\n";
    }

    return 0;
}