#include<bits/stdc++.h>

using namespace std;

vector<int> maxSubarraySum_kadanes_algo(vector<int>arr,int n){
    long long sum=0,maxi=LONG_MIN;
    int start=-1,ansstart=-1,ansend=-1;
    for(int i=0;i<n;i++){
        if(sum==0) start=i;
        sum+=arr[i];
        if(sum>maxi){
            maxi=sum;
            ansstart=start;
            ansend=i;
        }
        if(sum<0){
            sum=0;
        }
    }
    return {ansstart,ansend};
}

long long maxSubarraySum_brute(vector<int>arr,int n){
    long long maxi=LONG_MIN;
    for(int i=0;i<n;i++){
        long long sum=0;
        for(int j=i;j<n;j++){
            sum+=arr[j];
            maxi=max(sum,maxi);
        }
    }
    return maxi;
} 

int main() {
    vector<int> arr = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
    int n = arr.size();

    vector<int> kadane_res = maxSubarraySum_kadanes_algo(arr, n);
    cout << "Kadane's Algorithm: Max Subarray is from index "
         << kadane_res[0] << " to " << kadane_res[1] << endl;

    long long brute_res = maxSubarraySum_brute(arr, n);
    cout << "Brute-force: Maximum Subarray Sum = " << brute_res << endl;

    return 0;
}

