#include<iostream>
#include<vector>
#include<algorithm>
#include<map>
using namespace std;
int longestSubarrayWithSumK_2pointer(vector<int>&a,long long k){
int left=0,right=0,maxlen=0,n=a.size();
long long sum=0;
while(right<n){
    sum+=a[right];
    while(left<=right && sum>k){
        sum-=a[left];
        left++;
    }
    if(sum==k){
        maxlen=max(maxlen,right-left+1);
    }
    right++;
}
return maxlen;
}
int longestSubarrayWithSumK_hashing(vector<int>&a,long long k){
    map<long long,int>preSummap;
    long long sum=0;
    int maxlen=0;
    for(int i=0;i<a.size();i++){
        sum+=a[i];
        if(sum==k){
            maxlen=max(maxlen,i+1);
        }
        int rem=sum-k;
        if(preSummap.find(rem)!=preSummap.end()){
            int len= i-preSummap[rem];
            maxlen=max(maxlen,len);
            
        }
        if(preSummap.find(sum)==preSummap.end()) preSummap[sum]=i;
    }
    return maxlen;
}
int longestSubarrayWithSumK_brute(vector<int>&a,long long k){
    int n=a.size(),len=0;
    for(int i=0;i<n;i++){
     long long sum=0;
     for(int j=i;j<n;j++){
        sum+=a[j];
        if(sum==k) len=max(len,j-i+1);
     }
    }
    return len;
}

int main() {
    int n;
    long long k;
    cout << "Enter array size: ";
    cin >> n;
    vector<int> arr(n);
    cout << "Enter the elements: ";
    for (int i = 0; i < n; ++i) {
        cin >> arr[i];
    }
    cout << "Enter target sum k: ";
    cin >> k;

    cout << "Longest subarray with sum " << k << ":\n";
    cout << "Brute Force: " << longestSubarrayWithSumK_brute(arr, k) << endl;
    cout << "Hashing: " << longestSubarrayWithSumK_hashing(arr, k) << endl;
    cout << "Two-pointer: " << longestSubarrayWithSumK_2pointer(arr, k) << " (Only for non-negative numbers)" << endl;

    return 0;
}