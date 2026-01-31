import java.util.*;

public class PascalsTriangle {

    // Generate a specific row using combinations (nCr)
    static List<Integer> generateRow(int row) {
        long ans = 1;
        List<Integer> ansRow = new ArrayList<>();
        ansRow.add(1); // First element is always 1

        for (int col = 1; col < row; col++) {
            ans = ans * (row - col);
            ans = ans / col;
            ansRow.add((int) ans);
        }
        return ansRow;
    }

    // Optimized Pascal's Triangle: row indexing from 1 to n (inclusive)
    static List<List<Integer>> pascalTriangleOptimized(int n) {
        List<List<Integer>> ans = new ArrayList<>();
        for (int i = 1; i <= n; i++) {
            ans.add(generateRow(i));
        }
        return ans;
    }

    // Find a single element at position (n, r) using nCr
    static long findElementPascalTri(int n, int r) {
        long res = 1;
        for (int i = 1; i <= r; i++) {
            res *= (n - i + 1);
            res /= i;
        }
        return res;
    }

    // Brute-force Pascal's Triangle using nCr
    static List<List<Integer>> pascalTriangleBrute(int n) {
        List<List<Integer>> ans = new ArrayList<>();

        for (int row = 0; row < n; row++) {
            List<Integer> tempList = new ArrayList<>();
            for (int col = 0; col <= row; col++) {
                tempList.add((int) findElementPascalTri(row, col));
            }
            ans.add(tempList);
        }
        return ans;
    }

    // Utility function to print the triangle
    static void printTriangle(List<List<Integer>> triangle) {
        for (List<Integer> row : triangle) {
            for (int val : row) {
                System.out.print(val + " ");
            }
            System.out.println();
        }
    }

    // Main Function
    public static void main(String[] args) {
        int n = 5;

        System.out.println("Pascal Triangle (Optimized):");
        List<List<Integer>> opt = pascalTriangleOptimized(n);
        printTriangle(opt);

        System.out.println("\nPascal Triangle (Brute Force):");
        List<List<Integer>> brute = pascalTriangleBrute(n);
        printTriangle(brute);
    }
}
