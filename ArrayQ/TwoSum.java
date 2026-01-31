import java.util.*;

public class TwoSum {

    /*--------------------------------------------------
      Hashing Approach
      Time Complexity: O(n)
      Space Complexity: O(n)
      Returns indices of the two elements
    --------------------------------------------------*/
    static int[] twoSumHashing(int[] arr, int target) {
        HashMap<Integer, Integer> map = new HashMap<>();

        for (int i = 0; i < arr.length; i++) {
            int num = arr[i];
            int more = target - num;

            if (map.containsKey(more)) {
                return new int[]{map.get(more), i};
            }
            map.put(num, i);
        }
        return new int[]{-1, -1};
    }

    /*--------------------------------------------------
      Two Pointer Approach (Only checks existence)
      NOTE: Works after sorting → indices are NOT preserved
      Time Complexity: O(n log n)
      Space Complexity: O(1)
    --------------------------------------------------*/
    static String twoSumTwoPointer(int[] arr, int target) {
        Arrays.sort(arr);
        int left = 0, right = arr.length - 1;

        while (left < right) {
            int sum = arr[left] + arr[right];
            if (sum == target) return "YES";
            else if (sum < target) left++;
            else right--;
        }
        return "NO";
    }

    /*--------------------------------------------------
      Brute Force Approach
      Time Complexity: O(n²)
      Space Complexity: O(1)
      Returns indices
    --------------------------------------------------*/
    static int[] twoSumBrute(int[] arr, int target) {
        int n = arr.length;

        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                if (arr[i] + arr[j] == target) {
                    return new int[]{i, j};
                }
            }
        }
        return new int[]{-1, -1};
    }

    // ---------------- MAIN ----------------
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        System.out.print("Enter array size: ");
        int n = sc.nextInt();

        int[] arr = new int[n];
        System.out.print("Enter the elements: ");
        for (int i = 0; i < n; i++) {
            arr[i] = sc.nextInt();
        }

        System.out.print("Enter target sum k: ");
        int k = sc.nextInt();

        // Hashing Approach
        int[] hashResult = twoSumHashing(arr, k);
        System.out.println("\nHashing Approach:");
        if (hashResult[0] != -1) {
            System.out.println("Indices found: " + hashResult[0] + " and " + hashResult[1]);
            System.out.println("Values: " + arr[hashResult[0]] + " + " + arr[hashResult[1]] + " = " + k);
        } else {
            System.out.println("No valid pair found.");
        }

        // Two-pointer Approach
        System.out.println("\nTwo-pointer Approach: " + twoSumTwoPointer(arr.clone(), k));

        // Brute-force Approach
        int[] bruteResult = twoSumBrute(arr, k);
        System.out.println("\nBrute-force Approach:");
        if (bruteResult[0] != -1) {
            System.out.println("Indices found: " + bruteResult[0] + " and " + bruteResult[1]);
            System.out.println("Values: " + arr[bruteResult[0]] + " + " + arr[bruteResult[1]] + " = " + k);
        } else {
            System.out.println("No valid pair found.");
        }

        sc.close();
    }
}
