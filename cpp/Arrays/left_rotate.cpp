#include<iostream>
#include<vector>
using namespace std;
vector<int> leftrotate(vector<int>&a,int n){
    int temp=a[0];
    for(int i=1;i<n;i++){
        a[i-1]=a[i];
    }
    a[n-1]=temp;
    return a;
}
int main(){
    int n;
    cin>>n;
    vector<int>arr(n);
    cout<<"Enter the elements: ";
    for(int i=0;i<n;++i){
        cin>>arr[i];
    }
    arr=leftrotate(arr,n);
    for(auto it:arr) cout<<it<<" ";

    return 0;
}