package ArrayQ;

import java.util.*;

public class MoveZeros {

    // Method 1: Using extra space
    public static int[] moveZeroAtEnd(int[] arr) {
        int n = arr.length;
        List<Integer> temp = new ArrayList<>();

        // Store non-zero elements
        for (int i = 0; i < n; i++) {
            if (arr[i] != 0) {
                temp.add(arr[i]);
            }
        }

        // Copy back non-zero elements
        int index = 0;
        for (int x : temp) {
            arr[index++] = x;
        }

        // Fill remaining with zeros
        while (index < n) {
            arr[index++] = 0;
        }

        return arr;
    }

    // Method 2: Optimal in-place (Two pointers)
    public static int[] moveZeroAtEnd2(int[] arr) {
        int n = arr.length;
        int j = -1;

        // Find first zero
        for (int i = 0; i < n; i++) {
            if (arr[i] == 0) {
                j = i;
                break;
            }
        }

        // If no zero found
        if (j == -1) return arr;

        // Move non-zero elements forward
        for (int i = j + 1; i < n; i++) {
            if (arr[i] != 0) {
                int temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
                j++;
            }
        }

        return arr;
    }

    // Driver code
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        int n = sc.nextInt();
        int[] arr = new int[n];

        System.out.println("Enter the elements:");
        for (int i = 0; i < n; i++) {
            arr[i] = sc.nextInt();
        }

        arr = moveZeroAtEnd2(arr);

        for (int x : arr) {
            System.out.print(x + " ");
        }

        sc.close();
    }
}
