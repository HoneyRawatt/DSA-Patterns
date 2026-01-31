package ArrayQ;

import java.util.Arrays;

public class LeftRotate {

    // Rotate array by 1 position
    public static int[] leftrotate_arr(int[] arr) {
        int n = arr.length;
        int temp = arr[0];

        for (int i = 1; i < n; i++) {
            arr[i - 1] = arr[i];
        }
        arr[n - 1] = temp;
        return arr;
    }

    // Rotate array by k positions (using extra space)
    public static int[] leftrotate_arr_k(int[] arr, int k) {
        int n = arr.length;
        k = k % n;

        int[] temp = new int[k];

        // Store first k elements
        for (int i = 0; i < k; i++) {
            temp[i] = arr[i];
        }

        // Shift remaining elements
        for (int i = k; i < n; i++) {
            arr[i - k] = arr[i];
        }

        // Put temp back
        for (int i = n - k; i < n; i++) {
            arr[i] = temp[i - (n - k)];
        }

        return arr;
    }

    // Optimal rotation using reversal algorithm
    public static int[] leftrotate_arr_k_optimal(int[] arr, int k) {
        int n = arr.length;
        k = k % n;

        reverse(arr, 0, k - 1);
        reverse(arr, k, n - 1);
        reverse(arr, 0, n - 1);

        return arr;
    }

    // Reverse helper function
    private static void reverse(int[] arr, int left, int right) {
        while (left < right) {
            int temp = arr[left];
            arr[left] = arr[right];
            arr[right] = temp;
            left++;
            right--;
        }
    }

    // Driver code
    public static void main(String[] args) {
        int[] arr = {1, 2, 3, 4, 5};

        System.out.println(Arrays.toString(leftrotate_arr(arr.clone())));
        System.out.println(Arrays.toString(leftrotate_arr_k(arr.clone(), 2)));
        System.out.println(Arrays.toString(leftrotate_arr_k_optimal(arr.clone(), 2)));
    }
}

// | Method             | Time | Space  |
// | ------------------ | ---- | ------ |
// | Rotate by 1        | O(n) | O(1)   |
// | Rotate by k (temp) | O(n) | O(k)   |
// | Optimal (reverse)  | O(n) | O(1) ✅ |