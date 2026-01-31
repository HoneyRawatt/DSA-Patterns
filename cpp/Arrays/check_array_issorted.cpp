#include<iostream>
#include<vector>
using namespace std;
bool arrayissorted(vector<int>&a,int n){
    for(int i=0;i<n-1;i++){
        if(a[i+1]>=a[i]){
        continue;
        }else{
            return false;
        }
    }
    return true;
}
int main(){
    int n;
    cin>>n;
    vector<int>arr(n);
    cout<<"Enter the elements: ";
    for(int i=0;i<n;++i){
        cin>>arr[i];
    }
    cout<<arrayissorted(arr,n);
    return 0;
}