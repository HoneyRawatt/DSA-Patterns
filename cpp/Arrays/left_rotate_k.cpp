#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
vector<int> leftrotate_k2(vector<int>&a,int n,int k){
    reverse(a.begin(),a.begin()+k);
    reverse(a.begin()+k,a.begin()+n);
    reverse(a.begin(),a.end());
    return a;
}
vector<int> leftrotate_k(vector<int>&a,int n,int k){
    vector<int>temp;
    for(int i=0;i<k;i++){
        temp.push_back(a[i]);
    }
    for(int i=k;i<n;i++){
        a[i-k]=a[i];
    }
    for(int i=n-k;i<n;i++){
        a[i]=temp[i-(n-k)];
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
    arr=leftrotate_k2(arr,n,k);
    for(auto it:arr) cout<<it<<" ";

    return 0;
}