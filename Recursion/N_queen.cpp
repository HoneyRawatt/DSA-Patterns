#include <bits/stdc++.h>
using namespace std;

// Aspect   	      Complexity   
// Time	              𝑂(𝑁!⋅𝑁)    
// Space (board)  	  𝑂(𝑁2)
// Space (answers)	  𝑂(𝑁!⋅𝑁2)

bool issafe(int row, int col, vector<string>& board, int n) {
    int duprow = row;
    int dupcol = col;

    // Upper-left diagonal
    while (row >= 0 && col >= 0) {
        if (board[row][col] == 'Q') return false;
        row--;
        col--;
    }

    // Left side
    row = duprow;
    col = dupcol;
    while (col >= 0) {
        if (board[row][col] == 'Q') return false;
        col--;
    }

    // Lower-left diagonal
    row = duprow;
    col = dupcol;
    while (row < n && col >= 0) {
        if (board[row][col] == 'Q') return false;
        row++;
        col--;
    }

    return true;
}



void solve(int col, vector<string>& board, vector<vector<string>>& ans, int n) {
    if (col == n) {
        ans.push_back(board);
        return;
    }
    for (int row = 0; row < n; row++) {
        if (issafe(row, col, board, n)) {
            board[row][col] = 'Q';
            solve(col + 1, board, ans, n);
            board[row][col] = '.';
        }
    }
}


// | Metric                             | Complexity                                            |
// | ---------------------------------- | ----------------------------------------------------- |
// | Time                               | `O(N!)`                                               |
// | Space (Without result storage)     | `O(N^2)` (board) + `O(N)` (arrays + stack) = `O(N^2)` |
// | Space (With result storage)        | `O(N! * N^2)` total                                   |

void solve_optimized(int col, vector<string>& board, vector<vector<string>>& ans,vector<int>&leftrow,
    vector<int>&upperdigonal,vector<int>&lowerdiagonal,int n){
        if(col==n){
            ans.push_back(board);
            return;
        }

        for(int row=0;row<n;row++){
            if(leftrow[row]==0 && lowerdiagonal[row+col]==0 && upperdigonal[n-1+col-row]==0){
                board[row][col]='Q';
                leftrow[row]=1;
                lowerdiagonal[row+col]=1;
                upperdigonal[n-1+col-row]=1;
                solve_optimized(col+1,board,ans,leftrow,upperdigonal,lowerdiagonal,n);
                board[row][col]='.';
                leftrow[row]=0;
                lowerdiagonal[row+col]=0;
                upperdigonal[n-1+col-row]=0;
            }
        }
}

int main() {
    int n = 4;
    vector<vector<string>> ans;
    vector<string> board(n, string(n, '.'));
    vector<int>leftrow(n,0),upperdiagonal(2*n-1,0),lowerdiagonal(2*n-1,0);
    solve(0, board, ans, n);
    // Print solutions
    for (auto &sol : ans) {
        for (auto &row : sol)
            cout << row << "\n";
        cout << "\n";
    }
ans.clear(); // <- clear previous solutions

solve_optimized(0, board, ans, leftrow, upperdiagonal, lowerdiagonal, n);
cout << "Optimized Solution:\n";
for (auto &sol : ans) {
    for (auto &row : sol)
        cout << row << "\n";
    cout << "\n";
}
}
