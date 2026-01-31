package BinarySearch.1D;

import java.util.*;
import static java.lang.Math.*;

/*
    Approach 1: Brute-force
    ------------------------
    - Merge both arrays into one sorted array.
    - Return the middle element(s) as the median.

    Time Complexity: O(n1 + n2)
    Space Complexity: O(n1 + n2)
*/
public class MedianOfTwoSortedArrays {

    public static double medianBrute(int[] a, int[] b) {
        int n1 = a.length, n2 = b.length;
        int[] c = new int[n1 + n2];

        int i = 0, j = 0, k = 0;

        // Merge both arrays
        while (i < n1 && j < n2) {
            if (a[i] < b[j]) c[k++] = a[i++];
            else c[k++] = b[j++];
        }

        // Copy remaining elements
        while (i < n1) c[k++] = a[i++];
        while (j < n2) c[k++] = b[j++];

        int n = n1 + n2;

        // Return median
        if (n % 2 == 1)
            return c[n / 2];
        return (c[n / 2] + c[n / 2 - 1]) / 2.0;
    }

    /*
        Approach 2: Better merge (No extra space)
        ------------------------------------------
        - Simulate merge until median position.
        - Track middle elements only.

        Time Complexity: O(n1 + n2)
        Space Complexity: O(1)
    */
    public static double medianBetter(int[] a, int[] b) {
        int n1 = a.length, n2 = b.length;
        int total = n1 + n2;

        int mid2 = total / 2;
        int mid1 = mid2 - 1;

        int i = 0, j = 0, count = 0;
        int val1 = -1, val2 = -1;

        while (i < n1 && j < n2) {
            int val = (a[i] < b[j]) ? a[i++] : b[j++];
            if (count == mid1) val1 = val;
            if (count == mid2) val2 = val;
            count++;
        }

        while (i < n1) {
            int val = a[i++];
            if (count == mid1) val1 = val;
            if (count == mid2) val2 = val;
            count++;
        }

        while (j < n2) {
            int val = b[j++];
            if (count == mid1) val1 = val;
            if (count == mid2) val2 = val;
            count++;
        }

        if (total % 2 == 1)
            return val2;
        return (val1 + val2) / 2.0;
    }

    /*
        Approach 3: Binary Search (Optimal)
        -----------------------------------
        🧠 INTUITION:
        - Binary search on the smaller array.
        - Partition arrays so that:
            max(left1, left2) <= min(right1, right2)

        Time Complexity: O(log(min(n1, n2)))
        Space Complexity: O(1)
    */
    public static double findMedianSortedArrays(int[] nums1, int[] nums2) {
        int n1 = nums1.length;
        int n2 = nums2.length;

        // Ensure nums1 is the smaller array
        if (n1 > n2)
            return findMedianSortedArrays(nums2, nums1);

        int low = 0, high = n1;
        int total = n1 + n2;
        int leftPartitionSize = (total + 1) / 2;

        while (low <= high) {
            int cut1 = (low + high) / 2;
            int cut2 = leftPartitionSize - cut1;

            int l1 = (cut1 == 0) ? Integer.MIN_VALUE : nums1[cut1 - 1];
            int l2 = (cut2 == 0) ? Integer.MIN_VALUE : nums2[cut2 - 1];
            int r1 = (cut1 == n1) ? Integer.MAX_VALUE : nums1[cut1];
            int r2 = (cut2 == n2) ? Integer.MAX_VALUE : nums2[cut2];

            // Valid partition
            if (l1 <= r2 && l2 <= r1) {
                if (total % 2 == 0)
                    return (Math.max(l1, l2) + Math.min(r1, r2)) / 2.0;
                else
                    return Math.max(l1, l2);
            }
            // Too many elements taken from nums1
            else if (l1 > r2) {
                high = cut1 - 1;
            }
            // Too few elements taken from nums1
            else {
                low = cut1 + 1;
            }
        }
        return 0.0; // Should never reach here
    }

    /*
        Driver Code
    */
    public static void main(String[] args) {
        int[] nums1 = {1, 3};
        int[] nums2 = {2, 4, 7};

        System.out.printf("Brute Force Median:   %.5f%n", medianBrute(nums1, nums2));
        System.out.printf("Better Merge Median:  %.5f%n", medianBetter(nums1, nums2));
        System.out.printf("Binary Search Median: %.5f%n", findMedianSortedArrays(nums1, nums2));
    }
}
