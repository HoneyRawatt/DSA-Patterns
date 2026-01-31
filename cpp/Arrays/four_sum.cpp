#include<iostream>
#include<vector>
#include<set>
#include<algorithm>
using namespace std;

/*
 * Brute-force Approach for 4-Sum
 * Time Complexity: O(n^4)
 * Space Complexity: O(m), where m = number of unique quadruplets
 */
vector<vector<int>> four_sum_brute(vector<int>& nums, int target) {
    int n = nums.size();
    set<vector<int>> st;

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            for (int k = j + 1; k < n; k++) {
                for (int l = k + 1; l < n; l++) {
                    long long sum = 1LL * nums[i] + nums[j] + nums[k] + nums[l];
                    if (sum == target) {
                        vector<int> temp = {nums[i], nums[j], nums[k], nums[l]};
                        sort(temp.begin(), temp.end()); // To avoid duplicates
                        st.insert(temp);
                    }
                }
            }
        }
    }

    return vector<vector<int>>(st.begin(), st.end());
}

/*
 * Hashing-based Approach for 4-Sum
 * Time Complexity: O(n^3 * log m) — due to set insertion
 * Space Complexity: O(n) for hashset + O(m) for storing results
 */
vector<vector<int>> four_sum_hashing(vector<int>& nums, int target) {
    int n = nums.size();
    set<vector<int>> st;

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            set<long long> hashset;
            for (int k = j + 1; k < n; k++) {
                long long sum = 1LL * nums[i] + nums[j] + nums[k];
                long long fourth = target - sum;

                if (hashset.find(fourth) != hashset.end()) {
                    vector<int> temp = {nums[i], nums[j], nums[k], (int)fourth};
                    sort(temp.begin(), temp.end());
                    st.insert(temp);
                }

                hashset.insert(nums[k]);
            }
        }
    }

    return vector<vector<int>>(st.begin(), st.end());
}

/*
 * Optimal Two-Pointer Approach
 * Time Complexity: O(n^3)
 * Space Complexity: O(1) excluding result
 */
vector<vector<int>> four_sum_optimal(vector<int>& nums, int target) {
    int n = nums.size();
    vector<vector<int>> ans;
    sort(nums.begin(), nums.end());

    for (int i = 0; i < n; i++) {
        if (i > 0 && nums[i] == nums[i - 1]) continue;  // Skip duplicates

        for (int j = i + 1; j < n; j++) {
            if (j > i + 1 && nums[j] == nums[j - 1]) continue;  // Skip duplicates

            int k = j + 1;
            int l = n - 1;

            while (k < l) {
                long long sum = 1LL * nums[i] + nums[j] + nums[k] + nums[l];

                if (sum == target) {
                    ans.push_back({nums[i], nums[j], nums[k], nums[l]});
                    k++;
                    l--;

                    while (k < l && nums[k] == nums[k - 1]) k++;  // Skip duplicates
                    while (k < l && nums[l] == nums[l + 1]) l--;  // Skip duplicates

                } else if (sum < target) {
                    k++;
                } else {
                    l--;
                }
            }
        }
    }

    return ans;
}
void print_result(const string& label, const vector<vector<int>>& res) {
    cout << label << ":\n";
    for (auto quad : res) {
        for (int x : quad) cout << x << " ";
        cout << endl;
    }
    cout << "------\n";
}
int main() {
    vector<int> nums = {1, 0, -1, 0, -2, 2};
    int target = 0;

    auto res_brute = four_sum_brute(nums, target);
    auto res_hash = four_sum_hashing(nums, target);
    auto res_opt = four_sum_optimal(nums, target);

    print_result("Brute-force", res_brute);
    print_result("Hashing", res_hash);
    print_result("Optimal", res_opt);

    return 0;
}