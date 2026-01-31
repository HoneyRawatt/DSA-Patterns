import java.util.*;

public class MajorityElement {

    // ---------------- Brute Force ----------------
    // Time Complexity: O(N^2)
    // Space Complexity: O(1)
    static int majorityElementBrute(int[] arr) {
        int n = arr.length;

        for (int i = 0; i < n; i++) {
            int cnt = 0;
            for (int j = 0; j < n; j++) {
                if (arr[i] == arr[j]) {
                    cnt++;
                }
            }
            if (cnt > n / 2) return arr[i];
        }
        return -1;
    }

    // ---------------- Hashing ----------------
    // Time Complexity: O(N)
    // Space Complexity: O(N)
    static int majorityElementHashing(int[] arr) {
        HashMap<Integer,Integer>mpp=new HashMap<>();
        for(int i=0;i<arr.length;i++){
            mpp.put(arr[i],mpp.getOrDefault(arr[i],0)+1);
        }
        for(var entry:mpp.entrySet()){
            if(entry.getValue()>arr.length/2){
                return entry.getKey();
            }
        }
        return -1;
    }

    // ---------------- Moore’s Voting Algorithm ----------------
    // Time Complexity: O(N)
    // Space Complexity: O(1)
    static int majorityElementMooresVoting(int[] arr) {
        int cnt = 0;
        int el = 0;

        // Step 1: Find potential candidate
        for (int num : arr) {
            if (cnt == 0) {
                el = num;
                cnt = 1;
            } else if (num == el) {
                cnt++;
            } else {
                cnt--;
            }
        }

        // Step 2: Verify candidate
        int count = 0;
        for (int num : arr) {
            if (num == el) count++;
        }

        if (count > arr.length / 2) return el;
        return -1;
    }

    public static void main(String[] args) {
        int[] arr = {2, 2, 1, 2, 2, 3, 2};

        System.out.println("Majority using brute: " + majorityElementBrute(arr));
        System.out.println("Majority using hashing: " + majorityElementHashing(arr));
        System.out.println("Majority using Moore's Voting: " + majorityElementMooresVoting(arr));
    }
}
