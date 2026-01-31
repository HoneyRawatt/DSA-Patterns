package BinarySearch.1D;
import java.util.*;

public class KthElementTwoSortedArrays {

    /*
     * 🧠 INTUITION:
     * -------------
     * - We perform binary search on the smaller array.
     * - We partition both arrays such that:
     *     left part has exactly k elements.
     * - The k-th smallest element is:
     *     max(left part of array1, left part of array2)
     *
     * Time Complexity: O(log(min(n1, n2)))
     * Space Complexity: O(1)
     */
    public static int findKthElement(int[] a, int[] b, int k) {
        int n1 = a.length;
        int n2 = b.length;

        // Always binary search on smaller array
        if (n1 > n2)
            return findKthElement(b, a, k);

        int low = Math.max(0, k - n2);
        int high = Math.min(k, n1);

        while (low <= high) {
            int mid1 = (low + high) / 2;
            int mid2 = k - mid1;

            int l1 = (mid1 == 0) ? Integer.MIN_VALUE : a[mid1 - 1];
            int l2 = (mid2 == 0) ? Integer.MIN_VALUE : b[mid2 - 1];

            int r1 = (mid1 == n1) ? Integer.MAX_VALUE : a[mid1];
            int r2 = (mid2 == n2) ? Integer.MAX_VALUE : b[mid2];

            // Valid partition
            if (l1 <= r2 && l2 <= r1) {
                return Math.max(l1, l2);
            }
            // Move left in array a
            else if (l1 > r2) {
                high = mid1 - 1;
            }
            // Move right in array a
            else {
                low = mid1 + 1;
            }
        }
        return 0; // Should never reach here
    }

    /*
     * 🧪 DRIVER CODE
     */
    public static void main(String[] args) {
        int[] a = {2, 3, 6, 7, 9};
        int[] b = {1, 4, 8, 10};

        Scanner sc = new Scanner(System.in);
        System.out.print("Enter k (1-based index): ");
        int k = sc.nextInt();

        int result = findKthElement(a, b, k);
        System.out.println("The " + k + "-th smallest element is: " + result);

        sc.close();
    }
}
