#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
vector<int> rightrotate_k2(vector<int>&a,int n,int k){
    reverse(a.begin(),a.begin()+(n-k));
    reverse(a.begin()+(n-k),a.begin()+n);
    reverse(a.begin(),a.begin()+n);
    return a;
}
vector<int> rightrotate_k(vector<int>&a,int n,int k){
    vector<int>temp;
    for (int i = n - k; i < n; i++) {
    temp.push_back(a[i]); 
    }
    for(int i=n-k-1;i>=0;i--){
        a[i+k]=a[i];
    }
    for(int i=0;i<k;i++){
        a[i]=temp[i];
    }
    return a;
}
int main(){
    int n,k;
    cout<<"Enter the size of the array: "<<endl;
    cin>>n;
    cout<<"Enter the value of k: "<<endl;
    cin>>k;
    vector<int>arr(n);
    cout<<"Enter the elements: ";
    for(int i=0;i<n;++i){
        cin>>arr[i];
    }
    k=k%n;
    arr=rightrotate_k2(arr,n,k);
    for(auto it:arr) cout<<it<<" ";

    return 0;
}