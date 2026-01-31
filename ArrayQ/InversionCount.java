import java.util.*;

public class InversionCount {

    // Brute force inversion count
    static int countInversionBrute(int[] arr) {
        int n = arr.length;
        int cnt = 0;

        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                if (arr[i] > arr[j]) cnt++;
            }
        }
        return cnt;
    }

    // Time Complexity: O(n log n)

// Space Complexity: O(n) for the temporary array during merge.
    // Merge function with inversion count
    static int merge(int[] arr, int low, int mid, int high) {
        ArrayList<Integer> temp = new ArrayList<>();
        int left = low;
        int right = mid + 1;
        int cnt = 0;

        while (left <= mid && right <= high) {
            if (arr[left] <= arr[right]) {
                temp.add(arr[left]);
                left++;
            } else {
                temp.add(arr[right]);
                cnt += (mid - left + 1); // remaining elements in left subarray
                right++;
            }
        }

        while (left <= mid) {
            temp.add(arr[left]);
            left++;
        }

        while (right <= high) {
            temp.add(arr[right]);
            right++;
        }

        for (int i = low; i <= high; i++) {
            arr[i] = temp.get(i - low);
        }

        return cnt;
    }

    // Recursive merge sort with inversion count
    static int mergeSort(int[] arr, int low, int high) {
        if (low >= high) return 0;

        int mid = (low + high) / 2;
        int cnt = 0;

        cnt += mergeSort(arr, low, mid);
        cnt += mergeSort(arr, mid + 1, high);
        cnt += merge(arr, low, mid, high);

        return cnt;
    }

    // Utility function
    static int countInversions(int[] arr) {
        return mergeSort(arr, 0, arr.length - 1);
    }

    // Main function
    public static void main(String[] args) {
        int[] arr = {5, 3, 2, 4, 1};

        System.out.println("Brute-force Count: " + countInversionBrute(arr.clone()));
        System.out.println("Inversion Count: " + countInversions(arr));
    }
}
