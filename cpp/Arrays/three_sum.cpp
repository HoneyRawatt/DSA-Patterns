#include<iostream>
#include<vector>
#include<set>
#include<algorithm>
using namespace std;

/*
 * Brute-force Approach
 * Time Complexity: O(n^3)
 * Space Complexity: O(number of triplets) due to set
 */
vector<vector<int>> three_sum_brute(int n, vector<int>& nums) {
    set<vector<int>> st;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            for (int k = j + 1; k < n; k++) {
                if (nums[i] + nums[j] + nums[k] == 0) {
                    vector<int> temp = {nums[i], nums[j], nums[k]};
                    sort(temp.begin(), temp.end()); // Sort to handle uniqueness
                    st.insert(temp);
                }
            }
        }
    }
    vector<vector<int>> ans(st.begin(), st.end());
    return ans;
}

/*
 * Hashing-based Approach
 * Time Complexity: O(n^2 * log m) where m = number of unique triplets (due to set insertions)
 * Space Complexity: O(n) for the hash set + O(m) for result storage
 */
vector<vector<int>> three_sum_hashing(int n, vector<int>& num) {
    set<vector<int>> st;
    for (int i = 0; i < n; i++) {
        set<int> hashset; // Keeps track of seen numbers for current i
        for (int j = i + 1; j < n; j++) {
            int third = -(num[i] + num[j]);
            if (hashset.find(third) != hashset.end()) {
                vector<int> temp = {num[i], num[j], third};
                sort(temp.begin(), temp.end()); // Sort to ensure uniqueness
                st.insert(temp); // Unique triplets
            }
            hashset.insert(num[j]);
        }
    }
    vector<vector<int>> ans(st.begin(), st.end());
    return ans;
}

/*
 * Optimal Approach (Two-Pointer Technique after sorting)
 * Time Complexity: O(n^2)
 * Space Complexity: O(1) (excluding output)
 */
vector<vector<int>> three_sum_optimal(int n, vector<int>& num) {
    sort(num.begin(), num.end());
    vector<vector<int>> ans;

    for (int i = 0; i < n; i++) {
        if (i > 0 && num[i] == num[i - 1]) continue;  // Skip duplicates

        int j = i + 1;
        int k = n - 1;

        while (j < k) {
            int sum = num[i] + num[j] + num[k];
            if (sum < 0) {
                j++;
            } else if (sum > 0) {
                k--;
            } else {
                vector<int> temp = {num[i], num[j], num[k]};
                ans.push_back(temp);
                j++;
                k--;

                // Skip duplicates
                while (j < k && num[j] == num[j - 1]) j++;
                while (j < k && num[k] == num[k + 1]) k--;
            }
        }
    }

    return ans;
}

// ---------- Utility function to print triplets ----------
void print_result(const string& label, const vector<vector<int>>& res) {
    cout << label << ":\n";
    for (const auto& triplet : res) {
        for (int val : triplet) cout << val << " ";
        cout << endl;
    }
    cout << "--------------------------\n";
}

// ---------- Main Function ----------
int main() {
    vector<int> nums = {-1, 0, 1, 2, -1, -4};
    int n = nums.size();

    vector<vector<int>> res_brute = three_sum_brute(n, nums);
    vector<vector<int>> res_hashing = three_sum_hashing(n, nums);
    vector<vector<int>> res_optimal = three_sum_optimal(n, nums);

    print_result("Brute-force Result", res_brute);
    print_result("Hashing Result", res_hashing);
    print_result("Optimal Two-Pointer Result", res_optimal);

    return 0;
}
