import java.util.*;

public class RotateMatrix {

    // 🟢 Optimized In-place Rotation (Transpose + Reverse)
    static void rotateMatrixOptimized(int[][] matrix) {
        int n = matrix.length;

        // Step 1: Transpose
        for (int i = 0; i < n - 1; i++) {
            for (int j = i + 1; j < n; j++) {
                int temp = matrix[i][j];
                matrix[i][j] = matrix[j][i];
                matrix[j][i] = temp;
            }
        }

        // Step 2: Reverse each row
        for (int i = 0; i < n; i++) {
            reverseRow(matrix[i]);
        }
    }

    // Helper to reverse an array
    static void reverseRow(int[] row) {
        int l = 0, r = row.length - 1;
        while (l < r) {
            int temp = row[l];
            row[l] = row[r];
            row[r] = temp;
            l++;
            r--;
        }
    }

    // 🔴 Brute Force Rotation (Using extra space)
    static void rotateMatrixBrute(int[][] matrix) {
        int n = matrix.length;
        int[][] ans = new int[n][n];

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                ans[j][n - i - 1] = matrix[i][j];
            }
        }

        // Copy back
        for (int i = 0; i < n; i++) {
            matrix[i] = ans[i].clone();
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
            {1, 2, 3},
            {4, 5, 6},
            {7, 8, 9}
        };

        System.out.println("Original Matrix:");
        printMatrix(matrix);

        // Choose one:
        rotateMatrixOptimized(matrix);
        // rotateMatrixBrute(matrix);

        System.out.println("\nRotated Matrix (90° Clockwise):");
        printMatrix(matrix);
    }
}
