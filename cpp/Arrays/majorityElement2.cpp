#include<iostream>
#include<vector>
#include<algorithm>
#include<climits>
#include<map>
using namespace std;

/*
 * Brute-force Approach
 * Time Complexity: O(n^2)
 * Space Complexity: O(1)  (excluding output list)
 */
vector<int> majorityElement2_brute(vector<int> arr) {
    vector<int> ls;
    int n = arr.size();
    int mini = n / 3;

    for (int i = 0; i < n; i++) {
        // Avoid checking same element again
        if (find(ls.begin(), ls.end(), arr[i]) == ls.end()) {
            int cnt = 0;
            for (int j = 0; j < n; j++) {
                if (arr[j] == arr[i]) cnt++;
            }
            if (cnt > mini)
                ls.push_back(arr[i]);
        }
        if (ls.size() == 2) break;  // Max 2 elements possible
    }

    return ls;
}

/*
 * Hashing Approach using map
 * Time Complexity: O(n)
 * Space Complexity: O(n) (for the hash map)
 */
vector<int> majorityElement2_hashing(vector<int> arr) {
    map<int, int> mpp;
    vector<int> ls;
    int n = arr.size();
    int mini = n / 3;

    for (int i = 0; i < n; i++) {
        mpp[arr[i]]++;  // Count frequency
    }

    for (auto it : mpp) {
        if (it.second > mini)
            ls.push_back(it.first);
    }

    return ls;
}

/*
 * Moore's Voting Algorithm (Extended for n/3 case)
 * Time Complexity: O(n)
 * Space Complexity: O(1)
 */
vector<int> majorityElement2_moores_voting_algo(vector<int> arr) {
    int cnt1 = 0, cnt2 = 0;
    int el1 = INT_MIN, el2 = INT_MIN;
    int n = arr.size();

    // Step 1: Find 2 potential majority candidates
    for (int i = 0; i < n; i++) {
        if (cnt1 == 0 && arr[i] != el2) {
            el1 = arr[i];
            cnt1 = 1;
        }
        else if (cnt2 == 0 && arr[i] != el1) {
            el2 = arr[i];
            cnt2 = 1;
        }
        else if (arr[i] == el1) cnt1++;
        else if (arr[i] == el2) cnt2++;
        else {
            cnt1--;
            cnt2--;
        }
    }

    // Step 2: Verify actual counts
    cnt1 = 0, cnt2 = 0;
    for (int i = 0; i < n; i++) {
        if (arr[i] == el1) cnt1++;
        if (arr[i] == el2) cnt2++;
    }

    vector<int> ls;
    int mini = n / 3;
    if (cnt1 > mini) ls.push_back(el1);
    if (el2 != el1 && cnt2 > mini) ls.push_back(el2);

    return ls;
}

// Utility function to print vector
void printVector(const vector<int>& v) {
    for (auto val : v) cout << val << " ";
    cout << endl;
}

int main() {
    vector<int> arr = {2, 2, 1, 2, 2, 3, 2};

    cout << "Majority using brute: ";
    printVector(majorityElement2_brute(arr));

    cout << "Majority using hashing: ";
    printVector(majorityElement2_hashing(arr));

    cout << "Majority using Moore's Voting: ";
    printVector(majorityElement2_moores_voting_algo(arr));

    return 0;
}
