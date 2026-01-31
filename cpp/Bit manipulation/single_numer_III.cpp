#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
using namespace std;

/*
 Brute Force Approach:
 - Count frequency of each number using a map
 - The numbers that appear exactly once are the answer

 Time Complexity:  O(n log n)   // map insert/search is log n
 Space Complexity: O(n)         // map stores counts for all numbers
*/
vector<int> singleNumber_III_brute(vector<int>& nums) {
    map<int,int> mpp;
    for(int i = 0; i < nums.size(); i++) 
        mpp[nums[i]]++;

    vector<int> ans;
    for(auto it : mpp) {
        if(it.second == 1) 
            ans.push_back(it.first);
    }
    return ans;
}

/*
 Optimized Bit Manipulation Approach:
 - XOR of all numbers = xor_val = num1 ^ num2 (two unique numbers)
 - Find rightmost set bit in xor_val (bit where num1 and num2 differ)
 - Partition numbers into two groups based on that bit
 - XOR each group to get num1 and num2

 Time Complexity:  O(n)   // single pass
 Space Complexity: O(1)   // constant extra space
*/
vector<int> singleNumber_III_optimized(vector<int>& nums) {
    long xorr = 0;
    for(int num : nums) 
        xorr ^= num;

    // Find the rightmost set bit in xorr
    long rightmost = xorr & -xorr;  // cleaner than (xorr & (xorr - 1)) ^ xorr

    int b1 = 0, b2 = 0;
    for(int num : nums) {
        if(num & rightmost) 
            b1 ^= num;  // group 1 
        else 
            b2 ^= num;  // group 2
    }
    return {b1, b2};
}

int main() {
    vector<int> nums = {1, 2, 1, 3, 2, 5};

    vector<int> brute_ans = singleNumber_III_brute(nums);
    cout << "Brute: " << brute_ans[0] << ", " << brute_ans[1] << endl;

    vector<int> opt_ans = singleNumber_III_optimized(nums);
    cout << "Optimized: " << opt_ans[0] << ", " << opt_ans[1] << endl;
}
