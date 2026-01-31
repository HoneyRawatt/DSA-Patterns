#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
using namespace std;

/*
 Brute Force Approach:
 - Count occurrences of each element using a map
 - Return the element whose count is 1

 Time Complexity:  O(n log n)  // because map insertion/search is O(log n)
 Space Complexity: O(n)        // storing counts in the map
*/
int single_number_II_brute(vector<int> &nums) {
    int n = nums.size();
    map<int,int> mpp;
    for(int i = 0; i < n; i++) 
        mpp[nums[i]]++;

    for(auto it : mpp) {
        if(it.second == 1) 
            return it.first;
    }
    return -1;
}

/*
 Better Approach:
 - For each bit position (0 to 30), count how many numbers have that bit set
 - If count % 3 == 1, then that bit belongs to the unique number
 - This works because all other numbers appear 3 times

 Time Complexity:  O(31 * n) → O(n)   // 31 is constant for 32-bit integers
 Space Complexity: O(1)               // only variables, no extra structures
*/
int single_numberr_II_better(vector<int> &nums) {
    int ans = 0;
    for(int bitind = 0; bitind < 31; bitind++) {
        int cnt = 0;
        for(int i = 0; i < nums.size(); i++) {
            if(nums[i] & (1 << bitind)) 
                cnt++;
        }
        if(cnt % 3 == 1) 
            ans |= (1 << bitind);
    }
    return ans;
}

/*
 Sorting Approach:
 - Sort the array
 - Unique number will not follow the "appear 3 times" pattern
 - Check in steps of 3

 Time Complexity:  O(n log n)  // sorting
 Space Complexity: O(1)        // in-place sort
*/
int single_number_II_optimized(vector<int> &nums) {
    sort(nums.begin(), nums.end());
    for(int i = 0; i < nums.size() - 1; i += 3) {
        if(i + 1 >= nums.size() || nums[i] != nums[i + 1]) 
            return nums[i];
    }
    return nums.back();
}

/*
 Bit Manipulation (Most Optimized):
 - Maintain two variables (onces and twos)
 - onces → bits which have appeared once
 - twos → bits which have appeared twice
 - On the third occurrence, the bit is removed from both

 Time Complexity:  O(n)   // single pass
 Space Complexity: O(1)   // constant variables
*/
int single_number_II_optimized_2(vector<int> &nums) {
    int onces = 0, twos = 0;
    for(int i = 0; i < nums.size(); i++) {
        onces = (onces ^ nums[i]) & (~twos);
        twos = (twos ^ nums[i]) & (~onces);
    }
    return onces;
}

int main() {
    vector<int> nums = {2, 2, 3, 2};
    cout << single_number_II_brute(nums) << endl;
    cout << single_numberr_II_better(nums) << endl;
    cout << single_number_II_optimized(nums) << endl;
    cout << single_number_II_optimized_2(nums) << endl;
}
