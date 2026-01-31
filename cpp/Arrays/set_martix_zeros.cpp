#include<iostream>
#include<vector>
using namespace std;

// Optimized Approach (Using O(1) space)
void zeroMatrix_optimized(vector<vector<int>>& matrix, int n, int m) {
    int col0 = 1;

    // Step 1: Use first row and column to mark
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {  
            if (matrix[i][j] == 0) {
                //mark the ith row
                matrix[i][0] = 0;
                //mark the jth col
                if(j!=0) matrix[0][j] = 0;
                else col0=0;
            }
        }  
    }

    // Step 2: Set cells to 0 using marks
    for (int i = 1; i < n; i++) {
        for (int j = 1; j < m; j++) {
            if(matrix[i][j]!=0){
            if (matrix[i][0] == 0 || matrix[0][j] == 0) { 
                matrix[i][j] = 0;
            }
        }
        }
    }

    // Step 3: First row
    if (matrix[0][0] == 0) {
        for (int j = 0; j < m; j++) matrix[0][j] = 0;
    }

    // Step 4: First column
    if (col0 == 0) {
        for (int i = 0; i < n; i++) matrix[i][0] = 0;
    }
}

// Brute Force Approach (Using -1 as marker)
void markrow(vector<vector<int>>& matrix, int i, int m) {
    for (int j = 0; j < m; j++) {
        if (matrix[i][j] != 0) matrix[i][j] = -1;
    }
}
void markcol(vector<vector<int>>& matrix, int j, int n) {
    for (int i = 0; i < n; i++) {
        if (matrix[i][j] != 0) matrix[i][j] = -1;
    }
}
void zeroMatrix_brute(vector<vector<int>>& matrix, int n, int m) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (matrix[i][j] == 0) {
                markrow(matrix, i, m);
                markcol(matrix, j, n);
            }
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (matrix[i][j] == -1) {
                matrix[i][j] = 0;
            }
        }
    }
}

// Better Approach (Using extra space O(n+m))
void zeroMatrix_better(vector<vector<int>>& matrix, int n, int m) {
    vector<int> row(n, 0), col(m, 0);

    // Mark rows and columns
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (matrix[i][j] == 0) {
                row[i] = 1;
                col[j] = 1;
            }
        }
    }

    // Update matrix
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (row[i]||col[j]) {
                matrix[i][j] = 0;
            }
        }
    }
}

// Utility function to print matrix
void printMatrix(const vector<vector<int>>& matrix) {
    for (auto row : matrix) {
        for (int val : row) cout << val << " ";
        cout << endl;
    }
}

// Main function
int main() {
    vector<vector<int>> matrix = {
        {1, 1, 1, 1},
        {1, 0, 1, 1},
        {1, 1, 0, 1},
        {0, 1, 1, 1}
    };
    int n = matrix.size();
    int m = matrix[0].size();

    // Test optimized version
    zeroMatrix_better(matrix, n, m);

    cout << "Modified Matrix:\n";
    printMatrix(matrix);

    return 0;
}
