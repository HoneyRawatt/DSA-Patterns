import java.util.*;

public class LeadersArray{

    // ---------------- Brute Force ----------------
    // Time Complexity: O(N^2)
    // Space Complexity: O(1) (excluding output list)
    static ArrayList<Integer> superiorElementBrute(int[] arr) {
        ArrayList<Integer> ans = new ArrayList<>();
        int n = arr.length;

        for (int i = 0; i < n; i++) {
            boolean leader = true;
            for (int j = i + 1; j < n; j++) {
                if (arr[j] > arr[i]) {
                    leader = false;
                    break;
                }
            }
            if (leader) ans.add(arr[i]);
        }
        return ans;
    }

    // ---------------- Optimized ----------------
    // Time Complexity: O(N)
    // Space Complexity: O(1) (excluding output list)
    static ArrayList<Integer> superiorElement(int[] arr) {
        ArrayList<Integer> ans = new ArrayList<>();
        int n = arr.length;

        int maxi = Integer.MIN_VALUE;

        for (int i = n - 1; i >= 0; i--) {
            if (arr[i] > maxi) {
                ans.add(arr[i]);
            }
            maxi = Math.max(maxi, arr[i]);
        }

        // Reverse to maintain original order
        Collections.reverse(ans);
        return ans;
    }

    public static void main(String[] args) {
        int[] arr = {1, 2, 3, 2, 1, 5, 3};

        ArrayList<Integer> res = superiorElement(arr);

        System.out.print("Superior elements are: ");
        for (int x : res) {
            System.out.print(x + " ");
        }
    }
}
