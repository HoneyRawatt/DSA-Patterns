#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
int findMaxConsicutive(vector<int>&arr,int n){
    int max1=0,cnt=0;
    for(int i=0;i<n;i++){
    if(arr[i]==1){
        cnt++;
        max1=max(max1,cnt);
    }else cnt=0;
    }
    return max1;
}
int main() {
    int n;
    cin >> n;
    vector<int> arr(n);
    cout << "Enter the elements: ";
    for (int i = 0; i < n; ++i) {
        cin >> arr[i];
    }
    cout<<"Max 1's: "<<findMaxConsicutive(arr,n);


    return 0;
}

  