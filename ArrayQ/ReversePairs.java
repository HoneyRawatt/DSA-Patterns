import java.util.*;

/*
====================================================
REVERSE PAIRS (arr[i] > 2 * arr[j])
====================================================

Intuition:
-----------
We need to count pairs (i, j) such that:
- i < j
- arr[i] > 2 * arr[j]

Brute Force:
------------
- Check every possible pair (i, j)
- Works but too slow for large n

Optimized (Merge Sort Based):
-----------------------------
- Similar to inversion count
- While merging two sorted halves:
    Left half  -> arr[low ... mid]
    Right half -> arr[mid+1 ... high]
- For each element in left half, find how many elements
  in right half satisfy:
        arr[i] > 2 * arr[j]
- Since halves are sorted, we can move pointers efficiently

Why Merge Sort?
---------------
- Both halves are already sorted
- Counting becomes linear per merge step
- Overall complexity improves drastically
*/

public class ReversePairs {

    /*
    ====================================================
    BRUTE FORCE APPROACH
    ====================================================

    Time Complexity:  O(n^2)
    Space Complexity: O(1)

    Checks all (i, j) pairs directly.
    */
    public static int reversePairsBrute(int[] arr) {
        int n = arr.length;
        int cnt = 0;

        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                if ((long) arr[i] > 2L * arr[j]) {
                    cnt++;
                }
            }
        }
        return cnt;
    }

    /*
    ====================================================
    COUNT VALID PAIRS BETWEEN TWO SORTED HALVES
    ====================================================

    Left  half: arr[low ... mid]
    Right half: arr[mid+1 ... high]

    Time Complexity: O(n)
    */
    private static int countPairs(int[] arr, int low, int mid, int high) {
        int cnt = 0;
        int right = mid + 1;

        for (int i = low; i <= mid; i++) {
            while (right <= high && (long) arr[i] > 2L * arr[right]) {
                right++;
            }
            cnt += (right - (mid + 1));
        }
        return cnt;
    }

    /*
    ====================================================
    MERGE TWO SORTED HALVES
    ====================================================

    Time Complexity: O(n)
    Space Complexity: O(n)
    */
    private static void merge(int[] arr, int low, int mid, int high) {
        ArrayList<Integer> temp = new ArrayList<>();

        int left = low;
        int right = mid + 1;

        while (left <= mid && right <= high) {
            if (arr[left] <= arr[right]) {
                temp.add(arr[left++]);
            } else {
                temp.add(arr[right++]);
            }
        }

        while (left <= mid) {
            temp.add(arr[left++]);
        }

        while (right <= high) {
            temp.add(arr[right++]);
        }

        for (int i = low; i <= high; i++) {
            arr[i] = temp.get(i - low);
        }
    }

    /*
    ====================================================
    MERGE SORT WITH REVERSE PAIR COUNTING
    ====================================================

    Time Complexity:  O(n log n)
    Space Complexity: O(n)
    */
    private static int mergeSort(int[] arr, int low, int high) {
        if (low >= high) return 0;

        int mid = (low + high) / 2;
        int cnt = 0;

        cnt += mergeSort(arr, low, mid);
        cnt += mergeSort(arr, mid + 1, high);
        cnt += countPairs(arr, low, mid, high);
        merge(arr, low, mid, high);

        return cnt;
    }

    /*
    ====================================================
    WRAPPER FUNCTION
    ====================================================
    */
    public static int countReversePairs(int[] nums) {
        return mergeSort(nums, 0, nums.length - 1);
    }

    /*
    ====================================================
    MAIN FUNCTION
    ====================================================
    */
    public static void main(String[] args) {

        int[] arr = {1, 3, 2, 3, 1};

        System.out.println("Original Array: " + Arrays.toString(arr));

        // Brute Force
        System.out.println("Brute-force Reverse Pairs Count: "
                + reversePairsBrute(arr));

        // Optimized (use copy to avoid modifying original)
        int[] arrCopy = Arrays.copyOf(arr, arr.length);
        System.out.println("Optimized Merge Sort Reverse Pairs Count: "
                + countReversePairs(arrCopy));
    }
}
