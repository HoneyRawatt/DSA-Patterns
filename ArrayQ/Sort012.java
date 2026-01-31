import java.util.Scanner;
import java.util.Arrays;

public class Sort012 {

    /*
     * Brute-force Counting Method
     *
     * Time Complexity: O(N)
     * - One loop to count 0s, 1s, and 2s
     * - One loop to overwrite the array
     *
     * Space Complexity: O(1)
     * - Uses only constant extra variables
     */
    static void sortArrayBrute(int[] arr, int n) {
        int cnt0 = 0, cnt1 = 0, cnt2 = 0;

        // Count number of 0s, 1s, and 2s
        for (int i = 0; i < n; i++) {
            if (arr[i] == 0) cnt0++;
            else if (arr[i] == 1) cnt1++;
            else cnt2++;
        }

        // Overwrite array with counted values
        int index = 0;
        for (int i = 0; i < cnt0; i++) arr[index++] = 0;
        for (int i = 0; i < cnt1; i++) arr[index++] = 1;
        for (int i = 0; i < cnt2; i++) arr[index++] = 2;
    }

    /*
     * Dutch National Flag Algorithm
     *
     * Time Complexity: O(N)
     * - Single traversal of the array
     *
     * Space Complexity: O(1)
     * - In-place sorting, no extra space used
     */
    static void sortArrayDutchNationalFlag(int[] arr, int n) {
        int low = 0, mid = 0, high = n - 1;

        while (mid <= high) {
            if (arr[mid] == 0) {
                // Swap arr[low] and arr[mid]
                int temp = arr[low];
                arr[low] = arr[mid];
                arr[mid] = temp;

                low++;
                mid++;
            } else if (arr[mid] == 1) {
                mid++;
            } else { // arr[mid] == 2
                // Swap arr[mid] and arr[high]
                int temp = arr[mid];
                arr[mid] = arr[high];
                arr[high] = temp;

                high--;
            }
        }
    }

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        // Input array size
        System.out.print("Enter array size: ");
        int n = sc.nextInt();

        int[] arr = new int[n];
        System.out.print("Enter the elements (0s, 1s, and 2s): ");
        for (int i = 0; i < n; i++) {
            arr[i] = sc.nextInt();
        }

        // Original array
        System.out.println("\nOriginal Array:");
        System.out.println(Arrays.toString(arr));

        // Brute-force method
        int[] arrBrute = arr.clone();
        sortArrayBrute(arrBrute, n);
        System.out.println("\nSorted using Brute-force Counting:");
        System.out.println(Arrays.toString(arrBrute));

        // Dutch National Flag Algorithm
        int[] arrDutch = arr.clone();
        sortArrayDutchNationalFlag(arrDutch, n);
        System.out.println("\nSorted using Dutch National Flag Algorithm:");
        System.out.println(Arrays.toString(arrDutch));

        sc.close();
    }
}
