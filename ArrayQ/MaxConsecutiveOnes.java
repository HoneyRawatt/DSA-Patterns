import java.util.*;

public class MaxConsecutiveOnes {

    /*
     * Function to find the maximum number of consecutive 1's
     * Time Complexity: O(n)
     * Space Complexity: O(1)
     */
    static int findMaxConsecutive(int[] arr, int n) {
        int maxCount = 0;
        int count = 0;

        for (int i = 0; i < n; i++) {
            if (arr[i] == 1) {
                count++;
                maxCount = Math.max(maxCount, count);
            } else {
                count = 0;
            }
        }
        return maxCount;
    }

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        int n = sc.nextInt();
        int[] arr = new int[n];

        System.out.println("Enter the elements: ");
        for (int i = 0; i < n; i++) {
            arr[i] = sc.nextInt();
        }

        System.out.println("Max 1's: " + findMaxConsecutive(arr, n));

        sc.close();
    }
}
