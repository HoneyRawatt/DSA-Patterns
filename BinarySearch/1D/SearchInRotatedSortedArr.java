package BinarySearch.1D;
import java.util.*;

public class SearchInRotatedSortedArr {
    /*
     * CASE 1: Array has UNIQUE elements
     *
     * Time Complexity:
     * ----------------
     * O(log n) → normal binary search
     *
     * Space Complexity:
     * -----------------
     * O(1)
     */

    static int findElementUnique(int[] arr, int target) {
        int low = 0, high = arr.length - 1;

        while (low <= high) {
            int mid = low + (high - low) / 2;

            if (arr[mid] == target)
                return mid;

            // Left half is sorted
            if (arr[low] <= arr[mid]) {
                if (arr[low] <= target && target <= arr[mid])
                    high = mid - 1;
                else
                    low = mid + 1;
            }
            // Right half is sorted
            else {
                if (arr[mid] <= target && target <= arr[high])
                    low = mid + 1;
                else
                    high = mid - 1;
            }
        }
        return -1;
    }

    /*
     * CASE 2: Array has DUPLICATE elements
     *
     * Time Complexity:
     * ----------------
     * Average Case: O(log n)
     * Worst Case  : O(n)  → when many duplicates exist
     *
     * Space Complexity:
     * -----------------
     * O(1)
     */

    static int findElementDuplicate(int[] arr, int target) {
        int low = 0, high = arr.length - 1;

        while (low <= high) {
            int mid = low + (high - low) / 2;

            if (arr[mid] == target)
                return mid;

            // Shrink boundaries when duplicates block decision
            if (arr[low] == arr[mid] && arr[mid] == arr[high]) {
                low++;
                high--;
                continue;
            }

            // Left half is sorted
            if (arr[low] <= arr[mid]) {
                if (arr[low] <= target && target <= arr[mid])
                    high = mid - 1;
                else
                    low = mid + 1;
            }
            // Right half is sorted
            else {
                if (arr[mid] <= target && target <= arr[high])
                    low = mid + 1;
                else
                    high = mid - 1;
            }
        }
        return -1;
    }

    public static void main(String[] args) {

        int[] uniqueArr = {4, 5, 6, 7, 0, 1, 2};
        int target1 = 0;
        System.out.println("Unique array index: " +
                findElementUnique(uniqueArr, target1));

        int[] dupArr = {2, 5, 6, 0, 0, 1, 2};
        int target2 = 0;
        System.out.println("Duplicate array index: " +
                findElementDuplicate(dupArr, target2));
    }
}
