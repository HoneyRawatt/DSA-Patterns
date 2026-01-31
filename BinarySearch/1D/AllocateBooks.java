package BinarySearch.1D;

import java.util.Arrays;
public class AllocateBooks {


    /*
     * 🧠 INTUITION (Helper Function):
     * --------------------------------
     * Given a maximum allowed pages limit (`pages`),
     * we count how many students are required if:
     * - Each student gets contiguous books.
     * - No student gets more than `pages`.
     *
     * If pages exceed limit, assign next book to a new student.
     *
     * Time Complexity: O(N)
     * Space Complexity: O(1)
     */
    public static int countStudent(int[] arr, int pages) {
        int students = 1;
        long pagesStudent = 0;

        for (int i = 0; i < arr.length; i++) {
            if (pagesStudent + arr[i] <= pages) {
                pagesStudent += arr[i];
            } else {
                students++;
                pagesStudent = arr[i];
            }
        }
        return students;
    }

    /*
     * 🐢 BRUTE FORCE APPROACH
     * ------------------------
     * - Try every possible maximum pages value
     *   from max(book pages) to sum(book pages).
     * - For each value, check how many students are needed.
     * - First valid value is the answer.
     *
     * Time Complexity:
     *   O((sum - max) * N) → Very slow
     *
     * Space Complexity: O(1)
     */
    public static int findPagesBrute(int[] arr, int m, int n) {
        if (m > n) return -1;

        int low = Arrays.stream(arr).max().getAsInt();
        int high = Arrays.stream(arr).sum();

        for (int pages = low; pages <= high; pages++) {
            if (countStudent(arr, pages) <= m) {
                return pages;
            }
        }
        return -1;
    }

    /*
     * 🚀 OPTIMIZED APPROACH (Binary Search on Answer)
     * -----------------------------------------------
     * 🧠 INTUITION:
     * - We are minimizing the maximum pages assigned to any student.
     * - If we can allocate books with max pages = X,
     *   then we can also allocate with any value > X.
     * - If we cannot allocate with X,
     *   then any value < X will also fail.
     *
     * Search Space:
     * - Minimum = max(book pages)
     * - Maximum = sum(book pages)
     *
     * Time Complexity:
     *   Sorting not required
     *   Binary Search → O(log(sum - max))
     *   Count check → O(N)
     *   Overall → O(N log(sum))
     *
     * Space Complexity: O(1)
     */
    public static int findPages(int[] arr, int m, int n) {
        if (m > n) return -1;

        int low = Arrays.stream(arr).max().getAsInt();
        int high = Arrays.stream(arr).sum();

        while (low <= high) {
            int mid = low + (high - low) / 2;
            int students = countStudent(arr, mid);

            if (students > m) {
                low = mid + 1;   // Need more pages
            } else {
                high = mid - 1;  // Try minimizing max pages
            }
        }
        return low; // Minimum possible maximum pages
    }

    /*
     * 🧪 DRIVER CODE
     *
     * Time Complexity: O(N log N)
     * Space Complexity: O(1)
     */
    public static void main(String[] args) {
        int[] books = {12, 34, 67, 90};
        int students = 2;
        int n = books.length;

        int result = findPages(books, students, n);
        if (result != -1)
            System.out.println("Minimum pages: " + result);
        else
            System.out.println("Assignment not possible!");

        int bruteResult = findPagesBrute(books, students, n);
        if (bruteResult != -1)
            System.out.println("Minimum pages (brute): " + bruteResult);
        else
            System.out.println("Assignment not possible!");
    }
}

