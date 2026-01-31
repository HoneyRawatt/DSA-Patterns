package ArrayQ;

import java.util.Arrays;

public class RightRotate {

    // Rotate array by 1 position (RIGHT)
    public static int[] rightrotate_arr(int[] arr) {
        int n = arr.length;
        int temp = arr[n - 1];

        for (int i = n - 2; i >= 0; i--) {
            arr[i + 1] = arr[i];
        }
        arr[0] = temp;
        return arr;
    }

    // Rotate array by k positions (using extra space)
    public static int[] rightrotate_arr_k(int[] arr, int k) {
        int n = arr.length;
        k = k % n;

        int[] temp = new int[k];

        // Store last k elements
        for (int i = 0; i < k; i++) {
            temp[i] = arr[n - k + i];
        }

        // Shift remaining elements to the right
        for (int i = n - k - 1; i >= 0; i--) {
            arr[i + k] = arr[i];
        }

        // Put temp at the beginning
        for (int i = 0; i < k; i++) {
            arr[i] = temp[i];
        }

        return arr;
    }

    // Optimal right rotation using reversal algorithm
    public static int[] rightrotate_arr_k_optimal(int[] arr, int k) {
        int n = arr.length;
        k = k % n;

        reverse(arr, 0, n - 1);
        reverse(arr, 0, k - 1);
        reverse(arr, k, n - 1);

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

        System.out.println(Arrays.toString(rightrotate_arr(arr.clone())));
        System.out.println(Arrays.toString(rightrotate_arr_k(arr.clone(), 2)));
        System.out.println(Arrays.toString(rightrotate_arr_k_optimal(arr.clone(), 2)));
    }
}

// | Method             | Time | Space  |
// | ------------------ | ---- | ------ |
// | Rotate by 1        | O(n) | O(1)   |
// | Rotate by k (temp) | O(n) | O(k)   |
// | Optimal (reverse)  | O(n) | O(1) ✅ |
