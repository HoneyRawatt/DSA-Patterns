#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
int linearsearch(vector<int>&arr,int k){
    for(int i=0;i<arr.size();i++){
        if(arr[i]==k) return i+1;
    }
    return -1;
}
int main(){
    int n,k;
    cin>>n;
    vector<int>arr(n);
    cout<<"Enter the key: ";
    cin>>k;
    cout<<"Enter the elements: ";
    for(int i=0;i<n;++i){
        cin>>arr[i];
    }
    cout<<"Index: "<<linearsearch(arr,k);

    return 0;
}