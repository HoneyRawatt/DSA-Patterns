import java.util.*;

public class RearrangeBySign {

    // ---------------- Equal Positives & Negatives (Brute Force) ----------------
    // Time Complexity: O(N)
    // Space Complexity: O(N)
    static int[] rearrangeEqualBrute(int[] arr, int n) {
        ArrayList<Integer> pos = new ArrayList<>();
        ArrayList<Integer> neg = new ArrayList<>();

        for (int i = 0; i < n; i++) {
            if (arr[i] > 0) pos.add(arr[i]);
            else neg.add(arr[i]);
        }

        for (int i = 0; i < n / 2; i++) {
            arr[2 * i] = pos.get(i);
            arr[2 * i + 1] = neg.get(i);
        }

        return arr;
    }

    // ---------------- Equal Positives & Negatives (Optimized) ----------------
    // Time Complexity: O(N)
    // Space Complexity: O(N)
    static int[] rearrangeEqual(int[] arr, int n) {
        int[] ans = new int[n];

        int posIndex = 0;
        int negIndex = 1;

        for (int i = 0; i < n; i++) {
            if (arr[i] < 0) {
                ans[negIndex] = arr[i];
                negIndex += 2;
            } else {
                ans[posIndex] = arr[i];
                posIndex += 2;
            }
        }

        return ans;
    }

    // ---------------- Unequal Positives & Negatives ----------------
    // Time Complexity: O(N)
    // Space Complexity: O(N)
    static int[] rearrangeUnequal(int[] arr, int n) {
        ArrayList<Integer> pos = new ArrayList<>();
        ArrayList<Integer> neg = new ArrayList<>();

        for (int i = 0; i < n; i++) {
            if (arr[i] >= 0) pos.add(arr[i]);
            else neg.add(arr[i]);
        }

        int index = 0;

        if (pos.size() > neg.size()) {
            for (int i = 0; i < neg.size(); i++) {
                arr[index++] = pos.get(i);
                arr[index++] = neg.get(i);
            }
            for (int i = neg.size(); i < pos.size(); i++) {
                arr[index++] = pos.get(i);
            }
        } else {
            for (int i = 0; i < pos.size(); i++) {
                arr[index++] = pos.get(i);
                arr[index++] = neg.get(i);
            }
            for (int i = pos.size(); i < neg.size(); i++) {
                arr[index++] = neg.get(i);
            }
        }

        return arr;
    }

    public static void main(String[] args) {

        // ✅ Equal positives & negatives
        int[] equalArr = {3, -1, -2, 4, -5, 6};
        int nEqual = equalArr.length;

        System.out.println("Equal Count Input: " + Arrays.toString(equalArr));

        int[] res1 = rearrangeEqualBrute(equalArr.clone(), nEqual);
        System.out.println("Equal Count (Brute): " + Arrays.toString(res1));

        int[] res2 = rearrangeEqual(equalArr.clone(), nEqual);
        System.out.println("Equal Count (Optimized): " + Arrays.toString(res2));

        System.out.println("\n-----------------------------");

        // ✅ Unequal positives & negatives
        int[] unequalArr = {3, -1, -2, 4, 5, 6, 7};
        int nUnequal = unequalArr.length;

        System.out.println("Unequal Count Input: " + Arrays.toString(unequalArr));

        int[] res3 = rearrangeUnequal(unequalArr.clone(), nUnequal);
        System.out.println("Unequal Count Rearranged: " + Arrays.toString(res3));
    }
}
