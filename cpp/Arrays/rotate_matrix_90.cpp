#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

// Optimized in-place matrix rotation (90° clockwise)
void rotateMatrix_optimize(vector<vector<int>>& matrix) {
    int n = matrix.size();

    // Transpose the matrix
    for(int i = 0; i < n-1; i++) {          
        for(int j = i+1; j < n; j++) {        // Transpose only upper triangle
            swap(matrix[i][j], matrix[j][i]);
        }
    }

    // Reverse each row
    for(int i = 0; i < n; i++) {
        reverse(matrix[i].begin(), matrix[i].end());
    }
}

// Brute force rotation using extra space
void rotateMatrix_brute(vector<vector<int>>& matrix) {
    int n = matrix.size();
    vector<vector<int>> ans(n, vector<int>(n, 0));  // Initialize with size

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            ans[j][n - i - 1] = matrix[i][j];
        }
    }
    matrix = ans;  // Copy result back
}

// Utility to print the matrix
void printMatrix(const vector<vector<int>>& matrix) {
    for(const auto& row : matrix) {
        for(int val : row) cout << val << " ";
        cout << "\n";
    }
}

int main() {
    vector<vector<int>> matrix = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };

    cout << "Original Matrix:\n";
    printMatrix(matrix);

    // Choose one:
    rotateMatrix_optimize(matrix);
    // rotateMatrix_brute(matrix);

    cout << "\nRotated Matrix (90° clockwise):\n";
    printMatrix(matrix);

    return 0;
}
