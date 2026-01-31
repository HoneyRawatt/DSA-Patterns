import java.util.*;

public class ZeroMatrix {

    // 🟢 Optimized Approach (O(1) extra space)
    static void zeroMatrixOptimized(int[][] matrix) {
        int n = matrix.length;
        int m = matrix[0].length;

        int col0 = 1;

        // Step 1: Mark first row & column
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (matrix[i][j] == 0) {
                    matrix[i][0] = 0;
                    if (j != 0) matrix[0][j] = 0;
                    else col0 = 0;
                }
            }
        }

        // Step 2: Use marks to set zeros
        for (int i = 1; i < n; i++) {
            for (int j = 1; j < m; j++) {
                if (matrix[i][j] != 0 &&
                    (matrix[i][0] == 0 || matrix[0][j] == 0)) {
                    matrix[i][j] = 0;
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

    // 🔴 Brute Force Approach (Using -1 marker)
    static void markRow(int[][] matrix, int i) {
        for (int j = 0; j < matrix[0].length; j++) {
            if (matrix[i][j] != 0) matrix[i][j] = -1;
        }
    }

    static void markCol(int[][] matrix, int j) {
        for (int i = 0; i < matrix.length; i++) {
            if (matrix[i][j] != 0) matrix[i][j] = -1;
        }
    }

    static void zeroMatrixBrute(int[][] matrix) {
        int n = matrix.length;
        int m = matrix[0].length;

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (matrix[i][j] == 0) {
                    markRow(matrix, i);
                    markCol(matrix, j);
                }
            }
        }

        // Convert -1 to 0
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (matrix[i][j] == -1) matrix[i][j] = 0;
            }
        }
    }

    // 🟠 Better Approach (O(n + m) space)
    static void zeroMatrixBetter(int[][] matrix) {
        int n = matrix.length;
        int m = matrix[0].length;

        int[] row = new int[n];
        int[] col = new int[m];

        // Mark rows & columns
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (matrix[i][j] == 0) {
                    row[i] = 1;
                    col[j] = 1;
                }
            }
        }

        // Set zeros
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (row[i] == 1 || col[j] == 1) {
                    matrix[i][j] = 0;
                }
            }
        }
    }

    // Utility to print matrix
    static void printMatrix(int[][] matrix) {
        for (int[] row : matrix) {
            for (int val : row) {
                System.out.print(val + " ");
            }
            System.out.println();
        }
    }

    // Main
    public static void main(String[] args) {
        int[][] matrix = {
            {1, 1, 1, 1},
            {1, 0, 1, 1},
            {1, 1, 0, 1},
            {0, 1, 1, 1}
        };

        // Test Better approach
        zeroMatrixBetter(matrix);

        System.out.println("Modified Matrix:");
        printMatrix(matrix);
    }
}
