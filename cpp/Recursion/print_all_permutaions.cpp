#include <bits/stdc++.h>
using namespace std;

void print_all_permu(vector<int>& ds, vector<int>& arr, vector<vector<int>>& ans, vector<int>& freq) {
    if (ds.size() == arr.size()) {
        ans.push_back(ds);
        return;
    }

    for (int i = 0; i < arr.size(); i++) {
        // Skip already used
        if (freq[i]) continue;

        // Skip duplicates (only first unused duplicate is allowed)
        if (i > 0 && arr[i] == arr[i - 1] && !freq[i - 1]) continue;

        ds.push_back(arr[i]);
        freq[i] = 1;
        print_all_permu(ds, arr, ans, freq);
        freq[i] = 0;
        ds.pop_back();
    }
}

void print_all_permu_optimize(int ind,vector<int>&arr,vector<vector<int>>&ans){
    if(ind==arr.size()){
        ans.push_back(arr);
        return;
    }
    for(int i=ind;i<arr.size();i++){
        swap(arr[ind],arr[i]);
        print_all_permu_optimize(ind+1,arr,ans);
        swap(arr[ind],arr[i]);
    }
}

int main() {
    vector<int> arr = {1, 1, 2}; // Example input with duplicates
    sort(arr.begin(), arr.end()); // Important for handling duplicates

    vector<vector<int>> ans;
    vector<int> ds;
    vector<int> freq(arr.size(), 0); // 0 = not used

    print_all_permu(ds, arr, ans, freq);

    // Print all unique permutations
    for (auto& vec : ans) {
        for (int num : vec)
            cout << num << " ";
        cout << endl;
    }

    return 0;
}

    /*
    ====================================================
    TIME COMPLEXITY:
    ----------------------------------------------------
    O(n! * n)
    - n! permutations
    - Copying each permutation costs O(n)

    SPACE COMPLEXITY:
    ----------------------------------------------------
    O(n)
    - Recursion stack
    - Frequency array
    - Temporary permutation list
    - Output space not counted
    ====================================================
    */