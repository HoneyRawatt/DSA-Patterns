import java.util.*;

public class MajorityElementII {

    /*
     * Brute-force Approach
     * Time Complexity: O(n^2)
     * Space Complexity: O(1) (excluding output list)
     */
    static List<Integer> majorityElement2Brute(int[] arr) {
        List<Integer> ls = new ArrayList<>();
        int n = arr.length;
        int mini = n / 3;

        for (int i = 0; i < n; i++) {
            if (!ls.contains(arr[i])) {
                int cnt = 0;
                for (int j = 0; j < n; j++) {
                    if (arr[j] == arr[i]) cnt++;
                }
                if (cnt > mini) {
                    ls.add(arr[i]);
                }
            }
            if (ls.size() == 2) break; // Max 2 elements possible
        }

        return ls;
    }

    /*
     * Hashing Approach using HashMap
     * Time Complexity: O(n)
     * Space Complexity: O(n)
     */
    static List<Integer> majorityElement2Hashing(int[] arr) {
        Map<Integer, Integer> map = new HashMap<>();
        List<Integer> ls = new ArrayList<>();
        int n = arr.length;
        int mini = n / 3;

        for (int num : arr) {
            map.put(num, map.getOrDefault(num, 0) + 1);
        }

        for (Map.Entry<Integer, Integer> entry : map.entrySet()) {
            if (entry.getValue() > mini) {
                ls.add(entry.getKey());
            }
        }

        return ls;
    }

    /*
     * Moore's Voting Algorithm (Extended for n/3 case)
     * Time Complexity: O(n)
     * Space Complexity: O(1)
     */
    static List<Integer> majorityElement2MooresVoting(int[] arr) {
        int cnt1 = 0, cnt2 = 0;
        int el1 = Integer.MIN_VALUE, el2 = Integer.MIN_VALUE;
        int n = arr.length;

        // Step 1: Find potential candidates
        for (int num : arr) {
            if (cnt1 == 0 && num != el2) {
                el1 = num;
                cnt1 = 1;
            } else if (cnt2 == 0 && num != el1) {
                el2 = num;
                cnt2 = 1;
            } else if (num == el1) {
                cnt1++;
            } else if (num == el2) {
                cnt2++;
            } else {
                cnt1--;
                cnt2--;
            }
        }

        // Step 2: Verify counts
        cnt1 = 0;
        cnt2 = 0;
        for (int num : arr) {
            if (num == el1) cnt1++;
            if (num == el2) cnt2++;
        }

        List<Integer> ls = new ArrayList<>();
        int mini = n / 3;
        if (cnt1 > mini) ls.add(el1);
        if (el2 != el1 && cnt2 > mini) ls.add(el2);

        return ls;
    }

    // Utility function
    static void printList(List<Integer> list) {
        for (int val : list) {
            System.out.print(val + " ");
        }
        System.out.println();
    }

    public static void main(String[] args) {
        int[] arr = {2, 2, 1, 2, 2, 3, 2};

        System.out.print("Majority using brute: ");
        printList(majorityElement2Brute(arr));

        System.out.print("Majority using hashing: ");
        printList(majorityElement2Hashing(arr));

        System.out.print("Majority using Moore's Voting: ");
        printList(majorityElement2MooresVoting(arr));
    }
}
