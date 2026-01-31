import java.util.*;
public class MergeTwoSortedArrays {
    
    /* ---------------- Brute Force ----------------
     * Time: O(n + m)
     * Space: O(n + m)
     */
    public static void mergeBrute(long[] arr1, long[] arr2, int n, int m) {
        long[] arr3 = new long[n + m];
        int i = 0, j = 0, k = 0;

        while (i < n && j < m) {
            if (arr1[i] < arr2[j]) arr3[k++] = arr1[i++];
            else arr3[k++] = arr2[j++];
        }

        while (i < n) arr3[k++] = arr1[i++];
        while (j < m) arr3[k++] = arr2[j++];

        for (int x = 0; x < n + m; x++) {
            if (x < n) arr1[x] = arr3[x];
            else arr2[x - n] = arr3[x];
        }
    }

    /* ---------------- Optimal 1 ----------------
     * Swap ends + sort
     * Time: O(n log n + m log m)
     * Space: O(1)
     */
    public static void mergeOptimal1(long[] arr1, long[] arr2, int n, int m) {
        int left = n - 1;
        int right = 0;

        while (left >= 0 && right < m) {
            if (arr1[left] > arr2[right]) {
                long temp = arr1[left];
                arr1[left] = arr2[right];
                arr2[right] = temp;
                left--;
                right++;
            } else break;
        }

        Arrays.sort(arr1);
        Arrays.sort(arr2);
    }

    /* ---------------- Helper ---------------- */
    static void swapGreater(long[] a, long[] b, int i, int j) {
        if (a[i] > b[j]) {
            long temp = a[i];
            a[i] = b[j];
            b[j] = temp;
        }
    }

    /* ---------------- Optimal 2 (GAP Method) ----------------
     * Time: O((n + m) log(n + m))
     * Space: O(1)
     */
    public static void mergeOptimal2(long[] arr1, long[] arr2, int n, int m) {
        int len = n + m;
        int gap = (len + 1) / 2;

        while (gap > 0) {
            int left = 0;
            int right = left + gap;

            while (right < len) {

                // both in arr1
                if (left < n && right < n) {
                    swapGreater(arr1, arr1, left, right);
                }
                // left in arr1, right in arr2
                else if (left < n && right >= n) {
                    swapGreater(arr1, arr2, left, right - n);
                }
                // both in arr2
                else {
                    swapGreater(arr2, arr2, left - n, right - n);
                }

                left++;
                right++;
            }

            if (gap == 1) break;
            gap = (gap + 1) / 2;
        }
    }

    // -------- Driver --------
    public static void main(String[] args) {
        long[] arr1 = {1, 4, 7, 8, 10};
        long[] arr2 = {2, 3, 9};

        int n = arr1.length;
        int m = arr2.length;

        mergeOptimal2(arr1, arr2, n, m);

        System.out.println(Arrays.toString(arr1));
        System.out.println(Arrays.toString(arr2));
    }
}
